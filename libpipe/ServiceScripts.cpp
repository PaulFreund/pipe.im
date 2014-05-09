//======================================================================================================================

#include "CommonHeader.h"
#include "ServiceScripts.h"
using namespace std;

//======================================================================================================================

ServiceScripts::ServiceScripts(const tstring& address, const tstring& path, PipeObjectPtr settings) 
	: PipeServiceNodeBase(_T("scripts"), _T("Manager of automation scripts"), address, path, settings) 
{

}

//----------------------------------------------------------------------------------------------------------------------

void ServiceScripts::processPreSend(PipeArrayPtr messages) {

}

//----------------------------------------------------------------------------------------------------------------------

void ServiceScripts::processPostReceive(PipeArrayPtr messages) {

}

//----------------------------------------------------------------------------------------------------------------------

ServiceScripts::~ServiceScripts() {
}

//======================================================================================================================
