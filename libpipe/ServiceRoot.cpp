//======================================================================================================================

#include "CommonHeader.h"
#include "ServiceRoot.h"
#include "ServiceScripts.h"

using namespace std;

//======================================================================================================================

ServiceRoot::ServiceRoot(const tstring& address, const tstring& path, PipeObjectPtr settings) : PipeServiceNodeBase(_T("pipe"), _T("Pipe root node"), address, path, settings) {
	// TODO: Load configuration from config in path
	
	initScripts();
	initServices();
}

//----------------------------------------------------------------------------------------------------------------------
void ServiceRoot::initScripts() {
	auto serviceScripts = make_shared<ServiceScripts>(_address + TokenAddressSeparator + _T("scripts"), _path, _settings);
	addChild(serviceScripts);

	enablePreSendHook([&](PipeArrayPtr messages) { serviceScripts->processPreSend(messages); });
	enablePostReceiveHook([&](PipeArrayPtr messages) { serviceScripts->processPostReceive(messages); });
}

//----------------------------------------------------------------------------------------------------------------------

void ServiceRoot::initServices() {
	tstring addressServices = _address + TokenAddressSeparator + _T("services");
	auto serviceServices = make_shared<PipeServiceNodeBase>(_T("services"), _T("Manager of services"), addressServices, _path, _settings);
	addChild(serviceServices);

	tstring addressServicesProvider = addressServices + TokenAddressSeparator + _T("provider");
	auto serviceServicesProvider = make_shared<PipeServiceNodeBase>(_T("service_provider"), _T("Service provider types"), addressServicesProvider, _path, _settings);
	serviceServices->addChild(serviceServicesProvider);

	tstring addressServicesInstances = addressServices + TokenAddressSeparator + _T("instances");
	auto serviceServicesInstances = make_shared<PipeServiceNodeBase>(_T("service_instances"), _T("Service instances"), addressServicesInstances, _path, _settings);
	serviceServices->addChild(serviceServicesInstances);
}

//----------------------------------------------------------------------------------------------------------------------

ServiceRoot::~ServiceRoot() {
}

//======================================================================================================================
