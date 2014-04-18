//======================================================================================================================

#include "CommonHeader.h"
#include "LibPipe.h"

using namespace std;
using namespace Poco;

//======================================================================================================================



//======================================================================================================================

void* loadExtensionSymbol(SharedLibrary& library, tstring name) {
	if(!library.hasSymbol(name))
		throw;

	void* symbol = library.getSymbol(name);
	if(symbol == nullptr)
		throw;

	return symbol;
}

void loadExtension(tstring path) {
	auto suffix = SharedLibrary::suffix();
	if(path.length() <= suffix.length())
		return;

	auto ext = path.substr(path.length() - suffix.length(), string::npos);
	if(!File(path).isFile() || ext != suffix)
		return;

	SharedLibrary library(path);
	if(!library.isLoaded())
		return;

	if(!library.hasSymbol(NamePipeExtensionGetServiceTypes))
		return;

	PipeExtensionFunctions extensionFunctions;
	try {
		extensionFunctions.fktPipeExtensionGetServiceTypes = reinterpret_cast<FktPipeExtensionGetServiceTypes>(loadExtensionSymbol(library, NamePipeExtensionGetServiceTypes));
		extensionFunctions.fktPipeExtensionServiceCreate = reinterpret_cast<FktPipeExtensionServiceCreate>(loadExtensionSymbol(library,NamePipeExtensionServiceCreate));
		extensionFunctions.fktPipeExtensionServiceDestroy = reinterpret_cast<FktPipeExtensionServiceDestroy>(loadExtensionSymbol(library,NamePipeExtensionServiceDestroy));
		extensionFunctions.fktPipeExtensionServiceSend = reinterpret_cast<FktPipeExtensionServiceSend>(loadExtensionSymbol(library,NamePipeExtensionServiceSend));
		extensionFunctions.fktPipeExtensionServiceReceive = reinterpret_cast<FktPipeExtensionServiceReceive>(loadExtensionSymbol(library,NamePipeExtensionServiceReceive));
		extensionFunctions.fktPipeExtensionServiceGetNodeChildren = reinterpret_cast<FktPipeExtensionServiceGetNodeChildren>(loadExtensionSymbol(library, NamePipeExtensionServiceGetNodeChildren));
		extensionFunctions.fktPipeExtensionServiceGetNodeInfo = reinterpret_cast<FktPipeExtensionServiceGetNodeInfo>(loadExtensionSymbol(library, NamePipeExtensionServiceGetNodeInfo));
	}
	catch(...) { return; }

	LibPipe::Extensions.push_back(PipeExtensionInstance(extensionFunctions));
}

//======================================================================================================================
LIBPIPE_ITF void LibPipeLoadExtensions(LibPipeStr path) {
	File extensionPath(path);

	if(!extensionPath.exists() || !extensionPath.canRead())
		return;

	if(extensionPath.isDirectory()) {
		for(DirectoryIterator it(extensionPath), itEnd; it != itEnd; ++it) {
			loadExtension(it->path());
		}
	}
	else {
		loadExtension(extensionPath.path());
	}
}

LIBPIPE_ITF void LibPipeGetServiceTypes(LibPipeCbContext context, LibPipeCbServiceTypes cbServiceTypes) {
	vector<tstring> serviceTypes;
	for(auto&& extension : LibPipe::Extensions) {
		auto extensionServiceTypes = extension.serviceTypes();
		for(auto&& extensionServiceType : extensionServiceTypes) {
			serviceTypes.push_back(extensionServiceType.id);
		}
	}

	vector<LibPipeStr> pointers;
	for(auto& serviceType : serviceTypes) {
		pointers.push_back(serviceType.c_str());
	}

	cbServiceTypes(context, pointers.data(), pointers.size());
}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeCreate(LibPipeStr path, LibPipeStr* serviceTypes, LibPipeEleCnt serviceTypeCount, HLibPipe* instance) {
	vector<tstring> Types;
	for(auto i = 0; i < serviceTypeCount; i++) {
		Types.push_back(tstring(serviceTypes[i]));
	}

	LibPipe::Instances.push_back(LibPipe(tstring(path), Types));
	(*instance) = reinterpret_cast<HLibPipe>(&LibPipe::Instances.back());
}

LIBPIPE_ITF void LibPipeDestroy(HLibPipe instance) {
	LibPipe* pInstance = reinterpret_cast<LibPipe*>(instance);
	for(auto it = begin(LibPipe::Instances); it != end(LibPipe::Instances); it++) {
		if(&(*it) == pInstance) {
			LibPipe::Instances.erase(it);
			return;
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeSend(HLibPipe instance, LibPipeMessageData* messages, LibPipeEleCnt count) {
	LibPipe* pInstance = reinterpret_cast<LibPipe*>(instance);
	vector<LibPipeMessage> sendMessages;
	for(auto idxMessage = 0; idxMessage < count; idxMessage++) {
		std::vector<tstring> parameters;
		for(auto idxParameter = 0; idxParameter < messages[idxMessage].parameterCount; idxParameter++) {
			parameters.push_back(tstring(
				messages[idxMessage].parameterData[idxParameter],
				messages[idxMessage].parameterData[idxParameter] + messages[idxMessage].parameterLength[idxParameter]
			));
		}

		sendMessages.push_back({
			tstring(messages[idxMessage].address),
			tstring(messages[idxMessage].type),
			parameters
		});
	}

	pInstance->send(sendMessages);
}

LIBPIPE_ITF void LibPipeReceive(HLibPipe instance, LibPipeCbContext context, LibPipeCbMessages cbMessages) {
	LibPipe* pInstance = reinterpret_cast<LibPipe*>(instance);
	auto&& messages = pInstance->receive();

	std::vector<LibPipeMessageData> messagePointers;
	std::vector<std::vector<LibPipeEleCnt>> parameterLengthPointers;
	std::vector<std::vector<LibPipeStr>> parameterDataPointers;

	for(auto i = 0; i < messages.size(); i++) {
		parameterLengthPointers.push_back({});
		parameterDataPointers.push_back({});
		for(auto& parameter : messages[i].parameters) {
			parameterLengthPointers[i].push_back(parameter.length());
			parameterDataPointers[i].push_back(parameter.c_str());
		}

		messagePointers.push_back({
			messages[i].address.c_str(),
			messages[i].type.c_str(),
			messages[i].parameters.size(),
			parameterLengthPointers[i].data(),
			parameterDataPointers[i].data()
		});
	}

	cbMessages(context, messagePointers.data(), messagePointers.size());
}

//======================================================================================================================
