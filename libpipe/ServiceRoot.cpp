//======================================================================================================================

#include "CommonHeader.h"
#include "ServiceRoot.h"
using namespace std;

//======================================================================================================================

ServiceRoot::ServiceRoot(map<tstring, tstring> settings) : PipeServiceBase(settings) {

}

//----------------------------------------------------------------------------------------------------------------------

ServiceRoot::~ServiceRoot() {

}

//----------------------------------------------------------------------------------------------------------------------

void ServiceRoot::send(const LibPipeMessage& message) {

	// TODO: Check for hooks

	__super::send(message);

	auto lenId = _id.length();

	if(message.address.empty()) {
		vector<tstring> parameters = {
			_T("Missing address"),
			_T("Syntax is: address command [<parameter>...]")
		};
		_outgoing.push_back({ _id, _T("error"), parameters });
		return;
	}

	if(message.type.empty()) {
		vector<tstring> parameters = {
			_T("Missing command"),
			_T("Syntax is: address command [<parameter>...]")
		};
		_outgoing.push_back({ _id, _T("error"), parameters });
		return;
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
			return;
		}

		_services[target]->send({ message });
	}
	else {
		vector<tstring> parameters = {
			_T("Invalid Address"),
			_T("Start from \"") + _id + _T("\" and use the children command to find available addresses")
		};
		_outgoing.push_back({ _id, _T("error"), parameters });
		return;
	}
}

//----------------------------------------------------------------------------------------------------------------------

std::vector<LibPipeMessage> ServiceRoot::receive() {
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

std::vector<tstring> ServiceRoot::children(tstring address) {
	return {};
}

//----------------------------------------------------------------------------------------------------------------------

PipeExtensionServiceNodeInfo ServiceRoot::info(tstring address) {
	return {};
}

//----------------------------------------------------------------------------------------------------------------------

void ServiceRoot::handleCommand(const LibPipeMessage& message) {

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
