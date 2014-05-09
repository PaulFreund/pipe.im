//======================================================================================================================

#include "CommonHeader.h"
#include "LibPipe.h"

using namespace std;

//======================================================================================================================

vector<shared_ptr<LibPipe>>                 LibPipe::Instances;
vector<shared_ptr<PipeExtensionInstance>>   LibPipe::Extensions;

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

//----------------------------------------------------------------------------------------------------------------------

PipeArrayPtr LibPipe::nodeChildren(const tstring& address) {
	return _serviceRoot->nodeChildren(address);
}

//----------------------------------------------------------------------------------------------------------------------

PipeArrayPtr LibPipe::nodeCommandTypes(const tstring& address) {
	return _serviceRoot->nodeCommandTypes(address);
}

//----------------------------------------------------------------------------------------------------------------------

PipeArrayPtr LibPipe::nodeMessageTypes(const tstring& address) {
	return _serviceRoot->nodeMessageTypes(address);
}

//----------------------------------------------------------------------------------------------------------------------

PipeObjectPtr LibPipe::nodeInfo(const tstring& address) {
	return _serviceRoot->nodeInfo(address);
}

//======================================================================================================================