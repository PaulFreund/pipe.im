//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInterface.h"

//======================================================================================================================

class PipeServiceBase : public IPipeExtensionService {
public:
	const tstring basicCommandCommands = _T("commands");
	const tstring basicCommandMessages = _T("messages");
	const tstring basicCommandChildren = _T("children");
	const tstring basicCommandInfo = _T("info");

public:
	const tstring _id;
	const tstring _path;
	const tstring _settings;

protected:
	tstring _outgoing;

public:
	PipeServiceBase(tstring id, tstring path, tstring settings) : _id(id), _path(path), _settings(settings) {}
	virtual ~PipeServiceBase() {}

public:
	virtual void send(const tstring& message) {
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

	virtual tstring receive() = 0;

	virtual tstring nodeChildren(tstring address) = 0;
	virtual tstring nodeMessageTypes(tstring address) = 0;
	virtual tstring nodeInfo(tstring address) = 0;

};
//======================================================================================================================

