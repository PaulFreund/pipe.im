#include "PipeExtensionItf.h"

#include <algorithm>
#include <exception>
#include <iostream>
#include <map>
using namespace std;

#include <boost/filesystem.hpp>
using namespace boost::filesystem;

#include "chaiscript\chaiscript.hpp"

#ifdef WIN32
    #include <Windows.h>
#endif


/***********************************************************************************************************************

// bytes instead of strings as data
// type metadata
// active scripts
    http://www.chaiscript.com/
    http://libwebsockets.org/

***********************************************************************************************************************/


namespace Pipe {

    class Pipe {
    private:
        map<tstring, IServiceProvider_sptr> _serviceProviders;
        map<tstring, IGatewayProvider_sptr> _gatewayProviders;

    public:
        Pipe() {

        };

        ~Pipe() {

        };

    public:
        void run() {
            loadExtensions();
        }

    private:
        void loadExtensions() {

            path appPath = _T("");
            #ifdef WIN32
                TCHAR appPathBuffer[MAX_PATH]; 
                HMODULE appModule = GetModuleHandle(NULL);
                if (appModule == NULL) { throw new exception("Failed to get module path"); }
                GetModuleFileName(appModule, appPathBuffer, (sizeof(appPathBuffer))); 
                appPath = path(appPathBuffer).parent_path();
            #else
                throw new exception("LIBRARY LOADING NOT IMPLEMENTED");
            #endif

            try {
                if (exists(appPath) && is_directory(appPath)) {
                    for ( directory_iterator it( appPath ), itEnd; it != itEnd; ++it ) {
                        auto elementPath = it->path();
                        if(is_regular_file(elementPath) && elementPath.extension() == ".dll") {
                            ExtensionInitPtr initFunction = nullptr;
                            #ifdef WIN32
                                HMODULE library = LoadLibrary(elementPath.c_str());
                                if(library == NULL) { continue; }

                                void* functionAddress = GetProcAddress(library, EXTENSION_INIT_NAME);
                                if(functionAddress == NULL) { continue; }

                                initFunction = (ExtensionInitPtr)functionAddress;
                            #else
                                throw new exception("LIBRARY LOADING NOT IMPLEMENTED");
                            #endif
                        
                            if(initFunction == nullptr) continue;
                            IExtensionPtr extension = initFunction();

                            // TODO
                        }
                    }
                }
            }
            catch (const filesystem_error& ex) {
                cout << ex.what() << '\n';
            }
        }
    };
}

int main(int /*argc*/, wchar_t* /*argv[]*/)
{
    try {
        Pipe::Pipe pipeInstance;
        pipeInstance.run();
    }
    catch(exception e) {
        cout << "Exception: " << e.what() << endl;
        cin.get();
    }
	return 0;
}

