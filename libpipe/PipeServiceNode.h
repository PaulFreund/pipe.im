//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInterface.h"
#include "LibPipeHelper.h"

//======================================================================================================================

class PipeServiceNode : public IPipeExtensionService {
public:
	typedef std::function<void(PipeObject&)> PipeCommandFunction;
	typedef std::function<void(PipeArrayPtr)> PipeHookFunction;

public:
	const tstring           _type_name;
	const tstring           _type_description;
	const tstring           _address;
	const tstring           _path;
	const tstring           _icon;
	const PipeObjectPtr    _settings;

	//------------------------------------------------------------------------------------------------------------------

private:
	std::map<tstring, std::shared_ptr<IPipeExtensionService>> _children;
	PipeArrayPtr _outgoing;
	std::map<tstring, PipeCommandFunction> _commands;
	PipeArrayPtr _baseCommandTypes;
	PipeArrayPtr _baseMessageTypes;
	PipeArrayPtr _commandTypes;
	PipeArrayPtr _messageTypes;
	std::map<tstring, PipeObject> _commandTypeSchemas;
	std::map<tstring, PipeObject> _messageTypeSchemas;
private:
	tstring           _instance_name;
	tstring           _instance_description;
	PipeArrayPtr      _state_infos;

public:
	//------------------------------------------------------------------------------------------------------------------

	PipeServiceNode(const tstring& address, const tstring& path, PipeObjectPtr settings, const tstring& type_name, const tstring& type_description, const tstring& instance_name, const tstring& instance_description, const tstring& icon = _T(""))
		: _type_name(type_name)
		, _type_description(type_description)
		, _address(address)
		, _path(path)
		, _icon(icon)
		, _settings(settings)
		, _outgoing(newArray())
		, _baseCommandTypes(newArray())
		, _baseMessageTypes(newArray())
		, _commandTypes(newArray())
		, _messageTypes(newArray())
		, _instance_name(instance_name)
		, _instance_description(instance_description)
		, _state_infos(newArray())
	{
		addBaseMessageTypes();
		addBaseCommandTypes();
	}

	virtual ~PipeServiceNode() {}

protected:
	//------------------------------------------------------------------------------------------------------------------
	const std::map<tstring, std::shared_ptr<IPipeExtensionService>>& children() {
		return _children;
	}

	//------------------------------------------------------------------------------------------------------------------
	void stateSetName(const tstring& newName) {
		_instance_name = newName;
		stateUpdated();
	}

	//------------------------------------------------------------------------------------------------------------------

	void stateSetDescription(const tstring& newDescription) {
		_instance_description = newDescription;
		stateUpdated();
	}
	
	//------------------------------------------------------------------------------------------------------------------

	void stateSetInfoState(const tstring& key, const tstring& value) {
		for(size_t idx = 0, cnt = _state_infos->size(); idx < cnt; idx++) {
			if((*_state_infos)[idx].object_items()[_T("key")].string_value() == key) {
				(*_state_infos)[idx].object_items()[_T("value")] = value;
				stateUpdated();
				return;
			}
		}
		_state_infos->push_back(PipeObject { { _T("key"), key}, { _T("value"), value} });
		stateUpdated();
	}

	//------------------------------------------------------------------------------------------------------------------

	tstring stateGetInfoState(const tstring& key) {
		for(size_t idx = 0, cnt = _state_infos->size(); idx < cnt; idx++) {
			if((*_state_infos)[idx].object_items()[_T("key")].string_value() == key) {
				return (*_state_infos)[idx].object_items()[_T("value")].string_value();
			}
		}
		return _T("");
	}

	//------------------------------------------------------------------------------------------------------------------

	void stateDeleteInfoState(const tstring& key) {
		for(size_t idx = 0, cnt = _state_infos->size(); idx < cnt; idx++) {
			if((*_state_infos)[idx].object_items()[_T("key")].string_value() == key) {
				_state_infos->erase(begin(*_state_infos)+idx);
				stateUpdated();
				break;
			}
		}
	}
	
	//------------------------------------------------------------------------------------------------------------------

	void stateUpdated() {
		pushOutgoing(_T(""), _T("state_updated"), *nodeState());
	}

public:
	//------------------------------------------------------------------------------------------------------------------

	void pushOutgoing(const tstring& reference, const tstring& type, PipeJson data) {
		PipeObject message;
		message[TokenMessageAddress] = _address;
		message[TokenMessageTimestamp] = currentTimestamp();
		message[TokenMessageRef] = reference;
		message[TokenMessageMessage] = type;
		message[TokenMessageData] = data;
		
		_outgoing->push_back(std::move(message));
	}

	//------------------------------------------------------------------------------------------------------------------

	void addChild(const tstring& address, const std::shared_ptr<IPipeExtensionService>& child) {
		if(_children.count(address))
			throw tstring(_T("There already is a child with the name \"") + address + _T("\""));

		_children[address] = child;
		pushOutgoing(_T(""), _T("node_added"), address);
	}

	//------------------------------------------------------------------------------------------------------------------

	void removeChild(const tstring& address) {
		if(_children.count(address)) {
			_children.erase(address);
			pushOutgoing(_T(""), _T("node_removed"), address);
		}
	}

	//------------------------------------------------------------------------------------------------------------------
	void addCommand(const tstring& name, const tstring& description, PipeCommandFunction handler, bool baseCommand = false) { auto def = PipeObject(); addCommand(name, description, def, handler, baseCommand); }
	void addCommand(const tstring& name, const tstring& description, PipeObject& commandTypeDefinition, PipeCommandFunction handler, bool baseCommand = false) {
		if(_commandTypeSchemas.count(name))
		   throw tstring(_T("Command already defined"));

		// Add command
		if(baseCommand) {
			_baseCommandTypes->push_back(PipeObject {
					{ TokenMessageCommand, name },
					{ _T("description"), description },
			});
		}
		else {
			_commandTypes->push_back(PipeObject {
					{ TokenMessageCommand, name },
					{ _T("description"), description },
			});
		}

		_commandTypeSchemas[name] = PipeObject { 
			{ _T("name"), name },
			{ _T("schema"), commandTypeDefinition }
		};
		_commands[name] = handler;
	}

	//------------------------------------------------------------------------------------------------------------------
	void addMessageType(const tstring& name, const tstring& description, PipeObject& messageTypeDefinition, bool baseMessage = false) {
		if(_messageTypeSchemas.count(name))
			throw tstring(_T("Message type already defined"));


		if(baseMessage) {
			_baseMessageTypes->push_back(PipeObject {
					{ TokenMessageMessage, name },
					{ _T("description"), description },
			});
		}
		else {
			_messageTypes->push_back(PipeObject {
					{ TokenMessageMessage, name },
					{ _T("description"), description },
			});
		}

		_messageTypeSchemas[name] = PipeObject {
			{ _T("name"), name },
			{ _T("schema"), messageTypeDefinition } 
		};
	}

	//------------------------------------------------------------------------------------------------------------------

public:
	//------------------------------------------------------------------------------------------------------------------

	virtual void push(PipeArrayPtr messages) {
		for(auto&& messagesMember : *messages) {
			auto& message = messagesMember.object_items();

			if(message.empty() || (!message.count(TokenMessageRef) || !message[TokenMessageRef].is_string())) {
				pushOutgoing(_T(""), _T("error"), _T("Missing ref property"));
				continue;
			}

			try {
				if(!message.count(TokenMessageAddress) || !message[TokenMessageAddress].is_string())
					throw tstring(_T("Missing or invalid address property"));

				if(!message.count(TokenMessageCommand) || !message[TokenMessageCommand].is_string())
					throw tstring(_T("Missing or invalid command property"));

				auto& messageAddress = message[TokenMessageAddress].string_value();

				if(messageAddress == _address) {
					auto messageCommand = message[TokenMessageCommand].string_value();
					if(!_commands.count(messageCommand))
						throw tstring(_T("Command not found"));

					try {
						_commands[messageCommand](message);
					}
					catch(...) {
						throw tstring(_T("There was an error executing the command"));
					}
				}
				else {
					tstring nextAddress = relativeChildAddress(messageAddress);
					if(_children.count(nextAddress))
						_children[nextAddress]->push(newArray({ message }));
					else 
						throw tstring(_T("Address not found"));
				}
			}
			catch(tstring errorDescription) {
				pushOutgoing(message[TokenMessageRef].string_value(), _T("error"), errorDescription);
			}
			catch(...) {
				pushOutgoing(message[TokenMessageRef].string_value(), _T("error"), _T("Unknown error"));
			}
		}
	}
	
	//------------------------------------------------------------------------------------------------------------------

	virtual PipeArrayPtr pull() {
		PipeArrayPtr messages = _outgoing;
		_outgoing = newArray();

		for(auto&& child : _children) {
			auto&& serviceOutgoing = child.second->pull();
			if(serviceOutgoing->size() > 0)
				messages->insert(messages->end(), serviceOutgoing->begin(), serviceOutgoing->end());
		}

		return messages;
	}

	//------------------------------------------------------------------------------------------------------------------

protected:
	virtual PipeArrayPtr nodeChildren() {
		PipeArrayPtr children = newArray();
		for(auto&& child : _children) {
			children->push_back(child.first);
		}
		return children;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeArrayPtr nodeCommandTypes(bool includeBasic = false) {
		if(includeBasic) {
			auto result = newArray();
			result->insert(begin(*result), begin(*_baseCommandTypes), end(*_baseCommandTypes));
			result->insert(begin(*result), begin(*_commandTypes), end(*_commandTypes));
			return result;
		}

		return _commandTypes;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeArrayPtr nodeMessageTypes(bool includeBasic = false) {
		if(includeBasic) {
			auto result = newArray();
			result->insert(begin(*result), begin(*_baseMessageTypes), end(*_baseMessageTypes));
			result->insert(begin(*result), begin(*_messageTypes), end(*_messageTypes));
			return result;
		}

		return _messageTypes;
	}

	//------------------------------------------------------------------------------------------------------------------
	
	virtual const PipeObject nodeCommandType(const tstring& name) {
		if(_commandTypeSchemas.count(name) == 1)
			return _commandTypeSchemas[name];

		return PipeObject();
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual const PipeObject nodeMessageType(const tstring& name) {
		if(_messageTypeSchemas.count(name) == 1)
			return _messageTypeSchemas[name];

		return PipeObject();
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeObjectPtr nodeInfo() {
		PipeObjectPtr info = newObject();
		(*info)[TokenMessageAddress] = _address;
		(*info)[_T("type")] = _type_name;			
		(*info)[_T("description")] = _type_description;
		(*info)[_T("children")] = *nodeChildren();
		(*info)[_T("state")] = *nodeState();
		(*info)[_T("commands")] = *nodeCommandTypes();
		(*info)[_T("messages")] = *nodeMessageTypes();
		return info;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeObjectPtr nodeState() {
		PipeObjectPtr state = newObject();
		(*state)[_T("name")] = _instance_name;
		(*state)[_T("description")] = _instance_description;
		(*state)[_T("icon")] = _icon;
		(*state)[_T("state_infos")] = *_state_infos;
		return state;
	}
	//------------------------------------------------------------------------------------------------------------------

private:
	tstring relativeChildAddress(tstring address) {
		auto searchAddressLength = address.length();
		auto selfAddressLength = _address.length();
		if(searchAddressLength >= (selfAddressLength + 2) && address[selfAddressLength] == TokenAddressSeparator) {
			auto secondSeparator = address.find(TokenAddressSeparator, selfAddressLength + 1);
			if(secondSeparator != tstring::npos)
				return address.substr(0, secondSeparator);
		}

		return address;
	}

	void addBaseCommandTypes() {
		//--------------------------------------------------------------------------------------------------------------
		addCommand(_T("children"), _T("Get a list of all child nodes"), [&](PipeObject& message) {
			pushOutgoing(message[TokenMessageRef].string_value(), _T("children"), *nodeChildren());
		}, true);

		//--------------------------------------------------------------------------------------------------------------
		addCommand(_T("commands"), _T("Get a list of all available commands including base commands"), [&](PipeObject& message) {
			pushOutgoing(message[TokenMessageRef].string_value(), _T("commands"), *nodeCommandTypes(true));
		}, true);

		//--------------------------------------------------------------------------------------------------------------
		auto cmdCommand = PipeSchema::Create(PipeSchemaTypeString).title(_T("Command")).description(_T("Command type name"));
		addCommand(_T("command"), _T("Get the schema of a command"), cmdCommand, [&](PipeObject& message) {
			auto ref = message[TokenMessageRef].string_value();

			if(message.count(TokenMessageData) != 1) {
				pushOutgoing(ref, _T("error"), _T("Missing command data"));
			}

			pushOutgoing(ref, _T("command"), nodeCommandType(message[TokenMessageData].string_value()));
		}, true);

		//--------------------------------------------------------------------------------------------------------------
		addCommand(_T("messages"), _T("Get a list of all message types this node can emmit including base messages"), [&](PipeObject& message) {
			pushOutgoing(message[TokenMessageRef].string_value(), _T("messages"), *nodeMessageTypes(true));
		}, true);

		//--------------------------------------------------------------------------------------------------------------
		auto cmdMessage = PipeSchema::Create(PipeSchemaTypeString).title(_T("Message")).description(_T("Message type name"));
		addCommand(_T("message"), _T("Get the schema of a message"), cmdMessage, [&](PipeObject& message) {
			auto ref = message[TokenMessageRef].string_value();

			if(message.count(TokenMessageData) != 1) {
				pushOutgoing(ref, _T("error"), _T("Missing command data"));
			}

			pushOutgoing(ref, _T("message"), nodeMessageType(message[TokenMessageData].string_value()));
		}, true);

		//--------------------------------------------------------------------------------------------------------------
		addCommand(_T("info"), _T("Get full information about the node including state"), [&](PipeObject& message) {
			pushOutgoing(message[TokenMessageRef].string_value(), _T("info"),*nodeInfo());
		}, true);

		//--------------------------------------------------------------------------------------------------------------
		addCommand(_T("state"), _T("Get state information about the node"), [&](PipeObject& message) {
			pushOutgoing(message[TokenMessageRef].string_value(), _T("state"), *nodeState());
		}, true);
	}

	//------------------------------------------------------------------------------------------------------------------

	void addBaseMessageTypes() {
		////--------------------------------------------------------------------------------------------------------------
		auto state = PipeSchema::Create(PipeSchemaTypeObject).title(_T("State")).description(_T("State of the node"));
		state.property(_T("name"), PipeSchemaTypeString).title(_T("Title")).description(_T("Name of the node instance"));
		state.property(_T("description"), PipeSchemaTypeString).title(_T("Title")).description(_T("Description of the node instance"));
		state.property(_T("icon"), PipeSchemaTypeString).title(_T("Icon")).description(_T("Node icon"));
		auto& stateDataState = state.property(_T("state_infos"), PipeSchemaTypeArray).title(_T("State infos")).description(_T("Runtime state information pairs for the node"));
		auto& stateDataStateItems = stateDataState.items(PipeSchemaTypeObject).title(_T("State info")).description(_T("Runtime state info"));
		stateDataStateItems.property(_T("key"), PipeSchemaTypeString).title(_T("Key")).description(_T("Name of the state info"));
		stateDataStateItems.property(_T("value"), PipeSchemaTypeString).title(_T("Value")).description(_T("Value of the state info"));
		addMessageType(_T("state"), _T("State of the node"), state, true);

		////--------------------------------------------------------------------------------------------------------------
		auto commands = PipeSchema::Create(PipeSchemaTypeArray).title(_T("Command types")).description(_T("List of commands this node accepts"));
		auto& commandsItems = commands.items(PipeSchemaTypeObject).title(_T("Command type")).description(_T("Definition of a command type"));
		commandsItems.property(TokenMessageCommand, PipeSchemaTypeString).title(_T("Name")).description(_T("Name of the command"));
		commandsItems.property(_T("description"), PipeSchemaTypeString).title(_T("Description")).description(_T("Description of the command"));
		addMessageType(_T("commands"), _T("List of all available commands"), commands, true);

		////--------------------------------------------------------------------------------------------------------------
		auto command = PipeSchema::Create(PipeSchemaTypeObject).title(_T("Command definition")).description(_T("Contains data schema of the command"));
		command.property(_T("name"), PipeSchemaTypeString).title(_T("Command name")).description(_T("Name for command schema"));
		command.property(_T("schema"), PipeSchemaTypeObject).title(_T("Command schema")).description(_T("Data schema of the command"));
		addMessageType(_T("command"), _T("Data schema of a command"), command, true);

		////--------------------------------------------------------------------------------------------------------------
		auto messages = PipeSchema::Create(PipeSchemaTypeArray).title(_T("Message types")).description(_T("List of messages this node can emmit"));
		auto& messagesItems = messages.items(PipeSchemaTypeObject).title(_T("Message type")).description(_T("Definition of a message type"));
		messagesItems.property(TokenMessageMessage, PipeSchemaTypeString).title(_T("Name")).description(_T("Name of the message type"));
		messagesItems.property(_T("description"), PipeSchemaTypeString).title(_T("Description")).description(_T("Description of the message type"));
		addMessageType(_T("messages"), _T("List of all message types this node can emmit"), messages, true);

		////--------------------------------------------------------------------------------------------------------------
		auto message = PipeSchema::Create(PipeSchemaTypeObject).title(_T("Message definition")).description(_T("Contains data schema of the message"));
		message.property(_T("name"), PipeSchemaTypeString).title(_T("Message name")).description(_T("Name for message schema"));
		message.property(_T("schema"), PipeSchemaTypeObject).title(_T("Message schema")).description(_T("Data schema of the message"));
		addMessageType(_T("message"), _T("Data schema of a message"), message, true);

		////--------------------------------------------------------------------------------------------------------------
		auto children = PipeSchema::Create(PipeSchemaTypeArray).title(_T("Chilren")).description(_T("List of child nodes"));
		children.items(PipeSchemaTypeString).title(_T("Child")).description(_T("Name of a child node"));
		addMessageType(_T("children"), _T("List of all child nodes"), children, true);

		////--------------------------------------------------------------------------------------------------------------
		auto info = PipeSchema::Create(PipeSchemaTypeObject).title(_T("Info")).description(_T("Information about the node"));
		info.property(TokenMessageAddress, PipeSchemaTypeString).title(_T("Address")).description(_T("Address of the node"));
		info.property(_T("type"), PipeSchemaTypeString).title(_T("Type")).description(_T("Unique type identifier of this node"));
		info.property(_T("description"), PipeSchemaTypeString).title(_T("Description")).description(_T("Description of the node type"));
		info.property(_T("state"), state);
		info.property(_T("children"), children);
		info.property(_T("commands"), commands);
		info.property(_T("messages"), messages);
		addMessageType(_T("info"), _T("Information about this node"), info, true);

		////--------------------------------------------------------------------------------------------------------------
		addMessageType(_T("error"), _T("Error message"), PipeSchema::Create(PipeSchemaTypeString).title(_T("Message")).description(_T("Error message text")), true);

		////--------------------------------------------------------------------------------------------------------------
		addMessageType(_T("node_added"), _T("Added node"), PipeSchema::Create(PipeSchemaTypeString).title(_T("Address")).description(_T("Address of the added node")), true);

		////--------------------------------------------------------------------------------------------------------------
		addMessageType(_T("node_removed"), _T("Removed node"), PipeSchema::Create(PipeSchemaTypeString).title(_T("Address")).description(_T("Address of the removed node")), true);
		
		////--------------------------------------------------------------------------------------------------------------
		addMessageType(_T("state_updated"), _T("Updated node state"), state, true);
	}
};
//======================================================================================================================
