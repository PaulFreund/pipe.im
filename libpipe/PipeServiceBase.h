//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInterface.h"

//======================================================================================================================

class PipeServiceBase : public IPipeExtensionService {
public:
	const tstring basicCommandCommands	= _T("commands");
	const tstring basicCommandMessages	= _T("messages");
	const tstring basicCommandChildren	= _T("children");
	const tstring basicCommandInfo		= _T("info");

public:
	const tstring _id;
	const tstring _path;
	const std::map<tstring, tstring> _settings;

protected:
	std::vector<LibPipeMessage> _outgoing;

public:
	PipeServiceBase(tstring id, tstring path, std::map<tstring, tstring> settings) : _id(id), _path(path), _settings(settings) {}
	virtual ~PipeServiceBase() {}

public:
	virtual void send(const LibPipeMessage& message) {
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
	}

	virtual std::vector<LibPipeMessage> receive() = 0;

	virtual std::vector<tstring> children(tstring address) = 0;
	virtual PipeExtensionServiceNodeInfo info(tstring address) = 0;

protected:
	inline bool isBasicCommand(const tstring& command) {
		if(command == basicCommandCommands || command == basicCommandMessages || command == basicCommandChildren || command == basicCommandInfo)
			return true;

		return false;
	}
};

//======================================================================================================================
