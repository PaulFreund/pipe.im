//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInterface.h"
#include "LibPipeHelper.h"

//======================================================================================================================

class PipeServiceNodeBase : public IPipeExtensionService {
public:
	typedef std::function<void(PipeObject&)> PipeCommandFunction;
	typedef std::function<void(PipeArrayPtr)> PipeHookFunction;

public:
	const tstring           _type_name;
	const tstring           _type_description;
	const tstring           _instance_name;
	const tstring           _instance_description;
	const tstring           _address;
	const tstring           _path;
	const tstring           _icon;
	const PipeObjectPtr    _settings;

protected:
	PipeArrayPtr _state_infos;

	//------------------------------------------------------------------------------------------------------------------

private:
	std::map<tstring, std::shared_ptr<IPipeExtensionService>> _children;
	PipeArrayPtr _outgoing;
	std::map<tstring, PipeCommandFunction> _commands;
	PipeArrayPtr _commandTypes;
	PipeArrayPtr _messageTypes;

	bool _preSendHookEnabled = false;
	PipeHookFunction _preSendHook;

	bool _postReceiveHookEnabled = false;
	PipeHookFunction _postReceiveHook;

public:
	//------------------------------------------------------------------------------------------------------------------

	PipeServiceNodeBase(const tstring& address, const tstring& path, PipeObjectPtr settings, const tstring& type_name, const tstring& type_description, const tstring& instance_name, const tstring& instance_description, const tstring& icon = _T(""))
		: _address(address)
		, _path(path)
		, _settings(settings)
		, _type_name(type_name)
		, _type_description(type_description)
		, _instance_name(instance_name)
		, _instance_description(instance_description)
		, _icon(icon)
		, _outgoing(newArray())
		, _commandTypes(newArray())
		, _messageTypes(newArray())
		, _state_infos(newArray())
	{
		addBaseMessageTypes();
		addBaseCommandTypes();
	}

	virtual ~PipeServiceNodeBase() {}

public:
	//------------------------------------------------------------------------------------------------------------------

	void enablePreSendHook(PipeHookFunction hook) {
		_preSendHook = hook;
		_preSendHookEnabled = true;
	}
	//------------------------------------------------------------------------------------------------------------------

	void disablePreSendHook() {
		_preSendHookEnabled = false;
	}
	
	//------------------------------------------------------------------------------------------------------------------

	void enablePostReceiveHook(PipeHookFunction hook) {
		_postReceiveHook = hook;
		_postReceiveHookEnabled = true;
	}

	//------------------------------------------------------------------------------------------------------------------

	void disablePostReceiveHook() {
		_postReceiveHookEnabled = false;
	}

	//------------------------------------------------------------------------------------------------------------------

	void pushOutgoing(const tstring& reference, const tstring& type, PipeJson data) {
		PipeObject message;
		message[TokenMessageAddress] = _address;
		message[TokenMessageRef] = reference;
		message[TokenMessageMessage] = type;
		message[TokenMessageData] = data;

		// Optionally validate messages with message type when debugging

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

	void removeChild(const tstring& name) {
		if(_children.count(name)) {
			_children.erase(name);
			pushOutgoing(_T(""), _T("node_removed"), name);
		}
	}

	//------------------------------------------------------------------------------------------------------------------
	void addCommand(const tstring& name, const tstring& description, PipeCommandFunction handler) { auto def = PipeObject(); addCommand(name, description, def, handler); }
	void addCommand(const tstring& name, const tstring& description, PipeObject& commandTypeDefinition, PipeCommandFunction handler) {
		if(_commands.count(name))
		   throw tstring(_T("Command already defined"));

		// Optinally assert that the definition has the right format

		for(auto&& commandType : *_commandTypes) {
			if(commandType[TokenMessageCommand].string_value() == name)
				throw tstring(_T("Message type already defined"));
		}

		_commandTypes->push_back(PipeObject {
			{ TokenMessageCommand, name },
			{ _T("description"), description },
			{ _T("data_schema"), commandTypeDefinition }
		});

		_commands[name] = handler;
	}

	//------------------------------------------------------------------------------------------------------------------
	void addMessageType(const tstring& name, const tstring& description, PipeObject& messageTypeDefinition) {

		// Optinally assert that the definition has the right format

		for(auto&& messageType : *_messageTypes) {
			if(messageType[TokenMessageMessage].string_value() == name)
				throw tstring(_T("Message type already defined"));
		}

		_messageTypes->push_back(PipeObject {
			{ TokenMessageMessage, name },
			{ _T("description"), description },
			{ _T("data_schema"), messageTypeDefinition }
		});
	}

	//------------------------------------------------------------------------------------------------------------------

public:
	virtual void send(PipeArrayPtr messages) {
		if(_preSendHookEnabled)
			_preSendHook(messages);

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
						_children[nextAddress]->send(newArray({ message }));
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

	virtual PipeArrayPtr receive() {
		PipeArrayPtr messages = _outgoing;
		_outgoing = newArray();

		for(auto&& child : _children) {
			auto&& serviceOutgoing = child.second->receive();
			if(serviceOutgoing->size() > 0)
				messages->insert(messages->end(), serviceOutgoing->begin(), serviceOutgoing->end());
		}

		if(_postReceiveHookEnabled)
			_postReceiveHook(messages);

		return messages;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeArrayPtr nodeChildren(const tstring& address) {
		PipeArrayPtr children = newArray();
		if(address == _address) {
			for(auto&& child : _children) {
				children->push_back(child.first);
			}
		}
		else {
			tstring nextAddress = relativeChildAddress(address);
			if(_children.count(nextAddress))
				children = _children[nextAddress]->nodeChildren(address);
		}

		return children;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeArrayPtr nodeCommandTypes(const tstring& address) {
		PipeArrayPtr commandTypes = newArray();
		if(address == _address) {
			commandTypes = _commandTypes;
		}
		else {
			tstring nextAddress = relativeChildAddress(address);
			if(_children.count(nextAddress))
				commandTypes = _children[nextAddress]->nodeCommandTypes(address);
		}

		return commandTypes;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeArrayPtr nodeMessageTypes(const tstring& address) {
		PipeArrayPtr messageTypes = newArray();
		if(address == _address) {
			messageTypes = _messageTypes;
		}
		else {
			tstring nextAddress = relativeChildAddress(address);
			if(_children.count(nextAddress))
				messageTypes = _children[nextAddress]->nodeMessageTypes(address);
		}

		return messageTypes;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeObjectPtr nodeInfo(const tstring& address) {
		PipeObjectPtr info = newObject();
		if(address == _address) {
			(*info)[TokenMessageAddress] = _address;
			(*info)[_T("type_name")] = _type_name;
			(*info)[_T("type_description")] = _type_description;
			(*info)[_T("instance_name")] = _instance_name;
			(*info)[_T("instance_description")] = _instance_description;
			(*info)[_T("icon")] = _icon;
			(*info)[_T("state_infos")] = *_state_infos;
		}
		else {
			tstring nextAddress = relativeChildAddress(address);
			if(_children.count(nextAddress))
				info = _children[nextAddress]->nodeInfo(address);
		}

		return info;
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
			pushOutgoing(message[TokenMessageRef].string_value(), _T("children"), *nodeChildren(message[TokenMessageAddress].string_value()));
		});

		//--------------------------------------------------------------------------------------------------------------
		addCommand(_T("commands"), _T("Get a list of all available commands"), [&](PipeObject& message) {
			pushOutgoing(message[TokenMessageRef].string_value(), _T("commands"), *nodeCommandTypes(message[TokenMessageAddress].string_value()));
		});

		//--------------------------------------------------------------------------------------------------------------
		addCommand(_T("messages"), _T("Get a list of all message types this node can emmit"), [&](PipeObject& message) {
			pushOutgoing(message[TokenMessageRef].string_value(), _T("messages"), *nodeMessageTypes(message[TokenMessageAddress].string_value()));
		});

		//--------------------------------------------------------------------------------------------------------------
		addCommand(_T("info"), _T("Get a list of all child nodes"), [&](PipeObject& message) {
			pushOutgoing(message[TokenMessageRef].string_value(), _T("info"),*nodeInfo(message[TokenMessageAddress].string_value()));
		});
	}

	//------------------------------------------------------------------------------------------------------------------

	void addBaseMessageTypes() {
		////--------------------------------------------------------------------------------------------------------------

		addMessageType(_T("error"), _T("Error message"), PipeSchema::Create(PipeSchemaTypeString).title(_T("Message")).description(_T("Error message text")));

		////--------------------------------------------------------------------------------------------------------------
		addMessageType(_T("node_added"), _T("Added node"), PipeSchema::Create(PipeSchemaTypeString).title(_T("Name")).description(_T("Name of the added node")));

		////--------------------------------------------------------------------------------------------------------------
		addMessageType(_T("node_removed"), _T("Removed node"), PipeSchema::Create(PipeSchemaTypeString).title(_T("Name")).description(_T("Name of the removed node")));

		////--------------------------------------------------------------------------------------------------------------
		auto children = PipeSchema::Create(PipeSchemaTypeArray).title(_T("Chilren")).description(_T("List of child nodes"));
		children.items(PipeSchemaTypeString).title(_T("Child")).description(_T("Name of a child node"));
		addMessageType(_T("children"), _T("List of all child nodes"), children);

		////--------------------------------------------------------------------------------------------------------------
		auto commands = PipeSchema::Create(PipeSchemaTypeArray).title(_T("Command types")).description(_T("List of commands this node accepts"));
		auto& commandsItems = commands.items(PipeSchemaTypeObject).title(_T("Command type")).description(_T("Definition of a command type"));
		commandsItems.property(TokenMessageCommand, PipeSchemaTypeString).title(_T("Name")).description(_T("Name of the command"));
		commandsItems.property(_T("description"), PipeSchemaTypeString).title(_T("Description")).description(_T("Description of the command"));
		commandsItems.property(_T("data_schema"), PipeSchemaTypeObject).title(_T("Data schema")).description(_T("Data schema of the command"));
		addMessageType(_T("commands"), _T("List of all available commands"), commands);

		////--------------------------------------------------------------------------------------------------------------
		auto messages = PipeSchema::Create(PipeSchemaTypeArray).title(_T("Message types")).description(_T("List of messages this node can emmit"));
		auto& messagesItems = messages.items(PipeSchemaTypeObject).title(_T("Message type")).description(_T("Definition of a message type"));
		messagesItems.property(TokenMessageMessage, PipeSchemaTypeString).title(_T("Name")).description(_T("Name of the message type"));
		messagesItems.property(_T("description"), PipeSchemaTypeString).title(_T("Description")).description(_T("Description of the message type"));
		messagesItems.property(_T("data_schema"), PipeSchemaTypeObject).title(_T("Data schema")).description(_T("Data schema of the message"));
		addMessageType(_T("messages"), _T("List of all message types this node can emmit"), messages);

		//--------------------------------------------------------------------------------------------------------------
		auto info = PipeSchema::Create(PipeSchemaTypeObject).title(_T("Info")).description(_T("Information about the node"));
		info.property(TokenMessageAddress, PipeSchemaTypeString).title(_T("Address")).description(_T("Address of the node"));
		info.property(_T("type_name"), PipeSchemaTypeString).title(_T("Type")).description(_T("Unique type identifier of this node"));
		info.property(_T("type_description"), PipeSchemaTypeString).title(_T("Description")).description(_T("Description of the node type"));
		info.property(_T("instance_name"), PipeSchemaTypeString).title(_T("Title")).description(_T("Name of the node instance"));
		info.property(_T("instance_description"), PipeSchemaTypeString).title(_T("Title")).description(_T("Description of the node instance"));
		info.property(_T("icon"), PipeSchemaTypeString).title(_T("Icon")).description(_T("Node icon identifier"));
		auto& infoDataState = info.property(_T("state_infos"), PipeSchemaTypeArray).title(_T("State infos")).description(_T("Runtime state information pairs for the node"));
		auto& infoDataStateItems = infoDataState.items(PipeSchemaTypeObject).title(_T("State info")).description(_T("Runtime state info"));
		infoDataStateItems.property(_T("key"), PipeSchemaTypeString).title(_T("Key")).description(_T("Name of the state info"));
		infoDataStateItems.property(_T("value"), PipeSchemaTypeString).title(_T("Value")).description(_T("Value of the state info"));
		addMessageType(_T("info"), _T("Information about this node"), info);
	}
};
//======================================================================================================================
