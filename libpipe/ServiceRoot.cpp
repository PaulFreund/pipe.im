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
tstring ServiceRoot::createService(const tstring& type, const tstring& name, PipeObject& settings) {
	// TODO
	return _T("");
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
	_serviceServices = make_shared<PipeServiceNodeBase>(_T("services"), _T("Management of services"), addressServices, _path, newObject());
	addChild(_serviceServices);

	tstring addressServicesProviders = addressServices + TokenAddressSeparator + _T("providers");
	_serviceServicesProviders = make_shared<PipeServiceNodeBase>(_T("services_providers"), _T("Service provider types"), addressServicesProviders, _path, newObject());
	_serviceServices->addChild(_serviceServicesProviders);

	// Add providers
	for(auto& extension : LibPipe::Extensions) {
		auto extensionProviders = extension->serviceTypes();
		for(auto& type : *extensionProviders) {
			auto& providerType = type.object_items();
			tstring typeName = providerType[_T("type")].string_value();

			if(find(begin(_providerTypes), end(_providerTypes), providerType[_T("type")].string_value()) == end(_providerTypes))
				continue;

			tstring typeDescription = providerType[_T("description")].string_value();
			auto& typeSettingsSchema = providerType[_T("settings_schema")].object_items();

			tstring addressProvider = addressServicesProviders + TokenAddressSeparator + typeName;

			auto providerSettings = newObject();
			providerSettings->operator[](_T("type")).string_value() = typeName;
			auto provider = make_shared<PipeServiceNodeBase>(_T("provider_") + typeName, typeDescription, addressProvider, _path, providerSettings);
			_serviceServicesProviders->addChild(provider);

			// Create command
			{
				auto cmdCreate = newObject();
				auto& cmdCreateData = schemaAddObject(*cmdCreate, TokenMessageData, _T("Data to create a new service"), false);
				schemaAddValue(cmdCreateData, _T("name"), SchemaValueTypeString, _T("Name of the new service"));
				schemaAddObject(cmdCreateData, _T("settings"), _T("Settings for the new service"), false) = typeSettingsSchema;
				
				provider->addCommand(_T("create"), _T("Create a service instance"), cmdCreate, [&, typeName](PipeObject& message) {
					auto ref = message[_T("ref")].string_value();
					if(!message.count(_T("data")) || !message[_T("data")].is_object()) {
						pushOutgoing(ref, _T("error"), _T("Missing command data"));
						return;
					}

					auto& msgData = message[_T("data")].object_items();
					if(!msgData.count(_T("name")) || !msgData[_T("name")].is_string() || !msgData.count(_T("settings")) || !msgData[_T("settings")].is_object()) {
						pushOutgoing(ref, _T("error"), _T("Invalid create request"));
						return;
					}
					
					tstring errorMsg = createService(typeName, msgData[_T("name")].string_value(), msgData[_T("settings")].object_items());
					if(!errorMsg.empty())
						pushOutgoing(ref, _T("error"), _T("Error creating service: ") + errorMsg);
				});
			}
			// Response
			{
				PipeObjectPtr schemaMessageCreate = newObject();
				schemaAddValue(*schemaMessageCreate, TokenMessageData, SchemaValueTypeString, _T("Name of the created service"));
				provider->addMessageType(_T("created"), _T("Service creation notification"), schemaMessageCreate);
			}
		}
	}

	tstring addressServicesInstances = addressServices + TokenAddressSeparator + _T("instances");
	_serviceServicesInstances = make_shared<PipeServiceNodeBase>(_T("services_instances"), _T("Service instances"), addressServicesInstances, _path, newObject());
	_serviceServices->addChild(_serviceServicesInstances);
}

//----------------------------------------------------------------------------------------------------------------------

void ServiceRoot::loadConfig() {
	if(!readConfig())
		return;

	if(!_config->count(_T("services")))
	   return;

	auto& services = _config->operator[](_T("services")).array_items();
	for(auto& service : services) {
		auto& serviceObject = service.object_items();
		tstring name = serviceObject[_T("name")].string_value();
		tstring type = serviceObject[_T("type")].string_value();
		auto& settings = serviceObject[_T("settings")].object_items();

		if(find(begin(_providerTypes), end(_providerTypes), type) == end(_providerTypes)) {
			pushOutgoing(_T(""), _T("error"), _T("Could not load service \"") + name + _T("\", unsupported type \"") + type + _T("\""));
		}

		tstring errorMsg = createService(type, name, settings);
		if(!errorMsg.empty())
			pushOutgoing(_T(""), _T("error"), _T("Error creating service: ") + errorMsg);
	}
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
