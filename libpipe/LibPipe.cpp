//======================================================================================================================

#include "CommonHeader.h"
#include "LibPipe.h"

#include "BaseServiceService.h"
#include "BaseServiceScript.h"
#include "BaseServiceConfig.h"

using namespace std;

//======================================================================================================================

std::vector<LibPipe> LibPipe::Instances;
std::vector<PipeExtensionInstance> LibPipe::Extensions;

//======================================================================================================================

LibPipe::LibPipe(tstring path, vector<tstring> providers) : _path(path), _providers(providers) {
	map<tstring, tstring> settings;
	settings[_T("path")] = _path;

	_services[_T("script")] = make_shared<BaseServiceScript>(settings);
	_services[_T("config")] = make_shared<BaseServiceConfig>(settings);
	
	settings[_T("providers")] = timplode(_providers, _T(';'));
	_services[_T("service")] = make_shared<BaseServiceService>(settings);
}

//----------------------------------------------------------------------------------------------------------------------

LibPipe::~LibPipe() {

}

//----------------------------------------------------------------------------------------------------------------------

void LibPipe::send(const vector<LibPipeMessage>& messages) {

	// TODO: Check for hooks

	auto lenId = _id.length();
	for(auto&& message : messages) {
		if(message.type.empty()) {
			vector<tstring> parameters = { _T("Missing command") };
			_outgoing.push_back({ _id, _T("error"), parameters });
			continue;
		}

		// This is the destination
		if(message.address == _id) {
			handleCommand(message);
		}
		// The address can be dispatched
		else if(message.address.length() >= (lenId + 2) && message.address[lenId] == PAS) {

			auto second = message.address.find(PAS, lenId + 1);
			if(second == -1) { second = message.address.length(); }
			auto target = message.address.substr(lenId + 1, second);

			if(_services.find(target) == end(_services)) {
				vector<tstring> parameters = { _T("Address not available") };
				_outgoing.push_back({ _id, _T("error"), parameters });
				continue;
			}
			
			_services[target]->send({ message });
		}
		else {
			vector<tstring> parameters = { _T("Invalid Address") };
			_outgoing.push_back({ _id, _T("error"), parameters });
			continue;
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------

vector<LibPipeMessage> LibPipe::receive() {
	vector<LibPipeMessage> messages = _outgoing;
	_outgoing.clear();

	for(auto&& service : _services) {
		auto&& serviceOutgoing = service.second->receive();
		messages.insert(end(messages), begin(serviceOutgoing), end(serviceOutgoing));
	}

	// TODO: Check for hooks

	return messages;
}

//----------------------------------------------------------------------------------------------------------------------

void LibPipe::handleCommand(const LibPipeMessage& message) {
	// Handle commands
	// Handle status
	// Handle about
	// handle messages
	// handle children
}

//======================================================================================================================