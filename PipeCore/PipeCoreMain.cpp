#include "PipeExtensionItf.h"

#include <algorithm>
#include <exception>
#include <iostream>
#include <map>
using namespace std;

#include <chaiscript\chaiscript.hpp>


#include <Poco/DirectoryIterator.h>
#include <Poco/SharedLibrary.h>
#include <Poco/Util/Application.h>
#include <Poco/String.h>

using namespace Poco;
using namespace Poco::Util;


/***********************************************************************************************************************

	http://www.chaiscript.com/
	http://pocoproject.org/features.html

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
        }

    public:
        void loadExtensions(tstring path) {

			Path appPath(path);
			File appFolder(appPath);
 
			auto suffix = SharedLibrary::suffix();

            try {
				if(appFolder.exists() && appFolder.isDirectory() && appFolder.canRead()) {
                    for ( DirectoryIterator it( appPath ), itEnd; it != itEnd; ++it ) {
						auto path = it->path();
						auto ext = path.substr(path.length() - suffix.length(), string::npos);
						if(!File(path).isFile() || ext != suffix)
							continue;

						SharedLibrary library(path);
						if(!library.isLoaded())
							continue;

						if(!library.hasSymbol(EXTENSION_INIT_NAME))
							continue;

						ExtensionInitPtr initFunction = static_cast<ExtensionInitPtr>(library.getSymbol(EXTENSION_INIT_NAME));
						if(initFunction == nullptr)
							continue;


                        IExtensionPtr extension = initFunction();

						// TODO
                    }
                }
            }
            catch (...) {
                cout << "Error loading libraries" << endl;
            }
        }
    };
}

class PipeApplication : public Application {
public:
	PipeApplication(int argc, char* argv[]) : Application(argc, argv) {}
	~PipeApplication() {  }
};

int main(int argc, TCHAR* argv[])
{
    try {
		PipeApplication self(argc, argv);
		Path commandPath(self.commandPath());
		
		Pipe::Pipe pipeInstance;
		pipeInstance.loadExtensions(commandPath.parent().toString());
        pipeInstance.run();
    }
    catch(exception e) {
        cout << "Exception: " << e.what() << endl;
        cin.get();
    }
	return 0;
}

