//======================================================================================================================

#include "CommonHeader.h"
#include "ServiceRoot.h"
#include "LibPipe.h"

using namespace std;
using namespace Poco; // TODO: Remove

std::vector<std::shared_ptr<PipeExtensionInstance>> ServiceRoot::Extensions;

//======================================================================================================================

ServiceRoot::ServiceRoot(const tstring& path, PipeObjectPtr settings) 
	: PipeServiceNodeBase(TokenPipe, path, settings, TokenPipe, _T("Pipe root node"), _T("Pipe"), _T("Pipe root node"), TokenPipe)
	, _config(newObject())
	, _scriptIncomingQueue(newArray())
	, _scriptOutgoingQueue(newArray())
{	
	if(settings->count(_T("service_types"))) {
		auto& serviceTypes = (*settings)[_T("service_types")].array_items();
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
	if(!pathObj.exists()) { try { pathObj.createDirectories(); } catch(...) {}
	}
	
	// Load configuration or display error
	if(!pathObj.exists() || !pathObj.isDirectory() || !pathObj.canRead() || !pathObj.canWrite()) {
		pushOutgoing(_T(""), _T("error"), _T("Instance path location is invalid. Config can not be loaded or saved"));
	}
	else {
		loadConfig();
	}
}

//----------------------------------------------------------------------------------------------------------------------

ServiceRoot::~ServiceRoot() {}

//----------------------------------------------------------------------------------------------------------------------

void ServiceRoot::scriptPushIncoming(PipeObjectPtr message) {
	_scriptIncomingQueue->push_back(*message);
}

//----------------------------------------------------------------------------------------------------------------------

void ServiceRoot::scriptPushOutgoing(PipeObjectPtr message) {
	_scriptOutgoingQueue->push_back(*message);
}

//----------------------------------------------------------------------------------------------------------------------

void ServiceRoot::process() {
	// TODO [PROCESS]
	//_exchangeMutex.lock();
	//{
	//	// Receive
	//	PipeArrayPtr incoming = LibPipe::pull();
	//	_incomingQueue->insert(end(*_incomingQueue), begin(*incoming), end(*incoming));

	//	// Send
	//	LibPipe::push(_outgoingQueue);
	//	_outgoingQueue->clear();
	//}
	//_exchangeMutex.unlock();

	/*
					pApp->_exchangeMutex.lock();
				pApp->_pipeOutgoing->insert(end(*pApp->_pipeOutgoing), begin(*outgoing), end(*outgoing));
				pApp->_exchangeMutex.unlock();


				pApp->_exchangeMutex.lock();
				outstream << PipeJson(*pApp->_pipeIncoming).dump();
				pApp->_pipeIncoming->clear();
				pApp->_exchangeMutex.unlock();

				if(_acquiredLock) {
				PipeWebsocketTerminalApplication* pApp = reinterpret_cast<PipeWebsocketTerminalApplication*>(&Application::instance());
				try { pApp->_exchangeMutex.unlock(); }
				catch(...) {}
				}
	*/


}

//----------------------------------------------------------------------------------------------------------------------

void ServiceRoot::loadConfig() {
	if(!readConfig())
		return;

	if(_config->count(_T("services"))) {
		auto& services = (*_config)[_T("services")].array_items();
		for(auto& service : services) {
			auto& serviceObject = service.object_items();
			tstring name = serviceObject[_T("name")].string_value();
			tstring type = serviceObject[_T("type")].string_value();
			auto& settings = serviceObject[_T("settings")].object_items();

			if(find(begin(_providerTypes), end(_providerTypes), type) == end(_providerTypes)) {
				pushOutgoing(_T(""), _T("error"), _T("Could not load service \"") + name + _T("\", unsupported type \"") + type + _T("\""));
				continue;
			}

			tstring errorMsg = createService(type, name, settings);
			if(!errorMsg.empty()) {
				pushOutgoing(_T(""), _T("error"), _T("Error creating service ") + name + _T(": ") + errorMsg);
				continue;
			}
		}
	}

	if(_config->count(_T("scripts"))) {
		auto& services = (*_config)[_T("scripts")].array_items();
		for(auto& service : services) {
			auto& serviceObject = service.object_items();
			tstring name = serviceObject[_T("name")].string_value();
			bool preSend = serviceObject[_T("preSend")].bool_value();
			bool postReceive = serviceObject[_T("postReceive")].bool_value();
			int priority = serviceObject[_T("priority")].int_value();
			tstring data = serviceObject[_T("data")].string_value();

			tstring errorMsg = createScript(name, preSend, postReceive, priority, data);
			if(!errorMsg.empty()) {
				pushOutgoing(_T(""), _T("error"), _T("Error creating script ") + name + _T(": ") + errorMsg);
				continue;
			}
		}
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
			return;
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

void ServiceRoot::initServices() {
	tstring addressServices = _address + TokenAddressSeparator + _T("services");
	_serviceServices = make_shared<PipeServiceNodeBase>(addressServices, _path, newObject(), _T("services"), _T("Management of services"), _T("Services"), _T("Management of services"), _T("services"));
	addChild(addressServices, _serviceServices);

	tstring addressServicesProviders = addressServices + TokenAddressSeparator + _T("providers");
	_serviceServicesProviders = make_shared<PipeServiceNodeBase>(addressServicesProviders, _path, newObject(), _T("service_providers"), _T("Service provider types"), _T("Service providers"), _T("Available service providers"), _T("service_providers"));
	_serviceServices->addChild(addressServicesProviders, _serviceServicesProviders);

	// Add providers
	for(auto& extension : Extensions) {
		auto extensionProviders = extension->serviceTypes();
		for(auto& type : *extensionProviders) {
			auto& providerType = type.object_items();
			tstring typeName = providerType[_T("type")].string_value();

			if(find(begin(_providerTypes), end(_providerTypes), providerType[_T("type")].string_value()) == end(_providerTypes))
				continue;

			tstring typeDescription = providerType[_T("description")].string_value();
			PipeSchema& typeSettingsSchema = reinterpret_cast<PipeSchema&>(providerType[_T("settings_schema")].object_items());

			tstring addressProvider = addressServicesProviders + TokenAddressSeparator + typeName;

			auto providerSettings = newObject();
			(*providerSettings)[_T("type")].string_value() = typeName;
			auto provider = make_shared<PipeServiceNodeBase>(addressProvider, _path, providerSettings, _T("service_provider"), _T("Representation of a service"), typeName, typeDescription, _T("service_provider_") + typeName);
			_serviceServicesProviders->addChild(addressProvider, provider);

			// Create command
			{
				auto cmdCreate = PipeSchema::Create(PipeSchemaTypeObject).title(_T("Creation Data")).description(_T("Data to create a new service"));
				cmdCreate.property(_T("name"), PipeSchemaTypeString).title(_T("Name")).description(_T("Name of the new service")).pattern(_T("[A-z_]+"));
				cmdCreate.property(_T("settings"), typeSettingsSchema).title(_T("Settings")).description(_T("Settings for the new service"));
				
				provider->addCommand(_T("create"), _T("Create a service instance"), cmdCreate, [&, typeName, provider](PipeObject& message) {
					auto ref = message[_T("ref")].string_value();
					if(!message.count(_T("data")) || !message[_T("data")].is_object()) {
						provider->pushOutgoing(ref, _T("error"), _T("Missing command data"));
						return;
					}

					auto& msgData = message[_T("data")].object_items();
					if(!msgData.count(_T("name")) || !msgData[_T("name")].is_string() || !msgData.count(_T("settings")) || !msgData[_T("settings")].is_object()) {
						provider->pushOutgoing(ref, _T("error"), _T("Invalid create request"));
						return;
					}
					
					tstring serviceName = msgData[_T("name")].string_value();
					auto& settingsData = msgData[_T("settings")].object_items();

					if(!_config->count(_T("services")))
						(*_config)[_T("services")] = PipeJson(PipeArray());

					auto& services = (*_config)[_T("services")].array_items();
					for(auto& service : services) {
						auto& serviceObj = service.object_items();
						if(serviceObj.count(_T("name")) && serviceObj[_T("name")].is_string()) {
							if(serviceObj[_T("name")].string_value() == serviceName) {
								provider->pushOutgoing(ref, _T("error"), _T("Name ") + serviceName + _T(" is already taken"));
								return;
							}
						}
					}

					tstring errorMsg = createService(typeName, serviceName, settingsData);
					if(!errorMsg.empty()) {
						provider->pushOutgoing(ref, _T("error"), _T("Error creating service: ") + errorMsg);
						return;
					}

					PipeObject serviceConfig;
					serviceConfig[_T("name")] = serviceName;
					serviceConfig[_T("type")] = typeName;
					serviceConfig[_T("settings")] = settingsData;
					services.push_back(serviceConfig);

					writeConfig();
				});
			}
		}
	}

	tstring addressServicesInstances = addressServices + TokenAddressSeparator + _T("instances");
	_serviceServicesInstances = make_shared<PipeServiceNodeBase>(addressServicesInstances, _path, newObject(), _T("service_instances"), _T("Service instance nodes"), _T("Instances"), _T("Instance representations"), _T("service_instances"));
	_serviceServices->addChild(addressServicesInstances, _serviceServicesInstances);
}

//----------------------------------------------------------------------------------------------------------------------

tstring ServiceRoot::createService(const tstring& type, const tstring& name, PipeObject& settings) {
	auto children = nodeChildren(TokenPipe);
	for(auto& child : *children) {
		auto childParts = texplode(child.string_value(), TokenAddressSeparator);
		if(childParts[1] == name)
			return _T("Name \"") + name + _T("\" is already taken");
	}

	for(auto& extension : Extensions) {
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
		auto instance = make_shared<PipeServiceNodeBase>(addressInstance, _path, newObject(), _T("service_instance"), _T("Instance of a service"), type, _T("A ") + type + _T(" instance"), _T("service_instance_") + type);
		_serviceServicesInstances->addChild(addressInstance, instance);

		// Delete command
		{
			instance->addCommand(_T("delete"), _T("Delete this service instance"), [&, name](PipeObject& message) {
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

	auto& services = (*_config)[_T("services")].array_items();
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
	_serviceScripts = make_shared<PipeServiceNodeBase>(addressScripts, _path, _settings, _T("script_manager"), _T("Management of scripts"), _T("Scripts"), _T("Management of scripts"), _T("script_manager"));
	addChild(addressScripts, _serviceScripts);

	auto cmdCreate = PipeSchema::Create(PipeSchemaTypeObject).title(_T("Script data")).description(_T("Data to create a new script"));
	cmdCreate.property(_T("name"), PipeSchemaTypeString).title(_T("Name")).description(_T("Name of the new script")).pattern(_T("[A-z_]+"));
	cmdCreate.property(_T("preSend"), PipeSchemaTypeBoolean).title(_T("Pre send hook")).description(_T("Script will be executed before a incoming message is processed"));
	cmdCreate.property(_T("postReceive"), PipeSchemaTypeBoolean).title(_T("Post receive hook")).description(_T("Script will be executed after a outgoing message was processed"));
	cmdCreate.property(_T("priority"), PipeSchemaTypeInteger).title(_T("Priority")).description(_T("Execution priority"));
	cmdCreate.property(_T("data"), PipeSchemaTypeString).title(_T("Script")).description(_T("The script body code")).format(_T("js"));
	{
		_serviceScripts->addCommand(_T("create"), _T("Create a automation script"), cmdCreate, [&](PipeObject& message) {
			auto ref = message[_T("ref")].string_value();
			if(!message.count(_T("data")) || !message[_T("data")].is_object()) {
				_serviceScripts->pushOutgoing(ref, _T("error"), _T("Missing command data"));
				return;
			}

			auto& msgData = message[_T("data")].object_items();
			if(    !msgData.count(_T("name"))           || !msgData[_T("name")].is_string() 
				|| !msgData.count(_T("preSend"))        || !msgData[_T("preSend")].is_bool()
				|| !msgData.count(_T("postReceive"))    || !msgData[_T("postReceive")].is_bool()
				|| !msgData.count(_T("priority"))       || !msgData[_T("priority")].is_number()
				|| !msgData.count(_T("data"))           || !msgData[_T("data")].is_string()) 
			{
				_serviceScripts->pushOutgoing(ref, _T("error"), _T("Invalid create request"));
				return;
			}

			tstring scriptName = msgData[_T("name")].string_value();
			bool scriptPreSend = msgData[_T("preSend")].bool_value();
			bool scriptPostReceive = msgData[_T("postReceive")].bool_value();
			int scriptPriority = msgData[_T("priority")].int_value();
			tstring scriptData = msgData[_T("data")].string_value();

			if(!_config->count(_T("scripts")))
				(*_config)[_T("scripts")] = PipeJson(PipeArray());

			auto& scripts = (*_config)[_T("scripts")].array_items();
			for(auto& script : scripts) {
				auto& scriptObj = script.object_items();
				if(scriptObj.count(_T("name")) && scriptObj[_T("name")].is_string()) {
					if(scriptObj[_T("name")].string_value() == scriptName) {
						_serviceScripts->pushOutgoing(ref, _T("error"), _T("Name ") + scriptName + _T(" is already taken"));
						return;
					}
				}
			}

			tstring errorMsg = createScript(scriptName, scriptPreSend, scriptPostReceive, scriptPriority, scriptData);
			if(!errorMsg.empty()) {
				_serviceScripts->pushOutgoing(ref, _T("error"), _T("Error creating script: ") + errorMsg);
				return;
			}

			PipeObject scriptConfig;
			scriptConfig[_T("name")] = scriptName;
			scriptConfig[_T("preSend")] = scriptPreSend;
			scriptConfig[_T("postReceive")] = scriptPostReceive;
			scriptConfig[_T("priority")] = scriptPriority;
			scriptConfig[_T("data")] = scriptData;
			scripts.push_back(scriptConfig);

			writeConfig();
		});
	}

	enableHookPrePush([&](PipeArrayPtr messages) { executeScripts(messages, true, false); });
	enableHookPostPull([&](PipeArrayPtr messages) { executeScripts(messages, false, true); });
}

//----------------------------------------------------------------------------------------------------------------------

tstring ServiceRoot::createScript(const tstring& name, bool preSend, bool postReceive, int priority, const tstring& data) {
	shared_ptr<PipeScript> scriptInstance;
	try {
		scriptInstance = PipeScript::create(this, name, preSend, postReceive, priority, data);
	}
	catch(tstring error) {
		return error;
	}

	if(preSend) { _scriptsPreSend.push_back(scriptInstance); }
	if(postReceive) { _scriptsPostReceive.push_back(scriptInstance); }

	tstring addressScriptNode = _serviceScripts->_address + TokenAddressSeparator + name;
	auto scriptNode = make_shared<PipeServiceNodeBase>(addressScriptNode, _path, newObject(), _T("script_instance"), _T("Automation script instance"), name, _T("A automation script"), _T("script_instance"));
	_serviceScripts->addChild(addressScriptNode, scriptNode);

	// Delete command
	{
		scriptNode->addCommand(_T("delete"), _T("Delete this script"), [&, name](PipeObject& message) {
			tstring scriptName = name;
			deleteScript(scriptName);
		});
	}

	// Read command and response
	{
		scriptNode->addCommand(_T("read"), _T("Get the data of this script"), [&, name, scriptNode](PipeObject& message) {
			tstring scriptName = name;
			auto ref = message[_T("ref")].string_value();
			auto& scripts = (*_config)[_T("scripts")].array_items();
			for(auto& script : scripts) {
				auto& scriptObj = script.object_items();
				if(scriptObj.count(_T("name")) && scriptObj[_T("name")].is_string()) {
					if(scriptObj[_T("name")].string_value() == scriptName) {
						scriptNode->pushOutgoing(ref, _T("script_data"), scriptObj);
						return;
					}
				}
			}
		});

		auto msgScriptData = PipeSchema::Create(PipeSchemaTypeObject).title(_T("Script data")).description(_T("Data of the script"));
		msgScriptData.property(_T("name"), PipeSchemaTypeString).title(_T("Name")).description(_T("Name of the new script"));
		msgScriptData.property(_T("preSend"), PipeSchemaTypeBoolean).title(_T("Pre send hook")).description(_T("Script will be executed before a incoming message is processed"));
		msgScriptData.property(_T("postReceive"), PipeSchemaTypeBoolean).title(_T("Post receive hook")).description(_T("Script will be executed after a outgoing message was processed"));
		msgScriptData.property(_T("priority"), PipeSchemaTypeInteger).title(_T("Priority")).description(_T("Execution priority"));
		msgScriptData.property(_T("data"), PipeSchemaTypeString).title(_T("Script")).description(_T("The script body code")).format(_T("js"));
		scriptNode->addMessageType(_T("script_data"), _T("Data that is stored for this script"), msgScriptData);
	}

	// Update command and response
	{
		auto cmdUpdate = PipeSchema::Create(PipeSchemaTypeObject).title(_T("Updated data")).description(_T("Data to update an existing script"));
		cmdUpdate.property(_T("preSend"), PipeSchemaTypeBoolean).title(_T("Pre send hook")).description(_T("Script will be executed before a incoming message is processed"));
		cmdUpdate.property(_T("postReceive"), PipeSchemaTypeBoolean).title(_T("Post receive hook")).description(_T("Script will be executed after a outgoing message was processed"));
		cmdUpdate.property(_T("priority"), PipeSchemaTypeInteger).title(_T("Priority")).description(_T("Execution priority"));
		cmdUpdate.property(_T("data"), PipeSchemaTypeString).title(_T("Script")).description(_T("The script body code")).format(_T("js"));
		scriptNode->addCommand(_T("update"), _T("Update a script"), cmdUpdate, [&, name, scriptNode](PipeObject& message) {
			tstring scriptName = name;

			auto ref = message[_T("ref")].string_value();
			if(!message.count(_T("data")) || !message[_T("data")].is_object()) {
				scriptNode->pushOutgoing(ref, _T("error"), _T("Missing command data"));
				return;
			}

			auto& msgData = message[_T("data")].object_items();
			if(!msgData.count(_T("preSend")) || !msgData[_T("preSend")].is_bool()
			   || !msgData.count(_T("postReceive")) || !msgData[_T("postReceive")].is_bool()
			   || !msgData.count(_T("priority")) || !msgData[_T("priority")].is_number()
			   || !msgData.count(_T("data")) || !msgData[_T("data")].is_string()) {
				scriptNode->pushOutgoing(ref, _T("error"), _T("Invalid create request"));
				return;
			}

			bool scriptPreSend = msgData[_T("preSend")].bool_value();
			bool scriptPostReceive = msgData[_T("postReceive")].bool_value();
			int scriptPriority = msgData[_T("priority")].int_value();
			tstring scriptData = msgData[_T("data")].string_value();

			if(_config->count(_T("scripts"))) {
				auto& scripts = (*_config)[_T("scripts")].array_items();
				for(auto& script : scripts) {
					auto& scriptObj = script.object_items();
					if(scriptObj.count(_T("name")) && scriptObj[_T("name")].is_string()) {
						if(scriptObj[_T("name")].string_value() == scriptName) {
							// Create new instance
							shared_ptr<PipeScript> updatedScriptInstance;
							try {
								updatedScriptInstance = PipeScript::create(this, name, preSend, postReceive, priority, data);
							}
							catch(tstring error) {
								scriptNode->pushOutgoing(ref, _T("error"), _T("Invalid script data: ") + error);
								return;
							}
							
							// Remove from pre-send
							for(size_t idx = 0, cnt = _scriptsPreSend.size(); idx < cnt; idx++) {
								if(_scriptsPreSend[idx]->_name == scriptName) {
									_scriptsPreSend.erase(begin(_scriptsPreSend) + idx);
									break;
								}
							}

							// Remove from post-receive
							for(size_t idx = 0, cnt = _scriptsPostReceive.size(); idx < cnt; idx++) {
								if(_scriptsPostReceive[idx]->_name == scriptName) {
									_scriptsPostReceive.erase(begin(_scriptsPostReceive) + idx);
									break;
								}
							}

							// Readd
							if(preSend) { _scriptsPreSend.push_back(updatedScriptInstance); }
							if(postReceive) { _scriptsPostReceive.push_back(updatedScriptInstance); }

							// Update config data
							scriptObj[_T("preSend")] = scriptPreSend;
							scriptObj[_T("postReceive")] = scriptPostReceive;
							scriptObj[_T("priority")] = scriptPriority;
							scriptObj[_T("data")] = scriptData;

							scriptNode->pushOutgoing(ref, _T("updated"), scriptName);
							writeConfig();
							return;
						}
					}
				}
			}

			scriptNode->pushOutgoing(ref, _T("error"), _T("Name ") + scriptName + _T(" could not be found"));
			return;
		});
		
		scriptNode->addMessageType(_T("updated"), _T("Script update notification"), PipeSchema::Create(PipeSchemaTypeString).title(_T("Name")).description(_T("Name of the updated script")));
	}

	auto scriptSort = [](shared_ptr<PipeScript> a, shared_ptr<PipeScript> b) {
		return a->_priority > b->_priority;
	};

	sort(begin(_scriptsPreSend), end(_scriptsPreSend), scriptSort);
	sort(begin(_scriptsPostReceive), end(_scriptsPostReceive), scriptSort);
	return _T("");
}

//----------------------------------------------------------------------------------------------------------------------

void ServiceRoot::deleteScript(const tstring& name) {
	// Remove from DOM
	tstring addressScriptNode = _serviceScripts->_address + TokenAddressSeparator + name;
	_serviceScripts->removeChild(addressScriptNode);

	// Remove from pre-send
	for(size_t idx = 0, cnt = _scriptsPreSend.size(); idx < cnt; idx++) {
		if(_scriptsPreSend[idx]->_name == name) {
			_scriptsPreSend.erase(begin(_scriptsPreSend) + idx);
			break;
		}
	}

	// Remove from post-receive
	for(size_t idx = 0, cnt = _scriptsPostReceive.size(); idx < cnt; idx++) {
		if(_scriptsPostReceive[idx]->_name == name) {
			_scriptsPostReceive.erase(begin(_scriptsPostReceive) + idx);
			break;
		}
	}

	// Remove from config
	auto& scripts = (*_config)[_T("scripts")].array_items();
	for(size_t idx = 0, cnt = scripts.size(); idx < cnt; idx++) {
		auto& script = scripts[idx].object_items();
		if(script.count(_T("name")) && script[_T("name")].is_string() && script[_T("name")].string_value() == name) {
			scripts.erase(begin(scripts) + idx);
			break;
		}
	}

	writeConfig();
}

//----------------------------------------------------------------------------------------------------------------------

void ServiceRoot::executeScripts(PipeArrayPtr messages, bool preSend, bool postReceive) {
	// Get the right list of scripts
	vector<shared_ptr<PipeScript>>* targetList = nullptr;
	tstring targetFunction = _T("");
	if(preSend) { targetList = &_scriptsPreSend; targetFunction = _T("preSend"); }
	else if(postReceive) { targetList = &_scriptsPostReceive; targetFunction = _T("postReceive"); }
	if(targetList == nullptr || targetFunction.empty()) { return; }

	// Process messages for outbound script messages
	if(postReceive && !_scriptOutgoingQueue->empty()) {
		messages->insert(begin(*messages), begin(*_scriptOutgoingQueue), end(*_scriptOutgoingQueue));
		_scriptOutgoingQueue->clear();
	}

	auto& messageData = *messages;
	vector<int> deleteList;

	const tstring tokenScriptNode = _address + TokenAddressSeparator + _T("scripts");
	for(size_t idx = 0, cnt = messageData.size(); idx < cnt; idx++) {
		auto& message = messageData[idx];
		tstring address = message[TokenMessageAddress].string_value();

		// Do not execute scripts on the script node
		if(address.substr(0, tokenScriptNode.length()) == tokenScriptNode)
			continue;

		for(auto& script : *targetList) {
			try {
				script->execute(targetFunction, message.object_items());
			}
			catch(tstring error) {
				pushOutgoing(_T(""), _T("error"), _T("Execution of script \"") + script->_name + _T("\" failed: ") + error);
			}
			if(!message.is_object() || message.object_items().empty()) {
				deleteList.push_back(idx);
				break;
			}
		}
	}

	for(auto& deleteIndex : deleteList) {
		messageData.erase(begin(messageData) + deleteIndex);
	}

	// Process messages for inbound script messages
	if(preSend && !_scriptIncomingQueue->empty()) {
		PipeArrayPtr incoming = move(_scriptIncomingQueue);
		_scriptIncomingQueue = newArray();
		push(incoming);
	}
}



//======================================================================================================================
