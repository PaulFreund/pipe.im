//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeServiceNodeBase.h"

//======================================================================================================================

class ServiceRoot : public PipeServiceNodeBase {
private:
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
			, _context(context)
		{}

		~PipeScript() {
			if(_context != nullptr) {
				duk_destroy_heap(_context);
			}
		}

		void execute(tstring function, PipeObject& message) {
			// Create a new execution context
			duk_push_global_object(_context);

			// Add the function to the context
			try {
				duk_get_prop_string(_context, -1, function.c_str());
			}
			catch(...) {
				// TODO: Throw error
			}

			// Add the message to the context
			try {
				duk_push_string(_context, PipeJson(message).dump().c_str());
				duk_json_decode(_context, -1);
			}
			catch(...) {
				// TODO: Throw error
			}

			// Call the function
			try {
				duk_call(_context, 1);
			}
			catch(...) {
				// TODO: Throw error
			}

			// Get the result			
			try {
				message = *parseObject(duk_json_encode(_context, -1));
				duk_pop(_context);
			}
			catch(...) {
				// TODO: Throw error
			}
		}

		static std::shared_ptr<PipeScript> Create(const tstring& name, bool preSend, bool postReceive, int priority, const tstring& data) {
			duk_context* newContext = duk_create_heap_default();
			if(!newContext) {
				throw tstring(_T("Could not create script context"));
			}

			// TODO: DEBUG
			tstring scriptData = _T("function preSend(message) { message.ref += 'rofl'; return message; } function postReceive(message) { message.ref += 'peter'; return message; }");

			// Add the functions to the context
			try {
				duk_eval_string(newContext, scriptData.c_str());
				duk_pop(newContext); // Ignore the evaluation result 
			}
			catch(...) {
				throw tstring(_T("The script could not be evaluated"));
			}

			// TODO: Check if the required functions are there

			// TODO: Add helper functions to js context

			return std::make_shared<PipeScript>(name, priority, data, newContext);
		}
	};

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


};

//======================================================================================================================
