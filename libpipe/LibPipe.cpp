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
	PipeJSON settings;
	settings.SetObject();
	settings.AddMember(_T("serviceTypes"), serviceTypes, settings.GetAllocator());
	//map<tstring, tstring> settings { make_pair(_T("serviceTypes"), timplode(serviceTypes, _T(','))) };
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