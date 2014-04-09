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
#include <Poco/SharedLibrary.h>
#include <Poco/String.h>
#include <Poco/Util/Application.h>
#include <Poco/Thread.h>
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

vector<tstring> getProviderList() {
	vector<tstring> providerList;

	LibPipeGetServiceProviders(&providerList, [](LibPipeCbContext context, LibPipeStr* providers, LibPipeEleCnt providerCount) {
		vector<tstring>* pProviderList = static_cast<vector<tstring>*>(context);
		for(auto i = 0; i < providerCount; i++) {
			pProviderList->push_back(tstring(providers[i]));
		}
	});

	return providerList;
}

LibPipeInstance createInstance(tstring appPath, vector<tstring> providers) {
	tstring userPath = appPath + Path::separator() + _T("PipeShellData");

	vector<LibPipeStr> pointers;
	for(auto& provider : providers) {
		pointers.push_back(provider.c_str());
	}

	LibPipeInstance instance;
	LibPipeCreateInstance(userPath.c_str(), pointers.data(), pointers.size(), &instance);
	return instance;
}

void receiveMessages(LibPipeInstance instance, vector<tstring>& messages) {
	LibPipeReceive(instance, &messages, [](LibPipeCbContext context, LibPipeMessageData* messages, LibPipeEleCnt messageCount) {
		vector<tstring>* pMessages = static_cast<vector<tstring>*>(context);
		for(auto i = 0; i < messageCount; i++) {
			pMessages->push_back(tstring(messages[i].data, messages[i].data + messages[i].dataSize));
		}
	});
}

void sendMessages(LibPipeInstance instance, vector<tstring>& messages) {
	vector<LibPipeMessageData> pointers;
	for(auto& message : messages) {
		pointers.push_back({ message.length(), reinterpret_cast<const unsigned char*>(message.c_str()) });
	}
	LibPipeSend(instance, pointers.data(), pointers.size());
}

int main(int argc, char* argv[]) {
	LibPipeInstance instance = 0;

	try {
		// Get application path
		PipeShellApplication self(argc, argv);
		Path commandPath(self.commandPath());
		auto appPath = commandPath.parent().toString();

		// Load extensions
        LibPipeLoadExtensions(appPath.c_str());

		// Get available providers
		auto providers = getProviderList();

		// Create instance
		instance = createInstance(appPath, providers);
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
			vector<tstring> messages;
			while(!exit) {
				receiveMessages(instance, messages);
				for(auto& message: messages) {
					cout << message << endl;
				}
				messages.clear();

				Thread::sleep(100);
			}
		});

		thread send([&]() {
			vector<tstring> messages;
			while(!exit) {
				tstring input;
				cin >> input;

				if(input.compare(_T("exit")) == 0) {
					exit = true;
					continue;
				}
				messages.push_back(input);
				sendMessages(instance, messages);
				messages.clear();
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
	
	LibPipeDestroyInstance(instance);

	cin.get();
	return 0;
}
