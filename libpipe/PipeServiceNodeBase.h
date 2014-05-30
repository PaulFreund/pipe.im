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
	const tstring           _type;
	const tstring           _description;
	const tstring           _address;
	const tstring           _path;
	const PipeObjectPtr    _settings;

	//------------------------------------------------------------------------------------------------------------------

private:
	std::map<tstring, std::shared_ptr<IPipeExtensionService>> _children;
	PipeArrayPtr _outgoing;
	std::map<tstring, PipeCommandFunction> _commands;
	PipeArrayPtr _commandTypes;
	PipeArrayPtr _messageTypes;
	PipeArrayPtr _properties;

	bool _preSendHookEnabled = false;
	PipeHookFunction _preSendHook;

	bool _postReceiveHookEnabled = false;
	PipeHookFunction _postReceiveHook;

public:
	//------------------------------------------------------------------------------------------------------------------

	PipeServiceNodeBase(const tstring& type, const tstring& description, const tstring& address, const tstring& path, PipeObjectPtr settings)
		: _type(type)
		, _description(description)
		, _address(address)
		, _path(path)
		, _settings(settings)
		, _outgoing(newArray())
		, _commandTypes(newArray())
		, _messageTypes(newArray())
		, _properties(newArray())
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

	void addCommand(const tstring& name, const tstring& description, PipeObjectPtr commandTypeDefinition, PipeCommandFunction handler) {
		if(_commands.count(name))
		   throw tstring(_T("Command already defined"));
		
		// Optinally assert that the definition has the right format

		for(auto&& commandType : *_commandTypes) {
			if(commandType[TokenMessageCommand].string_value() == name)
				throw tstring(_T("Message type already defined"));
		}

		_commandTypes->push_back(PipeObject {
			{ TokenMessageCommand, name },
			{ TokenSchemaDescription, description },
			{ TokenSchema, *commandTypeDefinition }
		});

		_commands[name] = handler;
	}

	//------------------------------------------------------------------------------------------------------------------

	void addMessageType(const tstring& name, const tstring& description, PipeObjectPtr messageTypeDefinition) {

		// Optinally assert that the definition has the right format

		for(auto&& messageType : *_messageTypes) {
			if(messageType[TokenMessageMessage].string_value() == name)
				throw tstring(_T("Message type already defined"));
		}

		_messageTypes->push_back(PipeObject {
			{ TokenMessageMessage, name },
			{ TokenSchemaDescription, description },
			{ TokenSchema, *messageTypeDefinition }
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
			(*info)[_T("type")] = _type;
			(*info)[_T("description")] = _description;
			(*info)[_T("properties")] = *_properties;
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
		addCommand(_T("children"), _T("Get a list of all child nodes"), newObject(), [&](PipeObject& message) {
			pushOutgoing(message[TokenMessageRef].string_value(), _T("children"), *nodeChildren(message[TokenMessageAddress].string_value()));
		});

		//--------------------------------------------------------------------------------------------------------------
		addCommand(_T("commands"), _T("Get a list of all available commands"), newObject(), [&](PipeObject& message) {
			pushOutgoing(message[TokenMessageRef].string_value(), _T("commands"), *nodeCommandTypes(message[TokenMessageAddress].string_value()));
		});

		//--------------------------------------------------------------------------------------------------------------
		addCommand(_T("messages"), _T("Get a list of all message types this node can emmit"), newObject(), [&](PipeObject& message) {
			pushOutgoing(message[TokenMessageRef].string_value(), _T("messages"), *nodeMessageTypes(message[TokenMessageAddress].string_value()));
		});

		//--------------------------------------------------------------------------------------------------------------
		addCommand(_T("info"), _T("Get a list of all child nodes"), newObject(), [&](PipeObject& message) {
			pushOutgoing(message[TokenMessageRef].string_value(), _T("info"),*nodeInfo(message[TokenMessageAddress].string_value()));
		});
	}

	//------------------------------------------------------------------------------------------------------------------

	void addBaseMessageTypes() {
		////--------------------------------------------------------------------------------------------------------------
		PipeObjectPtr schemaError = newObject();
		schemaAddValue(*schemaError, TokenMessageData, SchemaValueTypeString, _T("Error message text"));

		addMessageType(_T("error"), _T("Error message"), schemaError);

		////--------------------------------------------------------------------------------------------------------------
		PipeObjectPtr schemaNodeAdded = newObject();
		schemaAddValue(*schemaNodeAdded, TokenMessageData, SchemaValueTypeString, _T("Name of the added node"));

		addMessageType(_T("node_added"), _T("Added node"), schemaNodeAdded);

		////--------------------------------------------------------------------------------------------------------------
		PipeObjectPtr schemaNodeRemoved = newObject();
		schemaAddValue(*schemaNodeRemoved, TokenMessageData, SchemaValueTypeString, _T("Name of the removed node"));

		addMessageType(_T("node_removed"), _T("Removed node"), schemaNodeRemoved);

		////--------------------------------------------------------------------------------------------------------------
		PipeObjectPtr schemaChildren = newObject();
		schemaAddValueArray(*schemaChildren, TokenMessageData, _T("List of child nodes"), SchemaValueTypeString, _T("Name of a child node"));

		addMessageType(_T("children"), _T("List of all child nodes"), schemaChildren);

		////--------------------------------------------------------------------------------------------------------------
		PipeObjectPtr schemaCommands = newObject();
		auto&& schemaCommandsItems = schemaAddObjectArray(*schemaCommands, TokenMessageData, _T("List of commands this node accepts"), _T("Command")); {
			schemaAddValue(schemaCommandsItems, TokenMessageCommand, SchemaValueTypeString, _T("Name of the command"));
			schemaAddValue(schemaCommandsItems, TokenSchemaDescription, SchemaValueTypeString, _T("Description of the command"));
			schemaAddObject(schemaCommandsItems, TokenSchema, _T("Schema of the command"));
		}

		addMessageType(_T("commands"), _T("List of all available commands"), schemaCommands);

		////--------------------------------------------------------------------------------------------------------------
		PipeObjectPtr schemaMessages = newObject();
		auto&& schemaMessagesItems = schemaAddObjectArray(*schemaMessages, TokenMessageData, _T("List of messages this node can emmit"), _T("Message type")); {
			schemaAddValue(schemaMessagesItems, TokenMessageMessage, SchemaValueTypeString, _T("Name of the message type"));
			schemaAddValue(schemaMessagesItems, TokenSchemaDescription, SchemaValueTypeString, _T("Description of the message type"));
			schemaAddObject(schemaMessagesItems, TokenSchema, _T("Schema of the message type"));
		}

		addMessageType(_T("messages"), _T("List of all message types this node can emmit"), schemaMessages);

		//--------------------------------------------------------------------------------------------------------------
		PipeObjectPtr schemaInfo = newObject();
		auto&& schemaInfoProperties = schemaAddObject(*schemaInfo, TokenMessageData, _T("Information about the node")); {
			schemaAddValue(schemaInfoProperties, TokenMessageAddress, SchemaValueTypeString, _T("Address of the node"));
			schemaAddValue(schemaInfoProperties, TokenSchemaType, SchemaValueTypeString, _T("Unique type of this node"));
			schemaAddValue(schemaInfoProperties, TokenSchemaDescription, SchemaValueTypeString, _T("Description of the node"));
			auto&& schemaInfoPropertiesItems = schemaAddObjectArray(schemaInfoProperties, _T("properties"), _T("Runtime properties of the node"), _T("Runtime property")); {
				schemaAddValue(schemaInfoPropertiesItems, _T("key"), SchemaValueTypeString, _T("Name of the property"));
				schemaAddValue(schemaInfoPropertiesItems, _T("value"), SchemaValueTypeString, _T("Value of the property"));
			}
		}

		addMessageType(_T("info"), _T("Information about this node"), schemaInfo);
	}
};
//======================================================================================================================

