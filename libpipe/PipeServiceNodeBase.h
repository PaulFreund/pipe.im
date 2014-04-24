//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInterface.h"

//======================================================================================================================

class PipeServiceNodeBase : public IPipeExtensionService {

public:
	const tstring _type;
	const tstring _description;
	const tstring _address;
	const tstring _path;
	const PipeJSON::object _settings;

protected:
	std::map<tstring, std::shared_ptr<PipeServiceNodeBase>> _children; 
	PipeJSON::array _outgoing;
	std::map<tstring, std::function<void(PipeJSON::object&)> > _commands;
	PipeJSON::array _messageTypes;
	PipeJSON::object _properties;

public:
	PipeServiceNodeBase(tstring type, tstring description, tstring address, tstring path, PipeJSON::object settings) 
		: _type(type)
		, _description(description)
		, _address(address) 
		, _path(path)
		, _settings(settings) 
	{
		// Add default commands
	}

	virtual ~PipeServiceNodeBase() {}

public:
	void addCommand(tstring name, PipeJSON::object& messageType, std::function<void(PipeJSON::object&)> handler) {
		_commands[name] = handler;
		addMessageType(messageType);
	}

	void addMessageType(PipeJSON::object messageType) {
		_messageTypes.push_back(messageType);
	}

public:
	virtual void send(PipeJSON::object& message) {
		if(!message.count(PipeConstants::basicMsgKeyReference) || !message[PipeConstants::basicMsgKeyReference].is_string()) {
			pushError(PipeConstants::errorMsgDescriptionInvalidReference);
			return;
		}

		if(!message.count(PipeConstants::basicMsgKeyAddress) || !message[PipeConstants::basicMsgKeyAddress].is_string()) {
			pushError(PipeConstants::errorMsgDescriptionInvalidAddress, message[PipeConstants::basicMsgKeyReference].string_value());
			return;
		}

		if(!message.count(PipeConstants::basicMsgKeyType) || !message[PipeConstants::basicMsgKeyType].is_string()) {
			pushError(PipeConstants::errorMsgDescriptionInvalidType, message[PipeConstants::basicMsgKeyReference].string_value());
			return;
		}

		auto&& messageAddress = message[PipeConstants::basicMsgKeyAddress].string_value();

		if(messageAddress == _address) {
			auto&& messageCommand = message[PipeConstants::basicMsgKeyType].string_value();
			if(!_commands.count(messageCommand)) {
				pushError(PipeConstants::errorMsgDescriptionUnknownCommand, message[PipeConstants::basicMsgKeyReference].string_value());
				return;
			}

			_commands[messageCommand](message);
		}
		else if(messageAddress.length() >= (_address.length() + 2) && messageAddress[_address.length()] == PAS && _children.count(messageAddress)) {
			_children[messageAddress]->send(message);
		}
		else {
			pushError(PipeConstants::errorMsgDescriptionUnknownAddress, message[PipeConstants::basicMsgKeyReference].string_value());
			return;
		}
	}
	
	virtual PipeJSON::array receive() {
		PipeJSON::array messages = move(_outgoing);
		_outgoing = {};

		for(auto&& child : _children) {
			auto&& serviceOutgoing = child.second->receive();
			messages.insert(end(messages), begin(serviceOutgoing), end(serviceOutgoing));
		}

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
			{ PipeConstants::basicInfoKeyAddress, _address },
			{ PipeConstants::basicInfoKeyType, _type },
			{ PipeConstants::basicInfoKeyDescription, _description },
			{ PipeConstants::basicInfoKeyProperties, _properties }
		};
	}

private:
	void pushError(const tstring& description, tstring reference = _T("")) {
		_outgoing.push_back(PipeJSON::object {
			{ PipeConstants::basicMsgKeyAddress, _address },
			{ PipeConstants::basicMsgKeyReference, reference },
			{ PipeConstants::basicMsgKeyType, PipeConstants::basicMsgTypeError },
			{ PipeConstants::errorMsgKeyDescription, description }
		});
	}
};
//======================================================================================================================

