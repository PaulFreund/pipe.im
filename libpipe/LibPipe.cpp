//======================================================================================================================

#include "CommonHeader.h"
#include "LibPipe.h"

#include "BaseServiceService.h"
#include "BaseServiceScript.h"
#include "BaseServiceConfig.h"

using namespace std;

//======================================================================================================================

std::vector<LibPipe> LibPipe::Instances;
std::vector<PipeExtensionInstance> LibPipe::Extensions;

//======================================================================================================================

LibPipe::LibPipe(tstring path, vector<tstring> serviceTypes) : _path(path), _serviceTypes(serviceTypes) {
	map<tstring, tstring> settings;
	settings[_T("path")] = _path;

	_services[_T("script")] = make_shared<BaseServiceScript>(settings);
	_services[_T("config")] = make_shared<BaseServiceConfig>(settings);
	
	settings[_T("serviceTypes")] = timplode(_serviceTypes, _T(','));
	_services[_T("service")] = make_shared<BaseServiceService>(settings);
}

//----------------------------------------------------------------------------------------------------------------------

LibPipe::~LibPipe() {

}

//----------------------------------------------------------------------------------------------------------------------

void LibPipe::send(const vector<LibPipeMessage>& messages) {

	// TODO: Check for hooks

	auto lenId = _id.length();
	for(auto&& message : messages) {
		if(message.address.empty()) {
			vector<tstring> parameters = {
				_T("Missing address"),
				_T("Syntax is: address command [<parameter>...]")
			};
			_outgoing.push_back({ _id, _T("error"), parameters });
			continue;
		}

		if(message.type.empty()) {
			vector<tstring> parameters = { 
				_T("Missing command"),
				_T("Syntax is: address command [<parameter>...]")
			};
			_outgoing.push_back({ _id, _T("error"), parameters });
			continue;
		}

		// This is the destination
		if(message.address == _id) {
			handleCommand(message);
		}
		// The address can be dispatched
		else if(message.address.length() >= (lenId + 2) && message.address[lenId] == PAS) {

			auto second = message.address.find(PAS, lenId + 1);
			if(second == -1) { second = message.address.length(); }
			auto target = message.address.substr(lenId + 1, second);

			if(_services.find(target) == end(_services)) {
				vector<tstring> parameters = { 
					_T("Address not available") 
					_T("Start from \"") + _id + _T("\" and use the children command to find available addresses")
				};
				_outgoing.push_back({ _id, _T("error"), parameters });
				continue;
			}
			
			_services[target]->send({ message });
		}
		else {
			vector<tstring> parameters = { 
				_T("Invalid Address"), 
				_T("Start from \"") + _id + _T("\" and use the children command to find available addresses") 
			};
			_outgoing.push_back({ _id, _T("error"), parameters });
			continue;
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------

vector<LibPipeMessage> LibPipe::receive() {
	vector<LibPipeMessage> messages = _outgoing;
	_outgoing.clear();

	for(auto&& service : _services) {
		auto&& serviceOutgoing = service.second->receive();
		messages.insert(end(messages), begin(serviceOutgoing), end(serviceOutgoing));
	}

	// TODO: Check for hooks

	return messages;
}

//----------------------------------------------------------------------------------------------------------------------

void LibPipe::handleCommand(const LibPipeMessage& message) {

	if(message.type == _T("commands")) {
		// Commands
		// status
		// about
		// messages
		// children
	}

	else if(message.type == _T("about")) {

	}

	else if(message.type == _T("messages")) {
		// error
		// children
		// status
		// messages
	}
	else if(message.type == _T("children")) {
		tstring children;
		size_t idxServices = 0;
		size_t cntServices = _services.size();
		for(auto&& service : _services) {
			children.append(service.first);
			if(idxServices < (cntServices - 1)) {
				children += _T(',');
			}
			idxServices++;
		}

		vector<tstring> parameters = { children };
		_outgoing.push_back({ _id, _T("children"), parameters });
	}
	else {
		vector<tstring> parameters = { 
			_T("Unknown command"),
			_T("Use: ") + _id + _T(" commands to get all available commands")
		};
		_outgoing.push_back({ _id, _T("error"), parameters });
	}
}

//======================================================================================================================

/*
	CMD: about 
	MSG: about <id> <type> 

	CMD: children
	MSG: children <id list>

	CMD: commands
	MSG: commands <command list>

	// node types
		// node type commands
		// node type messages



*/