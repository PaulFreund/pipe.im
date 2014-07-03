//======================================================================================================================

#include "CommonHeader.h"
#include "PipeScript.h"
#include "ServiceRoot.h"

using namespace std;

//======================================================================================================================

ServiceRoot* getContextPtr(duk_context* ctx) {
	// Get context
	duk_push_heap_stash(ctx); // Value stack: [heap]
	if(duk_get_prop_string(ctx, -1, _T("contextPtr")) == 0) { // Value stack: [heap][prop]
		duk_pop(ctx); // Remove undefined prop, Value stack: [heap]
		duk_pop(ctx); // Remove heap stash, Value stack: 
		return nullptr;
	}

	ServiceRoot* pContextPtr = static_cast<ServiceRoot*>(duk_get_pointer(ctx, -1)); // Value stack: [heap][prop]
	duk_pop(ctx); // Remove pointer from stash, Value stack: [heap]
	duk_pop(ctx); // Remove heap stash, Value stack:

	return pContextPtr;
}

//----------------------------------------------------------------------------------------------------------------------

PipeScript* getScriptPtr(duk_context* ctx) {
	// Get context
	duk_push_heap_stash(ctx); // Value stack: [heap]
	if(duk_get_prop_string(ctx, -1, _T("scriptPtr")) == 0) { // Value stack: [heap][prop]
		duk_pop(ctx); // Remove undefined prop, Value stack: [heap]
		duk_pop(ctx); // Remove heap stash, Value stack: 
		return nullptr;
	}

	PipeScript* pScriptPtr = static_cast<PipeScript*>(duk_get_pointer(ctx, -1)); // Value stack: [heap][prop]
	duk_pop(ctx); // Remove pointer from stash, Value stack: [heap]
	duk_pop(ctx); // Remove heap stash, Value stack:

	return pScriptPtr;
}


//======================================================================================================================

PipeScript::PipeScript(const tstring& name, int priority, const tstring& data, duk_context* context)
	: _name(name)
	, _priority(priority)
	, _data(data)
	, _context(context) {
}

//----------------------------------------------------------------------------------------------------------------------

PipeScript::~PipeScript() {
	if(_context != nullptr)
		duk_destroy_heap(_context);
}

//----------------------------------------------------------------------------------------------------------------------

shared_ptr<PipeScript> PipeScript::create(ServiceRoot* serviceRoot, const tstring& name, bool preSend, bool postReceive, int priority, const tstring& data) {
	duk_context* ctx = duk_create_heap_default();
	if(!ctx) { throw tstring(_T("Could not create script context")); }

	auto newScript = std::make_shared<PipeScript>(name, priority, data, ctx);

	// Add the functions to the context
	if(duk_peval_string_noresult(ctx, data.c_str()) != 0) { throw tstring(_T("The script could not be evaluated")); }

	// Create a new execution context
	duk_push_global_object(ctx); // Value stack: [global]

	// Check if the required functions exist
	if(preSend) {
		if(duk_is_valid_index(ctx, -1) != 1 || duk_has_prop_string(ctx, -1, _T("preSend")) == 0)
			throw tstring(_T("Script has no preSend function"));
	}

	if(postReceive) {
		if(duk_is_valid_index(ctx, -1) != 1 || duk_has_prop_string(ctx, -1, _T("postReceive")) == 0)
			throw tstring(_T("Script has no postReceive function"));
	}

	// Add script pointer to the heap stash
	duk_push_heap_stash(ctx); // Value stack: [global][heap]
	duk_push_pointer(ctx, static_cast<void*>(newScript.get())); // Value stack: [global][heap][pointer]
	if(duk_put_prop_string(ctx, -2, _T("scriptPtr")) == 0) { // Value stack: [global][heap]
		duk_pop(ctx); // Value stack: [global]
		throw tstring(_T("Could not add scriptPtr to scripting context"));
	}

	// Add context pointer to the heap stash
	duk_push_pointer(ctx, static_cast<void*>(serviceRoot)); // Value stack: [global][heap][pointer]
	if(duk_put_prop_string(ctx, -2, _T("contextPtr")) == 0) { // Value stack: [global][heap]
		duk_pop(ctx); // Value stack: [global]
		throw tstring(_T("Could not add contextPtr to scripting context"));
	}

	// Remove heap from value stack
	duk_pop(ctx); // Value stack: [global]

	// Add the "pipe" object to the stack
	duk_push_object(ctx);

	// Add children function to the stack
	{
		duk_push_c_function(ctx, [](duk_context* fctx) -> int {
			// Get parameter
			auto addressPtr = duk_get_string(fctx, -1); // Value stack: [string?]
			if(addressPtr == NULL) { return 0; }

			tstring address = tstring(addressPtr);
			duk_pop(fctx); // Value stack: 

			// Get Context
			auto pContext = getContextPtr(fctx);
			if(pContext == nullptr) { return 0; }

			tstring result = PipeJson(*pContext->nodeChildren(address)).dump();

			duk_push_string(fctx, result.c_str()); // Value stack: [string]
			duk_json_decode(fctx, -1); // Value stack: [json]

			return 1;
		}, 1); // One argument, Value stack: [global][object][function]

		if(duk_put_prop_string(ctx, -2, _T("children")) == 0) { // Value stack: [global][object]
			throw tstring(_T("Could not add children function to scripting context"));
		}
	}

	// Add commands function to the stack
	{
		duk_push_c_function(ctx, [](duk_context* fctx) -> int {
			// Get parameter
			auto addressPtr = duk_get_string(fctx, -1); // Value stack: [string?]
			if(addressPtr == NULL) { return 0; }

			tstring address = tstring(addressPtr);
			duk_pop(fctx); // Value stack: 

			// Get Context
			auto pContext = getContextPtr(fctx);
			if(pContext == nullptr) { return 0; }

			tstring result = PipeJson(*pContext->nodeCommandTypes(address)).dump();

			duk_push_string(fctx, result.c_str()); // Value stack: [string]
			duk_json_decode(fctx, -1); // Value stack: [json]

			return 1;
		}, 1); // One argument, Value stack: [global][object][function]

		if(duk_put_prop_string(ctx, -2, _T("commands")) == 0) { // Value stack: [global][object]
			throw tstring(_T("Could not add commands function to scripting context"));
		}
	}

	// Add messages function to the stack
	{
		duk_push_c_function(ctx, [](duk_context* fctx) -> int {
			// Get parameter
			auto addressPtr = duk_get_string(fctx, -1); // Value stack: [string?]
			if(addressPtr == NULL) { return 0; }

			tstring address = tstring(addressPtr);
			duk_pop(fctx); // Value stack: 

			// Get Context
			auto pContext = getContextPtr(fctx);
			if(pContext == nullptr) { return 0; }

			tstring result = PipeJson(*pContext->nodeMessageTypes(address)).dump();

			duk_push_string(fctx, result.c_str()); // Value stack: [string]
			duk_json_decode(fctx, -1); // Value stack: [json]

			return 1;
		}, 1); // One argument, Value stack: [global][object][function]

		if(duk_put_prop_string(ctx, -2, _T("messages")) == 0) { // Value stack: [global][object]
			throw tstring(_T("Could not add messages function to scripting context"));
		}
	}

	// Add info function to the stack
	{
		duk_push_c_function(ctx, [](duk_context* fctx) -> int {
			// Get parameter
			auto addressPtr = duk_get_string(fctx, -1); // Value stack: [string?]
			if(addressPtr == NULL) { return 0; }

			tstring address = tstring(addressPtr);
			duk_pop(fctx); // Value stack: 

			// Get Context
			auto pContext = getContextPtr(fctx);
			if(pContext == nullptr) { return 0; }

			tstring result = PipeJson(*pContext->nodeInfo(address)).dump();

			duk_push_string(fctx, result.c_str()); // Value stack: [string]
			duk_json_decode(fctx, -1); // Value stack: [json]

			return 1;
		}, 1); // One argument, Value stack: [global][object][function]

		if(duk_put_prop_string(ctx, -2, _T("info")) == 0) { // Value stack: [global][object]
			throw tstring(_T("Could not add info function to scripting context"));
		}
	}

	// Add set function to the stack
	{
		duk_push_c_function(ctx, [](duk_context* fctx) -> int {
			// Get parameters
			duk_json_encode(fctx, -1); 
			auto dataPtr = duk_get_string(fctx, -1);
			if(dataPtr == NULL) { return 0; }

			tstring data = tstring(dataPtr);
			duk_pop(fctx); 

			auto keyPtr = duk_get_string(fctx, -1); 
			if(keyPtr == NULL) { return 0; }

			tstring key = tstring(keyPtr);
			duk_pop(fctx);

			// Get Context
			auto pScript = getScriptPtr(fctx);
			if(pScript == nullptr) { return 0; }

			pScript->_dataStore[key] = data;

			return 0;
		}, 2); // Two arguments, Value stack: [global][object][function]

		if(duk_put_prop_string(ctx, -2, _T("set")) == 0) { // Value stack: [global][object]
			throw tstring(_T("Could not add set function to scripting context"));
		}
	}

	// Add get function to the stack
	{
		duk_push_c_function(ctx, [](duk_context* fctx) -> int {
			// Get parameter
			auto keyPtr = duk_get_string(fctx, -1); // Value stack: [string?]
			if(keyPtr == NULL) { return 0; }

			tstring key = tstring(keyPtr);
			duk_pop(fctx); // Value stack: 

			// Get Context
			auto pScript = getScriptPtr(fctx);
			if(pScript == nullptr) { return 0; }

			if(!pScript->_dataStore.count(key))
				return 0;

			tstring data = pScript->_dataStore[key];

			duk_push_string(fctx, data.c_str()); // Value stack: [string]
			duk_json_decode(fctx, -1); // Value stack: [json]

			return 1;
		}, 1); // Two arguments, Value stack: [global][object][function]

		if(duk_put_prop_string(ctx, -2, _T("get")) == 0) { // Value stack: [global][object]
			throw tstring(_T("Could not add get function to scripting context"));
		}
	}

	// Add pushIncoming function to the stack
	{
		duk_push_c_function(ctx, [](duk_context* fctx) -> int {
			// Get parameter
			duk_json_encode(fctx, -1);
			auto messagePtr = duk_get_string(fctx, -1); // Value stack: [string?]
			if(messagePtr == NULL) { return 0; }

			tstring message = tstring(messagePtr);
			duk_pop(fctx); // Value stack: 

			// Get Context
			auto pContext = getContextPtr(fctx);
			if(pContext == nullptr) { return 0; }

			auto messageObject = parseObject(message);

			int currentRecursionCount = 1;
			if(messageObject->count(_T("recursionCount"))) {
				currentRecursionCount = (*messageObject)[_T("recursionCount")].int_value();
				// If the recursion count is too high, cancel
				if(currentRecursionCount > PipeScript::MaxRecursionCount) {
					pContext->pushOutgoing(_T(""), _T("error"), _T("Maximum recursion count of ") + to_string(PipeScript::MaxRecursionCount) + _T(" exceeded, terminating script"));
					return 0;
				}

				currentRecursionCount++;
				(*messageObject)[_T("recursionCount")].int_value() = currentRecursionCount;
			}
			else {
				(*messageObject)[_T("recursionCount")] = currentRecursionCount;
			}

			pContext->scriptPushIncoming(messageObject);

			return 0;
		}, 1); // One argument, Value stack: [global][object][function]

		if(duk_put_prop_string(ctx, -2, _T("pushIncoming")) == 0) { // Value stack: [global][object]
			throw tstring(_T("Could not add pushIncoming function to scripting context"));
		}
	}


	// Add pushOutgoing function to the stack
	{
		duk_push_c_function(ctx, [](duk_context* fctx) -> int {
			// Get parameter
			duk_json_encode(fctx, -1);
			auto messagePtr = duk_get_string(fctx, -1); // Value stack: [string?]
			if(messagePtr == NULL) { return 0; }

			tstring message = tstring(messagePtr);
			duk_pop(fctx); // Value stack: 

			// Get Context
			auto pContext = getContextPtr(fctx);
			if(pContext == nullptr) { return 0; }

			pContext->scriptPushOutgoing(parseObject(message));

			return 0;
		}, 1); // One argument, Value stack: [global][object][function]

		if(duk_put_prop_string(ctx, -2, _T("pushOutgoing")) == 0) { // Value stack: [global][object]
			throw tstring(_T("Could not add pushOutgoing function to scripting context"));
		}
	}

	// Push the current object as "pipe" to the stash
	duk_put_prop_string(ctx, -2, "pipe"); // Value stack: [global]

	return newScript;
}

//----------------------------------------------------------------------------------------------------------------------

void PipeScript::execute(tstring function, PipeObject& message) {
	if(function.empty()) { throw tstring(_T("Missing function name")); }
	tstring messageText = PipeJson(message).dump();
	if(messageText.empty()) { throw tstring(_T("Invalid or empty mesage")); }

	// Add function to the value stack
	if(function.empty() || duk_get_prop_string(_context, -1, function.c_str()) == 0) { // Value stack: [global][function]
		duk_pop(_context); // remove function
		throw tstring(_T("Instantiating function \"") + function + _T("\" failed"));
	}

	// Add the message as first argument to the value stack
	if(duk_push_string(_context, messageText.c_str()) == NULL) { // Value stack: [global][function][string]
		duk_pop(_context); // remove function
		duk_pop(_context); // remove string result
		throw tstring(_T("Adding message to script context failed"));
	}

	// Convert message to json
	duk_json_decode(_context, -1); // Value stack: [global][function][json]

	// Call the function
	if(duk_pcall(_context, 1 /*nargs*/) != DUK_EXEC_SUCCESS) { // Value stack: [global][json]
		tstring error(duk_to_string(_context, -1));
		duk_pop(_context); // remove json value
		throw tstring(_T("Error in script (") + error + _T(")"));
	}

	// Get the result from the value stack and decode it
	auto resultText = duk_json_encode(_context, -1); // Value stack: [global][string]

	// Parse back message or empty object
	if(resultText == nullptr)
		message = *newObject();
	else
		message = *parseObject(resultText);

	// Remove the result from the value stack (should be empty now)
	duk_pop(_context);  // Value stack: [global]
}

//======================================================================================================================
