//======================================================================================================================

#include "CommonHeader.h"
#include "ServiceRoot.h"
using namespace std;

//======================================================================================================================

ServiceRoot::ServiceRoot(tstring id, tstring path, tstring settings) : PipeServiceBase(id, path, settings) {

}

//----------------------------------------------------------------------------------------------------------------------

ServiceRoot::~ServiceRoot() {

}

//----------------------------------------------------------------------------------------------------------------------

void ServiceRoot::send(const tstring& message) {

	// TODO: Check for hooks
	/* TODO
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
	*/
	__super::send(message);

}

//----------------------------------------------------------------------------------------------------------------------

tstring ServiceRoot::receive() {
	/* TODO
	vector<LibPipeMessage> messages = move(_outgoing);
	_outgoing.clear();

	for(auto&& service : _services) {
		auto&& serviceOutgoing = service.second->receive();
		messages.insert(end(messages), begin(serviceOutgoing), end(serviceOutgoing));
	}

	// TODO: Check for hooks

	return messages;
	*/
	return _T("");
}

//----------------------------------------------------------------------------------------------------------------------

tstring ServiceRoot::nodeChildren(tstring address) {
	return _T("");
}

//----------------------------------------------------------------------------------------------------------------------

tstring ServiceRoot::nodeMessageTypes(tstring address) {
	return _T("");
}
//----------------------------------------------------------------------------------------------------------------------

tstring ServiceRoot::nodeInfo(tstring address) {
	return _T("");
}

//======================================================================================================================
