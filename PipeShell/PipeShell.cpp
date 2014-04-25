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

#include <Poco/DirectoryIterator.h>
#include <Poco/String.h>
#include <Poco/StringTokenizer.h>
#include <Poco/Util/Application.h>
#include <Poco/Thread.h>
using namespace Poco;
using namespace Poco::Util;

//======================================================================================================================

class PipeShellApplication : public Application {
public:
	PipeShellApplication(int argc, char* argv[]) : Application(argc, argv) {}
	~PipeShellApplication() {}
};

//======================================================================================================================

#include <libpipe/LibPipeInstance.h>

//======================================================================================================================

int main(int argc, char* argv[]) {
	try {
		// Get application path
		PipeShellApplication self(argc, argv);
		Path commandPath(self.commandPath());

		auto appPath = commandPath.parent().toString();
		auto userPath = appPath + _T("PipeShellData");

		LibPipeInstance::loadExtensions(appPath);
		auto serviceTypes = LibPipeInstance::serviceTypes();

		LibPipeInstance pipe(userPath, serviceTypes);

		// Create instance
		cout << _T("------------------------------------------") << endl;
		cout << _T("Welcome to pipe shell") << endl;
		cout << _T("------------------------------------------") << endl;
		cout << _T("Available service types: ") << PipeJson(*serviceTypes).dump() << endl;

		cout << _T("------------------------------------------") << endl;
		cout << endl;

		bool exit = false;

		thread receive([&]() {
			while(!exit) {
				
				auto messages = pipe.receive();
				for(auto& message: *messages) {
					cout << message.dump() << endl;
				}

				Thread::sleep(100);
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

				PipeJsonObjectData messageData = PipeJson::parse(message).object_items();
				pipe.send(std::make_shared<PipeJsonArrayData>(PipeJsonArrayData({ messageData })));
			}
		});

		while(!exit) {
			Thread::sleep(1000);
		}

		receive.join();
		send.join();
	}
	catch(exception e) {
		cout << _T("Exception: ") << e.what() << endl;
	}

	return 0;
}
