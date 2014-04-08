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

typedef unsigned char* ZtStr;
typedef unsigned int Count;

typedef void* HPipeServiceProvider;
typedef void* HPipeService;
typedef void* HPipeServiceNode;

//======================================================================================================================

//----------------------------------------------------------------------------------------------------------------------
struct PipeServiceSettingType {
    ZtStr id;                                    // Id of setting type
    ZtStr description;                           // Human readable description
};

//----------------------------------------------------------------------------------------------------------------------
struct PipeMessageParameterType {
    ZtStr id;                                    // Id of parameter type
    ZtStr description;                           // Human readable description
    bool optional;                                  // Can this parameter be ommitted
};

//----------------------------------------------------------------------------------------------------------------------
struct PipeMessageType {
    ZtStr id;                                    // Id of this message type
    ZtStr description;                           // Human readable description 
    bool receiving;                                 // Is the HPipeServiceNode receiving or sending this message type
    bool binary;                                    // Contains the data buffer binary or space separated parameters
    Count parameterCount;                           // Number of parametes
    PipeMessageParameterType* parameterTypes[];     // List of parameter types
};

//----------------------------------------------------------------------------------------------------------------------
struct PipeServiceSetting {
    ZtStr id;                                    // Id of setting variable
    ZtStr value;                                 // Value of setting variable
};

//----------------------------------------------------------------------------------------------------------------------
struct PipeMessage {
    ZtStr address;                               // Point separated path to sending or receiving HPipeServiceNode
    ZtStr type;                                  // Id of a PipeMessageType
    unsigned int dataSize;                          // Bytecount for data buffer
    unsigned char* data;                            // Databuffer
};

//======================================================================================================================

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeExtensionGetServiceProviders    (void(*cbServiceProviders)(HPipeServiceProvider*, Count));

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceProviderGetType          (HPipeServiceProvider provider, void(*cbType)(ZtStr));
PIPE_EXTENSION_ITF void PipeServiceProviderGetSettingTypes  (HPipeServiceProvider provider, void(*cbSettingTypes)(PipeServiceSettingType*, Count));
PIPE_EXTENSION_ITF void PipeServiceProviderCreateService    (HPipeServiceProvider provider, ZtStr id, PipeServiceSetting* settings, Count count, HPipeService* service);
PIPE_EXTENSION_ITF void PipeServiceProviderDestroyService   (HPipeServiceProvider provider, HPipeService service);

//----------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceGetId                    (HPipeService service, void(*cbId)(ZtStr));
PIPE_EXTENSION_ITF void PipeServiceGetType                  (HPipeService service, void(*cbType)(ZtStr));
PIPE_EXTENSION_ITF void PipeServiceGetRoot                  (HPipeService service, void(*cbRoot)(HPipeServiceNode));
PIPE_EXTENSION_ITF void PipeServiceSendMessages             (HPipeService service, PipeMessage* messages, Count count);
PIPE_EXTENSION_ITF void PipeServiceReceiveMessages          (HPipeService service, void(*cbReceiveMessages)(PipeMessage*, Count));

//----------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceNodeGetId                (HPipeServiceNode node, void(*cbId)(ZtStr));
PIPE_EXTENSION_ITF void PipeServiceNodeGetType              (HPipeServiceNode node, void(*cbType)(ZtStr));
PIPE_EXTENSION_ITF void PipeServiceNodeGetMessageTypes      (HPipeServiceNode node, void(*cbMessageTypes)(PipeMessageType*, Count));
PIPE_EXTENSION_ITF void PipeServiceNodeGetChildren          (HPipeServiceNode node, void(*cbChildren)(HPipeServiceNode*, Count));

//======================================================================================================================
