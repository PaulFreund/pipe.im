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
			// Commands
			// status
			// about
			// messages
			// children
		}

		else if(message.type == basicCommandInfo) {  // former about

		}

		else if(message.type == basicCommandMessages) {
			// error
			// children
			// status
			// messages
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
			std::vector<tstring> parameters = {
				_T("Unknown command"),
				_T("Use: ") + _id + _T(" commands to get all available commands")
			};
			_outgoing.push_back({ _id, _T("error"), parameters });
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

/*
Was jeder service gleich machen muss:
- Die basic commands handlen, das bedeutet send zuerst hooken
- info ( bekommt infos aus info funktion )
- commands (bekommt infos aus info funktion)
- messages (bekommt infos aus info funktion)
- children (bekommt infos aus children funktion
- id, settings und path bekommen das bedeutet immer diese als construtcor fordern
- Bei receive messages in outgoing weitergeben

*/