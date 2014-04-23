//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInterface.h"

//======================================================================================================================

class PipeServiceNodeBase : public IPipeExtensionService {

public:
	const tstring _id;
	const tstring _path;
	const PipeJSON::object _settings;

protected:
	std::map<tstring, std::shared_ptr<PipeServiceNodeBase>> _children; 
	PipeJSON::array _outgoing;

// These have to be overwritten or completed by deriving class
protected:
	tstring _type;
	PipeJSON::array _messageTypes;

public:
	PipeServiceNodeBase(tstring id, tstring path, PipeJSON::object settings) : _id(id), _path(path), _settings(settings) {}
	virtual ~PipeServiceNodeBase() {}

public:
	virtual void send(PipeJSON::object& message) {
		if(!message.count(PipeMessageConstants::basicMsgKeyAddress)) {
			_outgoing.push_back(PipeJSON::object {
				{ PipeMessageConstants::basicMsgKeyAddress, _id },
				{ PipeMessageConstants::basicMsgKeyType, PipeMessageConstants::basicMsgTypeError },
				{ PipeMessageConstants::errorMsgKeyDescription, PipeMessageConstants::errorMsgDescriptionMissingAddress }
			});
			message.clear();
			return;
		}

		if(!message.count(PipeMessageConstants::basicMsgKeyType)) {
			_outgoing.push_back(PipeJSON::object {
				{ PipeMessageConstants::basicMsgKeyAddress, _id },
				{ PipeMessageConstants::basicMsgKeyType, PipeMessageConstants::basicMsgTypeError },
				{ PipeMessageConstants::errorMsgKeyDescription, PipeMessageConstants::errorMsgDescriptionMissingType }
			});
			message.clear();
			return;

		}
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
		// Return info from this node
		return {} ;
	}

};
//======================================================================================================================

