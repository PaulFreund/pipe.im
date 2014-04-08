//#include "PipeExtensionItf.h"
/*
#include <algorithm>
#include <exception>
#include <iostream>
#include <map>
#include <array>
#include <string>
using namespace std;

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

#include <chaiscript\chaiscript.hpp>

#include <Poco/DirectoryIterator.h>
#include <Poco/SharedLibrary.h>
#include <Poco/String.h>

using namespace Poco;





namespace Pipe {

	class Pipe {
	private:

	public:
		Pipe() { };

		~Pipe() { };

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

						if(!library.hasSymbol(_T("PipeExtensionGetServiceProviders")))
							continue;

						auto initFunction = static_cast<void (*)(PipeCbServiceProviders)>(library.getSymbol(_T("PipeExtensionGetServiceProviders")));
						if(initFunction == nullptr)
							continue;

						vector<HPipeServiceProvider> providers;
						// Can not work!
						initFunction((PipeCbServiceProviders) &[&providers](HPipeServiceProvider* data, EleCnt cnt) {
							for(EleCnt i = 0; i < cnt; i++) {
								providers.push_back(data[i]);
							}
						});

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

*/