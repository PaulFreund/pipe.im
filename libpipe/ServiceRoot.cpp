//======================================================================================================================

#include "CommonHeader.h"
#include "ServiceRoot.h"
using namespace std;

//======================================================================================================================

ServiceRoot::ServiceRoot(tstring id, tstring path, PipeJSON::object settings) : PipeServiceBase(id, path, settings) {

}

//----------------------------------------------------------------------------------------------------------------------

ServiceRoot::~ServiceRoot() {

}

//----------------------------------------------------------------------------------------------------------------------

void ServiceRoot::send(PipeJSON::object& message) {

	PipeServiceBase::send(message);
	if(message.empty())
		return;

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

//----------------------------------------------------------------------------------------------------------------------

PipeJSON::array ServiceRoot::receive() {
	PipeJSON::array messages = move(_outgoing);
	_outgoing = {};

	for(auto&& service : _services) {
		auto&& serviceOutgoing = service.second->receive();
		messages.insert(end(messages), begin(serviceOutgoing), end(serviceOutgoing));
	}

	// TODO: Check for hooks

	return messages;
}

//----------------------------------------------------------------------------------------------------------------------

PipeJSON::array ServiceRoot::nodeChildren(tstring address) {
	return {};
}

//----------------------------------------------------------------------------------------------------------------------

PipeJSON::array ServiceRoot::nodeMessageTypes(tstring address) {
	return {};
}
//----------------------------------------------------------------------------------------------------------------------

PipeJSON::object ServiceRoot::nodeInfo(tstring address) {
	return {};
}

//======================================================================================================================
