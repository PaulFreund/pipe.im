//======================================================================================================================

#include "CommonHeader.h"
#include "InstanceManager.h"
#include "Account.h"

#include <thread>

#include <Poco/File.h>
#include <Poco/Path.h>
#include <Poco/Process.h>
#include <Poco/DirectoryIterator.h>

using namespace std;
using namespace Poco;
using namespace Poco::Util;
using namespace Poco::Net;

//======================================================================================================================

InstanceConnection::InstanceConnection(const StreamSocket& socket) : TCPServerConnection(socket) {}

//----------------------------------------------------------------------------------------------------------------------

void InstanceConnection::run() {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());
	tstring clientName = _T("");
	shared_ptr<InstanceClient> client = shared_ptr<InstanceClient>(nullptr);
	bool associated = false;

	try {
		StreamSocket& ss = socket();
		ss.setBlocking(false);

		if(pApp->_debug) { pApp->logger().information(tstring(_T("[InstanceConnection::run] InstanceConnection connection established"))); }

		vector<tstring> incoming;
		vector<tstring> outgoing;

		const int bufferSize = 10240;
		ss.setReceiveBufferSize(bufferSize);
		ubyte buffer[bufferSize];

		int flags = 0;
		int bytesRead = 0;

		vector<ubyte> receivedBuffer;
		do {
			this_thread::sleep_for(chrono::milliseconds(10)); // TODO: DEBUG SETTING

			try {
				bytesRead = ss.receiveBytes(buffer, sizeof(buffer), flags);
				if(bytesRead > 0) {
					receivedBuffer.insert(end(receivedBuffer), reinterpret_cast<ubyte*>(&buffer), reinterpret_cast<ubyte*>(&buffer[bytesRead]));
					while(!receivedBuffer.empty()) {
						uint32_t messageSize = *reinterpret_cast<uint32_t*>(receivedBuffer.data());
						uint32_t packetSize = messageSize + sizeof(uint32_t);
						if(receivedBuffer.size() < packetSize) { break; }

						incoming.push_back(tstring(receivedBuffer.begin() + sizeof(uint32_t), receivedBuffer.begin() + packetSize));
						receivedBuffer.erase(begin(receivedBuffer), begin(receivedBuffer) + packetSize);
					}
				}
			}
			catch(TimeoutException& /*e*/) {} // Not very good but works for the moment

			// Send to pipe
			if(incoming.size() > 0) {
				for(auto& message : incoming) {
					if(message.empty()) { continue; }
					if(pApp->_debug) { pApp->logger().information(tstring(_T("[InstanceConnection::run] InstanceConnection Message received: ")) + message); }
					try {
						if(!associated) {
							PipeObjectPtr messageObj = parseObject(message);
							if((*messageObj)[TokenMessageAddress].string_value() == _T("pipe_host")) {
								if((*messageObj)[TokenMessageMessage].string_value() == _T("account")) {
									clientName = (*messageObj)[TokenMessageData].string_value();
									
									// Register with InstanceManager
									pApp->_instanceManager->addInstance(clientName, this);

									// This is the gateway
									if(clientName == GatewayPipe::GatewayPipeAccountName) {
										client = pApp->_gatewayPipe;
									}
									// This is an actual account
									else {
										client = pApp->_accountManager->account(clientName);
									}

									if(client.get() != nullptr) { client->setConnection(this); }
								}
							}
							else {
								throw new exception(_T("InstanceConnection did not authenticate"));
							}
						}
						// Add message to instance incoming queue
						else if(client.get() != nullptr) {
							client->addIncoming(message);
						}
					}
					catch(...) {}
				}

				incoming.clear();
			}

			// Get outgoing messages from instance
			if(client.get() != nullptr) {
				auto newOutgoing = client->getOutgoing(); // TODO: Inefficeint
				outgoing.insert(begin(outgoing), begin(newOutgoing), end(newOutgoing));
			}

			// Send to server
			if(outgoing.size() > 0) {
				for(auto& message : outgoing) {
					uint32_t messageSize = static_cast<uint32_t>(message.length());
					ss.sendBytes(&messageSize, sizeof(uint32_t));
					ss.sendBytes(message.data(), message.length());
					pApp->logger().information(tstring(_T("[InstanceConnection::run] Message sent: ")) + message);
				}
				outgoing.clear();
			}
		}
		while(bytesRead != 0);	
	}
	catch(exception e) {
		pApp->logger().warning(tstring(_T("[InstanceConnection::run] Exception: ")) + e.what());
	}

	if(client.get() != nullptr) {	client->setConnection(nullptr); }
	pApp->_instanceManager->removeInstance(clientName);
}

//======================================================================================================================

InstanceManager::InstanceManager() {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	// InstanceConnection management server
	_socket = make_shared<ServerSocket>(SocketAddress(pApp->_instanceAddress, pApp->_instancePort));

	TCPServerParams* pParams = new TCPServerParams();
	pParams->setMaxThreads(1000);

	_server = make_shared<TCPServer>(new TCPServerConnectionFactoryImpl<InstanceConnection>(), *_socket, pParams);
	_server->start();
}

//----------------------------------------------------------------------------------------------------------------------

InstanceManager::~InstanceManager() {
	_instances.clear();
	_server->stop();
}

//----------------------------------------------------------------------------------------------------------------------

InstanceConnection* InstanceManager::instance(const tstring& name) {
	if(_instances.count(name) == 1)
		return _instances[name];
	
	return nullptr;
}

//----------------------------------------------------------------------------------------------------------------------

void InstanceManager::addInstance(const tstring& name, InstanceConnection* instance) {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	if(_instances.count(name) != 0) {
		pApp->logger().warning(tstring(_T("[InstanceManager::addInstance] InstanceConnection already exists: ")) + name);
		return;
	}

	_instances[name] = instance;
}

//----------------------------------------------------------------------------------------------------------------------

void InstanceManager::removeInstance(const tstring& name) {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	if(_instances.count(name) == 0) {
		pApp->logger().warning(tstring(_T("[InstanceManager::removeInstance] InstanceConnection could not be removed: ")) + name);
		return;
	}

	_instances.erase(name);
}

//----------------------------------------------------------------------------------------------------------------------

void InstanceManager::spawnInstance(const tstring& name, const tstring& path) {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	Process::Args args;
	args.push_back(_T("--account=") + name);
	args.push_back(_T("--address=") + pApp->_instanceAddress);
	args.push_back(_T("--port=") + to_tstring(pApp->_instancePort));
	args.push_back(_T("--extdir=") + pApp->_extdir);
	args.push_back(_T("--userdir=") + path);

	if(pApp->_debug)
		args.push_back(_T("--debug"));

	//args.push_back(_T("--includedServices=")); // TODO
	//args.push_back(_T("--excludedServices="));

	Process::launch(pApp->_instanceCommand, args);
}

//======================================================================================================================
