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

typedef unsigned char* ZtStr;
typedef uint64_t EleCnt;

typedef uint64_t HPipeServiceProvider;
typedef uint64_t HPipeService;
typedef uint64_t HPipeServiceNode;

//======================================================================================================================

//----------------------------------------------------------------------------------------------------------------------
struct PipeServiceSettingType {
	ZtStr id;										// Id of setting type
	ZtStr description;								// Human readable description
};

//----------------------------------------------------------------------------------------------------------------------
struct PipeMessageParameterType {
    ZtStr id;										// Id of parameter type
	ZtStr description;								// Human readable description
	bool optional;									// Can this parameter be ommitted
};

//----------------------------------------------------------------------------------------------------------------------
struct PipeMessageType {
	ZtStr id;										// Id of this message type
	ZtStr description;								// Human readable description 
	bool receiving;									// Is the HPipeServiceNode receiving or sending this message type
	bool binary;									// Contains the data buffer binary or space separated parameters
	EleCnt parameterCount;							// Number of parametes
	PipeMessageParameterType* parameterTypes[];		// List of parameter types
};

//----------------------------------------------------------------------------------------------------------------------
struct PipeServiceSetting {
	ZtStr id;										// Id of setting variable
	ZtStr value;									// Value of setting variable
};

//----------------------------------------------------------------------------------------------------------------------
struct PipeMessage {
	ZtStr address;									// Point separated path to sending or receiving HPipeServiceNode
	ZtStr type;										// Id of a PipeMessageType
	unsigned int dataSize;							// Bytecount for data buffer
	unsigned char* data;							// Databuffer
};

//======================================================================================================================

typedef void(*PipeCbZtStr)(ZtStr);
typedef void(*PipeCbServiceNode)(HPipeServiceNode);
typedef void(*PipeCbServiceNodes)(HPipeServiceNode*, EleCnt);
typedef void(*PipeCbServiceProviders)(HPipeServiceProvider*, EleCnt);
typedef void(*PipeCbSettingTypes)(PipeServiceSettingType*, EleCnt);
typedef void(*PipeCbMessages)(PipeMessage*, EleCnt);
typedef void(*PipeCbMessageTypes)(PipeMessageType*, EleCnt);

//======================================================================================================================

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeExtensionGetServiceProviders	(PipeCbServiceProviders cbServiceProviders);

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceProviderGetType			(HPipeServiceProvider provider, PipeCbZtStr cbType);
PIPE_EXTENSION_ITF void PipeServiceProviderGetSettingTypes	(HPipeServiceProvider provider, PipeCbSettingTypes cbSettingTypes);
PIPE_EXTENSION_ITF void PipeServiceProviderCreateService	(HPipeServiceProvider provider, ZtStr id, PipeServiceSetting* settings, EleCnt count, HPipeService* service);
PIPE_EXTENSION_ITF void PipeServiceProviderDestroyService	(HPipeServiceProvider provider, HPipeService service);

//----------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceGetId					(HPipeService service, PipeCbZtStr cbId);
PIPE_EXTENSION_ITF void PipeServiceGetType					(HPipeService service, PipeCbZtStr cbType);
PIPE_EXTENSION_ITF void PipeServiceGetRoot					(HPipeService service, PipeCbServiceNode cbServiceNode);
PIPE_EXTENSION_ITF void PipeServiceSendMessages				(HPipeService service, PipeMessage* messages, EleCnt count);
PIPE_EXTENSION_ITF void PipeServiceReceiveMessages			(HPipeService service, PipeCbMessages cbReceivedMessages);

//----------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceNodeGetId				(HPipeServiceNode node, PipeCbZtStr cbId);
PIPE_EXTENSION_ITF void PipeServiceNodeGetType				(HPipeServiceNode node, PipeCbZtStr cbType);
PIPE_EXTENSION_ITF void PipeServiceNodeGetMessageTypes		(HPipeServiceNode node, PipeCbMessageTypes cbMessageTypes);
PIPE_EXTENSION_ITF void PipeServiceNodeGetChildren			(HPipeServiceNode node, PipeCbServiceNodes cbChildren);

//======================================================================================================================
