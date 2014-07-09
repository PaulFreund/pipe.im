//======================================================================================================================

#include "CommonHeader.h"
#include "UserInstanceManager.h"

#include <thread>

#include <Poco/File.h>
#include <Poco/Path.h>
#include <Poco/DirectoryIterator.h>

using namespace std;
using namespace Poco;
using namespace Poco::Util;
using namespace Poco::Net;

//======================================================================================================================

const tstring UserInstanceManager::UsersFolderName = _T("users");

//======================================================================================================================

UserInstanceConnection::UserInstanceConnection(const StreamSocket& socket) 
	: TCPServerConnection(socket)
{

}

//----------------------------------------------------------------------------------------------------------------------

void UserInstanceConnection::run() {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());
	shared_ptr<UserInstance> instance = shared_ptr<UserInstance>(nullptr);

	try {
		StreamSocket& ss = socket();
		ss.setBlocking(false);

		if(pApp->_debug) { pApp->logger().information(tstring(_T("[UserInstanceConnection::run] Instance connection established"))); }

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
					if(pApp->_debug) { pApp->logger().information(tstring(_T("[UserInstanceConnection::run] Instance Message received: ")) + message); }
					try {
						PipeObjectPtr messageObj = parseObject(message);
						if((*messageObj)[TokenMessageAddress].string_value() == _T("pipe_host")) {
							if((*messageObj)[TokenMessageMessage].string_value() == _T("account")) {
								tstring account = (*messageObj)[TokenMessageData].string_value();
								instance = pApp->_instanceManager->instance(account);
								if(instance.get() != nullptr) { instance->setConnection(this); }
							}
						}
						// Add message to instance incoming queue
						else if(instance.get() != nullptr) {
							instance->addIncoming(message);
						}
					}
					catch(...) {}
				}

				incoming.clear();
			}

			// Get outgoing messages from instance
			if(instance.get() != nullptr) {
				auto newOutgoing = instance->getOutgoing(); // TODO: Inefficeint
				outgoing.insert(begin(outgoing), begin(newOutgoing), end(newOutgoing));
			}

			// Send to server
			if(outgoing.size() > 0) {
				for(auto& message : outgoing) {
					uint32_t messageSize = static_cast<uint32_t>(message.length());
					ss.sendBytes(&messageSize, sizeof(uint32_t));
					ss.sendBytes(message.data(), message.length());
					pApp->logger().information(tstring(_T("[UserInstanceConnection::run] Message sent: ")) + message);
				}
				outgoing.clear();
			}
		}
		while(bytesRead != 0);	
	}
	catch(exception e) {
		pApp->logger().warning(tstring(_T("[UserInstanceConnection::run] Exception: ")) + e.what());
	}

	if(instance.get() != nullptr) {	instance->setConnection(nullptr); }
}

//======================================================================================================================

UserInstanceManager::UserInstanceManager() {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	// Instance management server
	_socket = make_shared<ServerSocket>(SocketAddress(pApp->_instanceAddress, pApp->_instancePort));

	TCPServerParams* pParams = new TCPServerParams();
	pParams->setMaxThreads(1000);

	_server = make_shared<TCPServer>(new TCPServerConnectionFactoryImpl<UserInstanceConnection>(), *_socket, pParams);
	_server->start();

	if(prepareUsersDataPath())
		loadUsers();
}

//----------------------------------------------------------------------------------------------------------------------

UserInstanceManager::~UserInstanceManager() {
	_instances.clear();
	_server->stop();
}

//----------------------------------------------------------------------------------------------------------------------

shared_ptr<UserInstance> UserInstanceManager::instance(const tstring& account) {
	if(_instances.count(account) == 1)
		return _instances[account];
	
	return shared_ptr<UserInstance>(nullptr);
}

//----------------------------------------------------------------------------------------------------------------------

void UserInstanceManager::loadUsers() {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	// Iterate over user directorys
	for(DirectoryIterator it(_usersDataPath), itEnd; it != itEnd; ++it) {
		File userDirectory(it->path());
		if(!userDirectory.exists() || !userDirectory.canRead() || !userDirectory.isDirectory()) { continue; }

		// Check if user file exist
		File userFile(Path(Path(userDirectory.path()), UserInstance::UserFileName));
		if(!userFile.exists() || !userFile.canRead() || !userFile.isFile()) { continue; }

		Path userDirectoryPath(userDirectory.path());
		tstring username = userDirectoryPath.getFileName();
		_instances[username] = make_shared<UserInstance>(userDirectory.path());
	}
}

//----------------------------------------------------------------------------------------------------------------------

void UserInstanceManager::createUser(const tstring& account, const tstring& password) {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	File userDirectory(_usersDataPath + Path::separator() + account);
	if(_instances.count(account) != 0 || userDirectory.exists()) {
		pApp->logger().warning(tstring(_T("[UserInstanceManager::createUser] User already exists")));
		return;
	}

	userDirectory.createDirectory();
	if(!userDirectory.exists() || !userDirectory.canRead() || !userDirectory.isDirectory()) { return; }

	_instances[account] = make_shared<UserInstance>(userDirectory.path(), account, password);
}

//----------------------------------------------------------------------------------------------------------------------

void UserInstanceManager::deleteUser(const tstring& account) {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	if(_instances.count(account) == 0) {
		pApp->logger().warning(tstring(_T("[UserInstanceManager::deleteUser] User could not be deleted")));
		return;
	}

	_instances.erase(account);
	File userDirectory(_usersDataPath + Path::separator() + account);
	userDirectory.remove(true);
}

//----------------------------------------------------------------------------------------------------------------------

bool UserInstanceManager::prepareUsersDataPath() {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	// Prepare data directory
	File dataPath(pApp->_datadir);
	if(!dataPath.exists()) { dataPath.createDirectory(); }

	if(!dataPath.exists() || !dataPath.canRead() || !dataPath.isDirectory()) {
		pApp->logger().warning(tstring(_T("[UserInstanceManager::prepareUsersDataPath] Could not open or create data folder")));
		return false;
	}

	// Prepare user data path
	tstring userDataDir = pApp->_datadir;
	if(userDataDir[userDataDir.size() - 1] != Path::separator()) { userDataDir += Path::separator(); }
	userDataDir += UserInstanceManager::UsersFolderName;

	File userDataPath(userDataDir);
	if(!userDataPath.exists()) { userDataPath.createDirectory(); }

	if(!userDataPath.exists() || !userDataPath.canRead() || !userDataPath.isDirectory()) {
		pApp->logger().warning(tstring(_T("[UserInstanceManager::prepareUsersDataPath] Could not open or create data folder")));
		return false;
	}

	_usersDataPath = userDataPath.path();
	return true;
}

//======================================================================================================================
