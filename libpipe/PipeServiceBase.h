//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInterface.h"

//======================================================================================================================

class PipeServiceBase : public IPipeExtensionService {

public:
	const tstring _id;
	const tstring _path;
	const PipeJSON::object _settings;

protected:
	PipeJSON::array _outgoing;

public:
	PipeServiceBase(tstring id, tstring path, PipeJSON::object settings) : _id(id), _path(path), _settings(settings) {}
	virtual ~PipeServiceBase() {}

public:
	virtual void send(PipeJSON::object& message) {
		if(!message.count(PipeMessageConstants::msgKeyAddress)) {
			_outgoing.push_back(PipeJSON::object {
				{ PipeMessageConstants::msgKeyAddress, _id },
				{ PipeMessageConstants::msgKeyType, PipeMessageConstants::msgTypeBasicError }
			});
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
	virtual PipeJSON::array receive() = 0;

	virtual PipeJSON::array nodeChildren(tstring address) = 0;
	virtual PipeJSON::array nodeMessageTypes(tstring address) = 0;
	virtual PipeJSON::object nodeInfo(tstring address) = 0;

};
//======================================================================================================================

