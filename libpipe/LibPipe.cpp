//======================================================================================================================

#include "CommonHeader.h"
#include "LibPipe.h"

#include "ServiceRoot.h"

using namespace std;

//======================================================================================================================

vector<shared_ptr<LibPipe>> LibPipe::Instances;
vector<shared_ptr<PipeExtensionInstance>> LibPipe::Extensions;

//======================================================================================================================

LibPipe::LibPipe(const tstring& path, const PipeJSON::array& serviceTypes) {
	PipeJSON::object settings {};
	settings[_T("serviceTypes")] = serviceTypes;
	// TODO: TEST!
	_serviceRoot = make_shared<ServiceRoot>(_T("pipe"), path, settings);
}

//----------------------------------------------------------------------------------------------------------------------

LibPipe::~LibPipe() {

}

//----------------------------------------------------------------------------------------------------------------------

void LibPipe::send(const PipeJSON::array& messages) {
	_serviceRoot->send(messages);
}

//----------------------------------------------------------------------------------------------------------------------

PipeJSON::array LibPipe::receive() {
	return _serviceRoot->receive();
}

//======================================================================================================================