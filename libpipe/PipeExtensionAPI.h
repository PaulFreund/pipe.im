//======================================================================================================================

#pragma once

//======================================================================================================================

#ifdef WIN32
	#ifdef PIPE_EXTENSION_EXPORTS
		#define PIPE_EXTENSION_ITF extern "C" __declspec(dllexport) 
	#else
		#define PIPE_EXTENSION_ITF extern "C" __declspec(dllimport) 
	#endif
#else
	#define PIPE_EXTENSION_ITF extern
#endif

//======================================================================================================================

#include <stdint.h>

//======================================================================================================================

typedef const char*		PipeExtensionStr;
typedef uint64_t		PipeExtensionEleCnt;

typedef uint64_t		HPipeExtensionService;

//======================================================================================================================

//----------------------------------------------------------------------------------------------------------------------
struct PipeExtensionProviderSettingTypeData {
	PipeExtensionStr id;										// Id of setting type
	PipeExtensionStr description;								// Human readable description
};

//----------------------------------------------------------------------------------------------------------------------
struct PipeExtensionMessageParameterTypeData {
	PipeExtensionStr id;										// Id of parameter type
	PipeExtensionStr description;								// Human readable description
	bool optional;												// Can this parameter be ommitted
	bool binary;												// Contains the data buffer binary or space separated parameters
};

//----------------------------------------------------------------------------------------------------------------------
struct PipeExtensionMessageTypeData {
	PipeExtensionStr id;										// Id of this message type
	PipeExtensionStr description;								// Human readable description 
	bool receiving;												// Is the HPipeExtensionServiceNode receiving or sending this message type
	PipeExtensionEleCnt parameterCount;							// Number of parametes
	PipeExtensionMessageParameterTypeData* parameterTypes;		// List of parameter types
};

//----------------------------------------------------------------------------------------------------------------------
struct PipeExtensionServiceSettingData {
	PipeExtensionStr id;										// Id of setting variable
	PipeExtensionStr value;										// Value of setting variable
};

//----------------------------------------------------------------------------------------------------------------------
struct PipeExtensionMessageData {
	PipeExtensionStr address;									// Point separated path to sending or receiving HPipeExtensionServiceNode
	PipeExtensionStr type;										// Id of a PipeMessageType
	PipeExtensionEleCnt parameterCount;							// Count of parameters
	PipeExtensionEleCnt* parameterLength;						// List of data buffer sizes
	PipeExtensionStr* parameterData;							// List of data buffers
};

//======================================================================================================================

typedef void* PipeExtensionCbContext;
typedef void(*PipeExtensionCbStr)(PipeExtensionCbContext, PipeExtensionStr);
typedef void(*PipeExtensionCbStrList)(PipeExtensionCbContext, PipeExtensionStr*, PipeExtensionEleCnt);
typedef void(*PipeExtensionCbProviderSettingTypes)(PipeExtensionCbContext, PipeExtensionProviderSettingTypeData*, PipeExtensionEleCnt);
typedef void(*PipeExtensionCbMessages)(PipeExtensionCbContext, PipeExtensionMessageData*, PipeExtensionEleCnt);
typedef void(*PipeExtensionCbMessageTypes)(PipeExtensionCbContext, PipeExtensionMessageTypeData*, PipeExtensionEleCnt);

//======================================================================================================================

PIPE_EXTENSION_ITF void PipeExtensionGetServiceProviders				(PipeExtensionCbContext context, PipeExtensionCbStrList cbProviders);
PIPE_EXTENSION_ITF void PipeExtensionGetServiceProviderSettingTypes		(PipeExtensionStr type, PipeExtensionCbContext context, PipeExtensionCbProviderSettingTypes cbProviderSettingTypes);

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceCreate						(PipeExtensionStr provider, PipeExtensionStr id, PipeExtensionServiceSettingData* settings, PipeExtensionEleCnt count, HPipeExtensionService* service);
PIPE_EXTENSION_ITF void PipeExtensionServiceDestroy						(HPipeExtensionService service);

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceSend						(HPipeExtensionService service, PipeExtensionMessageData* messages, PipeExtensionEleCnt count);
PIPE_EXTENSION_ITF void PipeExtensionServiceReceive						(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbMessages cbMessages);

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetChildNodes				(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStrList cbChildNodes);
PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeType					(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbNodeType);
PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeMessageTypes			(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbMessageTypes cbNodeMessageTypes);

//======================================================================================================================
