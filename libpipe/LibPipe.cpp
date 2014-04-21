//======================================================================================================================

#include "CommonHeader.h"
#include "LibPipe.h"

#include "ServiceRoot.h"

using namespace std;

//======================================================================================================================

std::vector<LibPipe> LibPipe::Instances;
std::vector<PipeExtensionInstance> LibPipe::Extensions;

//======================================================================================================================

LibPipe::LibPipe(tstring path, PipeJSON serviceTypes) {
	PipeJSON::object settings {};
	settings[_T("serviceTypes")] = serviceTypes;
	// TODO: TEST!
	_serviceRoot = make_shared<ServiceRoot>(_T("pipe"), path, settings);
}

//----------------------------------------------------------------------------------------------------------------------

LibPipe::~LibPipe() {

}

//----------------------------------------------------------------------------------------------------------------------

void LibPipe::send(PipeJSON& message) {
	_serviceRoot->send(message);
}

//----------------------------------------------------------------------------------------------------------------------

PipeJSON LibPipe::receive() {
	return _serviceRoot->receive();
}

//======================================================================================================================