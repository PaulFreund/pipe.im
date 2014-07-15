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

GatewayPipe::GatewayPipe() {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());
	InstanceManager::spawnInstance(GatewayPipe::GatewayPipeAccountName, pApp->_datadir + Path::separator() + GatewayPipe::GatewayPipeFolderName);
}

//----------------------------------------------------------------------------------------------------------------------

GatewayPipe::~GatewayPipe() {}

//----------------------------------------------------------------------------------------------------------------------

void GatewayPipe::addIncoming(const tstring& message) {
	// TODO
}

//----------------------------------------------------------------------------------------------------------------------

std::vector<tstring> GatewayPipe::getOutgoing() {
	// TODO
	return {};
}

//----------------------------------------------------------------------------------------------------------------------

void GatewayPipe::setConnection(InstanceConnection* connection) {
	int j = 0;
	// TODO
}

//======================================================================================================================
