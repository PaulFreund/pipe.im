//======================================================================================================================

#include "CommonHeader.h"
#include "GatewayPipe.h"

using namespace std;
using namespace Poco;
using namespace Poco::Util;

//======================================================================================================================

const tstring GatewayPipe::GatewayPipeFolderName = _T("gateway_pipe");
const tstring GatewayPipe::GatewayPipeAccountName = _T("host_gateway");

//======================================================================================================================

GatewayPipe::GatewayPipe() 
	: _connection(nullptr) 
{
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());
	InstanceManager::spawnInstance(GatewayPipe::GatewayPipeAccountName, pApp->_datadir + Path::separator() + GatewayPipe::GatewayPipeFolderName);
}

//----------------------------------------------------------------------------------------------------------------------

GatewayPipe::~GatewayPipe() {}

//----------------------------------------------------------------------------------------------------------------------

void GatewayPipe::addIncoming(const tstring& message) {
	if(_sessions.empty()) {
		_mutexQueue.lock();
		_incoming.push_back(message);
		_mutexQueue.unlock();
	}
	else {
		for(auto& session : _sessions) {
			session.second->accountIncomingAdd(message);
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------

std::vector<tstring> GatewayPipe::getOutgoing() {
	_mutexQueue.lock();
	vector<tstring> result = _outgoing; // TODO: Inefficient
	_outgoing.clear();
	_mutexQueue.unlock();
	return result;
}

//----------------------------------------------------------------------------------------------------------------------

void GatewayPipe::setConnection(InstanceConnection* connection) {
	_connection = connection;
}

//----------------------------------------------------------------------------------------------------------------------

void GatewayPipe::addOutgoing(const tstring& message) {
	_mutexQueue.lock();
	_outgoing.push_back(message);
	_mutexQueue.unlock();
}

//----------------------------------------------------------------------------------------------------------------------

void GatewayPipe::addSession(tstring id, InstanceSession* session) {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	if(_sessions.count(id) != 0) {
		pApp->logger().warning(tstring(_T("[GatewayPipe::addSession] InstanceSession already exists: ")) + id);
		return;
	}

	_sessions[id] = session;
}

//----------------------------------------------------------------------------------------------------------------------

void GatewayPipe::removeSession(tstring id) {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	if(_sessions.count(id) == 0) {
		pApp->logger().warning(tstring(_T("[GatewayPipe::removeSession] InstanceSession could not be removed: ")) + id);
		return;
	}

	_sessions.erase(id);
}

//======================================================================================================================
