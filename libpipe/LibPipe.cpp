//======================================================================================================================

#include "CommonHeader.h"
#include "LibPipe.h"

using namespace std;

//======================================================================================================================

std::vector<LibPipe> LibPipe::Instances;
std::vector<PipeExtensionInstance> LibPipe::Extensions;

//======================================================================================================================

LibPipe::LibPipe(tstring path, vector<tstring> providers) 
: _path(path), _providers(providers) {

}

//----------------------------------------------------------------------------------------------------------------------

LibPipe::~LibPipe() {

}

//----------------------------------------------------------------------------------------------------------------------

void LibPipe::send(const vector<LibPipeMessage>& messages) {
	for(auto& message : messages) {
		_outgoing.push_back(message);
	}
}

//----------------------------------------------------------------------------------------------------------------------

vector<LibPipeMessage> LibPipe::receive() {
	vector<LibPipeMessage> messages = _outgoing;
	_outgoing.clear();
	return messages;
}

//======================================================================================================================