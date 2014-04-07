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

typedef unsigned char* ZTSTRPTR;
typedef unsigned int COUNT;

typedef void* PipeServiceProvider;
typedef void* PipeService;
typedef void* PipeServiceNode;

//======================================================================================================================

//----------------------------------------------------------------------------------------------------------------------
struct PipeServiceSettingType {
    ZTSTRPTR id;                                    // Id of setting type
    ZTSTRPTR description;                           // Human readable description
};

//----------------------------------------------------------------------------------------------------------------------
struct PipeMessageParameterType {
    ZTSTRPTR id;                                    // Id of parameter type
    ZTSTRPTR description;                           // Human readable description
    bool optional;                                  // Can this parameter be ommitted
};

//----------------------------------------------------------------------------------------------------------------------
struct PipeMessageType {
    ZTSTRPTR id;                                    // Id of this message type
    ZTSTRPTR description;                           // Human readable description 
    bool receiving;                                 // Is the PipeServiceNode receiving or sending this message type
    bool binary;                                    // Contains the data buffer binary or space separated parameters
    COUNT parameterCount;                           // Number of parametes
    PipeMessageParameterType* parameterTypes[];     // List of parameter types
};

//----------------------------------------------------------------------------------------------------------------------
struct PipeServiceSetting {
    ZTSTRPTR id;                                    // Id of setting variable
    ZTSTRPTR value;                                 // Value of setting variable
};

//----------------------------------------------------------------------------------------------------------------------
struct PipeMessage {
    ZTSTRPTR address;                               // Point separated path to sending or receiving PipeServiceNode
    ZTSTRPTR type;                                  // Id of a PipeMessageType
    unsigned int dataSize;                          // Bytecount for data buffer
    unsigned char* data;                            // Databuffer
};

//======================================================================================================================

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeExtensionGetServiceProviders    (PipeServiceProvider providers[], COUNT count);

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceProviderGetType          (const PipeServiceProvider provider, ZTSTRPTR type);
PIPE_EXTENSION_ITF void PipeServiceProviderGetSettingTypes  (const PipeServiceProvider provider, PipeServiceSettingType* types[], COUNT count);
PIPE_EXTENSION_ITF void PipeServiceProviderCreateService    (const PipeServiceProvider provider, ZTSTRPTR id, PipeServiceSetting* settings[], const COUNT count, PipeService service);
PIPE_EXTENSION_ITF void PipeServiceProviderDestroyService   (const PipeServiceProvider provider, const PipeService service);

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceGetId                    (const PipeService service, ZTSTRPTR id);
PIPE_EXTENSION_ITF void PipeServiceGetType                  (const PipeService service, ZTSTRPTR type);
PIPE_EXTENSION_ITF void PipeServiceGetRoot                  (const PipeService service, PipeServiceNode node);
PIPE_EXTENSION_ITF void PipeServiceSendMessages             (const PipeService service, const PipeMessage* messages[], const COUNT count);
PIPE_EXTENSION_ITF void PipeServiceReceiveMessages          (const PipeService service, PipeMessage* messages[], COUNT count);

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceNodeGetId                (const PipeServiceNode node, ZTSTRPTR id);
PIPE_EXTENSION_ITF void PipeServiceNodeGetType              (const PipeServiceNode node, ZTSTRPTR type);
PIPE_EXTENSION_ITF void PipeServiceNodeGetMessageTypes      (const PipeServiceNode node, PipeMessageType* types[], COUNT count);
PIPE_EXTENSION_ITF void PipeServiceNodeGetChildren          (const PipeServiceNode node, PipeServiceNode children[], COUNT count);

//======================================================================================================================
