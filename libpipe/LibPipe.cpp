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
	_services[_T("service")] = make_shared<BaseServiceService>();	// TODO: Configuration
	_services[_T("script")] = make_shared<BaseServiceScript>();		// TODO: Configuration
	_services[_T("config")] = make_shared<BaseServiceConfig>();		// TODO: Configuration
}

//----------------------------------------------------------------------------------------------------------------------

LibPipe::~LibPipe() {

}

//----------------------------------------------------------------------------------------------------------------------

void LibPipe::send(const vector<LibPipeMessage>& messages) {
	for(auto& message : messages) {
		// TODO: Check for hooks

		// Check address and dispatch if neccessary
			// If available dispatch
			// If not, add error to outgoing

		// If address is empty, this is for us

		// Check command
			// Handle commands
			// Handle status
			// Handle about
			// handle messages
			// handle children

		_outgoing.push_back(message);
	}
}

//----------------------------------------------------------------------------------------------------------------------

vector<LibPipeMessage> LibPipe::receive() {
	// Process hooks
	// 
	vector<LibPipeMessage> messages = _outgoing;
	_outgoing.clear();
	return messages;
}

//======================================================================================================================