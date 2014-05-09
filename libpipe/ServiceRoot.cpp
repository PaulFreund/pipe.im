//======================================================================================================================

#include "CommonHeader.h"
#include "ServiceRoot.h"
using namespace std;

//======================================================================================================================

ServiceRoot::ServiceRoot(const tstring& address, const tstring& path, PipeObjectPtr settings) : PipeServiceNodeBase(_T("pipe"), _T("Pipe root node"), address, path, settings) {
	// DEBUG CODE
	{
		//------------------------------------------------------------------------------------------------------------------
		PipeObjectPtr schemaCmdTestAdd = newObject();
		schemaAddValue(*schemaCmdTestAdd, TokenMessageData, SchemaValueTypeString, _T("Child to be added"));

		addCommand(_T("test_add"), _T("Add a test child"), schemaCmdTestAdd, [&](PipeObject& message) {
			if(message.count(TokenMessageData) && message[TokenMessageData].is_string()) {
				tstring name = message[TokenMessageData].string_value();
				addChild(make_shared<PipeServiceNodeBase>(name + _T("type"), _T("A ") + name + _T(" child"), _address + TokenAddressSeparator + name, _path, newObject()));
			}
			else {
				pushOutgoing(message[TokenMessageRef].string_value(), _T("error"), _T("Invalid test_add request"));
			}
		});

		//------------------------------------------------------------------------------------------------------------------
		PipeObjectPtr schemaCmdTestRemove = newObject();
		schemaAddValue(*schemaCmdTestRemove, TokenMessageData, SchemaValueTypeString, _T("Child to be removed"));

		addCommand(_T("test_remove"), _T("Remove a test child"), schemaCmdTestRemove, [&](PipeObject& message) {
			if(message.count(TokenMessageData) && message[TokenMessageData].is_string()) {
				tstring name = message[TokenMessageData].string_value();
				removeChild(_address + TokenAddressSeparator + name);
			}
			else {
				pushOutgoing(message[TokenMessageRef].string_value(), _T("error"), _T("Invalid test_remove request"));
			}
		});

		//------------------------------------------------------------------------------------------------------------------
		PipeObjectPtr schemaCmdTest = newObject();
		schemaAddValue(*schemaCmdTest, TokenMessageData, SchemaValueTypeString, _T("Message to be changed"));

		addCommand(_T("test"), _T("A test command"), schemaCmdTest, [&](PipeObject& message) {
			if(message.count(TokenMessageData) && message[TokenMessageData].is_string()) {
				auto msg = message[TokenMessageData].string_value();
				TCHAR tmp = msg[0];
				msg[0] = msg[msg.length() - 1];
				msg[msg.length() - 1] = tmp;

				pushOutgoing(message[TokenMessageRef].string_value(), _T("test"), msg);
			}
			else {
				pushOutgoing(message[TokenMessageRef].string_value(), _T("error"), _T("Invalid test request"));
			}
		});

		PipeObjectPtr schemaMsgTest = newObject();
		schemaAddValue(*schemaMsgTest, TokenMessageData, SchemaValueTypeString, _T("Changed message"));

		addMessageType(_T("test"), _T("Test command response"), schemaMsgTest);

		//------------------------------------------------------------------------------------------------------------------
		PipeObjectPtr schemaCmdTest2 = newObject();
		auto& schemaCmdTest2Data = schemaAddObject(*schemaCmdTest2, TokenMessageData, _T("Message data to changed"));
		schemaAddValue(schemaCmdTest2Data, _T("key1"), SchemaValueTypeString, _T("description 1 text"));
		schemaAddValue(schemaCmdTest2Data, _T("key2"), SchemaValueTypeString, _T("description 2 text"), true);

		addCommand(_T("test2"), _T("A test command"), schemaCmdTest2, [&](PipeObject& message) {
			if(message.count(TokenMessageData) && message[TokenMessageData].is_object()) {
				auto msg1 = message[TokenMessageData][_T("key1")].string_value();
				TCHAR tmp1 = msg1[0];
				msg1[0] = msg1[msg1.length() - 1];
				msg1[msg1.length() - 1] = tmp1;

				if(message[TokenMessageData].object_items().count(_T("key2"))) {
					auto msg2 = message[TokenMessageData][_T("key2")].string_value();
					TCHAR tmp2 = msg2[0];
					msg2[0] = msg2[msg2.length() - 1];
					msg2[msg2.length() - 1] = tmp2;

					pushOutgoing(message[TokenMessageRef].string_value(), _T("test2"), PipeObject { { _T("key1"), msg1 }, { _T("key2"), msg2 } });
				}
				else {
					pushOutgoing(message[TokenMessageRef].string_value(), _T("test2"), PipeObject { { _T("key1"), msg1 } });
				}
			}
			else {
				pushOutgoing(message[TokenMessageRef].string_value(), _T("error"), _T("Invalid test2 request"));
			}
		});

		PipeObjectPtr schemaMsgTest2 = newObject();
		auto& schemaMsgTest2Data = schemaAddObject(*schemaMsgTest2, TokenMessageData, _T("Message data to changed"));
		schemaAddValue(schemaMsgTest2Data, _T("key1data"), SchemaValueTypeString, _T("description data 1 text"));
		schemaAddValue(schemaMsgTest2Data, _T("key2data"), SchemaValueTypeString, _T("description data 2 text"), true);

		addMessageType(_T("test2"), _T("Test command response data"), schemaMsgTest2);

		//------------------------------------------------------------------------------------------------------------------
		PipeObjectPtr s = newObject();

		auto& b = schemaAddObject(*s, TokenMessageData, _T("B"));
		auto& b3 = schemaAddObjectArray(b, _T("B3"), _T("B3D"), _T("B3DI"));
		schemaAddValueArray(b3, _T("B3A"), _T("B3AD"), SchemaValueTypeString, _T("B3ADI"));

		addCommand(_T("test3"), _T("A test command"), s, [&](PipeObject& message) {
			pushOutgoing(message[TokenMessageRef].string_value(), _T("test3"), PipeObject { { _T("keydata"), message[TokenMessageData].dump() } });
		});

		PipeObjectPtr schemaMsgTest3 = newObject();
		auto& schemaMsgTest3Data = schemaAddObject(*schemaMsgTest3, TokenMessageData, _T("Message data to output"));
		schemaAddValue(schemaMsgTest3Data, _T("keydata"), SchemaValueTypeString, _T("OUTPUT"));

		addMessageType(_T("test3"), _T("Test command response data"), schemaMsgTest3);

		//------------------------------------------------------------------------------------------------------------------
		auto&& childNode = make_shared<PipeServiceNodeBase>(_T("subtesttype"), _T("A sub test child"), _address + TokenAddressSeparator + _T("subtest"), path, settings);

		childNode->addCommand(
			_T("child_test"),
			_T("A test command"),
			newObject(),
			[&](PipeObject& message) {
			pushOutgoing(message[TokenMessageRef].string_value(), _T("child_test"), *newObject({
				{ _T("response"), _T("CHILD") }
			}));
		}
		);

		addChild(childNode);

		enablePreSendHook([&](PipeArrayPtr messages) {
			//for(auto& message: *messages) {
			//	message[TokenMessageRef].string_value() = _T("PRE_") + message[TokenMessageRef].string_value();
			//}

			// TODO: Process scripts
		});

		enablePostReceiveHook([&](PipeArrayPtr messages) {
			//for(auto& message : *messages) {
			//	message[TokenMessageRef].string_value() = message[TokenMessageRef].string_value() + _T("_POST");
			//}

			// TODO: Process scripts
		});
	}
	// TODO: Add real nodes (scripting, services etc) and remove tests
}

//----------------------------------------------------------------------------------------------------------------------

ServiceRoot::~ServiceRoot() {
}

//======================================================================================================================
