//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInterface.h"

//======================================================================================================================

class PipeServiceNodeBase : public IPipeExtensionService {
public:
	const TCHAR addressSeparator = _T('.');

	const tstring msgKeyAddress = _T("address");
	const tstring msgKeyType = _T("type");
	const tstring msgKeyRef = _T("ref");

	const tstring msgTypeCommands = _T("commands");
	const tstring msgTypeMessages = _T("messages");
	const tstring msgTypeChildren = _T("children");
	const tstring msgTypeInfo = _T("info");
	const tstring msgTypeError = _T("error");

	const tstring infoKeyAddress = _T("address");
	const tstring infoKeyType = _T("type");
	const tstring infoKeyDescription = _T("description");
	const tstring infoKeyProperties = _T("properties");

	const tstring messageTypeKeyType = _T("type");
	const tstring messageTypeKeyDescription = _T("description");
	const tstring messageTypeKeyCommand = _T("command");
	const tstring messageTypeKeyStructure = _T("structure");

	const tstring errorMsgKeyDescription = _T("description");
	
	const tstring errorMsgDescriptionInvalidMessageData = _T("Message data is invalid or missing");
	const tstring errorMsgDescriptionInvalidAddress = _T("Missing or invalid address field");
	const tstring errorMsgDescriptionInvalidType = _T("Missing or invalid type field");
	const tstring errorMsgDescriptionInvalidReference = _T("Missing or invalid reference field");
	const tstring errorMsgDescriptionUnknownAddress = _T("Address not found");
	const tstring errorMsgDescriptionUnknownCommand = _T("Command not found");

public:
	const tstring _type;
	const tstring _description;
	const tstring _address;
	const tstring _path;
	const PipeJSON::object _settings;

private:
	std::map<tstring, std::shared_ptr<PipeServiceNodeBase>> _children; 
	PipeJSON::array _outgoing;
	std::map<tstring, std::function<void(PipeJSON::object&)> > _commands;
	PipeJSON::array _messageTypes;
	PipeJSON::object _properties;

	bool _preSendHookEnabled = false;
	std::function<void(PipeJSON::array&)> _preSendHook;

	bool _postReceiveHookEnabled = false;
	std::function<void(PipeJSON::array&)> _postReceiveHook;

public:
	PipeServiceNodeBase(const tstring& type, const tstring& description, const tstring& address, const tstring& path, PipeJSON::object& settings) 
		: _type(type)
		, _description(description)
		, _address(address) 
		, _path(path)
		, _settings(settings) {

		// TODO: Add default commands and remove test

		addCommand(
			_T("base_test"),
			_T("A test command"),
			PipeJSON::object {
			},
			[&](PipeJSON::object& message) {
				_outgoing.push_back(PipeJSON::object {
					{ msgKeyAddress, _address },
					{ msgKeyRef, message[msgKeyRef] },
					{ _T("response"), _T("BASE") }
				});
			}
		);
	}

	virtual ~PipeServiceNodeBase() {}

public:
	void enablePreSendHook(std::function<void(PipeJSON::array&)> hook) {
		_preSendHook = hook;
		_preSendHookEnabled = true;
	}

	void disablePreSendHook() {
		_preSendHookEnabled = false;
	}

	void enablePostReceiveHook(std::function<void(PipeJSON::array&)> hook) {
		_postReceiveHook = hook;
		_postReceiveHookEnabled = true;
	}

	void disablePostReceiveHook() {
		_postReceiveHookEnabled = false;
	}

	void pushOutgoing(const tstring& reference, const tstring& type, PipeJSON::object& messageData) {
		if(!messageData.count(msgKeyAddress))
			messageData[msgKeyAddress] = _address;

		if(!messageData.count(msgKeyRef))
			messageData[msgKeyRef] = reference;

		if(!messageData.count(msgKeyType))
			messageData[msgKeyType] = type;

		// TODO: Optional, validate messages with message type when debugging

		_outgoing.push_back(messageData);

	}

	void addChild(const std::shared_ptr<PipeServiceNodeBase>& child) {
		auto& name = child->_address;
		if(_children.count(name))
			throw _T("There already is a child with the name \"") + name + _T("\"");

		_children[name] = child;
	}

	void removeChild(const tstring& name) {
		if(_children.count(name))
			_children.erase(name);
	}

	void addCommand(const tstring& name, const tstring& description, PipeJSON::object& structure, const std::function<void(PipeJSON::object&)>& handler) {
		if(_commands.count(name))
		   throw _T("Command already defined");

		addMessageType(name, description, true, structure);
		_commands[name] = handler;
	}

	void addMessageType(const tstring& type, const tstring& description, const bool& isCommand, PipeJSON::object& structure) {

		// TODO: Assert that the structure has the right format!

		for(auto&& messageType : _messageTypes) {
			if(messageType[messageTypeKeyType].string_value() == messageType.string_value())
				throw _T("Message type already defined");
		}

		_messageTypes.push_back(PipeJSON::object {
			{ messageTypeKeyType, type },
			{ messageTypeKeyDescription, description },
			{ messageTypeKeyCommand, isCommand },
			{ messageTypeKeyStructure, structure }
		});
	}

public:
	virtual void send(PipeJSON::array& messages) {
		if(_preSendHookEnabled)
			_preSendHook(messages);

		for(auto&& messagesMember : messages) {
			auto message = messagesMember.object_items();

			if(message.empty()) {
				pushOutgoing(_T(""), msgTypeError, PipeJSON::object { { errorMsgKeyDescription, errorMsgDescriptionInvalidMessageData } });
				continue;
			}

			if(!message.count(msgKeyRef) || !message[msgKeyRef].is_string()) {
				pushOutgoing(_T(""), msgTypeError, PipeJSON::object { { errorMsgKeyDescription, errorMsgDescriptionInvalidReference } });
				continue;
			}

			if(!message.count(msgKeyAddress) || !message[msgKeyAddress].is_string()) {
				pushOutgoing(message[msgKeyRef].string_value(), msgTypeError, PipeJSON::object { { errorMsgKeyDescription, errorMsgDescriptionInvalidAddress } });
				return;
			}

			if(!message.count(msgKeyType) || !message[msgKeyType].is_string()) {
				pushOutgoing(message[msgKeyRef].string_value(), msgTypeError, PipeJSON::object { { errorMsgKeyDescription, errorMsgDescriptionInvalidType } });
				return;
			}

			auto&& messageAddress = message[msgKeyAddress].string_value();

			if(messageAddress == _address) {
				auto&& messageCommand = message[msgKeyType].string_value();
				if(!_commands.count(messageCommand)) {
					pushOutgoing(message[msgKeyRef].string_value(), msgTypeError, PipeJSON::object { { errorMsgKeyDescription, errorMsgDescriptionUnknownCommand } });
					return;
				}

				_commands[messageCommand](message);
			}
			else if(messageAddress.length() >= (_address.length() + 2) && messageAddress[_address.length()] == addressSeparator && _children.count(messageAddress)) {
				_children[messageAddress]->send(PipeJSON::array {message});
			}
			else {
				pushOutgoing(message[msgKeyRef].string_value(), msgTypeError, PipeJSON::object { { errorMsgKeyDescription, errorMsgDescriptionUnknownAddress } });
				return;
			}
		}
	}
	
	virtual PipeJSON::array receive() {
		PipeJSON::array messages = move(_outgoing);
		_outgoing = {};

		for(auto&& child : _children) {
			auto&& serviceOutgoing = child.second->receive();
			messages.insert(end(messages), begin(serviceOutgoing), end(serviceOutgoing));
		}

		if(_postReceiveHookEnabled)
			_postReceiveHook(messages);

		return messages;
	}

	virtual PipeJSON::array nodeChildren(tstring address) {
		PipeJSON::array children;
		
		for(auto&& child : _children) {
			children.push_back(child.first);
		}

		return children;
	}

	virtual PipeJSON::array nodeMessageTypes(tstring address) {
		return _messageTypes;
	}

	virtual PipeJSON::object nodeInfo(tstring address) {
		return {
			{ infoKeyAddress, _address },
			{ infoKeyType, _type },
			{ infoKeyDescription, _description },
			{ infoKeyProperties, _properties }
		};
	}
};
//======================================================================================================================

