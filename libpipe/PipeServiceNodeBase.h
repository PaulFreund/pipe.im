//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInterface.h"

//======================================================================================================================

class PipeServiceNodeBase : public IPipeExtensionService {
public:
	const TCHAR addressSeparator = _T('.');

	const tstring msgKeyCommand = _T("command");
	const tstring msgKeyType = _T("type");
	const tstring msgKeyRef = _T("ref");

	const tstring msgTypeCommands = _T("commands");
	const tstring msgTypeMessages = _T("messages");
	const tstring msgTypeChildren = _T("children");
	const tstring msgTypeInfo = _T("info");
	const tstring msgTypeError = _T("error");

	const tstring infoKeyAddress = _T("address");
	const tstring infoKeyType = _T("type");
	const tstring infoKeyProperties = _T("properties");

	const tstring msgKeyAddress = _T("address");


	const tstring msgFieldName = _T("name");
	const tstring msgFieldStructure = _T("structure");
	const tstring msgFieldDescription = _T("description");

	typedef std::function<void(PipeJsonObjectData&)> PipeCommandFunction;
	typedef std::function<void(PipeJsonArray)> PipeHookFunction;

public:
	const tstring _type;
	const tstring _description;
	const tstring _address;
	const tstring _path;
	const PipeJsonObject _settings;

	//------------------------------------------------------------------------------------------------------------------

private:
	std::map<tstring, std::shared_ptr<PipeServiceNodeBase>> _children;
	PipeJsonArray _outgoing;
	std::map<tstring, PipeCommandFunction> _commands;
	PipeJsonArray _commandTypes;
	PipeJsonArray _messageTypes;
	PipeJsonObject _properties;

	bool _preSendHookEnabled = false;
	PipeHookFunction _preSendHook;

	bool _postReceiveHookEnabled = false;
	PipeHookFunction _postReceiveHook;

public:
	//------------------------------------------------------------------------------------------------------------------

	PipeServiceNodeBase(const tstring& type, const tstring& description, const tstring& address, const tstring& path, PipeJsonObject settings)
		: _type(type)
		, _description(description)
		, _address(address)
		, _path(path)
		, _settings(settings)
		, _outgoing(newArray())
		, _commandTypes(newArray())
		, _messageTypes(newArray())
		, _properties(newObject())
	{

		// TODO: Add default commands and remove test

		addCommand(
			msgTypeChildren,
			_T("Get a list of all child nodes"),
			newObject({
				//{ _T("childNodes"),  }
			}),
			[&](PipeJsonObjectData& message) {
				pushOutgoing(message[msgKeyRef].string_value(), msgTypeChildren, newObject({
					{ _T("children"), *nodeChildren(message[msgKeyAddress].string_value()) }
				}));
			}
		);

		addCommand(
			msgTypeCommands,
			_T("Get a list of all available commands"),
			newObject({
			//{ _T("childNodes"),  }
			}),
			[&](PipeJsonObjectData& message) {
				pushOutgoing(message[msgKeyRef].string_value(), msgTypeCommands, newObject({
					{ _T("commands"), *nodeCommandTypes(message[msgKeyAddress].string_value()) }
				}));
			}
		);

		addCommand(
			msgTypeMessages,
			_T("Get a list of all emmitable message types"),
			newObject({
			//{ _T("childNodes"),  }
			}),
			[&](PipeJsonObjectData& message) {
				pushOutgoing(message[msgKeyRef].string_value(), msgTypeMessages, newObject({
					{ _T("messages"), *nodeMessageTypes(message[msgKeyAddress].string_value()) }
				}));
			}
		);

		addCommand(
			msgTypeInfo,
			_T("Get a list of all child nodes"),
			newObject({
				//{ _T("childNodes"),  }
			}),
			[&](PipeJsonObjectData& message) {
				pushOutgoing(message[msgKeyRef].string_value(), msgTypeInfo, newObject({
					{ _T("info"), *nodeInfo(message[msgKeyAddress].string_value()) }
				}));
			}
		);
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

	void pushOutgoing(const tstring& reference, const tstring& type, PipeJsonObject message) {
		if(!message->count(msgKeyAddress))
			(*message)[msgKeyAddress] = _address;

		if(!message->count(msgKeyRef))
			(*message)[msgKeyRef] = reference;

		if(!message->count(msgKeyType))
			(*message)[msgKeyType] = type;

		// Optional, validate messages with message type when debugging

		_outgoing->push_back(std::move(*message));

	}

	//------------------------------------------------------------------------------------------------------------------

	void addChild(const std::shared_ptr<PipeServiceNodeBase>& child) {
		auto& name = child->_address;
		if(_children.count(name))
			throw _T("There already is a child with the name \"") + name + _T("\"");

		_children[name] = child;
	}

	//------------------------------------------------------------------------------------------------------------------

	void removeChild(const tstring& name) {
		if(_children.count(name))
			_children.erase(name);
	}

	//------------------------------------------------------------------------------------------------------------------

	void addCommand(const tstring& name, const tstring& description, PipeJsonObject commandTypeDefinition, PipeCommandFunction handler) {
		if(_commands.count(name))
		   throw _T("Command already defined");
		
		// TODO: Assert that the definition has the right format!

		for(auto&& commandType : *_commandTypes) {
			if(commandType[msgFieldName].string_value() == name)
				throw _T("Message type already defined");
		}

		_commandTypes->push_back(PipeJsonObjectData {
			{ msgFieldName, name },
			{ msgFieldDescription, description },
			{ msgFieldStructure, *commandTypeDefinition }
		});

		_commands[name] = handler;
	}

	//------------------------------------------------------------------------------------------------------------------

	void addMessageType(const tstring& name, const tstring& description, PipeJsonObject messageTypeDefinition) {

		// TODO: Assert that the definition has the right format!

		for(auto&& messageType : *_messageTypes) {
			if(messageType[msgFieldName].string_value() == name)
				throw _T("Message type already defined");
		}

		_messageTypes->push_back(PipeJsonObjectData {
			{ msgFieldName, name },
			{ msgFieldDescription, description },
			{ msgFieldStructure, *messageTypeDefinition }
		});
	}

	//------------------------------------------------------------------------------------------------------------------

public:
	virtual void send(PipeJsonArray messages) {
		if(_preSendHookEnabled)
			_preSendHook(messages);

		for(auto&& messagesMember : *messages) {
			auto& message = messagesMember.object_items();

			if(message.empty()) {
				pushOutgoing(_T(""), msgTypeError, newObject({ { msgFieldDescription, _T("Message data is invalid or missing") } }));
				continue;
			}

			if(!message.count(msgKeyRef) || !message[msgKeyRef].is_string()) {
				pushOutgoing(_T(""), msgTypeError, newObject({ { msgFieldDescription, _T("Missing or invalid reference field") } }));
				continue;
			}

			if(!message.count(msgKeyAddress) || !message[msgKeyAddress].is_string()) {
				pushOutgoing(message[msgKeyRef].string_value(), msgTypeError, newObject({ { msgFieldDescription, _T("Missing or invalid address field") } }));
				return;
			}

			if(!message.count(msgKeyCommand) || !message[msgKeyCommand].is_string()) {
				pushOutgoing(message[msgKeyRef].string_value(), msgTypeError, newObject({ { msgFieldDescription, _T("Missing or invalid command field") } }));
				return;
			}

			auto& messageAddress = message[msgKeyAddress].string_value();

			if(messageAddress == _address) {
				auto messageCommand = message[msgKeyCommand].string_value();
				if(!_commands.count(messageCommand)) {
					pushOutgoing(message[msgKeyRef].string_value(), msgTypeError, newObject({ { msgFieldDescription, _T("Command not found") } }));
					return;
				}

				try {
					_commands[messageCommand](message);
				}
				catch(...) {
					pushOutgoing(message[msgKeyRef].string_value(), msgTypeError, newObject({
						{ msgFieldDescription, _T("There was an error executing the command") }
					}));
				}
			}
			else if(messageAddress.length() >= (_address.length() + 2) && messageAddress[_address.length()] == addressSeparator && _children.count(messageAddress)) {
				_children[messageAddress]->send(newArray({ message }));
			}
			else {
				pushOutgoing(message[msgKeyRef].string_value(), msgTypeError, newObject({ { msgFieldDescription, _T("Address not found") } }));
				return;
			}
		}
	}
	
	//------------------------------------------------------------------------------------------------------------------

	virtual PipeJsonArray receive() {
		PipeJsonArray messages = _outgoing;
		_outgoing = newArray();

		for(auto&& child : _children) {
			auto&& serviceOutgoing = child.second->receive();
			messages->insert(end(*messages), begin(*serviceOutgoing), end(*serviceOutgoing));
		}

		if(_postReceiveHookEnabled)
			_postReceiveHook(messages);

		return messages;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeJsonArray nodeChildren(const tstring& address) {
		PipeJsonArray children = newArray();
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

	virtual PipeJsonArray nodeCommandTypes(const tstring& address) {
		PipeJsonArray commandTypes = newArray();
		if(address == _address) {
			commandTypes = _commandTypes;
		}
		else if(address.length() >= (_address.length() + 2) && address[_address.length()] == addressSeparator && _children.count(address)) {
			commandTypes = _children[address]->nodeCommandTypes(address);
		}

		return commandTypes;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeJsonArray nodeMessageTypes(const tstring& address) {
		PipeJsonArray messageTypes = newArray();
		if(address == _address) {
			messageTypes = _messageTypes;
		}
		else if(address.length() >= (_address.length() + 2) && address[_address.length()] == addressSeparator && _children.count(address)) {
			messageTypes = _children[address]->nodeMessageTypes(address);
		}

		return messageTypes;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeJsonObject nodeInfo(const tstring& address) {
		PipeJsonObject info = newObject();
		if(address == _address) {
			(*info)[infoKeyAddress] = _address;
			(*info)[infoKeyType] = _type;
			(*info)[msgFieldDescription] = _description;
			(*info)[infoKeyProperties] = *_properties;
		}
		else if(address.length() >= (_address.length() + 2) && address[_address.length()] == addressSeparator && _children.count(address)) {
			info = _children[address]->nodeInfo(address);
		}

		return info;
	}
};
//======================================================================================================================

