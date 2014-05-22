//======================================================================================================================

#include <thread>
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

#include <Poco/String.h>
#include <Poco/StringTokenizer.h>
#include <Poco/Util/Application.h>
#include <Poco/Thread.h>
using namespace Poco;
using namespace Poco::Util;

//======================================================================================================================

class PipeTerminalApplication : public Application {
public:
	PipeTerminalApplication(int argc, char* argv[]) : Application(argc, argv) {}
	~PipeTerminalApplication() {}
};

//======================================================================================================================

#include <libpipe/PipeShell.h>

//======================================================================================================================

int main(int argc, char* argv[]) {
	try {
		// Get application path
		PipeTerminalApplication self(argc, argv);
		Path commandPath(self.commandPath());

		auto appPath = commandPath.parent().toString();
		auto userPath = appPath + _T("PipeTerminalData");
		LibPipe::setErrorCallback([](tstring error) {
			cout << _T("[LIBPIPE ERROR]") << error << endl;
		});
		LibPipe::setPath(userPath);
		LibPipe::loadExtensions(appPath);
		auto serviceTypes = LibPipe::serviceTypes();
		LibPipe::init(serviceTypes);

		PipeShell shell(_T("terminal"), true);

		bool exit = false;

		thread receive([&]() {
			tstring received;
			while(!exit) {
				received = shell.receive();
				if(!received.empty())
					cout << received << endl;

				Thread::sleep(1000);
			}
		});

		thread send([&]() {
			const unsigned int bufferSize = 2048;
			TCHAR buffer[bufferSize];

			while(!exit) {
				cin.getline(buffer, bufferSize, _T('\n'));

				tstring message(buffer);

				if(message.compare(_T("exit")) == 0) {
					exit = true;
					continue;
				}

				shell.send(message);
			}
		});

		while(!exit) {
			Thread::sleep(100);
		}

		receive.join();
		send.join();
	}
	catch(exception e) {
		cout << _T("Exception: ") << e.what() << endl;
	}

	return 0;
}
