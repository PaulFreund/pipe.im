//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInterface.h"

//======================================================================================================================

class PipeServiceNodeBase : public IPipeExtensionService {

public:
	const tstring _address;
	const tstring _path;
	const PipeJSON::object _settings;

protected:
	std::map<tstring, std::shared_ptr<PipeServiceNodeBase>> _children; 
	PipeJSON::array _outgoing;

// These have to be overwritten or completed by deriving class
protected:
	tstring _type;
	tstring _description;
	PipeJSON::object _metaInfo;
	PipeJSON::array _messageTypes;

public:
	PipeServiceNodeBase(tstring address, tstring path, PipeJSON::object settings) : _address(address), _path(path), _settings(settings) {}
	virtual ~PipeServiceNodeBase() {}

public:
	virtual void send(PipeJSON::object& message) {
		if(!message.count(PipeMessageConstants::basicMsgKeyAddress)) {
			_outgoing.push_back(PipeJSON::object {
				{ PipeMessageConstants::basicMsgKeyAddress, _address },
				{ PipeMessageConstants::basicMsgKeyType, PipeMessageConstants::basicMsgTypeError },
				{ PipeMessageConstants::errorMsgKeyDescription, PipeMessageConstants::errorMsgDescriptionMissingAddress }
			});
			message.clear();
			return;
		}

		if(!message.count(PipeMessageConstants::basicMsgKeyType)) {
			_outgoing.push_back(PipeJSON::object {
				{ PipeMessageConstants::basicMsgKeyAddress, _address },
				{ PipeMessageConstants::basicMsgKeyType, PipeMessageConstants::basicMsgTypeError },
				{ PipeMessageConstants::errorMsgKeyDescription, PipeMessageConstants::errorMsgDescriptionMissingType }
			});
			message.clear();
			return;

		}

		// Check reference?

		/* TODO
		if(message.type == basicCommandCommands) {

		}

		else if(message.type == basicCommandInfo) {

		}

		else if(message.type == basicCommandMessages) {

		}
		else if(message.type == basicCommandChildren) {
		auto&& childNodes = children(message.address);
		tstring childNodeList;

		for(size_t i = 0, c = childNodes.size(); i < c; i++) {
		childNodeList.append(childNodes[i]);
		if(i < (c - 1)) {
		childNodeList += _T(',');
		}
		}

		std::vector<tstring> parameters = { childNodeList };
		_outgoing.push_back({ _id, _T("children"), parameters });
		}
		else {
		_outgoing.push_back({ _id, _T("error"), std::vector<tstring> { _T("Unknown command"), _T("Use: ") + _id + _T(" commands to get all available commands") } });
		}
		*/


		/*
		auto lenId = _id.length();

		if(message.address.empty()) {
		_outgoing.push_back({ _id, _T("error"), vector<tstring>{_T("Missing address"), _T("Syntax is: address command [<parameter>...]")} });
		return;
		}

		if(message.type.empty()) {
		_outgoing.push_back({ _id, _T("error"), vector<tstring> { _T("Missing command"), _T("Syntax is: address command [<parameter>...]") } });
		return;
		}

		// This is the destination
		if(message.address == _id) {
		}
		// The address can be dispatched
		else if(message.address.length() >= (lenId + 2) && message.address[lenId] == PAS) {

		auto second = message.address.find(PAS, lenId + 1);
		if(second == -1) { second = message.address.length(); }
		auto target = message.address.substr(lenId + 1, second);

		if(_services.find(target) == end(_services)) {
		_outgoing.push_back({ _id, _T("error"), vector<tstring> { _T("Address not available"), _T("Start from \"") + _id + _T("\" and use the children command to find available addresses") } });
		return;
		}

		_services[target]->send(message);
		}
		else {
		_outgoing.push_back({ _id, _T("error"), vector<tstring> { _T("Invalid Address"), _T("Start from \"") + _id + _T("\" and use the children command to find available addresses") } });
		return;
		}
		*/
	}


public:
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
			{ PipeMessageConstants::basicInfoKeyAddress, _address },
			{ PipeMessageConstants::basicInfoKeyType, _type },
			{ PipeMessageConstants::basicInfoKeyDescription, _description },
			{ PipeMessageConstants::basicInfoKeyMeta, _metaInfo }
		};
	}

};
//======================================================================================================================

