#include "CommonHeader.h"

const tstring NamePipeExtensionGetServiceProviders				 = _T("PipeExtensionGetServiceProviders");
const tstring NamePipeExtensionServiceProviderGetType			 = _T("PipeExtensionServiceProviderGetType");
const tstring NamePipeExtensionServiceProviderGetSettingTypes	 = _T("PipeExtensionServiceProviderGetSettingTypes");
const tstring NamePipeExtensionServiceProviderCreateService		 = _T("PipeExtensionServiceProviderCreateService");
const tstring NamePipeExtensionServiceProviderDestroyService	 = _T("PipeExtensionServiceProviderDestroyService");
const tstring NamePipeExtensionServiceGetId						 = _T("PipeExtensionServiceGetId");
const tstring NamePipeExtensionServiceGetType					 = _T("PipeExtensionServiceGetType");
const tstring NamePipeExtensionServiceGetRoot					 = _T("PipeExtensionServiceGetRoot");
const tstring NamePipeExtensionServiceSendMessages				 = _T("PipeExtensionServiceSendMessages");
const tstring NamePipeExtensionServiceReceiveMessages			 = _T("PipeExtensionServiceReceiveMessages");
const tstring NamePipeExtensionServiceNodeGetId					 = _T("PipeExtensionServiceNodeGetId");
const tstring NamePipeExtensionServiceNodeGetType				 = _T("PipeExtensionServiceNodeGetType");
const tstring NamePipeExtensionServiceNodeGetMessageTypes		 = _T("PipeExtensionServiceNodeGetMessageTypes");
const tstring NamePipeExtensionServiceNodeGetChildren			 = _T("PipeExtensionServiceNodeGetChildren");

typedef void (*FktPipeExtensionGetServiceProviders)(PipeExtensionCbServiceProviders);
typedef void (*FktPipeExtensionServiceProviderGetType)(PipeExtensionServiceProvider, PipeExtensionCbZtStr);
typedef void (*FktPipeExtensionServiceProviderGetSettingTypes)(PipeExtensionServiceProvider, PipeExtensionCbSettingTypes);
typedef void (*FktPipeExtensionServiceProviderCreateService)(PipeExtensionServiceProvider, PipeExtensionStr, PipeExtensionServiceSetting*, PipeExtensionEleCnt, PipeExtensionService*);
typedef void (*FktPipeExtensionServiceProviderDestroyService)(PipeExtensionServiceProvider, PipeExtensionService);
typedef void (*FktPipeExtensionServiceGetId)(PipeExtensionService, PipeExtensionCbZtStr);
typedef void (*FktPipeExtensionServiceGetType)(PipeExtensionService, PipeExtensionCbZtStr);
typedef void (*FktPipeExtensionServiceGetRoot)(PipeExtensionService, PipeExtensionCbServiceNode);
typedef void (*FktPipeExtensionServiceSendMessages)(PipeExtensionService, PipeExtensionMessage*, PipeExtensionEleCnt);
typedef void (*FktPipeExtensionServiceReceiveMessages)(PipeExtensionService, PipeExtensionCbMessages);
typedef void (*FktPipeExtensionServiceNodeGetId)(PipeExtensionServiceNode, PipeExtensionCbZtStr);
typedef void (*FktPipeExtensionServiceNodeGetType)(PipeExtensionServiceNode, PipeExtensionCbZtStr);
typedef void (*FktPipeExtensionServiceNodeGetMessageTypes)(PipeExtensionServiceNode, PipeExtensionCbMessageTypes);
typedef void (*FktPipeExtensionServiceNodeGetChildren)(PipeExtensionServiceNode, PipeExtensionCbServiceNodes);

//======================================================================================================================


struct PipeExtensionFunctions {
	FktPipeExtensionGetServiceProviders					fktGetServiceProviders				    = nullptr;
	FktPipeExtensionServiceProviderGetType				fktServiceProviderGetType			    = nullptr;
	FktPipeExtensionServiceProviderGetSettingTypes		fktServiceProviderGetSettingTypes	    = nullptr;
	FktPipeExtensionServiceProviderCreateService		fktServiceProviderCreateService		    = nullptr;
	FktPipeExtensionServiceProviderDestroyService		fktServiceProviderDestroyService	    = nullptr;
	FktPipeExtensionServiceGetId						fktServiceGetId						    = nullptr;
	FktPipeExtensionServiceGetType						fktServiceGetType					    = nullptr;
	FktPipeExtensionServiceGetRoot						fktServiceGetRoot					    = nullptr;
	FktPipeExtensionServiceSendMessages					fktServiceSendMessages				    = nullptr;
	FktPipeExtensionServiceReceiveMessages				fktServiceReceiveMessages			    = nullptr;
	FktPipeExtensionServiceNodeGetId					fktServiceNodeGetId					    = nullptr;
	FktPipeExtensionServiceNodeGetType					fktServiceNodeGetType				    = nullptr;
	FktPipeExtensionServiceNodeGetMessageTypes			fktServiceNodeGetMessageTypes		    = nullptr;
	FktPipeExtensionServiceNodeGetChildren				fktServiceNodeGetChildren			    = nullptr;
};

class PipeExtension {
public:
	PipeExtension(PipeExtensionFunctions functions) : _functions(functions) {

	}

	~PipeExtension() {

	}

private:
	PipeExtensionFunctions _functions;
};