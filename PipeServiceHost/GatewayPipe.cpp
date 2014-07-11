//======================================================================================================================

#include "CommonHeader.h"
#include "GatewayPipe.h"

//======================================================================================================================

const tstring GatewayPipe::GatewayPipeFolderName = _T("gateway_pipe");
const tstring GatewayPipe::GatewayPipeAccountName = _T("host_gateway");

//======================================================================================================================

GatewayPipe::GatewayPipe() {
	// TODO: Change to be overall path + foldername
	InstanceManager::spawnInstance(GatewayPipe::GatewayPipeAccountName, GatewayPipe::GatewayPipeFolderName);
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
	// TODO
}

//======================================================================================================================