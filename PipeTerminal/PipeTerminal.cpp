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
	// DEBUG

	auto info = PipeSchema::Create(PipeSchemaTypeObject).title(_T("Info")).description(_T("Information about the node")).required({});
	info.property(TokenMessageAddress, PipeSchemaTypeString).title(_T("Address")).description(_T("Address of the node")).enumTypes(PipeArray{_T("addyone"), _T("addytwo"), _T("3")});
	info.property(_T("type"), PipeSchemaTypeString).title(_T("Type")).description(_T("Unique type of this node")).defaultValue(_T("Rofl"));
	info.property(_T("description"), PipeSchemaTypeString).title(_T("Description")).description(_T("Description of the node"));
	auto& infoDataState = info.property(_T("states"), PipeSchemaTypeArray).title(_T("States")).description(_T("Runtime states of the node"));
	auto& infoDataStateItems = infoDataState.items(PipeSchemaTypeObject).title(_T("State")).description(_T("Runtime state"));
	infoDataStateItems.property(_T("key"), PipeSchemaTypeString).title(_T("Key")).description(_T("Name of the state"));
	infoDataStateItems.property(_T("value"), PipeSchemaTypeString).title(_T("Value")).description(_T("Value of the state"));
	
	PipeJson schema = PipeJson(info);
	cout << endl << _T("[Schema]") << endl << endl << PipeJson(schema).dump() << endl << endl;

	const unsigned int bufSize = 2048;
	TCHAR buf[bufSize];

	PipeSchemaGenerator gen;
	gen.clear();
	cout << gen.start(schema);

	while(!gen.complete()) {
		cin.getline(buf, bufSize, _T('\n'));
		cout << gen.add(tstring(buf)) << endl;
	}

	cout << endl << _T("[Value]") << endl << PipeJson(gen.instance()).dump() << endl << endl;


	// DEBUG

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
