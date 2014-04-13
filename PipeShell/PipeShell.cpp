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
//		Path commandPath(self.commandPath());
Path commandPath;
		auto appPath = commandPath.parent().toString();
		auto userPath = appPath + _T("PipeShellData");

		LibPipeInstance::loadExtensions(appPath);
		auto providers = LibPipeInstance::serviceProviders();

		LibPipeInstance pipe(userPath, providers);

		// Create instance
		cout << _T("------------------------------------------") << endl;
		cout << _T("Welcome to pipe shell") << endl;
		cout << _T("------------------------------------------") << endl;
		cout << _T("Available providers: ") << endl;
		for(auto& provider : providers) {
			cout << _T('\t') << provider << endl;
		}
		cout << _T("------------------------------------------") << endl;
		cout << endl;

		bool exit = false;

		thread receive([&]() {
			while(!exit) {
				auto messages = pipe.receive();
				for(auto& message: messages) {
					cout << message.address << _T(" ") << message.type;
					for(auto& parameter : message.parameters) {
						cout << _T(" ") << parameter;
					}
					cout << endl;
				}

				Thread::sleep(100);
			}
		});

		thread send([&]() {
			const unsigned int bufferSize = 2048;
			TCHAR buffer[bufferSize];

			while(!exit) {
				cin.getline(buffer, bufferSize, _T('\n'));

				tstring inputLine(buffer);

				if(inputLine.compare(_T("exit")) == 0) {
					exit = true;
					continue;
				}

				// TODO: Improve to allow spaces in parameters
				StringTokenizer tokens(inputLine, _T(" "), StringTokenizer::TOK_IGNORE_EMPTY);
				if(tokens.count() >= 2) {
					LibPipeMessage message;
					message.address = tokens[0];
					message.type = tokens[1];

					for(auto i = 2; i < tokens.count(); i++) {
						message.parameters.push_back(tokens[i]);
					}

					pipe.send({ message });
				}
				else {
					cout << _T("Input syntax: <address> <type> [<parameter> ...] OR exit") << endl;
				}
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
