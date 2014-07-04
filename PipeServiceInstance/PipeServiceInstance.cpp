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

#include <libpipe/LibPipe.h>

//======================================================================================================================

#include <Poco/String.h>
#include <Poco/StringTokenizer.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/ErrorHandler.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Net/TCPServer.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Thread.h>
using namespace Poco;
using namespace Poco::Util;
using namespace Poco::Net;

//======================================================================================================================

class PipeServiceInstanceErrorHandler : public ErrorHandler {
public:
	PipeServiceInstanceErrorHandler() : ErrorHandler() {}

	virtual void exception(const Exception& exc) { cout << _T("[POCO ERROR] ") << exc.message() << endl; }
	virtual void exception(const std::exception& exc) { cout << _T("[POCO ERROR] ") << exc.what() << endl; }
	virtual void exception() { cout << _T("[POCO ERROR] Unknown") << endl; }
};

//======================================================================================================================

class PipeServiceInstanceClientConnection : public TCPServerConnection {
public:
	PipeServiceInstanceClientConnection(const StreamSocket& s) : TCPServerConnection(s) {}

	void run() {
		StreamSocket& ss = socket();
		try {
			//char buffer[256];
			//int n = ss.receiveBytes(buffer, sizeof(buffer));
			//while(n > 0) {
			//	ss.sendBytes(buffer, n);
			//	n = ss.receiveBytes(buffer, sizeof(buffer));
			//}

			// TODO: Something like this but thread safe 

			/*
				try {
					// Get application path
					PipeServiceInstanceApplication self(argc, argv);
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

					PipeShell shell(
						_T("terminal"),
						[&](tstring text) {
							cout << text << endl;
						},
						[](PipeJson msg) {
							LibPipe::push(std::make_shared<PipeArray>(PipeArray { msg }));
						},
						true
					);

					bool exit = false;

					thread process([&]() {
						LibPipe::process();
						Thread::sleep(100);
					});

					thread pull([&]() {
						tstring received;
						while(!exit) {
							shell.inputMessages(LibPipe::pull());
							Thread::sleep(100);
						}
					});

					thread push([&]() {
						const unsigned int bufferSize = 2048;
						TCHAR buffer[bufferSize];

						while(!exit) {
							cin.getline(buffer, bufferSize, _T('\n'));

							tstring message(buffer);

							if(message.compare(_T("exit")) == 0) {
								exit = true;
								continue;
							}

							shell.inputText(message);
						}
					});

					while(!exit) {
						Thread::sleep(100);
					}

					process.join();
					pull.join();
					push.join();
				}

			*/
		}
		catch(Poco::Exception& exc) {
			std::cerr << "EchoConnection: " << exc.displayText() << std::endl;
		}
	}
};

//======================================================================================================================

class PipeServiceInstanceApplication : public Poco::Util::ServerApplication {
private:
	bool _startupError;
	tstring _startupErrorText;

	bool _help;
	tstring _address;
	int _port;
	tstring _extdir;
	tstring _userdir;
	bool _debug;
	vector<tstring> _services;

public:
	PipeServiceInstanceApplication() 
		: _startupError(false)
	{}

	~PipeServiceInstanceApplication() {}

	void displayHelp(const tstring& name, const tstring& value) {
		_help = true;
		stopOptionsProcessing();
	}

	void defineOptions(OptionSet& options) {
		options.addOption(
			Option(_T("help"), _T("h"), _T("Display help"))
			.required(false)
			.repeatable(false)
			.callback(OptionCallback<PipeServiceInstanceApplication>(this, &PipeServiceInstanceApplication::displayHelp))
		);
		options.addOption(
			Option(_T("address"), _T("a"), _T("Address to bind"))
			.required(false)
			.repeatable(false)
			.binding(_T("address"))
			.argument(_T("[address]"))
		);
		options.addOption(
			Option(_T("port"), _T("p"), _T("Port on which application will listen"))
			.required(false)
			.repeatable(false)
			.binding(_T("port"))
			.argument(_T("[port]"))
		);
		options.addOption(
			Option(_T("extdir"), _T("x"), _T("Path to folder where extensions are located"))
			.required(false)
			.repeatable(false)
			.binding(_T("extdir"))
			.argument(_T("[extdir]"))
		);
		options.addOption(
			Option(_T("userdir"), _T("u"), _T("Path to folder where user data will be located"))
			.required(false)
			.repeatable(false)
			.binding(_T("userdir"))
			.argument(_T("[userdir]"))
		);
		options.addOption(
			Option(_T("includedServices"), _T("i"), _T("No services except the ones defined in this comma separated list will be allowed"))
			.required(false)
			.repeatable(false)
			.binding(_T("includedServices"))
			.argument(_T("[includedServices]"))
		);
		options.addOption(
			Option(_T("excludedServices"), _T("e"), _T("All services except the ones defined in this comma separated list will be allowed"))
			.required(false)
			.repeatable(false)
			.binding(_T("excludedServices"))
			.argument(_T("[excludedServices]"))
		);
		options.addOption(
			Option(_T("debug"), _T("d"), _T("Enable debug console"))
			.required(false)
			.repeatable(false)
			.binding(_T("debug"))
			.argument(_T("[debug]"))
		);
	}

	int main(const vector<tstring>& args) {
		ErrorHandler* origHandler = ErrorHandler::get();
		ErrorHandler* newHandler = new PipeServiceInstanceErrorHandler();
		ErrorHandler::set(newHandler);

		try {
			_debug = config().getBool(_T("debug")), false;

			if(_help) {
				HelpFormatter helpFormatter(options());
				helpFormatter.setUnixStyle(true);
				helpFormatter.setCommand(commandName());
				helpFormatter.setUsage("OPTIONS");
				helpFormatter.setHeader("PipeWebsocketTerminal - Tester");
				helpFormatter.format(cout);
				return Application::EXIT_OK;
			}

			_address = config().getString(_T("address"), _T("127.0.0.1"));
			_port = config().getInt(_T("port"), 9980);

			_userdir = config().getString(_T("userdir"), _T(""));
			if(_userdir.empty()) { throw tstring(_T("Missing user dir path")); }
			LibPipe::setPath(_userdir);


			_extdir = config().getString(_T("extdir"), _T(""));
			if(_extdir.empty()) { throw tstring(_T("Missing extension dir path")); }
			LibPipe::loadExtensions(_extdir);


			LibPipe::setErrorCallback([](tstring error) {
				cout << _T("[LIBPIPE ERROR]") << error << endl;
			});

			PipeArrayPtr resultServices = newArray();

			vector<tstring> availableServices;
			auto serviceTypes = LibPipe::serviceTypes();
			for(auto& type : *serviceTypes) {
				availableServices.push_back(type.string_value());
			}

			bool includedServicesDefined = config().has(_T("includedServices"));
			bool excludedServicesDefined = config().has(_T("excludedServices"));
			if(includedServicesDefined && excludedServicesDefined) { throw tstring(_T("Included and excluded services can not be specified at the same time")); }

			if(includedServicesDefined) {
				vector<tstring> includedServices = texplode(config().getString(_T("includedServices"), _T("")), _T(','));
				for(auto& service : includedServices) {
					if(find(begin(availableServices), end(availableServices), service) != end(availableServices))
						resultServices->push_back(PipeJson(service));
				}
			}
			else if(excludedServicesDefined) {
				vector<tstring> excludedServices = texplode(config().getString(_T("excludedServices"), _T("")), _T(','));
				for(auto& service : availableServices) {
					if(find(begin(excludedServices), end(excludedServices), service) == end(excludedServices))
						resultServices->push_back(PipeJson(service));
				}
			}


			LibPipe::init(resultServices);

			// Set up Websocket server
			ServerSocket socket(SocketAddress(_address, _port));

			TCPServer server(new TCPServerConnectionFactoryImpl<PipeServiceInstanceClientConnection>());

			server.start();

			while(true) {
				this_thread::sleep_for(chrono::milliseconds(10));
				LibPipe::process();
			}

			server.stop();
		}
		catch(exception e) {
			cout << _T("Exception: ") << e.what() << endl;
		}

		ErrorHandler::set(origHandler);
		delete newHandler;

		return EXIT_OK;
	}
};

//======================================================================================================================

#include <libpipe/PipeShell.h>

//======================================================================================================================

int main(int argc, char* argv[]) {
	PipeServiceInstanceApplication self;
	self.run(argc, argv);
	return 0;
}
