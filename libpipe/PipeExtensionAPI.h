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

typedef unsigned char*	PipeExtensionStr;
typedef uint64_t		PipeExtensionEleCnt;

typedef uint64_t		HPipeExtensionServiceProvider;
typedef uint64_t		HPipeExtensionService;
typedef uint64_t		HPipeExtensionServiceNode;

//======================================================================================================================

//----------------------------------------------------------------------------------------------------------------------
struct PipeExtensionServiceSettingTypeData {
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
typedef void(*PipeExtensionCbZtStr)(PipeExtensionCbContext, PipeExtensionStr);
typedef void(*PipeExtensionCbServiceNode)(PipeExtensionCbContext, HPipeExtensionServiceNode);
typedef void(*PipeExtensionCbServiceNodes)(PipeExtensionCbContext, HPipeExtensionServiceNode*, PipeExtensionEleCnt);
typedef void(*PipeExtensionCbServiceProviders)(PipeExtensionCbContext, HPipeExtensionServiceProvider*, PipeExtensionEleCnt);
typedef void(*PipeExtensionCbSettingTypes)(PipeExtensionCbContext, PipeExtensionServiceSettingTypeData*, PipeExtensionEleCnt);
typedef void(*PipeExtensionCbMessages)(PipeExtensionCbContext, PipeExtensionMessageData*, PipeExtensionEleCnt);
typedef void(*PipeExtensionCbMessageTypes)(PipeExtensionCbContext, PipeExtensionMessageTypeData*, PipeExtensionEleCnt);

//======================================================================================================================

PIPE_EXTENSION_ITF void PipeExtensionGetServiceProviders			(PipeExtensionCbContext context, PipeExtensionCbServiceProviders cbServiceProviders);

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceProviderGetType			(HPipeExtensionServiceProvider provider, PipeExtensionCbContext context, PipeExtensionCbZtStr cbType);
PIPE_EXTENSION_ITF void PipeExtensionServiceProviderGetSettingTypes	(HPipeExtensionServiceProvider provider, PipeExtensionCbContext context, PipeExtensionCbSettingTypes cbSettingTypes);
PIPE_EXTENSION_ITF void PipeExtensionServiceProviderCreateService	(HPipeExtensionServiceProvider provider, PipeExtensionStr id, PipeExtensionServiceSettingData* settings, PipeExtensionEleCnt count, HPipeExtensionService* service);
PIPE_EXTENSION_ITF void PipeExtensionServiceProviderDestroyService	(HPipeExtensionServiceProvider provider, HPipeExtensionService service);

//----------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetId					(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbZtStr cbId);
PIPE_EXTENSION_ITF void PipeExtensionServiceGetType					(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbZtStr cbType);
PIPE_EXTENSION_ITF void PipeExtensionServiceGetRoot					(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbServiceNode cbServiceNode);
PIPE_EXTENSION_ITF void PipeExtensionServiceSendMessages			(HPipeExtensionService service, PipeExtensionMessageData* messages, PipeExtensionEleCnt count);
PIPE_EXTENSION_ITF void PipeExtensionServiceReceiveMessages			(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbMessages cbReceivedMessages);

//----------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetId				(HPipeExtensionServiceNode node, PipeExtensionCbContext context, PipeExtensionCbZtStr cbId);
PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetType				(HPipeExtensionServiceNode node, PipeExtensionCbContext context, PipeExtensionCbZtStr cbType);
PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetMessageTypes		(HPipeExtensionServiceNode node, PipeExtensionCbContext context, PipeExtensionCbMessageTypes cbMessageTypes);
PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetChildren			(HPipeExtensionServiceNode node, PipeExtensionCbContext context, PipeExtensionCbServiceNodes cbChildren);

//======================================================================================================================
