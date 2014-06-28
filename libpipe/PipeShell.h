//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipe.h"
#include "LibPipeHelper.h"
#include "PipeSchema.h"
#include <regex>

//======================================================================================================================

const tstring IndentSymbol = _T("    ");

//======================================================================================================================

class PipeSchemaGenerator {
	enum PipeSchemaGeneratorState {
		None,
		QueriedValue,
		QueriedEnum,
		QueriedDefault,
		QueriedOptional,
		AcceptedOptional,
		DeclinedOptional,
		AcceptedDefault,
		DeclinedDefault,
	};

private:
	bool _instanceEmpty;
	bool _instanceComplete;

	PipeSchemaGeneratorState _clientState;

	tstring _currentAddress;
	int _nodeLevel;
	bool _newItem;

	PipeJson _instance;
	PipeJson _schema;

public:
	PipeSchemaGenerator()
		: _instanceEmpty(true)
		, _instanceComplete(true)
		, _clientState(None)
		, _nodeLevel(0)
		, _newItem(false)
		, _currentAddress(_T(""))
		, _instance(PipeJson(PipeObject()))
		, _schema(nullptr)
		{}

public:
	//------------------------------------------------------------------------------------------------------------------
	bool empty() { return _instanceEmpty; }

	//------------------------------------------------------------------------------------------------------------------
	bool complete() { return _instanceComplete; }

	//------------------------------------------------------------------------------------------------------------------
	PipeJson& instance() { return _instance; }

	//------------------------------------------------------------------------------------------------------------------
	tstring start(PipeJson& schema, const tstring& parameter = _T("")) {
		clear();

		PipeSchema* schemaData = reinterpret_cast<PipeSchema*>(&schema.object_items());
		if(schemaData == nullptr || schemaData->type() == PipeSchemaTypeNone)
			return _T("Error! Invalid schema supplied");

		_schema = schema;
		_instanceEmpty = false;

		PipeSchemaType schemaType = schemaData->type();
		if(schemaType == PipeSchemaTypeObject || schemaType == PipeSchemaTypeArray) {
			if(!parameter.empty()) { return _T("Error! Schema can not be created by parameter"); }
			return queryValue();
		}
		else {
			_instanceEmpty = false;
			_instanceComplete = true;
			return setValue(_T(""), parameter);
		}
	}

	//------------------------------------------------------------------------------------------------------------------
	tstring add(const tstring& input) {
		switch(_clientState) {
			case QueriedValue: {
				tstring error = setValue(_currentAddress, input);
				if(!error.empty()) { return error; }

				_clientState = None;
				break;
			}

			case QueriedOptional: {
				tstring response = input;
				std::transform(begin(response), end(response), begin(response), ::tolower);
				if(response == _T("yes") || response == _T("y")) {
					_clientState = AcceptedOptional;
					return queryValue();
				}
				else if(response == _T("no") || response == _T("n")) {
					_clientState = DeclinedOptional;
				}
				else {
					return _T("Error! Only 'yes' or 'no' are accepted");
				}

				break;
			}
			case QueriedDefault: {
				tstring response = input;
				std::transform(begin(response), end(response), begin(response), ::tolower);
				if(response == _T("yes") || response == _T("y")) {
					valueNode(_currentAddress) = schemaNode(_currentAddress).defaultValue();
					_clientState = None;
				}
				else if(response == _T("no") || response == _T("n")) {
					_clientState = DeclinedDefault;
					return queryValue();
				}
				else {
					return _T("Error! Only 'yes' or 'no' are accepted");
				}

				break;
			}

			case QueriedEnum: {
				auto& currentNode = schemaNode(_currentAddress);
				auto& enumOptions = currentNode.enumTypes();
				int response = -1;
				try { response = std::stoi(input); } catch(...) {}

				if(response >= 0 && response < enumOptions.size())
					valueNode(_currentAddress) = enumOptions[response];
				else
					return _T("Error! Only 0-") + to_tstring(enumOptions.size() - 1) + _T(" are accepted");

				_clientState = None;
				break;
			}
			case None:
			default: {
				break;
			}
		}

		return nextValue();
	}

	//------------------------------------------------------------------------------------------------------------------
	void clear() {
		_instanceEmpty = true;
		_instanceComplete = false;
		_clientState = None;
		_currentAddress = _T("");
		_nodeLevel = 0;
		_newItem = false;
		_instance = PipeJson(PipeObject());
		_schema = nullptr;
	}

private:
	//------------------------------------------------------------------------------------------------------------------
	tstring nextValue() {
		// Go to next message node
		nextNode(_clientState == DeclinedOptional);
		_nodeLevel = texplode(_currentAddress, TokenAddressSeparator).size();
		_clientState = None;

		// Instance is complete
		if(_instanceComplete) { return _T("Instance completed\n"); }

		return queryValue();
	}

	//------------------------------------------------------------------------------------------------------------------
	tstring queryValue() {
		auto& currentNode = schemaNode(_currentAddress);
		auto nodeType = currentNode.type();

		tstring indent; for(auto idx = 0; idx < _nodeLevel; idx++) { indent += IndentSymbol; }

		tstring result;
		if(nodeType == PipeSchemaTypeObject || (_newItem && nodeType == PipeSchemaTypeArray)) {
			result += indent + _T("[") + currentNode.description() + _T("]\n");
		}
		_newItem = false;

		// Check if this is an optional value
		bool optional = false;
		auto tokenList = texplode(_currentAddress, TokenAddressSeparator);
		if(!tokenList.empty()) {
			tstring currentProperty = tokenList.back();
			tokenList.resize(tokenList.size() - 1);
			auto parent = schemaNode(timplode(tokenList, TokenAddressSeparator));

			if(parent.isDefined(_T("required"))) {
				optional = true;
				auto requiredList = parent.required();
				if(std::find(begin(requiredList), end(requiredList), currentProperty) != end(requiredList))
					optional = false;
			}
		}

		// Enforce array bounds
		auto min = currentNode.minItems();
		auto max = currentNode.maxItems();
		if(nodeType == PipeSchemaTypeArray && (min != 0 || max != 0)) {
			auto value = valueNode(_currentAddress);
			if(value.is_array()) {
				PipeArray& elements = value.array_items();
				if(min != 0 && elements.size() < min) { _clientState = AcceptedOptional; }
				if(max != 0 && elements.size() >= max) { 
					_clientState = DeclinedOptional; 
					return nextValue();
				}
			}
		}

		// Ask if optional element should be added
		if(_clientState == None && (optional || nodeType == PipeSchemaTypeArray)) {
			tstring description = currentNode.description();
			if(nodeType == PipeSchemaTypeArray)
				description = _T("a ") + description + _T(" value");

			result += indent + _T("Do you want to add ") + description + _T("? y/n: ");
			_clientState = QueriedOptional;
			return result;
		}
		// Ask if the default value should be used
		else if(_clientState != DeclinedDefault && currentNode.defaultValue() != PipeSchemaConstants::EmptyValue) {
			result += indent + _T("Do you want to use the default value (") + currentNode.defaultValue().dump() + _T(")? for ") + currentNode.description() + _T(" y/n: ");
			_clientState = QueriedDefault;
			return result;
		}
		// Ask for properties/items
		else if(nodeType == PipeSchemaTypeObject || nodeType == PipeSchemaTypeArray) {
			_clientState = None;
			return result += nextValue();
		}
		// Ask for value
		else {
			result += indent;
			result += _T("Value for ") + currentNode.description();
			result += _T(" [") + schemaTypeString(nodeType) + _T("]: ");

			// Check if we have to ask for an enum value
			if(!currentNode.enumTypes().empty()) {
				tstringstream options;
				options << std::endl;
				auto& enumOptions = currentNode.enumTypes();
				for(int idx = 0, cnt = enumOptions.size(); idx < cnt; idx++) {
					options << indent << std::setw(IndentSymbol.size()) << idx << _T(": ") << enumOptions[idx].dump() << std::endl;
				}
				options << indent << _T("Please choose an option(0-") << enumOptions.size()-1 << _T("): ");
				result += options.str();
				_clientState = QueriedEnum;
			}
			else {
				_clientState = QueriedValue;
			}

			return result;
		}
	}

	//------------------------------------------------------------------------------------------------------------------
	tstring setValue(const tstring& address, const tstring& data) {
		auto& valueMessageNode = valueNode(address);

		tstring schemaAddress = address.empty() ? TokenMessageData : address;
		auto& schemaMessageNode = schemaNode(schemaAddress);
		
		try {
			switch(schemaMessageNode.type()) {
				case PipeSchemaTypeBoolean: {
					tstring response = data;
					std::transform(begin(response), end(response), begin(response), ::tolower);
					if(response == _T("true") || response == _T("on") || response == _T("yes") || response == _T("y") || response == _T("1"))
						valueMessageNode = PipeJson(true); 
					else if(response == _T("false") || response == _T("off") || response == _T("no") || response == _T("n") || response == _T("0"))
						valueMessageNode = PipeJson(false); 
					else { return _T("Error! Only 'true' or 'false' are allowed"); }
					break;
				}
				
				case PipeSchemaTypeInteger: {
					int value = 0;
					try { value = std::stoi(data); }
					catch(...) { return _T("Error! Value does not seem to be a valid integer"); }

					int mo = schemaMessageNode.multipleOf();
					if(mo != 0) { if((value%mo) != 0) { return _T("Error! Value has to be a multiple of ") + to_tstring(mo) + _T("."); } }

					int min = schemaMessageNode.minimum();
					if(min != 0) { 
						if(schemaMessageNode.exclusiveMinimum()) {
							if(value <= min) { return _T("Error! Value has to be bigger than ") + to_tstring(min) + _T("."); }
						}
						else {
							if(value < min) { return _T("Error! Value has to be at least ") + to_tstring(min) + _T("."); }
						}
					}

					int max = schemaMessageNode.maximum();
					if(max != 0) { 
						if(schemaMessageNode.exclusiveMaximum()) {
							if(value >= max) { return _T("Error! Value has to be smaller than ") + to_tstring(max) + _T("."); }
						}
						else {
							if(value > max) { return _T("Error! Value has to be ") + to_tstring(max) + _T(" at most."); }
						}
					}

					valueMessageNode = PipeJson(value);
					break; 
				}
				
				case PipeSchemaTypeNumber: {
					double value = 0;
					try { value = std::stod(data); }
					catch(...) { return _T("Error! Value does not seem to be a valid number"); }

					double mo = schemaMessageNode.fmultipleOf();
					if(mo != 0.0) { if(fmod(value, mo) != 0) { return _T("Error! Value has to be a multiple of ") + to_tstring(mo) + _T("."); } }

					double min = schemaMessageNode.fminimum();
					if(min != 0.0) {
						if(schemaMessageNode.exclusiveMinimum()) {
							if(value <= min) { return _T("Error! Value has to be bigger than ") + to_tstring(min) + _T("."); }
						}
						else {
							if(value < min) { return _T("Error! Value has to be at least ") + to_tstring(min) + _T("."); }
						}
					}

					double max = schemaMessageNode.fmaximum();
					if(max != 0.0) {
						if(schemaMessageNode.exclusiveMaximum()) {
							if(value >= max) { return _T("Error! Value has to be smaller than ") + to_tstring(max) + _T("."); }
						}
						else {
							if(value > max) { return _T("Error! Value has to be ") + to_tstring(max) + _T(" at most."); }
						}
					}

					valueMessageNode = PipeJson(value);
					break; 
				}
				
				case PipeSchemaTypeString: {
					int min = schemaMessageNode.minLength();
					if(min != 0) { if(data.length() < min) { return _T("Error! String must not be shorter than ") + to_tstring(min) + _T(" characters."); } }

					int max = schemaMessageNode.maxLength();
					if(max != 0) { if(data.length() > max) { return _T("Error! String must not be longer than ") + to_tstring(max) + _T(" characters."); } }

					tstring pattern = schemaMessageNode.pattern();
					if(!pattern.empty()) {
						if(!std::regex_match(data, std::regex(pattern)))
							return _T("Error! String does not match pattern (") + pattern + _T(").");
					}

					valueMessageNode = PipeJson(data);
					break;
				}

				case PipeSchemaTypeNull: {
					valueMessageNode = PipeJson(nullptr);
					break;
				}

				default: {
					valueMessageNode = PipeJson(data);
					break;
				}
			}
			return _T("");
		}
		catch(...) {
			return _T("Error! unexpected value");
		}
	}

	//------------------------------------------------------------------------------------------------------------------
	PipeSchema& schemaNode(const tstring& address) {
		auto nodes = texplode(address, TokenAddressSeparator);

		PipeSchema* currentNode = reinterpret_cast<PipeSchema*>(&_schema.object_items());
		while(!nodes.empty()) {
			if(currentNode->type() == PipeSchemaTypeObject) {
				currentNode = &currentNode->property(*begin(nodes));
			}
			else if(currentNode->type() == PipeSchemaTypeArray) {
				currentNode = &currentNode->items();
			}

			nodes.erase(begin(nodes));
		}

		return *currentNode;
	}

	//------------------------------------------------------------------------------------------------------------------
	PipeSchema& schemaNodeParent(const tstring& address) {
		auto nodes = texplode(address, TokenAddressSeparator);
		if(!nodes.empty()) { nodes.resize(nodes.size() - 1); }
		return schemaNode(timplode(nodes, TokenAddressSeparator));
	}

	//------------------------------------------------------------------------------------------------------------------
	PipeJson& valueNode(const tstring& address) {
		// This function should be refactored but works
		PipeJson* resultNode = &_instance;

		tstring currentPath;
		auto nodes = texplode(address, TokenAddressSeparator);
		for(size_t idx = 0, cnt = nodes.size(); idx < cnt; idx++) {
			PipeJson& currentNode = resultNode->object_items()[nodes[idx]];

			// Get schema for this node
			if(idx != 0) { currentPath += TokenAddressSeparator; }
			currentPath += nodes[idx];
			auto& currentSchema = schemaNode(currentPath);

			// Initialize missing properties
			if(currentSchema.type() == PipeSchemaTypeObject && !currentNode.is_object())
				currentNode = PipeJson(PipeObject());
			else if(currentSchema.type() == PipeSchemaTypeArray && !currentNode.is_array())
				currentNode = PipeJson(PipeArray());

			if(currentNode.is_array() && ((idx + 1) < cnt)) { // We address array elements
				int arrIdx = std::stoi(nodes[idx + 1]);

				// Add item if index is not yet created
				if(currentNode.array_items().size() <= arrIdx) {
					auto& nestedSchema = currentSchema.items();

					if(nestedSchema.type() == PipeSchemaTypeObject)
						currentNode.array_items().push_back(PipeJson(PipeObject()));
					else if(nestedSchema.type() == PipeSchemaTypeArray)
						currentNode.array_items().push_back(PipeJson(PipeArray()));
					else
						currentNode.array_items().push_back(PipeJson());
				}

				resultNode = &currentNode.array_items()[arrIdx];
				currentPath += TokenAddressSeparator + nodes[idx+1];
				idx++;
			}
			else {
				resultNode = &currentNode;
			}
		}

		return *resultNode;
	}

	//------------------------------------------------------------------------------------------------------------------
	void nextNode(bool jumpOut = false) {
		tstring lastKey = _T("");
		auto nodes = texplode(_currentAddress, TokenAddressSeparator);
		tstring currentNodeAddress = _currentAddress;
		auto* currentNode = &schemaNode(currentNodeAddress);
		auto currentNodeType = currentNode->type();

		// Iterate over the levels 
		while(true) {
			if(jumpOut) { jumpOut = false; } // Try to go into node if not declined

			else if(currentNodeType == PipeSchemaTypeArray) {
				if(lastKey.empty()) {
					auto& arrayNode = valueNode(currentNodeAddress).array_items();
					nodes.push_back(to_tstring(arrayNode.size()));
					_currentAddress = timplode(nodes, TokenAddressSeparator);
					return;
				}
				else {
					_currentAddress = currentNodeAddress;
					return;
				}
			}

			else if(currentNodeType == PipeSchemaTypeObject && currentNode->properties().size() > 0) {
				bool next = false;
				for(auto& property : currentNode->properties()) {
					// Search for the current key
					if(property.first == lastKey) { next = true; continue; }

					// If found or this is the first, use it
					if(next || lastKey.empty()) {
						_newItem = true;
						nodes.push_back(property.first);
						_currentAddress = timplode(nodes, TokenAddressSeparator);
						return;
					}
				}
			}

			// Stop when no nodes are left and we are finished
			if(nodes.empty()) { _instanceComplete = true; return; }

			// Prepare next level
			lastKey = nodes.back();
			nodes.pop_back();
			currentNodeAddress = timplode(nodes, TokenAddressSeparator);
			currentNode = &schemaNode(currentNodeAddress);
			currentNodeType = currentNode->type();
			jumpOut = false; // Only the first level can be declined
		}
	}
};

//======================================================================================================================

struct PipeCommandBuffer {
	PipeCommandBuffer() {}
	PipeCommandBuffer(const tstring& identifier_, const tstring& address_, const tstring& command_)
		: identifier(identifier_)
		, address(address_)
		, command(command_)
	{}

	tstring identifier;
	tstring address;
	tstring command;
	PipeSchemaGenerator data;

	PipeJson instance() {
		PipeJson msg = PipeJson(PipeObject());
		PipeObject& msgObj = msg.object_items();
		msgObj[TokenMessageRef] = identifier;
		msgObj[TokenMessageAddress] = address;
		msgObj[TokenMessageCommand] = command;

		if(!data.empty() && data.complete())
			msgObj[TokenMessageData] = data.instance();

		return std::move(msg);
	}
};

//======================================================================================================================

class PipeShell {
private:
	//------------------------------------------------------------------------------------------------------------------
	const tstring _greetingText = _T("Welcome to the pipe shell, type help for further assistance\n");
	const tstring _abortText = _T("!abortcommand");
private:
	//------------------------------------------------------------------------------------------------------------------
	const tstring _identifier;
	bool _greeting;

	tstring _address;
	PipeArrayPtr _addressCommands;

	tstringstream _receiveBuffer;
	PipeCommandBuffer _sendBuffer;

public:
	//------------------------------------------------------------------------------------------------------------------

	PipeShell(const tstring& identifier, bool greeting = false)
		: _identifier(identifier)
		, _greeting(greeting)
		, _address(_T("pipe"))
		, _addressCommands(LibPipe::nodeCommandTypes(_address))

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
		newAddressCommands = LibPipe::nodeCommandTypes(newAddressAbsolute);
		if(LibPipe::nodeInfo(newAddressAbsolute)->empty())
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

	bool addOutgoing(const tstring& input) {
		// Abort command
		if(input == _abortText) {
			_sendBuffer.data.clear();
			_receiveBuffer << _T("Aborted command.") << std::endl;
			return false;
		}

		// New command
		if(_sendBuffer.data.empty()) {
			auto&& fragments = texplode(input, _T(' '));
			if(fragments.size() <= 0) { return false; }

			// Extract possible address
			auto address = _address;
			auto addressCommands = _addressCommands;
			if(fragments.size() >= 2) {
				if(fragments[0] == _T("pipe") || fragments[0].find_first_of(TokenAddressSeparator) != tstring::npos) {
					address = fragments[0];
					addressCommands = LibPipe::nodeCommandTypes(address);
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
					if(cmd[TokenMessageCommand].string_value() == command)
						schema = &addressCommand[_T("data_schema")];
				}

				// Invalid command
				if(schema == nullptr) {
					_receiveBuffer << _T("Error! command not found");
					return false;
				}

				_sendBuffer = PipeCommandBuffer(_identifier, address, command);
				
				// If data has to be supplied, start 
				if(!schema->object_items().empty())
					_receiveBuffer << _sendBuffer.data.start(*schema, parameter);

				return (_sendBuffer.data.empty() || _sendBuffer.data.complete());
			}
		}
		// This message has already been started
		else {
			_receiveBuffer << _sendBuffer.data.add(input);
			return (_sendBuffer.data.empty() || _sendBuffer.data.complete());
		}

		return false;
	}

	//------------------------------------------------------------------------------------------------------------------

	tstring addIncoming(PipeArrayPtr messages) {
		tstringstream output;
		output << _receiveBuffer.str();
		_receiveBuffer.str(tstring());

		for(auto& msg : *messages) {
			if(!msg.is_object()) { continue; }

			if(!output.str().empty())
				output << std::endl;

			auto&& obj = msg.object_items();
			if(!obj.count(TokenMessageRef) || !obj.count(TokenMessageAddress) || !obj.count(TokenMessageMessage) || !obj.count(TokenMessageData)) { continue; }

			auto ref = obj[TokenMessageRef].string_value();
			if(ref != _identifier && !ref.empty()) { continue; }

			auto address = obj[TokenMessageAddress].string_value();
			auto type = obj[TokenMessageMessage].string_value();
			auto data = obj[TokenMessageData];

			tstring source = address + _T(" - ") + type;

			if(data.is_object() || data.is_array()) {
				if((data.is_object() && data.object_items().empty()) || (data.is_array() && data.array_items().empty())) 
					output << source << _T(": Empty");
				else
					generateOutput(output, source, data);
			}
			else {
				output << source << _T(" ");

				if(data.is_bool()) {
					output << (data.bool_value() ? _T("true") : _T("false"));
				}
				else if(data.is_number()) {
					if(data.is_integer())
						output << to_tstring(data.int_value());
					else
						output << to_tstring(data.number_value());
				}
				else {
					output << data.string_value(); // Assume string
				}
			}
		}

		return output.str();
	}

	//------------------------------------------------------------------------------------------------------------------

	PipeJson getOutgoing() {
		PipeJson result = _sendBuffer.instance();
		_sendBuffer.data.clear();
		return result;
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
		else if(cmd == _T("tree")) { return true; }
		
		return false;
	}

	//------------------------------------------------------------------------------------------------------------------

	void newShellCommand(const tstring& command, const tstring& parameter, const tstring& address) {
		tstring cmd = command;
		if(command[0] == _T('!'))
			cmd.erase(begin(cmd));

		//--------------------------------------------------------------------------------------------------------------
		if(cmd == _T("help")) {
			tstring helpAddress = (parameter.length() > 0 ? getAbsoluteAddress(parameter) : getAbsoluteAddress(address));
			if(helpAddress.length() == 0) {
				_receiveBuffer << _T("Invalid address") << std::endl;
				return;
			}

			auto addressCommands = LibPipe::nodeCommandTypes(helpAddress);
			if(LibPipe::nodeInfo(helpAddress)->empty()) {
				_receiveBuffer << _T("Invalid node") << std::endl;
				return;
			}

			size_t cmdWidth = 0;
			for(auto&& command : *addressCommands) {
				auto&& cmd = command.object_items();
				auto objWidth = cmd[TokenMessageCommand].string_value().length();
				if(objWidth > cmdWidth)
					cmdWidth = objWidth;
			}

			_receiveBuffer << std::setfill(_T(' ')) ;
			_receiveBuffer << _T("Shell commands:") << std::endl;
			_receiveBuffer << IndentSymbol << std::setw(cmdWidth) << _T("help") << _T(" - ") << _T("Print a list of available commands") << std::endl;
			_receiveBuffer << IndentSymbol << std::setw(cmdWidth) << _T("usage") << _T(" - ") << _T("Print additional usage information") << std::endl;
			_receiveBuffer << IndentSymbol << std::setw(cmdWidth) << _T("ls") << _T(" - ") << _T("Get a list of child nodes") << std::endl;
			_receiveBuffer << IndentSymbol << std::setw(cmdWidth) << _T("cd") << _T(" - ") << _T("Set current node address") << std::endl;
			_receiveBuffer << IndentSymbol << std::setw(cmdWidth) << _T("pwd") << _T(" - ") << _T("Get current node address") << std::endl;
			_receiveBuffer << IndentSymbol << std::setw(cmdWidth) << _T("tree") << _T(" - ") << _T("Print a tree of subnodes") << std::endl;
			_receiveBuffer << std::endl;
			_receiveBuffer << _T("Node commands:") << std::endl;
			for(auto&& command : *addressCommands) {
				auto&& cmd = command.object_items();
				_receiveBuffer << IndentSymbol << std::setw(cmdWidth) << cmd[TokenMessageCommand].string_value() << _T(" - ") << cmd[_T("description")].string_value() << std::endl;
			}
		}

		//--------------------------------------------------------------------------------------------------------------
		if(cmd == _T("usage")) {
			_receiveBuffer << _T("Syntax to supply parameters on demand:") << std::endl;
			_receiveBuffer << IndentSymbol << _T("[<address>] <command>") << std::endl;
			_receiveBuffer << std::endl;
			_receiveBuffer << _T("Syntax if there is only on parameter for the command:") << std::endl;
			_receiveBuffer << IndentSymbol << _T("[<address>] <command> <parameter>") << std::endl;
			_receiveBuffer << std::endl;
			_receiveBuffer << _T("You can abort a command at any time by sending \"") + _abortText + _T("\".") << std::endl;
		}

		//--------------------------------------------------------------------------------------------------------------
		else if(cmd == _T("ls")) {
			tstring lsAddress = (parameter.length() > 0 ? getAbsoluteAddress(parameter) : getAbsoluteAddress(address));
			if(lsAddress.length() == 0) {
				_receiveBuffer << _T("Invalid address") << std::endl;
				return;
			}

			auto info = LibPipe::nodeInfo(lsAddress);
			if(info->size() == 0) {
				_receiveBuffer << _T("Invalid address") << std::endl;
				return;
			}

			auto children = LibPipe::nodeChildren(lsAddress);
			if(children->size() == 0) {
				_receiveBuffer << _T("No children") << std::endl;
				return;
			}

			for(auto&& child : *children)
				_receiveBuffer << texplode(child.string_value(), TokenAddressSeparator).back() << _T(" ");

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
		else if(cmd == _T("tree")) {
			tstring treeAddress = (parameter.length() > 0 ? getAbsoluteAddress(parameter) : getAbsoluteAddress(address));
			if(treeAddress.length() == 0) {
				_receiveBuffer << _T("Invalid address") << std::endl;
				return;
			}

			auto info = LibPipe::nodeInfo(treeAddress);
			if(info->size() == 0) {
				_receiveBuffer << _T("Invalid address") << std::endl;
				return;
			}

			std::function<void(tstring, tstring)> printChildren = [&](tstring address, tstring indent) {
				auto addressParts = texplode(address, TokenAddressSeparator);
				_receiveBuffer << indent << addressParts.back() << std::endl;

				auto children = LibPipe::nodeChildren(address);
				for(auto&& child : *children)
					printChildren(child.string_value(), indent + IndentSymbol);
			};

			printChildren(treeAddress, _T(""));
		}

		//--------------------------------------------------------------------------------------------------------------
	}

	//------------------------------------------------------------------------------------------------------------------

	bool isPipeCommand(const tstring& commandName, const PipeArrayPtr& addressCommands) {
		for(auto&& command : *addressCommands) {
			auto&& commandObj = command.object_items();
			if(commandObj[TokenMessageCommand].string_value() == commandName) {
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
			for(auto&& property : data.object_items()) {
				generateOutput(output, property.first, property.second, (first ? _T("") : (indent + IndentSymbol)), first);
				first = false;
			}
		}
		else if(data.is_array()) {
			if(!arrayItem) { output << _T(": ") << std::endl; }

			auto& items = data.array_items();
			for(auto item = begin(items); item != end(items); item++) {
				generateOutput(output, _T("  - "), *item, (indent + IndentSymbol), true);
				if((item + 1) != end(items)) { output << std::endl; }
			}
		}
		else {
			if(key != _T("  - ")) { output << _T(": "); }

			if(data.is_bool()) {
				output << (data.bool_value() ? _T("true") : _T("false"));
			}
			else if(data.is_number()) {
				if(data.is_integer())
					output << to_tstring(data.int_value());
				else
					output << to_tstring(data.number_value());
			}
			else {
				output << data.string_value(); // Assume string
			}


			output << std::endl;
		}
	}

	//------------------------------------------------------------------------------------------------------------------

	tstring getAbsoluteAddress(const tstring& address) {
		tstring absolute = address;

		if(address == _T("..")) {
			auto addressFragments = texplode(_address, TokenAddressSeparator);
			if(addressFragments.size() < 2)
				return _T("");

			addressFragments.erase(addressFragments.begin() + (addressFragments.size() - 1));
			absolute = timplode(addressFragments, TokenAddressSeparator);
		}
		else if(address == _T(".")) {
			return _address;
		}
		else if(address != _T("pipe") && address.find_first_of(TokenAddressSeparator) == tstring::npos) {
			absolute = _address + _T(".") + address;
		}

		return absolute;
	}

	//------------------------------------------------------------------------------------------------------------------
};

//======================================================================================================================
