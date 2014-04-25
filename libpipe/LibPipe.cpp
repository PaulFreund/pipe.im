//======================================================================================================================

#include "CommonHeader.h"
#include "LibPipe.h"

#include "ServiceRoot.h"

using namespace std;

//======================================================================================================================

vector<shared_ptr<LibPipe>> LibPipe::Instances;
vector<shared_ptr<PipeExtensionInstance>> LibPipe::Extensions;

//======================================================================================================================

LibPipe::LibPipe(const tstring& path, PipeJsonArray serviceTypes) {
	PipeJsonObjectData settings {};
	settings[_T("serviceTypes")] = *serviceTypes;
	// TODO: TEST!
	_serviceRoot = make_shared<ServiceRoot>(_T("pipe"), path, std::make_shared<PipeJsonObjectData>(settings));
}

//----------------------------------------------------------------------------------------------------------------------

LibPipe::~LibPipe() {

}

//----------------------------------------------------------------------------------------------------------------------

void LibPipe::send(PipeJsonArray messages) {
	_serviceRoot->send(messages);
}

//----------------------------------------------------------------------------------------------------------------------

PipeJsonArray LibPipe::receive() {
	return _serviceRoot->receive();
}

//======================================================================================================================