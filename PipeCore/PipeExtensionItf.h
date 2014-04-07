//======================================================================================================================

#include <string>
#include <memory>
#include <vector>
#include <map>
using namespace std;

//======================================================================================================================

#define _TCHAR_DEFINED
#ifdef UNICODE
    #define _T(x) L ##x
    #define TCHAR wchar_t
#else
    #define _T(x) x
    #define TCHAR char
#endif
typedef basic_string<TCHAR> tstring;
typedef unsigned char ubyte;

//======================================================================================================================

struct IExtension;
class IServiceProvider;
class IService;
class IServiceNode;

typedef IExtension* PtrExtension;
typedef shared_ptr<IServiceProvider> PtrServiceProvider;
typedef shared_ptr<IService> PtrService;
typedef shared_ptr<IServiceNode> PtrServiceNode;

#define EXTENSION_INIT_NAME "InitPipeExtension"
typedef PtrExtension(*ExtensionInitPtr)();

//======================================================================================================================

namespace Pipe {

    //==================================================================================================================

    enum ServiceState {
        ServiceStateOnline,
        ServiceStateOffline,
        ServiceStateError
    };

    //------------------------------------------------------------------------------------------------------------------

    struct PipeMessage {
        tstring address;
        tstring command;
        bool binary;
        vector<ubyte> data;
    };

    //------------------------------------------------------------------------------------------------------------------

    struct PipeCommand {
        tstring name;
        bool outgoing;
        tstring description;

    };

    //==================================================================================================================

    struct IExtension {
        vector<PtrServiceProvider> _serviceProviders;
    };

    //------------------------------------------------------------------------------------------------------------------

    class IServiceProvider {
        virtual tstring type() = 0;
        virtual map<tstring, tstring> settings() = 0;

        virtual PtrService create(tstring id, map<tstring, tstring> settings) = 0;
    };

    //------------------------------------------------------------------------------------------------------------------

    class IService {
        virtual tstring id() = 0;
        virtual tstring type() = 0;

        virtual PtrServiceNode root() = 0;

        virtual void send(vector<PipeMessage> messages) = 0;
        virtual vector<PipeMessage> receive() = 0;
    };

    //------------------------------------------------------------------------------------------------------------------

    class IServiceNode {
        virtual tstring id() = 0;
        virtual tstring type() = 0;

        virtual map<tstring, tstring> commands() = 0;
        virtual map<tstring, PtrServiceNode> children() = 0;
    };

    //==================================================================================================================
}

//======================================================================================================================
