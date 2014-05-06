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
			msg[0] = msg[msg.length()-1];
			msg[msg.length()-1] = tmp;

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
	PipeObjectPtr schemaCmdTest2 = newObject();
	auto& schemaCmdTest2Data = schemaAddObject(*schemaCmdTest2, msgKeyData, _T("Message data to changed"));
	schemaAddValue(schemaCmdTest2Data, _T("key1"), SchemaString, _T("description 1 text"));
	schemaAddValue(schemaCmdTest2Data, _T("key2"), SchemaString, _T("description 2 text"), true);

	addCommand(_T("test2"), _T("A test command"), schemaCmdTest2, [&](PipeObject& message) {
		if(message.count(msgKeyData) && message[msgKeyData].is_object()) {
			auto msg1 = message[msgKeyData][_T("key1")].string_value();
			TCHAR tmp1 = msg1[0];
			msg1[0] = msg1[msg1.length()-1];
			msg1[msg1.length()-1] = tmp1;

			if(message[msgKeyData].object_items().count(_T("key2"))) {
				auto msg2 = message[msgKeyData][_T("key2")].string_value();
				TCHAR tmp2 = msg2[0];
				msg2[0] = msg2[msg2.length() - 1];
				msg2[msg2.length() - 1] = tmp2;

				pushOutgoing(message[msgKeyRef].string_value(), _T("test2"), PipeObject { { _T("key1"), msg1 }, { _T("key2"), msg2 } });
			}
			else {
				pushOutgoing(message[msgKeyRef].string_value(), _T("test2"), PipeObject { { _T("key1"), msg1 } });
			}
		}
		else {
			pushOutgoing(message[msgKeyRef].string_value(), _T("error"), _T("Invalid test2 request"));
		}
	});

	PipeObjectPtr schemaMsgTest2 = newObject();
	auto& schemaMsgTest2Data = schemaAddObject(*schemaMsgTest2, msgKeyData, _T("Message data to changed"));
	schemaAddValue(schemaMsgTest2Data, _T("key1data"), SchemaString, _T("description data 1 text"));
	schemaAddValue(schemaMsgTest2Data, _T("key2data"), SchemaString, _T("description data 2 text"), true);

	addMessageType(_T("test2"), _T("Test command response data"), schemaMsgTest2);

	//------------------------------------------------------------------------------------------------------------------
	PipeObjectPtr schemaCmdTest3 = newObject();
	/*
		Tested:
		optional object with optional value


		Untested:

			array
				object
					array
			object
				array
					object
			array
				array
					object
			array
				optional
					object
	*/

	auto& schemaCmdTest3Data = schemaAddObject(*schemaCmdTest3, msgKeyData, _T("BASE"));

	//schemaAddValueArray(schemaCmdTest3Data, _T("key3"), _T("Array of strings"), SchemaString, _T("description 2 text"));


	auto& objarra = schemaAddObjectArray(schemaCmdTest3Data, _T("OBJARR"), _T("OBJARRDESC"), _T("OBJITEMDESC"));
	schemaAddValue(objarra, _T("OBJFIELD"), SchemaString, _T("OBJFIELDDESC"), false);


	//schemaAddValue(schemaCmdTest3Data, _T("key1"), SchemaString, _T("description 1 text"), true);
	//schemaAddValue(schemaCmdTest3Data, _T("key2"), SchemaString, _T("description 2 text"), true);
	//schemaAddValue(objarra, _T("keyarr1"), SchemaString, _T("description 2 text"), true);
	//schemaAddValueArray(objarra, _T("key3"), _T("Array of strings"), SchemaNumber, _T("description 2 text"), true);

	addCommand(_T("test3"), _T("A test command"), schemaCmdTest3, [&](PipeObject& message) {
		pushOutgoing(message[msgKeyRef].string_value(), _T("test3"), PipeObject { { _T("keydata"), message[msgKeyData].dump() } });
	});

	PipeObjectPtr schemaMsgTest3 = newObject();
	auto& schemaMsgTest3Data = schemaAddObject(*schemaMsgTest3, msgKeyData, _T("Message data to output"));
	schemaAddValue(schemaMsgTest3Data, _T("keydata"), SchemaString, _T("OUTPUT"));

	addMessageType(_T("test3"), _T("Test command response data"), schemaMsgTest3);

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
