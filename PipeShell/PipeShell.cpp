//======================================================================================================================

#include <algorithm>
#include <exception>
#include <iostream>
#include <map>
#include <array>
#include <string>
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

#include <Poco/DirectoryIterator.h>
#include <Poco/SharedLibrary.h>
#include <Poco/String.h>
#include <Poco/Util/Application.h>
using namespace Poco;
using namespace Poco::Util;

class PipeShellApplication : public Application {
public:
	PipeShellApplication(int argc, char* argv[]) : Application(argc, argv) {}
	~PipeShellApplication() {}
};

//======================================================================================================================

#include <libpipe/LibPipeItf.h>

#ifdef _DEBUG
	#pragma comment(lib, "LibPiped.lib")
#else
	#pragma comment(lib, "LibPipe.lib")
#endif

//======================================================================================================================

int main(int argc, char* argv[]) {

	try {
		PipeShellApplication self(argc, argv);
		Path commandPath(self.commandPath());
        LibPipeLoadExtensions(commandPath.parent().toString().c_str());

		cout << "Welcome to pipe shell: " << endl;

		//Pipe::Pipe pipeInstance;
		//pipeInstance.loadExtensions(commandPath.parent().toString());
		//pipeInstance.run();
	}
	catch(exception e) {
		cout << "Exception: " << e.what() << endl;
	}
	
	cin.get();
	return 0;
}
