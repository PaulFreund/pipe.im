#include "LibPipeItf.h"
#include "PipeExtensionItf.h"

#include <map>
using namespace std;

map<string, PipeExtensionServiceProvider> _serviceProviders;


//======================================================================================================================

LIBPIPE_ITF void LibPipeLoadExtension(LibPipeZtStr path) {
}

LIBPIPE_ITF void LibPipeGetServiceProviders(LibPipeCbServiceProviders) {

}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeCreateInstance(LibPipeZtStr path, LibPipeZtStr* serviceProviders, LibPipeEleCnt serviceProviderCount, LibPipeInstance* instance) {

}

LIBPIPE_ITF void LibPipeDestroyInstance(LibPipeInstance instance) {

}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeSend(LibPipeInstance instance, LibPipeMessageData* messages, LibPipeEleCnt count) {

}

LIBPIPE_ITF void LibPipeReceive(LibPipeInstance instance, LibPipeCbMessages) {

}

//======================================================================================================================