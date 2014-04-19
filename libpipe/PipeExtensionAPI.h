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
	#define PIPE_EXTENSION_ITF extern "C"
#endif

//======================================================================================================================

#include <stdint.h>

//======================================================================================================================

typedef const char*		PipeExtensionStr;
typedef uint64_t		PipeExtensionEleCnt;

typedef uint64_t		HPipeExtensionService;

//======================================================================================================================

struct PipeExtensionServiceTypeData {
	PipeExtensionStr id;										// Id of setting type
	PipeExtensionStr description;								// Human readable description
	PipeExtensionEleCnt settingTypeCount;						// Number of setting types			
	PipeExtensionStr* settingTypeIdData;						// List of setting type Ids
	PipeExtensionStr* settingTypeDescriptionData;				// List of setting type descriptions
};

//----------------------------------------------------------------------------------------------------------------------

struct PipeExtensionServiceSettingData {
	PipeExtensionStr id;										// Id of setting variable
	PipeExtensionStr value;										// Value of setting variable
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
	bool command;												// Is this a possible command or a message
	PipeExtensionEleCnt parameterCount;							// Number of parametes
	PipeExtensionMessageParameterTypeData* parameterTypes;		// List of parameter types
};

//----------------------------------------------------------------------------------------------------------------------

struct PipeExtensionServiceNodeTypeData {
	PipeExtensionStr id;										// Id of this node type
	PipeExtensionStr description;								// Human readable description 
	PipeExtensionEleCnt messageTypeCount;						// Number of message types
	PipeExtensionMessageTypeData* messageTypes;					// List of message types
};

//----------------------------------------------------------------------------------------------------------------------

struct PipeExtensionServiceNodeInfoData {
	PipeExtensionStr id;									// Id of this ServiceNode
	PipeExtensionServiceNodeTypeData type;					// The service node type of this node
	PipeExtensionEleCnt metaInfoCount;						// Number of meta information sets
	PipeExtensionStr* metaInfoKeys;							// List of meta information keys
	PipeExtensionStr* metaInfoValues;						// List of meta information values
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
typedef void(*PipeExtensionCbServiceType)(PipeExtensionCbContext, PipeExtensionServiceTypeData*, PipeExtensionEleCnt);
typedef void(*PipeExtensionCbMessages)(PipeExtensionCbContext, PipeExtensionMessageData*, PipeExtensionEleCnt);
typedef void(*PipeExtensionCbServiceNodeInfo)(PipeExtensionCbContext, PipeExtensionServiceNodeInfoData*);

//======================================================================================================================

PIPE_EXTENSION_ITF void PipeExtensionGetServiceTypes					(PipeExtensionCbContext context, PipeExtensionCbServiceType cbServiceTypes);

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceCreate						(PipeExtensionStr serviceTypeId, PipeExtensionStr id, PipeExtensionStr path, PipeExtensionServiceSettingData* settings, PipeExtensionEleCnt count, HPipeExtensionService* service);
PIPE_EXTENSION_ITF void PipeExtensionServiceDestroy						(HPipeExtensionService service);

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceSend						(HPipeExtensionService service, PipeExtensionMessageData* message);
PIPE_EXTENSION_ITF void PipeExtensionServiceReceive						(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbMessages cbMessages);

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeChildren				(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStrList cbChildNodes);
PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeInfo					(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbServiceNodeInfo cbNodeMessageTypes);

//======================================================================================================================
