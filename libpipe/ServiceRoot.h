//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeServiceNodeBase.h"

//======================================================================================================================

class PipeScript {
public:
	tstring _name;
	int _priority;
	tstring _data;
	duk_context* _context;

	PipeScript(const tstring& name, int priority, const tstring& data, duk_context* context)
		: _name(name)
		, _priority(priority)
		, _data(data)
		, _context(context) {}

	~PipeScript() {
		if(_context != nullptr) {
			duk_destroy_heap(_context);
		}
	}

	void execute(tstring function, PipeObject& message) {
		if(function.empty()) { throw tstring(_T("Missing function name"));}
		tstring messageText = PipeJson(message).dump();
		if(messageText.empty()) { throw tstring(_T("Invalid or empty mesage")); }

		// Add function to the value stack
		if(function.empty() || duk_get_prop_string(_context, -1, function.c_str()) == 0) {
			duk_pop(_context); // duk_get_prop_string pushs undefined to the value stack if it fails
			throw tstring(_T("Instantiating function \"") + function + _T("\" failed"));
		}

		// Add the message as first argument to the value stack
		if(duk_push_string(_context, messageText.c_str()) == NULL) {
			duk_pop(_context); // duk_push_string pushs null to the value stack if it fails
			throw tstring(_T("Adding message to script context failed"));
		}

		// Convert message to json
		duk_json_decode(_context, -1);

		// Call the function
		if(duk_pcall(_context, 1) != DUK_EXEC_SUCCESS) 
			throw tstring(_T("Evaluating script failed"));


		// Get the result from the value stack and decode it
		auto resultText = duk_json_encode(_context, -1);

		// Check if the result is valid
		if(resultText == NULL) {
			duk_pop(_context); // Remove the result from the value stack
			throw tstring(_T("Receiving message from script context failed"));
		}

		// Parse the result
		message = *parseObject(resultText);

		// Remove the result from the value stack (should be empty now)
		duk_pop(_context); 

		std::cout << _T("\n[DEBUG]\n") << PipeJson(message).dump() << _T("\n[/DEBUG]\n"); // TODO: DEBUG CODE
	}
};

//----------------------------------------------------------------------------------------------------------------------

class ServiceRoot : public PipeServiceNodeBase {
private:
	PipeObjectPtr _config;

	std::vector<tstring> _providerTypes;

	std::vector<std::shared_ptr<PipeScript>> _scriptsPreSend;
	std::vector<std::shared_ptr<PipeScript>> _scriptsPostReceive;

	std::shared_ptr<PipeServiceNodeBase> _serviceScripts;
	std::shared_ptr<PipeServiceNodeBase> _serviceServices;
	std::shared_ptr<PipeServiceNodeBase> _serviceServicesProviders;
	std::shared_ptr<PipeServiceNodeBase> _serviceServicesInstances;

public:
	ServiceRoot(const tstring& address, const tstring& path, PipeObjectPtr settings);
	virtual ~ServiceRoot();

private:
	void loadConfig();
	bool readConfig();
	void writeConfig();
	tstring configPath();

private:
	void initServices();
	tstring createService(const tstring& type, const tstring& name, PipeObject& settings);
	void deleteService(const tstring& name);

private:
	void initScripts();
	tstring createScript(const tstring& name, bool preSend, bool postReceive, int priority, const tstring& data);
	void deleteScript(const tstring& name);
	void executeScripts(PipeArrayPtr messages, bool preSend, bool postReceive);
	
	std::shared_ptr<PipeScript> buildScriptContext(const tstring& name, bool preSend, bool postReceive, int priority, const tstring& data);
};

//======================================================================================================================
