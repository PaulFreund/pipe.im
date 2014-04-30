//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeInstance.h"

//======================================================================================================================

/*
Local state for shell:
$PATH = object path

Inbuilt commands:
help - display help
cd - change $PATH
ls - list child nodes


$PATH>


cout << _T("------------------------------------------") << endl;
cout << _T("Welcome to pipe shell") << endl;
cout << _T("------------------------------------------") << endl;
cout << _T("Available service types: ") << dumpArray(serviceTypes) << endl;

cout << _T("------------------------------------------") << endl;
cout << endl;
*/


//======================================================================================================================

class PipeShell {
private:
	const tstring _identifier;
	std::shared_ptr<LibPipeInstance> _instance;
	bool _greeting;

	tstring _address;
	PipeObjectPtr _sendBuffer;
public:
	PipeShell(std::shared_ptr<LibPipeInstance> instance, const tstring& identifier, bool greeting = false) 
		: _instance(instance)
		, _identifier(identifier)
		, _greeting(greeting)
		, _address(_T("pipe"))
		, _sendBuffer(newObject())
		{}

	~PipeShell() {};

public:
	void send(const tstring& input) {
		if(_sendBuffer->empty()) {
			(*_sendBuffer)[_T("ref")] = _identifier;
			(*_sendBuffer)[_T("address")] = _address;
		}

		auto&& fragments = texplode(input, _T(' '));
		if(fragments.size() <= 0) { return; }

		if(_sendBuffer->count(_T("command")) == 0)
			(*_sendBuffer)[_T("command")] = fragments[0];

		// TODO : handle command building

		auto sendMessages = newArray({ *_sendBuffer });
		_instance->send(sendMessages);
		_sendBuffer = newObject();
	}

	tstring receive() {
		tstringstream output;
		auto messages = _instance->receive();
		for(auto& msg : *messages) {
			if(!msg.is_object()) { continue; }

			auto&& obj = msg.object_items();
			if(!obj.count(_T("ref")) || !obj.count(_T("address")) || !obj.count(_T("message")) || !obj.count(_T("data"))) { continue; }

			auto ref = obj[_T("ref")].string_value();
			if(ref != _identifier && !ref.empty()) { continue; }

			auto address = obj[_T("address")].string_value();
			auto type = obj[_T("message")].string_value();
			auto data = obj[_T("data")];

			tstring source = _T("[") + address + _T("][") + type + _T("]");

			if(data.is_object() || data.is_array()) {
				generateOutput(output, source, data);
			} 
			else {
				output << source << _T(" ");
				if(data.is_string())
					output << data.string_value();
				else if(data.is_bool())
					output << data.bool_value() ? _T("true") : _T("false");
				else if(data.is_number())
					output << to_tstring(data.number_value());
			}

		}

		return output.str();
	}

private:
	void generateOutput(tstringstream& output, const tstring& key, Json& data, tstring indent = _T(""), bool arrayItem = false) {
		if((data.is_object() && data.object_items().empty()) || (data.is_array() && data.array_items().empty())) { return; }

		output << indent << key;

		if(data.is_object()) {
			if(!arrayItem) { output << _T(": ") << std::endl; }

			bool first = arrayItem;
			for(auto&& field : data.object_items()) {
				generateOutput(output, field.first, field.second, (first ? _T("") : (indent + _T("\t"))), first);
				first = false;
			}
		}
		else if(data.is_array()) {
			if(!arrayItem) { output << _T(": ") << std::endl; }

			auto& items = data.array_items();
			for(auto item = begin(items); item != end(items); item++) {
				generateOutput(output, _T("  - "), *item, (indent + _T("\t")), true);
				if((item + 1) != end(items)) { output << std::endl; }
			}
		}
		else {
			if(key != _T("  - ")) { output << _T(": "); }

			if(data.is_string())
				output << data.string_value();
			else if(data.is_bool())
				output << data.bool_value() ? _T("true") : _T("false");
			else if(data.is_number())
				output << to_tstring(data.number_value());

			output << std::endl;
		}
	}
};

//======================================================================================================================
