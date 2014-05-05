//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeInstance.h"

//======================================================================================================================

class PipeShellSendMessage {
	enum PipeShellSendMessageState {
		None,
		QueriedValue,
		QueriedOptional,
		AcceptedOptional,
		DeclinedOptional
	};

private:
	bool _messageEmpty;
	bool _messageComplete;

	PipeShellSendMessageState _clientState;


	tstring _currentAddress;
	PipeJson _message;
	PipeJson _schema;

public:
	PipeShellSendMessage()
		: _messageEmpty(true)
		, _messageComplete(true)
		, _clientState(None)
		, _currentAddress(_T(""))
		, _message(PipeObject {})
		, _schema(PipeObject {}) {}

public:
	//------------------------------------------------------------------------------------------------------------------
	bool isEmpty() { return _messageEmpty; }

	//------------------------------------------------------------------------------------------------------------------
	bool isComplete() { return _messageComplete; }

	//------------------------------------------------------------------------------------------------------------------
	PipeArrayPtr getMessages() {
		auto sendMessages = newArray({ _message });
		clear();
		return sendMessages;
	}

	//------------------------------------------------------------------------------------------------------------------
	tstring start(const tstring& identifier, const tstring& command, const tstring& parameter, const tstring& address, PipeJson& schema) {
		PipeObject* schemaData = &schema[_T("data")].object_items();

		bool hasParameters = (schemaData != nullptr && schemaData->size() > 0);
		bool multipleParameters = (schemaData != nullptr && (schemaData->count(_T("fields")) || schemaData->count(_T("items"))));

		// Parametes have been supplied but are not accepted
		if(!hasParameters && !parameter.empty())
			return _T("Error! Command does not accept any parameters\n");

		if(multipleParameters && !parameter.empty())
			return _T("Error! Command can not be invoked with parameters\n");


		_messageEmpty = false;
		_messageComplete = false;

		_schema = schema;
		_message = PipeJson(PipeObject());
		auto& messageData = _message.object_items();

		messageData[_T("ref")] = identifier;
		messageData[_T("address")] = address;
		messageData[_T("command")] = command;

		if(!hasParameters) {
			_messageComplete = true;
			return _T("");
		}

		// command has one paramter
		else if(!multipleParameters && !parameter.empty()) {
			setValue(_T("data"), parameter);
			_messageComplete = true;
			return _T("");
		}
		else {
			return nextValue();
		}
	}

	//------------------------------------------------------------------------------------------------------------------
	tstring add(const tstring& input) { // Posible client states: None, QueriedValue, QueriedOptional
		switch(_clientState) {
			case None: {
				break;
			}

			case QueriedValue: {
				setValue(_currentAddress, input);
				_clientState = None;
				break;
			}

			case QueriedOptional: {
				if(input == _T("y")) {
					_clientState = AcceptedOptional;
				}
				else if(input == _T("n")) {
					_clientState = DeclinedOptional;
				}
				else {
					return _T("Error! only 'y' or 'n' is accepted");
				}

				break;
			}
		}

		return nextValue();
	}

	//------------------------------------------------------------------------------------------------------------------
	tstring nextValue() { // Possible client states: None, AcceptedOptional, DeclinedOptional
		tstring response;

		if(_clientState == AcceptedOptional)
			return queryValue();

		// Go to next message node
		nextNode(_clientState == DeclinedOptional);

		auto& currentNode = schemaNode(_currentAddress);

		if(_messageComplete)
			return _T("");

		// Handle optional/array items
		if(currentNode[_T("optional")].bool_value() || currentNode[_T("type")] == _T("array")) {
			tstring description = currentNode[_T("description")].string_value();
			if(currentNode[_T("type")] == _T("array"))
				description = _T("a ") + currentNode[_T("items")][_T("description")].string_value() + _T(" value");

			response = _T("Do you want to add ") + description + _T("? y/n:");
			_clientState = QueriedOptional;
			return response;
		}

		return queryValue();
	}

	//------------------------------------------------------------------------------------------------------------------
	tstring queryValue() {
		auto& currentNode = schemaNode(_currentAddress);

		if(currentNode[_T("type")] == _T("object")) {
			return  _T("[") + currentNode[_T("description")].string_value() + _T("]\n") + nextValue();
		}

		else if(currentNode[_T("type")] == _T("array")) {
			return  _T("[") + currentNode[_T("description")].string_value() + _T("]\n") + nextValue();
		}

		else {
			_clientState = QueriedValue;
			return currentNode[_T("description")].string_value() + _T(": ");
		}
	}

	//------------------------------------------------------------------------------------------------------------------
	void clear() {
		_messageEmpty = true;
		_messageComplete = false;

		_clientState = None;

		_currentAddress = _T("");
		_message = PipeJson(PipeObject());
		_schema = PipeJson(PipeObject());
	}

private:
	//------------------------------------------------------------------------------------------------------------------
	void setValue(const tstring& address, const tstring& data) {
		auto& valueSchemaNode = schemaNode(address);
		auto& valueMessageNode = messageNode(address);

		if(valueSchemaNode[_T("type")] == _T("string")) {
			valueMessageNode = PipeJson(data);
		}
		else if(valueSchemaNode[_T("type")] == _T("number")) {
			valueMessageNode = PipeJson(std::stof(data));
		}
		else if(valueSchemaNode[_T("type")] == _T("bool")) {
			valueMessageNode = PipeJson((data == _T("true") ? true : false));
		}
		else {
			valueMessageNode = PipeJson(nullptr);
		}
	}

	//------------------------------------------------------------------------------------------------------------------
	PipeObject& schemaNode(const tstring& address) {
		PipeJson* resultNode = &_schema;

		auto nodes = texplode(address, _T('.'));
		for(size_t idx = 0, cnt = nodes.size(); idx < cnt; idx++) {
			PipeJson& currentNode = resultNode->operator[](nodes[idx]);

			if(currentNode[_T("type")] == _T("object") && ((idx + 1) < cnt)) {
				resultNode = &currentNode[_T("fields")];
			}
			else if(currentNode[_T("type")] == _T("array") && ((idx + 1) < cnt)) {
				resultNode = &currentNode[_T("items")];
				idx++; // Ignore the index
			}
			else {
				resultNode = &currentNode;
			}
		}

		return resultNode->object_items();
	}

	//------------------------------------------------------------------------------------------------------------------
	PipeJson& messageNode(const tstring& address) {
		PipeJson* resultNode = &_message;

		tstring currentPath;
		auto nodes = texplode(address, _T('.'));
		for(size_t idx = 0, cnt = nodes.size(); idx < cnt; idx++) {
			PipeJson& currentNode = resultNode->object_items()[nodes[idx]];

			// Get schema for this node
			currentPath += (idx == 0 ? _T("") : _T(".")) + nodes[idx];
			PipeObject& currentSchema = schemaNode(currentPath);

			// Initialize missing fields
			if(currentSchema[_T("type")] == _T("object") && !currentNode.is_object())
				currentNode = PipeJson(PipeObject());
			else if(currentSchema[_T("type")] == _T("array") && !currentNode.is_array())
				currentNode = PipeJson(PipeArray());

			if(currentNode.is_array() && ((idx + 1) < cnt)) { // We address array elements
				int arrIdx = std::stoi(nodes[idx + 1]);

				// Add item if index is not yet created
				if(currentNode.array_items().size() <= arrIdx) {
					currentNode.array_items().push_back(PipeJson());
				}

				resultNode = &currentNode.array_items()[arrIdx];
				idx++;
			}
			else {
				resultNode = &currentNode;
			}
		}

		return *resultNode;
	}

	//------------------------------------------------------------------------------------------------------------------
	void nextNode(bool endArray = false) {
		// First run, set to data
		if(_currentAddress.empty()) {
			_currentAddress = _T("data");
			return;
		}
		
		auto nodes = texplode(_currentAddress, _T('.'));
		auto& currentSchemaNode = schemaNode(_currentAddress);

		// Go to next array index if neccessary
		if(currentSchemaNode[_T("type")] == _T("array") && !endArray) {
			int oldIdx = std::stoi(nodes.back());
			nodes.back() = to_tstring(oldIdx + 1); // TODO: Test
			_currentAddress = timplode(nodes, _T('.'));
			return;
		}

		// Current item has children, go to first
		if(currentSchemaNode[_T("type")] == _T("object") && currentSchemaNode[_T("fields")].object_items().size() > 0) {
			_currentAddress += _T(".") + currentSchemaNode[_T("fields")].object_items().begin()->first;
			return;
		}

		// Current item has no chidlren
		
		tstring lastKey = nodes.back();
		nodes.pop_back();
		for(auto& levelSchemaNode = schemaNode(timplode(nodes, _T('.'))); !nodes.empty(); nodes.pop_back()) {
			if(levelSchemaNode[_T("type")] == _T("object")) {
				bool next = false;
				for(auto& field : levelSchemaNode[_T("fields")].object_items()) {
					// Search for the current key
					if(field.first == lastKey) {
						next = true;
						continue;
					}

					// If found use it
					if(next) {
						nodes.push_back(field.first);

						// If this is an array, add first index
						if(schemaNode(timplode(nodes, _T('.')))[_T("type")] == _T("array"))
							nodes.push_back(_T(".0"));

						_currentAddress = timplode(nodes, _T('.'));
						return;
					}
				}
			}

			lastKey = nodes.back();
		}

		if(nodes.empty()) {
			_messageComplete = true;
			return;
		}
	}
};

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
	PipeShellSendMessage _sendBuffer;

public:
	//------------------------------------------------------------------------------------------------------------------

	PipeShell(std::shared_ptr<LibPipeInstance> instance, const tstring& identifier, bool greeting = false)
		: _instance(instance)
		, _identifier(identifier)
		, _greeting(greeting)
		, _address(_T("pipe"))
		, _addressCommands(_instance->nodeCommandTypes(_address))

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
		if(_sendBuffer.isEmpty()) {
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

			if(shellCommand) {
				newShellCommand(command, parameter, address);
			}
			else {
				PipeJson* schema = nullptr;
				for(auto&& addressCommand : *addressCommands) {
					auto&& cmd = addressCommand.object_items();
					if(cmd[_T("command")].string_value() == command)
						schema = &cmd[_T("schema")];
				}

				// invalid command
				if(schema == nullptr) {
					_receiveBuffer << _T("Error! command not found");
					_sendBuffer.clear();
					return;
				}

				_receiveBuffer << _sendBuffer.start(_identifier, command, parameter, address, *schema);
				if(!_sendBuffer.isEmpty() && _sendBuffer.isComplete())
					_instance->send(_sendBuffer.getMessages());

			}
		}
		// This message has already been started
		else {
			_receiveBuffer << _sendBuffer.add(input);
			if(!_sendBuffer.isEmpty() && _sendBuffer.isComplete())
				_instance->send(_sendBuffer.getMessages());
		}
	}

	//------------------------------------------------------------------------------------------------------------------
	tstring receive() {
		tstringstream output;
		output << _receiveBuffer.str();
		_receiveBuffer.str(tstring());

		if(_sendBuffer.isEmpty()) {
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
