//======================================================================================================================

#include "CommonHeader.h"
#include "LibPipe.h"

#include "ServiceRoot.h"

using namespace std;

//======================================================================================================================

vector<shared_ptr<LibPipe>> LibPipe::Instances;
vector<shared_ptr<PipeExtensionInstance>> LibPipe::Extensions;

//======================================================================================================================

LibPipe::LibPipe(const tstring& path, PipeArrayPtr serviceTypes) {
	auto settings = newObject();
	(*settings)[_T("serviceTypes")] = *serviceTypes;
	_serviceRoot = make_shared<ServiceRoot>(_T("pipe"), path, settings);
}

//----------------------------------------------------------------------------------------------------------------------

LibPipe::~LibPipe() {

}

//----------------------------------------------------------------------------------------------------------------------

void LibPipe::send(PipeArrayPtr messages) {
	_serviceRoot->send(messages);
}

//----------------------------------------------------------------------------------------------------------------------

PipeArrayPtr LibPipe::receive() {
	return _serviceRoot->receive();
}

//======================================================================================================================