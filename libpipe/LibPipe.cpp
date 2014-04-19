//======================================================================================================================

#include "CommonHeader.h"
#include "LibPipe.h"

#include "ServiceRoot.h"

using namespace std;

//======================================================================================================================

std::vector<LibPipe> LibPipe::Instances;
std::vector<PipeExtensionInstance> LibPipe::Extensions;

//======================================================================================================================

LibPipe::LibPipe(tstring path, vector<tstring> serviceTypes){
	map<tstring, tstring> settings { make_pair(_T("serviceTypes"), timplode(serviceTypes, _T(','))) };
	_serviceRoot = make_shared<ServiceRoot>(_T("pipe"), path, settings);
}

//----------------------------------------------------------------------------------------------------------------------

LibPipe::~LibPipe() {

}

//----------------------------------------------------------------------------------------------------------------------

void LibPipe::send(const LibPipeMessage& message) {
	_serviceRoot->send(message);
}

//----------------------------------------------------------------------------------------------------------------------

vector<LibPipeMessage> LibPipe::receive() {
	return _serviceRoot->receive();
}

//======================================================================================================================