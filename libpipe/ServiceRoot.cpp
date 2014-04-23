//======================================================================================================================

#include "CommonHeader.h"
#include "ServiceRoot.h"
using namespace std;

//======================================================================================================================

ServiceRoot::ServiceRoot(tstring address, tstring path, PipeJSON::object settings) : PipeServiceNodeBase(address, path, settings) {

}

//----------------------------------------------------------------------------------------------------------------------

ServiceRoot::~ServiceRoot() {

}

//----------------------------------------------------------------------------------------------------------------------

void ServiceRoot::send(PipeJSON::object& message) {

	PipeServiceNodeBase::send(message);
	if(message.empty())
		return;
}

//----------------------------------------------------------------------------------------------------------------------

PipeJSON::array ServiceRoot::receive() {
	PipeJSON::array messages = move(_outgoing);
	_outgoing = {};

	for(auto&& child : _children) {
		auto&& serviceOutgoing = child.second->receive();
		messages.insert(end(messages), begin(serviceOutgoing), end(serviceOutgoing));
	}

	// TODO: Check for hooks

	return messages;
}

//======================================================================================================================
