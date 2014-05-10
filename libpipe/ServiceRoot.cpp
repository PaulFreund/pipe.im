//======================================================================================================================

#include "CommonHeader.h"
#include "ServiceRoot.h"
#include "LibPipe.h"

using namespace std;
using namespace Poco;

//======================================================================================================================

ServiceRoot::ServiceRoot(const tstring& address, const tstring& path, PipeObjectPtr settings) 
	: PipeServiceNodeBase(_T("pipe"), _T("Pipe root node"), address, path, settings) 
	, _config(newObject())
{
	if(settings->count(_T("service_types"))) {
		auto& serviceTypes = settings->operator[](_T("service_types")).array_items();
		for(auto& type : serviceTypes) {
			auto& typeDefinition = type.object_items();
			_providerTypes.push_back(typeDefinition[_T("type")].string_value());
		}
	}
	else {
		pushOutgoing(_T(""), _T("error"), _T("Missing configuration of available service types"));
	}

	// Init baseic child serices
	initScripts();
	initServices();

	File pathObj(path);
	
	// Create directory if it does not exist
	if(!pathObj.exists()) {
		try {
			pathObj.createDirectories();
		}
		catch(...) {}
	}
	
	// Load configuration of display error
	if(!pathObj.exists() || !pathObj.isDirectory() || !pathObj.canRead() || !pathObj.canWrite()) {
		pushOutgoing(_T(""), _T("error"), _T("Instance path location is invalid. Config can not be loaded or saved"));
	}
	else {
		loadConfig();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void ServiceRoot::initScripts() {
	_serviceScripts = make_shared<PipeServiceNodeBase>(_T("scripts"), _T("Management of scripts"), _address + TokenAddressSeparator + _T("scripts"), _path, _settings);
	addChild(_serviceScripts);

	enablePreSendHook([&](PipeArrayPtr messages) { 
		// TODO
	});

	enablePostReceiveHook([&](PipeArrayPtr messages) {
		// TODO
	});
}

//----------------------------------------------------------------------------------------------------------------------

void ServiceRoot::initServices() {
	tstring addressServices = _address + TokenAddressSeparator + _T("services");
	_serviceServices = make_shared<PipeServiceNodeBase>(_T("services"), _T("Management of services"), addressServices, _path, _settings);
	addChild(_serviceServices);

	tstring addressServicesProvider = addressServices + TokenAddressSeparator + _T("providers");
	_serviceServicesProvider = make_shared<PipeServiceNodeBase>(_T("service_providers"), _T("Service provider types"), addressServicesProvider, _path, _settings);
	_serviceServices->addChild(_serviceServicesProvider);

	// Add providers
	for(auto& extension : LibPipe::Extensions) {
		auto& extensionProviders = extension->serviceTypes();
		for(auto& type : *extensionProviders) {
			auto& providerType = type.object_items();
			tstring typeName = providerType[_T("type")].string_value();
			tstring typeDescription = providerType[_T("description")].string_value();
			// TODO: Extract and use settings schema

			if(find(begin(_providerTypes), end(_providerTypes), providerType[_T("type")].string_value()) == end(_providerTypes))
				continue;

			tstring addressProvider = addressServicesProvider + TokenAddressSeparator + typeName;
			auto provider = make_shared<PipeServiceNodeBase>(typeName, typeDescription, addressProvider, _path, _settings);
			_serviceServicesProvider->addChild(provider);

			// TODO: Add commands and messages
		}
	}

	// TODO: Add commands and messages

	tstring addressServicesInstances = addressServices + TokenAddressSeparator + _T("instances");
	_serviceServicesInstances = make_shared<PipeServiceNodeBase>(_T("service_instances"), _T("Service instances"), addressServicesInstances, _path, _settings);
	_serviceServices->addChild(_serviceServicesInstances);

	// TODO: Add commands and messages
}

//----------------------------------------------------------------------------------------------------------------------

void ServiceRoot::loadConfig() {
	if(!readConfig())
		return;

	if(_config->empty())
		return;

	// Config format
	/*
	
		{
			"instances": [
				{
					"type": "...",
					"settings": {
						...
					}
			]
		}

	*/
}

//----------------------------------------------------------------------------------------------------------------------

bool ServiceRoot::readConfig() {
	tstring path = configPath();
	File configFile(path);

	if(!configFile.exists() || !configFile.canRead())
		return false;

	try {
		ifstream configReader(path);
		tstring configData((istreambuf_iterator<TCHAR>(configReader)), istreambuf_iterator<TCHAR>());
		
		tstring error;
		PipeJson configJson = PipeJson::parse(configData, error);
		if(!error.empty()) {
			pushOutgoing(_T(""), _T("error"), _T("Can not read pipe config file: ") + error);
			return false;
		}

		_config = make_shared<PipeObject>(configJson.object_items());
	}
	catch(...) { return false; }

	return true;
}

//----------------------------------------------------------------------------------------------------------------------

void ServiceRoot::writeConfig() {
	tstring path = configPath();
	File configFile(path);

	if(!configFile.exists()) {
		try {
			configFile.createFile();
		}
		catch(...) {
			pushOutgoing(_T(""), _T("error"), _T("Can not create pipe config file"));
		}
	}

	if(!configFile.exists() || !configFile.canWrite()) {
		pushOutgoing(_T(""), _T("error"), _T("Can not save pipe config, file is not writable"));
		return;
	}

	try {
		ofstream configWriter(path);
		configWriter << dumpObject(_config);
	}
	catch(...) { 
		pushOutgoing(_T(""), _T("error"), _T("There was an error writing the pipe config file"));
		return; 
	}
}

//----------------------------------------------------------------------------------------------------------------------

tstring ServiceRoot::configPath() {
	Path configFilePath;
	configFilePath.parseDirectory(_path);
	configFilePath.setFileName(_address);
	configFilePath.setExtension(_T("json"));

	File configFile(configFilePath.toString());

	return configFile.path();
}

//----------------------------------------------------------------------------------------------------------------------

ServiceRoot::~ServiceRoot() {
}

//======================================================================================================================
