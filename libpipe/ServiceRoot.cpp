//======================================================================================================================

#include "CommonHeader.h"
#include "ServiceRoot.h"
using namespace std;

//======================================================================================================================

ServiceRoot::ServiceRoot(tstring address, tstring path, PipeJSON::object settings) : PipeServiceNodeBase(_T("pipe"), _T("Pipe root node"), address, path, settings) {
	// TODO: Add command for testing
	// TODO: Add subnode for testing
	// TODO: Add real nodes (scripting, services etc)
}

//----------------------------------------------------------------------------------------------------------------------

ServiceRoot::~ServiceRoot() {

}

//----------------------------------------------------------------------------------------------------------------------

void ServiceRoot::send(PipeJSON::object& message) {

	// TODO: Process scripts

	PipeServiceNodeBase::send(message);
}

//----------------------------------------------------------------------------------------------------------------------

PipeJSON::array ServiceRoot::receive() {
	PipeJSON::array messages = move(_outgoing);
	_outgoing = {};

	for(auto&& child : _children) {
		auto&& serviceOutgoing = child.second->receive();
		messages.insert(end(messages), begin(serviceOutgoing), end(serviceOutgoing));
	}

	// TODO: Process scripts

	return messages;
}

//======================================================================================================================
