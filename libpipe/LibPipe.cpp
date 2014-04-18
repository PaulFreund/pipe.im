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
	map<tstring, tstring> settings;

	settings[_T("path")] = path;
	settings[_T("serviceTypes")] = timplode(serviceTypes, _T(','));

	_serviceRoot = make_shared<ServiceRoot>(settings);
}

//----------------------------------------------------------------------------------------------------------------------

LibPipe::~LibPipe() {

}

//----------------------------------------------------------------------------------------------------------------------

void LibPipe::send(const vector<LibPipeMessage>& messages) {
	_serviceRoot->send(messages);
}

//----------------------------------------------------------------------------------------------------------------------

vector<LibPipeMessage> LibPipe::receive() {
	return _serviceRoot->receive();
}

//======================================================================================================================