//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeInstance.h"

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

	tstringstream _receiveBuffer;

	PipeObject _sendMessageBuffer;
	tstring _sendMessageSchemaAddress;
	PipeObject _sendMessageSchema;
public:
	//------------------------------------------------------------------------------------------------------------------

	PipeShell(std::shared_ptr<LibPipeInstance> instance, const tstring& identifier, bool greeting = false)
		: _instance(instance)
		, _identifier(identifier)
		, _greeting(greeting)
		, _address(_T("pipe"))
		, _addressCommands(_instance->nodeCommandTypes(_address))
		, _sendMessageBuffer(PipeObject {})
		, _sendMessageSchemaAddress(_T(""))
		, _sendMessageSchema(PipeObject {})
	{
		if(_greeting)
			_receiveBuffer << _greetingText << std::endl;
	}

	~PipeShell() {};

public:
	//------------------------------------------------------------------------------------------------------------------
	bool setAddress(const tstring& newAddress = _T("pipe")) {
		tstring newAddressAbsolute = getAbsoluteAddress(newAddress);
		if(newAddressAbsolute.length() == 0)
			return false;

		PipeArrayPtr newAddressCommands;
		newAddressCommands = _instance->nodeCommandTypes(newAddressAbsolute);
		if(newAddressCommands->empty())
			return false;

		_address = newAddressAbsolute;
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

			tstring parameter = timplode(fragments, _T(' '));

			if(shellCommand)
				newShellCommand(command, parameter, address);
			else
				newPipeCommand(command, parameter, address, addressCommands);
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
	void newShellCommand(const tstring& command, const tstring& parameter, const tstring& address) {
		tstring cmd = command;
		if(command[0] == _T('!'))
			cmd.erase(begin(cmd));

		//--------------------------------------------------------------------------------------------------------------
		if(cmd == _T("help")) {
			size_t cmdWidth = 0;
			for(auto&& command : *_addressCommands) {
				auto&& cmd = command.object_items();
				auto objWidth = cmd[_T("command")].string_value().length();
				if(objWidth > cmdWidth)
					cmdWidth = objWidth;
			}

			_receiveBuffer << std::setfill(_T(' ')) ;
			_receiveBuffer << _T("Shell commands:") << std::endl;
			_receiveBuffer << indentSymbol << std::setw(cmdWidth) << _T("help") << _T(" - ") << _T("Print a list of available commands") << std::endl;
			_receiveBuffer << indentSymbol << std::setw(cmdWidth) << _T("usage") << _T(" - ") << _T("Print additional usage information") << std::endl;
			_receiveBuffer << indentSymbol << std::setw(cmdWidth) << _T("ls") << _T(" - ") << _T("Get a list of child nodes") << std::endl;
			_receiveBuffer << indentSymbol << std::setw(cmdWidth) << _T("cd") << _T(" - ") << _T("Set current node address") << std::endl;
			_receiveBuffer << indentSymbol << std::setw(cmdWidth) << _T("pwd") << _T(" - ") << _T("Get current node address") << std::endl;
			_receiveBuffer << std::endl;
			_receiveBuffer << _T("Node commands:") << std::endl;
			for(auto&& command : *_addressCommands) {
				auto&& cmd = command.object_items();
				_receiveBuffer << indentSymbol << std::setw(cmdWidth) << cmd[_T("command")].string_value() << _T(" - ") << cmd[_T("description")].string_value() << std::endl;
			}
		}

		//--------------------------------------------------------------------------------------------------------------
		if(cmd == _T("usage")) {
			_receiveBuffer << _T("Syntax to supply parameters on demand:") << std::endl;
			_receiveBuffer << indentSymbol << _T("[<address>] <command>") << std::endl;
			_receiveBuffer << std::endl;
			_receiveBuffer << _T("Syntax if there is only on parameter for the command:") << std::endl;
			_receiveBuffer << indentSymbol << _T("[<address>] <command> <parameter>") << std::endl;
		}

		//--------------------------------------------------------------------------------------------------------------
		else if(cmd == _T("ls")) {
			// Handle .. and .

			tstring lsAddress = (parameter.length() > 0 ? getAbsoluteAddress(parameter) : getAbsoluteAddress(address));
			if(lsAddress.length() == 0) {
				_receiveBuffer << _T("Invalid address") << std::endl;
				return;
			}

			auto info = _instance->nodeInfo(lsAddress);
			if(info->size() == 0) {
				_receiveBuffer << _T("Invalid address") << std::endl;
				return;
			}

			auto children = _instance->nodeChildren(lsAddress);
			if(children->size() == 0) {
				_receiveBuffer << _T("No children") << std::endl;
				return;
			}

			for(auto&& child : *children)
				_receiveBuffer << texplode(child.string_value(), _T('.')).back() << _T(" ");

			_receiveBuffer << std::endl;
		}

		//--------------------------------------------------------------------------------------------------------------
		else if(cmd == _T("cd")) {
			if(parameter.length() <= 0) {
				_receiveBuffer << _T("Shell error! \"cd\" requires one parameter") << std::endl;
				return;
			}

			if(!setAddress(parameter))
				_receiveBuffer << _T("Shell error! Invalid address") << std::endl;
			else 
				_receiveBuffer << _T("New address: ") << _address << std::endl;
		}

		//--------------------------------------------------------------------------------------------------------------
		else if(cmd == _T("pwd")) {
			if(parameter.length() > 0) {
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
			auto&& commandObj = command.object_items();
			if(commandObj[_T("command")].string_value() == commandName) {
				return true;
			}
		}
		return false;
	}

	//------------------------------------------------------------------------------------------------------------------
	void newPipeCommand(const tstring& command, const tstring& parameters, const tstring& address, PipeArrayPtr& addressCommands) {
		PipeObject* schema = nullptr;
		for(auto&& addressCommand : *addressCommands) {
			auto&& cmd = addressCommand.object_items();
			if(cmd[_T("command")].string_value() == command)
				schema = &cmd[_T("schema")].object_items()[_T("data")].object_items();
		}

		bool hasParameters = (schema != nullptr && schema->size() > 0);
		bool multipleParameters = (schema != nullptr && (schema->count(_T("fields")) || schema->count(_T("items"))));

		// Parametes have been supplied but are not accepted
		if(!hasParameters && parameters.size() > 0) {
			_receiveBuffer << _T("Error! Command does not accept any parameters") << std::endl;
			return;
		}

		// More than one parameters have been supplied but only one is accepted
		if(!multipleParameters && parameters.size() > 1) {
			_receiveBuffer << _T("Error! Command can only be invoked with one or no parameter") << std::endl;
			return;
		}

		// More than one parameters have been supplied but multiple would be needed which is impossible
		if(multipleParameters && parameters.size() > 0) {
			if(parameters.size() == 1)
				_receiveBuffer << _T("Error! Parameters can not be supplied for commands with multiple parameters") << std::endl;
			else
				_receiveBuffer << _T("Error! Command can not be invoked with multiple parameters") << std::endl;

			return;
		}

		_sendMessageBuffer[_T("ref")] = _identifier;
		_sendMessageBuffer[_T("address")] = address;
		_sendMessageBuffer[_T("command")] = command;

		if(!hasParameters) {
			finishPipeCommand();
			return;
		}

		// command has one paramter
		else if(!multipleParameters && parameters.size() == 1) {
			_sendMessageBuffer[_T("data")] = parameters[0];
			finishPipeCommand();
			return;
		}
		else {
			_sendMessageBuffer[_T("data")] = PipeObject();
			_sendMessageSchemaAddress = _T("");
			_sendMessageSchema = *schema;
			extendPipeCommand(_T(""));
		}
	}

	//------------------------------------------------------------------------------------------------------------------
	void extendPipeCommand(const tstring& input) {
		auto& currentNode = getSchemaNode(_sendMessageSchemaAddress);

		if(!input.empty()) {
			// TODO: Add to sendMessage

			_sendMessageSchemaAddress = nextSchemaNode(_sendMessageSchemaAddress);
			if(_sendMessageSchemaAddress.empty())
				finishPipeCommand();
		}

		// TODO: Poll for more input
	}

	//------------------------------------------------------------------------------------------------------------------
	void finishPipeCommand() {
		auto sendMessages = newArray({ _sendMessageBuffer });
		_instance->send(sendMessages);
		_sendMessageSchemaAddress = _T("");
		_sendMessageSchema = PipeObject {};
		_sendMessageBuffer = PipeObject {};
	}

	//------------------------------------------------------------------------------------------------------------------
	PipeObject& getSchemaNode(const tstring& address) {
		PipeObject* currentNode = &_sendMessageSchema;
		
		auto nodes = texplode(address, _T('.'));
		for(auto& node : nodes) {
			if(currentNode->count(node))
				currentNode = &currentNode->operator[](node).object_items();
		}

		return *currentNode;
	}

	//------------------------------------------------------------------------------------------------------------------
	tstring nextSchemaNode(const tstring& address) {
		tstring lastElement = _T("");
		auto nodes = texplode(address, _T('.'));
		do {
			auto& currentNode = getSchemaNode(timplode(nodes, _T('.')));

			if(currentNode[_T("type")] == _T("object")) {
				auto& fields = currentNode[_T("fields")].object_items();
				if(fields.size() > 0) {
					bool next = false;
					tstring found = _T("");
					for(auto& field : fields) {
						if(next || lastElement.empty()) {
							found = field.first;
							break;
						}

						if(field.first == lastElement)
							next = true;
					}

					if(!found.empty()) {
						nodes.push_back(_T("fields"));
						nodes.push_back(found);
						return timplode(nodes, _T('.'));
					}
					else {
						lastElement.clear();
					}
				}
			}

			if(nodes.size() > 0)
				lastElement = nodes.back();
			else
				break;

			nodes.pop_back();

			if(nodes.back() == _T("fields") || nodes.back() == _T("items"))
				nodes.pop_back();
		}
		while(nodes.size() > 0 || !lastElement.empty());

		return _T("");
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
				output << (data.bool_value() ? _T("true") : _T("false"));
			else if(data.is_number())
				output << to_tstring(data.number_value());

			output << std::endl;
		}
	}

	//------------------------------------------------------------------------------------------------------------------
	tstring getAbsoluteAddress(const tstring& address) {
		tstring absolute = address;

		if(address == _T("..")) {
			auto addressFragments = texplode(_address, _T('.'));
			if(addressFragments.size() < 2)
				return _T("");

			addressFragments.erase(addressFragments.begin() + (addressFragments.size() - 1));
			absolute = timplode(addressFragments, _T('.'));
		}
		else if(address == _T(".")) {
			return _address;
		}
		else if(address != _T("pipe") && address.find_first_of(_T('.')) == tstring::npos) {
			absolute = _address + _T(".") + address;
		}

		return absolute;
	}

	//------------------------------------------------------------------------------------------------------------------
};

//======================================================================================================================
