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
	auto children = nodeChildren(_T("pipe"));
	for(auto& child : *children) {
		auto childParts = texplode(child.string_value(), TokenAddressSeparator);
		if(childParts[1] == name)
			return _T("Name \"") + name + _T("\" is already taken");
	}

	for(auto& extension : LibPipe::Extensions) {
		bool found = false;

		auto extensionProviders = extension->serviceTypes();
		for(auto& extensionProvider : *extensionProviders) {
			auto& providerType = extensionProvider.object_items();
			if(type == providerType[_T("type")].string_value()) {
				found = true;
				break;
			}
		}

		if(!found)
			return _T("Service type could not be found");

		Path servicePath;
		servicePath.parseDirectory(_path);
		servicePath.pushDirectory(name);

		PipeObjectPtr ptrSettings(&settings, [](void*) { return; });
		tstring addressService = _address + TokenAddressSeparator + name;
		PipeServiceNodeBase* service = static_cast<PipeServiceNodeBase*>(extension->create(type, addressService, servicePath.toString(), ptrSettings));
		if(service == nullptr)
			return _T("Creating service failed");

		addChild(addressService, shared_ptr<PipeServiceNodeBase>(service));

		tstring addressInstance = _serviceServicesInstances->_address + TokenAddressSeparator + name;
		auto instance = make_shared<PipeServiceNodeBase>(_T("instance_") + type, _T("Instance of a ") + type + _T(" service"), addressInstance, _path, newObject());
		_serviceServicesInstances->addChild(addressInstance, instance);

		// Create command
		{
			instance->addCommand(_T("delete"), _T("Delete this service instance"), newObject(), [&, name](PipeObject& message) {
				tstring serviceName = name;
				deleteService(serviceName);
			});
		}
	}

	return _T("");
}

//----------------------------------------------------------------------------------------------------------------------

void ServiceRoot::deleteService(const tstring& name) {
	tstring addressService = _address + TokenAddressSeparator + name;
	tstring addressInstance = _serviceServicesInstances->_address + TokenAddressSeparator + name;

	removeChild(addressService);
	_serviceServicesInstances->removeChild(addressInstance);

	auto& services = _config->operator[](_T("services")).array_items();
	for(size_t idx = 0, cnt = services.size(); idx < cnt; idx++) {
		auto& service = services[idx].object_items();
		if(service.count(_T("name")) && service[_T("name")].is_string() && service[_T("name")].string_value() == name) {
			services.erase(begin(services) + idx);
			break;
		}
	}

	writeConfig();
}

//----------------------------------------------------------------------------------------------------------------------
void ServiceRoot::initScripts() {
	tstring addressScripts = _address + TokenAddressSeparator + _T("scripts");
	_serviceScripts = make_shared<PipeServiceNodeBase>(_T("scripts"), _T("Management of scripts"), addressScripts, _path, _settings);
	addChild(addressScripts, _serviceScripts);

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
	addChild(addressServices, _serviceServices);

	tstring addressServicesProviders = addressServices + TokenAddressSeparator + _T("providers");
	_serviceServicesProviders = make_shared<PipeServiceNodeBase>(_T("services_providers"), _T("Service provider types"), addressServicesProviders, _path, newObject());
	_serviceServices->addChild(addressServicesProviders, _serviceServicesProviders);

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
			_serviceServicesProviders->addChild(addressProvider, provider);

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
					
					tstring serviceName = msgData[_T("name")].string_value();
					auto& settingsData = msgData[_T("settings")].object_items();

					if(!_config->count(_T("services")))
						_config->operator[](_T("services")) = PipeJson(PipeArray());

					auto& services = _config->operator[](_T("services")).array_items();
					for(auto& service : services) {
						auto& serviceObj = service.object_items();
						if(serviceObj.count(_T("name")) && serviceObj[_T("name")].is_string()) {
							if(serviceObj[_T("name")].string_value() == serviceName)
								pushOutgoing(ref, _T("error"), _T("Name ") + serviceName + _T("is already taken"));
						}
					}

					tstring errorMsg = createService(typeName, serviceName, settingsData);
					if(!errorMsg.empty())
						pushOutgoing(ref, _T("error"), _T("Error creating service: ") + errorMsg);

					pushOutgoing(ref, _T("created"), serviceName);

					PipeObject serviceConfig;
					serviceConfig[_T("name")] = serviceName;
					serviceConfig[_T("type")] = typeName;
					serviceConfig[_T("settings")] = settingsData;
					services.push_back(serviceConfig);

					writeConfig();
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
	_serviceServices->addChild(addressServicesInstances, _serviceServicesInstances);
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
