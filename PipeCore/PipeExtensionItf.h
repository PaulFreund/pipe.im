//======================================================================================================================

#include <string>

#define _TCHAR_DEFINED
#ifdef UNICODE
    #define _T(x) L ##x
    #define TCHAR wchar_t
#else
    #define _T(x) x
    #define TCHAR char
#endif
typedef std::basic_string<TCHAR> tstring;

//======================================================================================================================

#include <memory>
#include <vector>
#include <map>

using namespace std;

//======================================================================================================================

namespace Pipe {
    //==================================================================================================================

    enum ServiceState {
        GatewayStateOnline,
        GatewayStateOffline,
        GatewayStateError
    };

    class IServiceNode {
        virtual string getId() = 0;
        // TODO: Get capabilities / commands
    };

    class IService {
        virtual string getId() = 0;
        virtual ServiceState getState() = 0; // TODO: to be reviewed
        virtual void setState(ServiceState state) = 0; // TODO: to be reviewed

        virtual IServiceNode getRootNode() = 0;

        virtual map<string, string> process(map<string, string> outbox) = 0;
    };

    //------------------------------------------------------------------------------------------------------------------

    enum GatewayState {
        GatewayStateOnline,
        GatewayStateOffline,
        GatewayStateError
    };

    enum GatewayClientState {
        GatewayClientStateConnected,
        GatewayClientStateDisconnected,
        GatewayClientStateError
    };

    class IGateway {
        virtual string getId() = 0;
        virtual GatewayState getState() = 0; // TODO: to be reviewed
        virtual void setState(GatewayState state) = 0; // TODO: to be reviewed

        virtual vector<string> getClientList() = 0;
        virtual map<string, GatewayClientState> getClientUpdates() = 0;

        virtual map<string, string> process(map<string, string> outbox) = 0;
    };

    //==================================================================================================================

    typedef shared_ptr<IService> IService_sptr;
    typedef shared_ptr<IGateway> IGateway_sptr;

    //------------------------------------------------------------------------------------------------------------------

    class IServiceProvider {
        virtual tstring getType() = 0;
        virtual map<tstring, tstring> getSettings() = 0;

        virtual IService_sptr create(tstring id, map<tstring, tstring> settings) = 0;

    };

    //------------------------------------------------------------------------------------------------------------------

    class IGatewayProvider {
        virtual tstring getType() = 0;
        virtual map<tstring, tstring> getSettings() = 0;

        virtual IGateway_sptr create(tstring id, map<tstring, tstring> settings) = 0;
    };

    //==================================================================================================================

    typedef shared_ptr<IServiceProvider> IServiceProvider_sptr;
    typedef shared_ptr<IGatewayProvider> IGatewayProvider_sptr;

    //------------------------------------------------------------------------------------------------------------------

    struct IExtension {
        map<tstring, IServiceProvider_sptr> _serviceProviders;
        map<tstring, IGatewayProvider_sptr> _gatewayProviders;
    };

    //------------------------------------------------------------------------------------------------------------------
}

//======================================================================================================================

#define EXTENSION_INIT_NAME "InitPipeExtension"
typedef Pipe::IExtension* IExtensionPtr;
typedef IExtensionPtr (*ExtensionInitPtr)();

//======================================================================================================================
