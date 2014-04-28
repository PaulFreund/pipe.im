//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInterface.h"

//======================================================================================================================

class PipeServiceNodeBase : public IPipeExtensionService {
public:
	const TCHAR addressSeparator        = _T('.');

	const tstring msgKeyRef             = _T("ref");
	const tstring msgKeyAddress         = _T("address");
	const tstring msgKeyCommand         = _T("command");
	const tstring msgKeyMessage         = _T("message");

	const tstring schemaDescription     = _T("description");
	const tstring schemaFields          = _T("fields");
	const tstring schemaItems           = _T("items");
	const tstring schemaType            = _T("type");

	const tstring schemaTypeObject      = _T("object");
	const tstring schemaTypeArray       = _T("array");
	const tstring schemaTypeString      = _T("string");
	const tstring schemaTypeNumber      = _T("number");
	const tstring schemaTypeInteger     = _T("integer");
	const tstring schemaTypeBool        = _T("bool");

	const tstring msgTypeCommands       = _T("commands");
	const tstring msgTypeMessages       = _T("messages");
	const tstring msgTypeChildren       = _T("children");
	const tstring msgTypeInfo           = _T("info");

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
	std::map<tstring, std::shared_ptr<PipeServiceNodeBase>> _children;
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
		PipeObject schemaInfo;
		auto&& schemaInfoFields = schemaAddObject(schemaInfo, _T("info"), _T("The information about the node"));
		schemaAddValue(schemaInfoFields, _T("address"), SchemaString, _T("The address of the node"));
		schemaAddValue(schemaInfoFields, _T("type"), SchemaString, _T("The (unique) type of this node"));
		schemaAddValue(schemaInfoFields, _T("description"), SchemaString, _T("The description of the node"));
		auto&& schemaInfoPropertiesItems = schemaAddArray(schemaInfoFields, _T("properties"), _T("Runtime properties of the node"));
		schemaAddValue(schemaInfoPropertiesItems, _T("key"), SchemaString, _T("The name of the property"));
		schemaAddValue(schemaInfoPropertiesItems, _T("value"), SchemaString, _T("The value of the property"));

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

	void pushOutgoing(const tstring& reference, const tstring& type, PipeObjectPtr message) {
		if(!message->count(msgKeyAddress))
			(*message)[msgKeyAddress] = _address;

		if(!message->count(msgKeyRef))
			(*message)[msgKeyRef] = reference;

		if(!message->count(msgKeyMessage))
			(*message)[msgKeyMessage] = type;

		// Optional: validate messages with message type when debugging

		_outgoing->push_back(std::move(*message));
	}

	//------------------------------------------------------------------------------------------------------------------

	void addChild(const std::shared_ptr<PipeServiceNodeBase>& child) {
		auto& name = child->_address;
		if(_children.count(name))
			throw tstring(_T("There already is a child with the name \"") + name + _T("\""));

		_children[name] = child;
	}

	//------------------------------------------------------------------------------------------------------------------

	void removeChild(const tstring& name) {
		if(_children.count(name))
			_children.erase(name);
	}

	//------------------------------------------------------------------------------------------------------------------

	void addCommand(const tstring& name, const tstring& description, PipeObjectPtr commandTypeDefinition, PipeCommandFunction handler) {
		if(_commands.count(name))
		   throw tstring(_T("Command already defined"));
		
		// Optinal: Assert that the definition has the right format!

		for(auto&& commandType : *_commandTypes) {
			if(commandType[msgKeyCommand].string_value() == name)
				throw tstring(_T("Message type already defined"));
		}

		_commandTypes->push_back(PipeObject {
			{ msgKeyCommand, name },
			{ _T("description"), description },
			{ _T("schema"), *commandTypeDefinition }
		});

		_commands[name] = handler;
	}

	//------------------------------------------------------------------------------------------------------------------

	void addMessageType(const tstring& name, const tstring& description, PipeObjectPtr messageTypeDefinition) {

		// Optinal: Assert that the definition has the right format!

		for(auto&& messageType : *_messageTypes) {
			if(messageType[msgKeyMessage].string_value() == name)
				throw tstring(_T("Message type already defined"));
		}

		_messageTypes->push_back(PipeObject {
			{ msgKeyMessage, name },
			{ _T("description"), description },
			{ _T("schema"), *messageTypeDefinition }
		});
	}

	//------------------------------------------------------------------------------------------------------------------

public:
	virtual void send(PipeArrayPtr messages) {
		if(_preSendHookEnabled)
			_preSendHook(messages);

		for(auto&& messagesMember : *messages) {
			auto& message = messagesMember.object_items();

			// Without a reference, everything is meaningless
			if(message.empty() || (!message.count(msgKeyRef) || !message[msgKeyRef].is_string()))
				continue;

			try {
				if(!message.count(msgKeyAddress) || !message[msgKeyAddress].is_string())
					throw tstring(_T("Missing or invalid address field"));

				if(!message.count(msgKeyCommand) || !message[msgKeyCommand].is_string())
					throw tstring(_T("Missing or invalid command field"));

				auto& messageAddress = message[msgKeyAddress].string_value();

				if(messageAddress == _address) {
					auto messageCommand = message[msgKeyCommand].string_value();
					if(!_commands.count(messageCommand))
						throw tstring(_T("Command not found"));

					try {
						_commands[messageCommand](message);
					}
					catch(...) {
						throw tstring(_T("There was an error executing the command"));
					}
				}
				else if(messageAddress.length() >= (_address.length() + 2) && messageAddress[_address.length()] == addressSeparator && _children.count(messageAddress)) {
					_children[messageAddress]->send(newArray({ message }));
				}
				else {
					throw tstring(_T("Address not found"));
				}
			}
			catch(tstring errorDescription) {
				pushOutgoing(message[msgKeyRef].string_value(), _T("error"), newObject({ { _T("description"), errorDescription } }));
			}
			catch(...) {
				pushOutgoing(message[msgKeyRef].string_value(), _T("error"), newObject({ { _T("description"), _T("Unknown error") } }));
			}
		}
	}
	
	//------------------------------------------------------------------------------------------------------------------

	virtual PipeArrayPtr receive() {
		PipeArrayPtr messages = _outgoing;
		_outgoing = newArray();

		for(auto&& child : _children) {
			auto&& serviceOutgoing = child.second->receive();
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
		else if(address.length() >= (_address.length() + 2) && address[_address.length()] == addressSeparator && _children.count(address)) {
			children = _children[address]->nodeChildren(address);
		}

		return children;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeArrayPtr nodeCommandTypes(const tstring& address) {
		PipeArrayPtr commandTypes = newArray();
		if(address == _address) {
			commandTypes = _commandTypes;
		}
		else if(address.length() >= (_address.length() + 2) && address[_address.length()] == addressSeparator && _children.count(address)) {
			commandTypes = _children[address]->nodeCommandTypes(address);
		}

		return commandTypes;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeArrayPtr nodeMessageTypes(const tstring& address) {
		PipeArrayPtr messageTypes = newArray();
		if(address == _address) {
			messageTypes = _messageTypes;
		}
		else if(address.length() >= (_address.length() + 2) && address[_address.length()] == addressSeparator && _children.count(address)) {
			messageTypes = _children[address]->nodeMessageTypes(address);
		}

		return messageTypes;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeObjectPtr nodeInfo(const tstring& address) {
		PipeObjectPtr info = newObject();
		if(address == _address) {
			(*info)[msgKeyAddress] = _address;
			(*info)[_T("type")] = _type;
			(*info)[_T("description")] = _description;
			(*info)[_T("properties")] = *_properties;
		}
		else if(address.length() >= (_address.length() + 2) && address[_address.length()] == addressSeparator && _children.count(address)) {
			info = _children[address]->nodeInfo(address);
		}

		return info;
	}

	//------------------------------------------------------------------------------------------------------------------

private:
	void addBaseCommandTypes() {
		//--------------------------------------------------------------------------------------------------------------
		addCommand(msgTypeChildren, _T("Get a list of all child nodes"), newObject(), [&](PipeObject& message) {
			pushOutgoing(message[msgKeyRef].string_value(), msgTypeChildren, newObject({
				{ _T("children"), *nodeChildren(message[msgKeyAddress].string_value()) }
			}));
		});

		//--------------------------------------------------------------------------------------------------------------
		addCommand(msgTypeCommands, _T("Get a list of all available commands"), newObject(), [&](PipeObject& message) {
			pushOutgoing(message[msgKeyRef].string_value(), msgTypeCommands, newObject({
				{ _T("commands"), *nodeCommandTypes(message[msgKeyAddress].string_value()) }
			}));
		});

		//--------------------------------------------------------------------------------------------------------------
		addCommand(msgTypeMessages, _T("Get a list of all message types this node can emmit"), newObject(), [&](PipeObject& message) {
			pushOutgoing(message[msgKeyRef].string_value(), msgTypeMessages, newObject({
				{ _T("messages"), *nodeMessageTypes(message[msgKeyAddress].string_value()) }
			}));
		});

		//--------------------------------------------------------------------------------------------------------------
		addCommand(msgTypeInfo, _T("Get a list of all child nodes"), newObject(), [&](PipeObject& message) {
			pushOutgoing(message[msgKeyRef].string_value(), msgTypeInfo, newObject({
				{ _T("info"), *nodeInfo(message[msgKeyAddress].string_value()) }
			}));
		});
	}

	//------------------------------------------------------------------------------------------------------------------

	void addBaseMessageTypes() {
		////--------------------------------------------------------------------------------------------------------------
		addMessageType(msgTypeChildren, _T("List of all child nodes"), newObject({
			{ _T("children"), _T("The list of child nodes") }
		}));

		////--------------------------------------------------------------------------------------------------------------
		//addMessageType(msgTypeCommands, _T("List of all available commands"), newObject({
		//	{ _T("commands"), _T("The list of command types") } // TODO!
		//	// TODO: Add the structure of a command to this
		//}));

		////--------------------------------------------------------------------------------------------------------------
		//addMessageType(msgTypeMessages, _T("List of all message types this node can emmit"), newObject({
		//	{ _T("messages"), _T("The list of message types") } // TODO!
		//	// TODO: Add the structure of a message to this
		//}));

		//--------------------------------------------------------------------------------------------------------------
		PipeObjectPtr schemaInfo = newObject(); {
			auto&& schemaInfoFields = schemaAddObject(*schemaInfo, _T("info"), _T("The information about the node")); {
				schemaAddValue(schemaInfoFields, _T("address"), SchemaString, _T("The address of the node"));
				schemaAddValue(schemaInfoFields, _T("type"), SchemaString, _T("The (unique) type of this node"));
				schemaAddValue(schemaInfoFields, _T("description"), SchemaString, _T("The description of the node"));
				auto&& schemaInfoPropertiesItems = schemaAddArray(schemaInfoFields, _T("properties"), _T("Runtime properties of the node")); {
					schemaAddValue(schemaInfoPropertiesItems, _T("key"), SchemaString, _T("The name of the property"));
					schemaAddValue(schemaInfoPropertiesItems, _T("value"), SchemaString, _T("The value of the property"));
				}
			}
		}
		addMessageType(msgTypeInfo, _T("Information about this node"), schemaInfo);
	}

};
//======================================================================================================================

