//======================================================================================================================

#include "PipeServiceInstance.h"
#include <thread>

#include <Poco/ErrorHandler.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Net/StreamSocket.h>

using namespace std;
using namespace Poco;
using namespace Poco::Util;
using namespace Poco::Net;

//======================================================================================================================

class PipeServiceInstanceErrorHandler : public ErrorHandler {
public:
	PipeServiceInstanceErrorHandler() : ErrorHandler() {}

	virtual void exception(const Exception& exc) { 
		Application::instance().logger().warning(tstring(_T("[POCO ERROR]") + exc.message()));
	}
	virtual void exception(const std::exception& exc) { 
		Application::instance().logger().warning(tstring(_T("[POCO ERROR]") + tstring(exc.what())));
	}
	virtual void exception() {
		Application::instance().logger().warning(tstring(_T("[POCO ERROR] Unknown")));
	}
};

//======================================================================================================================

PipeServiceInstanceApplication::PipeServiceInstanceApplication()
		: _resultServices(newArray())
		, _shutdown(false)
		, _debug(true)
		, _help(false)
		, _retryLimit(10)
		, _retryCount(0)
{
	setUnixOptions(true);
}

//----------------------------------------------------------------------------------------------------------------------

PipeServiceInstanceApplication::~PipeServiceInstanceApplication() {}

//----------------------------------------------------------------------------------------------------------------------

int PipeServiceInstanceApplication::main(const vector<tstring>& args) {
	ErrorHandler* origHandler = ErrorHandler::get();
	ErrorHandler* newHandler = new PipeServiceInstanceErrorHandler();
	ErrorHandler::set(newHandler);

	if(_help) {
		HelpFormatter helpFormatter(options());
		helpFormatter.setUnixStyle(true);
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader("PipeServiceInstance");
		helpFormatter.format(tcout);
		return EXIT_OK;
	}

	LibPipe::setErrorCallback(reinterpret_cast<LibPipe::ErrorCallbackContxt>(this), [](LibPipe::ErrorCallbackContxt context, tstring error) {
		PipeServiceInstanceApplication* app = reinterpret_cast<PipeServiceInstanceApplication*>(context);
		app->logger().warning(tstring(_T("[PipeServiceInstanceApplication::main] LibPipe error: ")) + error);
	});

	try {
		readOptions();
	}
	catch(...) {
		return EXIT_USAGE;
	}

	if(!_debug) { logger().setLevel(0); }

	LibPipe::init(_resultServices);

	vector<tstring> incoming;
	vector<tstring> outgoing;

	PipeObject msgAccount;
	msgAccount[TokenMessageRef] = _T("");
	msgAccount[TokenMessageAddress] = _T("pipe_host");
	msgAccount[TokenMessageMessage] = _T("account");
	msgAccount[TokenMessageData] = _account;
	outgoing.push_back(PipeJson(msgAccount).dump());

	while(!_shutdown) {
		try {
			StreamSocket ss(SocketAddress(_address, _port));
			ss.setBlocking(false);

			const int bufferSize = 10240;
			ss.setReceiveBufferSize(bufferSize);
			ubyte buffer[bufferSize];
			_retryCount = 0;

			int flags = 0;
			int bytesRead = 0;

			vector<ubyte> receivedBuffer;
			do {
				this_thread::sleep_for(chrono::milliseconds(10)); // TODO: DEBUG SETTING
				LibPipe::process();

				// Receive from client
				try {
					bytesRead = ss.receiveBytes(buffer, sizeof(buffer), flags);
					if(bytesRead > 0) {
						receivedBuffer.insert(end(receivedBuffer), reinterpret_cast<ubyte*>(&buffer), reinterpret_cast<ubyte*>(&buffer[bytesRead]));
						while(!receivedBuffer.empty()) {
							uint32_t messageSize = *reinterpret_cast<uint32_t*>(receivedBuffer.data());
							uint32_t packetSize = messageSize + sizeof(uint32_t);
							if(receivedBuffer.size() < packetSize) { break; }
		
							incoming.push_back(tstring(receivedBuffer.begin() + sizeof(uint32_t), receivedBuffer.begin() + packetSize));
							receivedBuffer.erase(begin(receivedBuffer), begin(receivedBuffer) + packetSize);
						}
					}
				}
				catch(TimeoutException& /*e*/) {} // Not very good but works for the moment

				// Send to pipe
				if(incoming.size() > 0) {
					for(auto& message : incoming) {
						logger().information(tstring(_T("[PipeServiceInstanceApplication::main] Message received: ")) + message);
						try {
							PipeObjectPtr messageObj = parseObject(message);
							if((*messageObj)[TokenMessageAddress].string_value() == _T("pipe_host")) {
								if((*messageObj)[TokenMessageCommand].string_value() == _T("exit"))
									_shutdown = true;
							}
						}
						catch(...) {}

						try {
							if(!message.empty())
								LibPipe::push(std::make_shared<PipeArray>(PipeArray { message }));
						}
						catch(...) {}
					}

					incoming.clear();
				}

				// Receive from pipe
				PipeArrayPtr received = LibPipe::pull();
				for(auto& ele : *received) {
					outgoing.push_back(ele.dump());
				}

				// Send to server
				if(outgoing.size() > 0) {
					for(auto& message : outgoing) {
						uint32_t messageSize = static_cast<uint32_t>(message.length());
						ss.sendBytes(&messageSize, sizeof(uint32_t));
						ss.sendBytes(message.data(), message.length());
						logger().information(tstring(_T("[PipeServiceInstanceApplication::main] Message sent: ")) + message);
					}
					outgoing.clear();
				}
			}
			while(bytesRead != 0);
		}
		catch(exception e) {
			logger().warning(tstring(_T("[PipeServiceInstanceApplication::main] Exception: ")) + e.what());
		}

		logger().warning(tstring(_T("[PipeServiceInstanceApplication::main] Connection lost")));
		if(_retryCount >= _retryLimit)
			_shutdown = true;
		else
			_retryCount++;
	}

	ErrorHandler::set(origHandler);
	delete newHandler;
	return EXIT_OK;
}

//----------------------------------------------------------------------------------------------------------------------

void PipeServiceInstanceApplication::defineOptions(OptionSet& options) {
	options.addOption(
		Option(_T("help"), _T("h"), _T("Display help"))
		.required(false)
		.repeatable(false)
		.callback(OptionCallback<PipeServiceInstanceApplication>(this, &PipeServiceInstanceApplication::displayHelp))
	);
	options.addOption(
		Option(_T("account"), _T("c"), _T("Account this instance is identified with"))
		.required(true)
		.repeatable(false)
		.binding(_T("account"))
		.argument(_T("[account]"))
	);
	options.addOption(
		Option(_T("address"), _T("a"), _T("Address to connect to"))
		.required(false)
		.repeatable(false)
		.binding(_T("address"))
		.argument(_T("[address]"))
	);
	options.addOption(
		Option(_T("port"), _T("p"), _T("Port to connect to"))
		.required(false)
		.repeatable(false)
		.binding(_T("port"))
		.argument(_T("[port]"))
	);
	options.addOption(
		Option(_T("extdir"), _T("x"), _T("Path to folder where extensions are located"))
		.required(true)
		.repeatable(false)
		.binding(_T("extdir"))
		.argument(_T("[extdir]"))
	);
	options.addOption(
		Option(_T("userdir"), _T("u"), _T("Path to folder where user data will be located"))
		.required(true)
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
	);
}

//----------------------------------------------------------------------------------------------------------------------

void PipeServiceInstanceApplication::readOptions() {
	_debug = config().has(_T("debug"));

	_account = config().getString(_T("account"), _T(""));

	_address = config().getString(_T("address"), _T("127.0.0.1"));
	_port = config().getInt(_T("port"), 9980);

	_userdir = config().getString(_T("userdir"), _T(""));
	if(_userdir.empty()) { throw tstring(_T("Missing user dir path")); }
	LibPipe::setPath(_userdir);


	_extdir = config().getString(_T("extdir"), _T(""));
	if(_extdir.empty()) { throw tstring(_T("Missing extension dir path")); }
	LibPipe::loadExtensions(_extdir);

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
				_resultServices->push_back(PipeJson(service));
		}
	}
	else if(excludedServicesDefined) {
		vector<tstring> excludedServices = texplode(config().getString(_T("excludedServices"), _T("")), _T(','));
		for(auto& service : availableServices) {
			if(find(begin(excludedServices), end(excludedServices), service) == end(excludedServices))
				_resultServices->push_back(PipeJson(service));
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------

void PipeServiceInstanceApplication::displayHelp(const tstring& name, const tstring& value) {
	_help = true;
	stopOptionsProcessing();
}

//======================================================================================================================

int main(int argc, char* argv[]) {
	PipeServiceInstanceApplication self;
	self.run(argc, argv);
	return 0;
}

//======================================================================================================================
