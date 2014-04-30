//======================================================================================================================

#include "CommonHeader.h"
#include "ServiceRoot.h"
using namespace std;

//======================================================================================================================

ServiceRoot::ServiceRoot(const tstring& address, const tstring& path, PipeObjectPtr settings) : PipeServiceNodeBase(_T("pipe"), _T("Pipe root node"), address, path, settings) {
	//------------------------------------------------------------------------------------------------------------------
	PipeObjectPtr schemaCmdTest = newObject();
	schemaAddValue(*schemaCmdTest, msgKeyData, SchemaString, _T("Message to be changed"));
	
	addCommand(_T("test"), _T("A test command"), schemaCmdTest, [&](PipeObject& message) {
		if(message.count(msgKeyData) && message[msgKeyData].is_string()) {
			auto msg = message[msgKeyData].string_value();
			TCHAR tmp = msg[0];
			msg[0] = msg[msg.length()];
			msg[msg.length()] = tmp;

			pushOutgoing(message[msgKeyRef].string_value(), _T("test"), msg);
		}
		else {
			pushOutgoing(message[msgKeyRef].string_value(), _T("error"), _T("Invalid test request"));
		}
	});

	PipeObjectPtr schemaMsgTest = newObject();
	schemaAddValue(*schemaMsgTest, msgKeyData, SchemaString, _T("Changed message"));

	addMessageType(_T("test"), _T("Test command response"), schemaMsgTest);

	//------------------------------------------------------------------------------------------------------------------
	auto&& childNode = make_shared<PipeServiceNodeBase>(_T("subtesttype"), _T("A sub test child"), _address + addressSeparator + _T("subtest"), path, settings);

	childNode->addCommand(
		_T("child_test"),
		_T("A test command"),
		newObject(),
		[&](PipeObject& message) {
			pushOutgoing(message[msgKeyRef].string_value(), _T("child_test"), *newObject({
				{ _T("response"), _T("CHILD") }
			}));
		}
	);

	addChild(childNode);

	enablePreSendHook([&](PipeArrayPtr messages) {
		//for(auto& message: *messages) {
		//	message[msgKeyRef].string_value() = _T("PRE_") + message[msgKeyRef].string_value();
		//}

		// TODO: Process scripts
	});

	enablePostReceiveHook([&](PipeArrayPtr messages) {
		//for(auto& message : *messages) {
		//	message[msgKeyRef].string_value() = message[msgKeyRef].string_value() + _T("_POST");
		//}

		// TODO: Process scripts
	});

	// TODO: Add real nodes (scripting, services etc) and remove tests
}

//----------------------------------------------------------------------------------------------------------------------

ServiceRoot::~ServiceRoot() {

}

//======================================================================================================================
