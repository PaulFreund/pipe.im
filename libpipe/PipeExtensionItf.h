//======================================================================================================================

#pragma once

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

typedef uint64_t		PipeExtensionServiceProvider;
typedef uint64_t		PipeExtensionService;
typedef uint64_t		PipeExtensionServiceNode;

//======================================================================================================================

//----------------------------------------------------------------------------------------------------------------------
struct PipeExtensionServiceSettingType {
	PipeExtensionStr id;										// Id of setting type
	PipeExtensionStr description;								// Human readable description
};

//----------------------------------------------------------------------------------------------------------------------
struct PipeExtensionMessageParameterType {
	PipeExtensionStr id;										// Id of parameter type
	PipeExtensionStr description;								// Human readable description
	bool optional;												// Can this parameter be ommitted
};

//----------------------------------------------------------------------------------------------------------------------
struct PipeExtensionMessageType {
	PipeExtensionStr id;										// Id of this message type
	PipeExtensionStr description;								// Human readable description 
	bool receiving;												// Is the PipeExtensionServiceNode receiving or sending this message type
	bool binary;												// Contains the data buffer binary or space separated parameters
	PipeExtensionEleCnt parameterCount;							// Number of parametes
	PipeExtensionMessageParameterType* parameterTypes[];		// List of parameter types
};

//----------------------------------------------------------------------------------------------------------------------
struct PipeExtensionServiceSetting {
	PipeExtensionStr id;										// Id of setting variable
	PipeExtensionStr value;										// Value of setting variable
};

//----------------------------------------------------------------------------------------------------------------------
struct PipeExtensionMessage {
	PipeExtensionStr address;									// Point separated path to sending or receiving PipeExtensionServiceNode
	PipeExtensionStr type;										// Id of a PipeMessageType
	unsigned int dataSize;										// Bytecount for data buffer
	unsigned char* data;										// Databuffer
};

//======================================================================================================================

typedef void* PipeExtensionCbContext;
typedef void(*PipeExtensionCbZtStr)(PipeExtensionCbContext, PipeExtensionStr);
typedef void(*PipeExtensionCbServiceNode)(PipeExtensionCbContext, PipeExtensionServiceNode);
typedef void(*PipeExtensionCbServiceNodes)(PipeExtensionCbContext, PipeExtensionServiceNode*, PipeExtensionEleCnt);
typedef void(*PipeExtensionCbServiceProviders)(PipeExtensionCbContext, PipeExtensionServiceProvider*, PipeExtensionEleCnt);
typedef void(*PipeExtensionCbSettingTypes)(PipeExtensionCbContext, PipeExtensionServiceSettingType*, PipeExtensionEleCnt);
typedef void(*PipeExtensionCbMessages)(PipeExtensionCbContext, PipeExtensionMessage*, PipeExtensionEleCnt);
typedef void(*PipeExtensionCbMessageTypes)(PipeExtensionCbContext, PipeExtensionMessageType*, PipeExtensionEleCnt);

//======================================================================================================================

PIPE_EXTENSION_ITF void PipeExtensionGetServiceProviders			(PipeExtensionCbContext context, PipeExtensionCbServiceProviders cbServiceProviders);

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceProviderGetType			(PipeExtensionServiceProvider provider, PipeExtensionCbContext context, PipeExtensionCbZtStr cbType);
PIPE_EXTENSION_ITF void PipeExtensionServiceProviderGetSettingTypes	(PipeExtensionServiceProvider provider, PipeExtensionCbContext context, PipeExtensionCbSettingTypes cbSettingTypes);
PIPE_EXTENSION_ITF void PipeExtensionServiceProviderCreateService	(PipeExtensionServiceProvider provider, PipeExtensionStr id, PipeExtensionServiceSetting* settings, PipeExtensionEleCnt count, PipeExtensionService* service);
PIPE_EXTENSION_ITF void PipeExtensionServiceProviderDestroyService	(PipeExtensionServiceProvider provider, PipeExtensionService service);

//----------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetId					(PipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbZtStr cbId);
PIPE_EXTENSION_ITF void PipeExtensionServiceGetType					(PipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbZtStr cbType);
PIPE_EXTENSION_ITF void PipeExtensionServiceGetRoot					(PipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbServiceNode cbServiceNode);
PIPE_EXTENSION_ITF void PipeExtensionServiceSendMessages			(PipeExtensionService service, PipeExtensionMessage* messages, PipeExtensionEleCnt count);
PIPE_EXTENSION_ITF void PipeExtensionServiceReceiveMessages			(PipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbMessages cbReceivedMessages);

//----------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetId				(PipeExtensionServiceNode node, PipeExtensionCbContext context, PipeExtensionCbZtStr cbId);
PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetType				(PipeExtensionServiceNode node, PipeExtensionCbContext context, PipeExtensionCbZtStr cbType);
PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetMessageTypes		(PipeExtensionServiceNode node, PipeExtensionCbContext context, PipeExtensionCbMessageTypes cbMessageTypes);
PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetChildren			(PipeExtensionServiceNode node, PipeExtensionCbContext context, PipeExtensionCbServiceNodes cbChildren);

//======================================================================================================================
