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

*/


//======================================================================================================================

class PipeShell {
private:
	//------------------------------------------------------------------------------------------------------------------
	const tstring _greetingText = _T("Welcome to the pipe shell, type help for further assistance\n");
	const tstring indentSymbol = _T("    ");

private:
	//------------------------------------------------------------------------------------------------------------------
	const tstring _identifier;
	std::shared_ptr<LibPipeInstance> _instance;
	bool _greeting;

	tstring _address;
	PipeArrayPtr _addressCommands;

	PipeObject _sendMessageBuffer;
	PipeObject _sendMessageSchema;
	tstringstream _receiveBuffer;
public:
	//------------------------------------------------------------------------------------------------------------------

	PipeShell(std::shared_ptr<LibPipeInstance> instance, const tstring& identifier, bool greeting = false) 
		: _instance(instance)
		, _identifier(identifier)
		, _greeting(greeting)
		, _address(_T("pipe"))
		, _addressCommands(_instance->nodeCommandTypes(_address))
		, _sendMessageBuffer(PipeObject {})
		, _sendMessageSchema(PipeObject {})
	{
		if(_greeting)
			_receiveBuffer << _greetingText << std::endl;
	}

	~PipeShell() {};

public:
	//------------------------------------------------------------------------------------------------------------------
	bool setAddress(tstring newAddress = _T("pipe")) {
		if(newAddress == _T("..")) {
			auto addressFragments = texplode(_address, _T('.'));
			if(addressFragments.size() < 2)
				return false;

			addressFragments.erase(addressFragments.begin() + (addressFragments.size() - 1));
			newAddress = timplode(addressFragments, _T('.'));
		}
		else if(newAddress == _T(".")) {
			return true;
		}
		else if(newAddress != _T("pipe") && newAddress.find_first_of(_T('.')) == tstring::npos) {
			newAddress = _address + _T(".") + newAddress;
		}

		PipeArrayPtr newAddressCommands;
		newAddressCommands = _instance->nodeCommandTypes(newAddress);
		if(newAddressCommands->empty())
			return false;

		_address = newAddress;
		_addressCommands = newAddressCommands;
		return true;
	}

	//------------------------------------------------------------------------------------------------------------------
	tstring getAddress() {
		return _address;
	}

	//------------------------------------------------------------------------------------------------------------------
	void send(const tstring& input) {
		// New command
		if(_sendMessageBuffer.empty()) {
			auto&& fragments = texplode(input, _T(' '));
			if(fragments.size() <= 0) { return; }

			// Extract possible address
			auto address = _address;
			auto addressCommands = _addressCommands;
			if(fragments.size() >= 2) {
				if(fragments[0] == _T("pipe") || fragments[0].find_first_of(_T('.')) != tstring::npos) {
					address = fragments[0];
					addressCommands = _instance->nodeCommandTypes(address);
					fragments.erase(begin(fragments));
				}
			}

			// Get command
			tstring command = fragments[0];
			fragments.erase(begin(fragments));

			bool shellCommand = isShellCommand(command);

			// commands starting with # indicate a service command
			if(command[0] == _T('#')) {
				command.erase(begin(command));
				shellCommand = false;
			}

			// Warn when command is ambigous between shell and service
			if(shellCommand && isPipeCommand(command, addressCommands)) {
				_receiveBuffer << _T("Warning! Command is ambiguous, use !<command> to use shell instead of service or #<command> to explicitly use the service and stop this warning") << std::endl;
				shellCommand = false;
			}

			if(shellCommand)
				newShellCommand(command, fragments, address);
			else
				newPipeCommand(command, fragments, address, addressCommands);
		}
		// This message has already been started
		else {
			extendPipeCommand(input);
		}
	}

	//------------------------------------------------------------------------------------------------------------------
	tstring receive() {
		tstringstream output;
		output << _receiveBuffer.str();
		_receiveBuffer.str(tstring());

		if(_sendMessageBuffer.empty()) {
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

				tstring source = address + _T(" - ") + type;

				if(data.is_object() || data.is_array()) {
					if((data.is_object() && data.object_items().empty()) || (data.is_array() && data.array_items().empty())) 
						output << source << _T(": Empty");
					else
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
		}

		return output.str();
	}

private:
	//------------------------------------------------------------------------------------------------------------------
	bool isShellCommand(const tstring& command) {
		tstring cmd = command;
		if(command[0] == _T('!'))
		   cmd.erase(begin(cmd));

		if(cmd == _T("help")) { return true; }
		if(cmd == _T("usage")) { return true; }
		else if(cmd == _T("ls")) { return true; }
		else if(cmd == _T("cd")) { return true; }
		else if(cmd == _T("pwd")) { return true; }
		
		return false;
	}

	//------------------------------------------------------------------------------------------------------------------
	void newShellCommand(const tstring& command, const std::vector<tstring>& parameters, const tstring& address) {
		tstring cmd = command;
		if(command[0] == _T('!'))
			cmd.erase(begin(cmd));

		//--------------------------------------------------------------------------------------------------------------
		if(cmd == _T("help")) {
			_receiveBuffer << _T("TODO: Generate help data") << std::endl; // TODO
		}

		//--------------------------------------------------------------------------------------------------------------
		if(cmd == _T("usage")) {
			_receiveBuffer << _T("TODO: Generate usage data") << std::endl; // TODO
		}

		//--------------------------------------------------------------------------------------------------------------
		else if(cmd == _T("ls")) {
			if(parameters.size() > 1) {
				_receiveBuffer << _T("Shell error! \"ls\" only accepts none or one parameter") << std::endl;
				return;
			}

			// Handle .. and .
			tstring lsAddress = address;
			if(parameters.size() == 1) {
				lsAddress = parameters[0];
				if(lsAddress == _T("..")) {
					auto addressFragments = texplode(_address, _T('.'));
					if(addressFragments.size() >= 2) {
						addressFragments.erase(addressFragments.begin() + (addressFragments.size() - 1));
						lsAddress = timplode(addressFragments, _T('.'));
					}
				}
				else if(lsAddress == _T(".")) {
					lsAddress = _address;
				}
			}

			auto children = _instance->nodeChildren(lsAddress);
			if(children->size() == 0) {
				_receiveBuffer << _T("No children") << std::endl;
				return;
			}

			for(auto&& child : *children)
				_receiveBuffer << child.string_value() << _T(" ");

			_receiveBuffer << std::endl;
		}

		//--------------------------------------------------------------------------------------------------------------
		else if(cmd == _T("cd")) {
			if(parameters.size() != 1) {
				_receiveBuffer << _T("Shell error! \"cd\" only accepts one parameter") << std::endl;
				return;
			}

			if(!setAddress(parameters[0]))
				_receiveBuffer << _T("Shell error! Invalid address") << std::endl;
			else 
				_receiveBuffer << _T("New address: ") << _address << std::endl;
		}

		//--------------------------------------------------------------------------------------------------------------
		else if(cmd == _T("pwd")) {
			if(parameters.size() > 0) {
				_receiveBuffer << _T("Shell error! \"pwd\" does not accept any parameters") << std::endl;
				return;
			}

			_receiveBuffer << _address << std::endl;
		}

		//--------------------------------------------------------------------------------------------------------------
	}

	//------------------------------------------------------------------------------------------------------------------
	bool isPipeCommand(const tstring& commandName, const PipeArrayPtr& addressCommands) {
		for(auto&& command : *addressCommands) {
			if(!command.is_object()) { continue; }
			auto&& commandObj = command.object_items();
			if(commandObj[_T("command")].string_value() == commandName) {
				return true;
			}
		}
		return false;
	}

	//------------------------------------------------------------------------------------------------------------------
	void newPipeCommand(tstring& command, std::vector<tstring>& parameters, const tstring& address, PipeArrayPtr& addressCommands) {
		_sendMessageBuffer[_T("ref")] = _identifier;
		_sendMessageBuffer[_T("address")] = address;
		_sendMessageBuffer[_T("command")] = command;

		// TODO

		finishPipeCommand();
	}

	//------------------------------------------------------------------------------------------------------------------
	void extendPipeCommand(const tstring& input) {
		// TODO!
	}

	//------------------------------------------------------------------------------------------------------------------
	void finishPipeCommand() {
		auto sendMessages = newArray({ _sendMessageBuffer });
		_instance->send(sendMessages);
		_sendMessageSchema = PipeObject {};
		_sendMessageBuffer = PipeObject {};
	}

	//------------------------------------------------------------------------------------------------------------------
	void generateOutput(tstringstream& output, const tstring& key, Json& data, tstring indent = _T(""), bool arrayItem = false) {
		if((data.is_object() && data.object_items().empty()) || (data.is_array() && data.array_items().empty())) { return; }

		output << indent << key;

		if(data.is_object()) {
			if(!arrayItem) { output << _T(": ") << std::endl; }

			bool first = arrayItem;
			for(auto&& field : data.object_items()) {
				generateOutput(output, field.first, field.second, (first ? _T("") : (indent + indentSymbol)), first);
				first = false;
			}
		}
		else if(data.is_array()) {
			if(!arrayItem) { output << _T(": ") << std::endl; }

			auto& items = data.array_items();
			for(auto item = begin(items); item != end(items); item++) {
				generateOutput(output, _T("  - "), *item, (indent + indentSymbol), true);
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

	//------------------------------------------------------------------------------------------------------------------
};

//======================================================================================================================
