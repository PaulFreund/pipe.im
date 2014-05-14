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
			// Add the function to the context
			if(function.empty() || duk_get_prop_string(_context, -1, function.c_str()) == 0)
				throw tstring(_T("Instantiating function \"") + function + _T("\" failed"));

			// Add the message to the context
			tstring messageText = PipeJson(message).dump();
			if(messageText.empty() || duk_push_string(_context, messageText.c_str()) == NULL)
				throw tstring(_T("Adding message to script context failed"));

			duk_json_decode(_context, -1);

			// Call the function
			if(duk_pcall(_context, 1) != DUK_EXEC_SUCCESS)
				throw tstring(_T("Evaluating script failed"));


			// Get the result
			auto resultText = duk_json_encode(_context, -1);
			if(resultText == NULL)
				throw tstring(_T("Receiving message from script context failed"));

			message = *parseObject(resultText);

			// Remove the result from the stack
			duk_pop(_context);
		}

		static std::shared_ptr<PipeScript> Create(const tstring& name, bool preSend, bool postReceive, int priority, const tstring& data) {
			duk_context* newContext = duk_create_heap_default();
			if(!newContext) {
				throw tstring(_T("Could not create script context"));
			}

			// Add the functions to the context
			if(duk_peval_string_noresult(newContext, data.c_str()) != 0)
				throw tstring(_T("The script could not be evaluated"));

			// Create a new execution context
			duk_push_global_object(newContext);

			// In the future use DUK_COMPILE_FUNCTION 

			// Check if the required functions exist
			if(preSend) {
				if(duk_is_valid_index(newContext, -1) != 1 || duk_has_prop_string(newContext, -1, _T("preSend")) == 0)
					throw tstring(_T("Script has no preSend function"));
			}

			if(postReceive) {
				if(duk_is_valid_index(newContext, -1) != 1 || duk_has_prop_string(newContext, -1, _T("postReceive")) == 0)
					throw tstring(_T("Script has no postReceive function"));
			}

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
