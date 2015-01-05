//======================================================================================================================
/*
	Copyright (c) since 2015 - Paul Freund (freund.paul@lvl3.org)
	
	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:
	
	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/
//======================================================================================================================

#include "CommonHeader.h"
#include "ServiceRoot.h"
#include "PipeExtensionInstance.h"

using namespace std;

//======================================================================================================================

static bool InitDone;
static tstring InstancePath;

static LibPipeCbContext ErrorCallbackContext;
static LibPipeCbErr ErrorCallback;

static shared_ptr<ServiceRoot> ServiceRootInstance;

//======================================================================================================================

void publishError(tstring error) {
	if(ErrorCallback != nullptr)
		ErrorCallback(ErrorCallbackContext, error.c_str());
}

//----------------------------------------------------------------------------------------------------------------------

void* loadExtensionSymbol(void* library, const tstring& path, const tstring& name) {
	if(!libraryHasSymbol(library, name))
		throw tstring(_T("LibPipeLoadExtensions: library ") + path + _T(" is missing symbol ") + name);

	void* symbol = libraryGetSymbol(library, name);
	if(symbol == nullptr)
		throw tstring(_T("LibPipeLoadExtensions: library ") + path + _T(" returned invalid symbol ") + name);

	return symbol;
}

//----------------------------------------------------------------------------------------------------------------------

void loadExtension(const tstring& path) {
	if(path.length() <= LibrarySuffix.length())
		return;

	auto ext = path.substr(path.length() - LibrarySuffix.length(), string::npos);
	if(!fileIsFile(path) || ext != LibrarySuffix)
		return;

	void* library = libraryLoad(path);
	if(library == nullptr) { return; }

	if(!libraryHasSymbol(library, NamePipeExtensionGetServiceTypes))
		return;

	PipeExtensionFunctions extensionFunctions;
	try {
		extensionFunctions.fktPipeExtensionSetErrorCallback = reinterpret_cast<FktPipeExtensionSetErrorCallback>    (loadExtensionSymbol(library, path, NamePipeExtensionSetErrorCallback ));
		extensionFunctions.fktPipeExtensionSetPath          = reinterpret_cast<FktPipeExtensionSetPath>             (loadExtensionSymbol(library, path, NamePipeExtensionSetPath          ));

		extensionFunctions.fktPipeExtensionGetServiceTypes  = reinterpret_cast<FktPipeExtensionGetServiceTypes>     (loadExtensionSymbol(library, path, NamePipeExtensionGetServiceTypes  ));
		extensionFunctions.fktPipeExtensionServiceCreate    = reinterpret_cast<FktPipeExtensionServiceCreate>       (loadExtensionSymbol(library, path, NamePipeExtensionServiceCreate    ));
		extensionFunctions.fktPipeExtensionServiceDestroy   = reinterpret_cast<FktPipeExtensionServiceDestroy>      (loadExtensionSymbol(library, path, NamePipeExtensionServiceDestroy   ));

		extensionFunctions.fktPipeExtensionProcess          = reinterpret_cast<FktPipeExtensionProcess>             (loadExtensionSymbol(library, path, NamePipeExtensionProcess          ));

		extensionFunctions.fktPipeExtensionServicePush      = reinterpret_cast<FktPipeExtensionServicePush>         (loadExtensionSymbol(library, path, NamePipeExtensionServicePush      ));
		extensionFunctions.fktPipeExtensionServicePull      = reinterpret_cast<FktPipeExtensionServicePull>         (loadExtensionSymbol(library, path, NamePipeExtensionServicePull      ));
	}
	catch(tstring error) { 
		publishError(error); 
		libraryUnload(library);
	}
	catch(...) { 
		libraryUnload(library);
		return;
	}

	ServiceRoot::Extensions.push_back(make_shared<PipeExtensionInstance>(extensionFunctions, InstancePath));
}

//======================================================================================================================

LIBPIPE_ITF void LibPipeSetErrorCallback(LibPipeCbContext context, LibPipeCbErr cbError) {
	ErrorCallbackContext = context;
	ErrorCallback = cbError;
}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeSetPath(LibPipeStr path) {
	try {
		InstancePath = tstring(path);
		if(InstancePath.empty()) { throw tstring(_T("Empty path supplied")); }
	}
	catch(tstring error) { publishError(_T("LibPipeSetPath: ") + error); }
	catch(...) { publishError(_T("LibPipeSetPath: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeLoadExtensions(LibPipeStr path) {
	try {
		if(InstancePath.empty()) { throw tstring(_T("Empty or invalid path supplied")); }
		tstring extensionPath(path);

		if(!fileExists(extensionPath) || !fileCanRead(extensionPath))
			return;

		if(fileIsDirectory(extensionPath)) {
			for(auto&& file: fileDirectoryContents(extensionPath)) {
				loadExtension(file);
			}
		}
		else {
			loadExtension(extensionPath);
		}
	}
	catch(tstring error) { publishError(_T("LibPipeLoadExtensions: ") + error); }
	catch(...) { publishError(_T("LibPipeLoadExtensions: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeGetServiceTypes(LibPipeCbContext context, LibPipeCbStr cbServiceTypes) {
	try {
		if(InstancePath.empty()) { throw tstring(_T("Empty or invalid path supplied")); }
		PipeArray serviceTypes;

		for(auto&& extension : ServiceRoot::Extensions) {
			auto extensionServiceTypes = extension->serviceTypes();
			for(auto&& extensionServiceType : *extensionServiceTypes) {
				serviceTypes.push_back(extensionServiceType);
			}
		}

		cbServiceTypes(context, dumpArray(serviceTypes).c_str());
	}
	catch(tstring error) { publishError(_T("LibPipeGetServiceTypes: ") + error); }
	catch(...) { publishError(_T("LibPipeGetServiceTypes: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeInit(LibPipeStr serviceTypes) {
	try {
		if(InstancePath.empty()) { throw tstring(_T("Empty or invalid path supplied")); }

		PipeObjectPtr settings = newObject();
		(*settings)[_T("service_types")] = *parseArray(serviceTypes);
		ServiceRootInstance = make_shared<ServiceRoot>(InstancePath, settings);

		InitDone = true;
	}
	catch(tstring error) { publishError(_T("LibPipeCreate: ") + error); }
	catch(...) { publishError(_T("LibPipeCreate: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeProcess() {
	try {
		if(!InitDone) { throw tstring(_T("LibPipe not initialized")); }
		ServiceRootInstance->process();
	}
	catch(tstring error) { publishError(_T("LibPipeProcess: ") + error); }
	catch(...) { publishError(_T("LibPipeProcess: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipePush(LibPipeStr messages) {
	try {
		if(!InitDone) { throw tstring(_T("LibPipe not initialized")); }
		ServiceRootInstance->addIncoming(parseArray(messages));
	}
	catch(tstring error) { publishError(_T("LibPipePush: ") + error); }
	catch(...) { publishError(_T("LibPipePush: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipePull(LibPipeCbContext context, LibPipeCbStr cbMessages) {
	try {
		if(!InitDone) { throw tstring(_T("LibPipe not initialized")); }
		cbMessages(context, dumpArray(ServiceRootInstance->getOutgoing()).c_str());
	}
	catch(tstring error) { publishError(_T("LibPipePull: ") + error); }
	catch(...) { publishError(_T("LibPipePull: Unknown error")); }
}

//======================================================================================================================
