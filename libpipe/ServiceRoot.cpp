//======================================================================================================================

#include "CommonHeader.h"
#include "ServiceRoot.h"
using namespace std;

//======================================================================================================================

ServiceRoot::ServiceRoot(const tstring& address, const tstring& path, PipeObjectPtr settings) : PipeServiceNodeBase(_T("pipe"), _T("Pipe root node"), address, path, settings) {
	addCommand(
		_T("root_test"), 
		_T("A test command"),
		newObject(),
		[&](PipeObject& message) {
			pushOutgoing(message[msgKeyRef].string_value(), _T("root_test"), newObject({
				{ _T("response"), _T("ROOT") }
			}));
		}
	);

	auto&& childNode = make_shared<PipeServiceNodeBase>(_T("subtesttype"), _T("A sub test child"), _address + addressSeparator + _T("subtest"), path, settings);

	childNode->addCommand(
		_T("child_test"),
		_T("A test command"),
		newObject(),
		[&](PipeObject& message) {
			pushOutgoing(message[msgKeyRef].string_value(), _T("child_test"), newObject({
				{ _T("response"), _T("CHILD") }
			}));
		}
	);

	addChild(childNode);

	enablePreSendHook([&](PipeArrayPtr messages) {
		for(auto& message: *messages) {
			message[msgKeyRef].string_value() = _T("PRE_") + message[msgKeyRef].string_value();
		}

		// TODO: Process scripts
	});

	enablePostReceiveHook([&](PipeArrayPtr messages) {
		for(auto& message : *messages) {
			message[msgKeyRef].string_value() = message[msgKeyRef].string_value() + _T("_POST");
		}

		// TODO: Process scripts
	});

	// TODO: Add real nodes (scripting, services etc) and remove tests
}

//----------------------------------------------------------------------------------------------------------------------

ServiceRoot::~ServiceRoot() {

}

//======================================================================================================================
