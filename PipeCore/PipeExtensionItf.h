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
#include <map>

//======================================================================================================================

namespace Pipe {
    //==================================================================================================================

    //==================================================================================================================

    class IExtension {

    };

    enum ProviderTye {
        ProviderTypeStorage,
        ProviderTypeService,
        ProviderTypeGateway
    };

    class IProvider {
        virtual ProviderTye getType() = 0;
    };
    typedef std::shared_ptr<IProvider> IProvider_sptr;

    //==================================================================================================================

    class IService {

    };
    typedef std::shared_ptr<IService> IService_sptr;


    class IServiceProvider : IProvider {

    };
    typedef std::shared_ptr<IServiceProvider> IServiceProvider_sptr;

    //==================================================================================================================

    class IGateway {

    };
    typedef std::shared_ptr<IGateway> IGateway_sptr;

    class IGatewayProvider : IProvider {

    };
    typedef std::shared_ptr<IGatewayProvider> IGatewayProvider_sptr;

    //==================================================================================================================

    class IStorage {

    };
    typedef std::shared_ptr<IStorage> IStorage_sptr;

    class IStorageProvider : IProvider {
    
    };
    typedef std::shared_ptr<IStorageProvider> IStorageProvider_sptr;

    //==================================================================================================================
}

//======================================================================================================================

#define EXTENSION_INIT_NAME "InitPipeExtension"
typedef Pipe::IExtension* IExtensionPtr;
typedef IExtensionPtr (*ExtensionInitPtr)();

//======================================================================================================================
