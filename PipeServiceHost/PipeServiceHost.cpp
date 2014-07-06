//======================================================================================================================

#include "CommonHeader.h"
#include "PipeServiceHost.h"

#include <Poco/ErrorHandler.h>
#include <Poco/Util/HelpFormatter.h>

using namespace std;
using namespace Poco;
using namespace Poco::Util;

//======================================================================================================================

class PipeServiceHostErrorHandler : public ErrorHandler {
public:
	PipeServiceHostErrorHandler() : ErrorHandler() {}

	virtual void exception(const Exception& exc) { tcout << _T("[POCO ERROR] ") << exc.message() << endl; }
	virtual void exception(const std::exception& exc) { tcout << _T("[POCO ERROR] ") << exc.what() << endl; }
	virtual void exception() { tcout << _T("[POCO ERROR] Unknown") << endl; }
};

//======================================================================================================================

PipeServiceHost::PipeServiceHost()
	: _help(false)
	, _debug(false)
{
	setUnixOptions(true); 
}

//----------------------------------------------------------------------------------------------------------------------

PipeServiceHost::~PipeServiceHost() {}

//----------------------------------------------------------------------------------------------------------------------

int PipeServiceHost::main(const vector<tstring>& args) {
	ErrorHandler* origHandler = ErrorHandler::get();
	ErrorHandler* newHandler = new PipeServiceHostErrorHandler();
	ErrorHandler::set(newHandler);

	if(_help) {
		HelpFormatter helpFormatter(options());
		helpFormatter.setUnixStyle(true);
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader("PipeServiceHost");
		helpFormatter.format(tcout);
		return Application::EXIT_OK;
	}

	try {
		readOptions();
	}
	catch(...) {
		return EXIT_USAGE;
	}

	_manager = make_shared<UserInstanceManager>();
	_service = make_shared<WebService>();

	waitForTerminationRequest();

	ErrorHandler::set(origHandler);
	delete newHandler;

	return EXIT_OK;
}

//----------------------------------------------------------------------------------------------------------------------

void PipeServiceHost::defineOptions(OptionSet& options) {
	options.addOption(
		Option(_T("help"), _T("h"), _T("Display help"))
		.required(false)
		.repeatable(false)
		.callback(OptionCallback<PipeServiceHost>(this, &PipeServiceHost::displayHelp))
	);
	options.addOption(
		Option(_T("extdir"), _T("e"), _T("Path to folder where extensions are located"))
		.required(false)
		.repeatable(false)
		.binding(_T("extdir"))
		.argument(_T("[extdir]"))
	);
	options.addOption(
		Option(_T("datadir"), _T("d"), _T("Path to folder where user data will be located"))
		.required(false)
		.repeatable(false)
		.binding(_T("datadir"))
		.argument(_T("[datadir]"))
	);
	options.addOption(
		Option(_T("staticdir"), _T("s"), _T("Path to folder where web files are located"))
		.required(false)
		.repeatable(false)
		.binding(_T("staticdir"))
		.argument(_T("[staticdir]"))
	);
	options.addOption(
		Option(_T("webserverAddress"), _T("wa"), _T("Address the webserver binds to"))
		.required(false)
		.repeatable(false)
		.binding(_T("webserverAddress"))
		.argument(_T("[webserverAddress]"))
	);
	options.addOption(
		Option(_T("webserverPort"), _T("wp"), _T("Port on which webserver will listen"))
		.required(false)
		.repeatable(false)
		.binding(_T("webserverPort"))
		.argument(_T("[webserverPort]"))
	);
	options.addOption(
		Option(_T("webserverPath"), _T("wu"), _T("Subpath where application will be served"))
		.required(false)
		.repeatable(false)
		.binding(_T("webserverPath"))
		.argument(_T("[webserverPath]"))
	);
	options.addOption(
		Option(_T("instanceAddress"), _T("ia"), _T("Address the instance listener binds to"))
		.required(false)
		.repeatable(false)
		.binding(_T("instanceAddress"))
		.argument(_T("[instanceAddress]"))
	);
	options.addOption(
		Option(_T("instancePort"), _T("ip"), _T("Port on which instance listener will listen"))
		.required(false)
		.repeatable(false)
		.binding(_T("instancePort"))
		.argument(_T("[instancePort]"))
	);
	options.addOption(
		Option(_T("instanceCommand"), _T("ic"), _T("Command (path) of the service instance application"))
		.required(false)
		.repeatable(false)
		.binding(_T("instanceCommand"))
		.argument(_T("[instanceCommand]"))
	);
	options.addOption(
		Option(_T("debug"), _T("d"), _T("Enable debug console"))
		.required(false)
		.repeatable(false)
		.binding(_T("debug"))
	);
}

//----------------------------------------------------------------------------------------------------------------------

void PipeServiceHost::readOptions() {
	_debug = config().has(_T("debug"));

	_appPath = Path(commandPath()).parent().toString();
	_extdir = config().getString(_T("extdir"), _appPath);
	_datadir = config().getString(_T("datadir"), _appPath + _T("Data"));
	_staticdir = config().getString(_T("staticdir"), _appPath + _T("static"));

	_webserverAddress = config().getString(_T("webserverAddress"), _T("127.0.0.1"));
	_webserverPort = config().getInt(_T("webserverPort"), 9980);
	_webserverPath = config().getString(_T("webserverPath"), _T(""));
	if(_webserverPath[0] != _T('/'))
		_webserverPath = _T("/") + _webserverPath;

	_instanceAddress = config().getString(_T("instanceAddress"), _T("127.0.0.1"));
	_instancePort = config().getInt(_T("instancePort"), 9991);
	_instanceCommand = config().getString(_T("instanceCommand"), _T("PipeServiceInstance"));
}

//----------------------------------------------------------------------------------------------------------------------

void PipeServiceHost::displayHelp(const tstring& name, const tstring& value) {
	_help = true;
	stopOptionsProcessing();
}

//----------------------------------------------------------------------------------------------------------------------

void PipeServiceHost::onError(tstring error) {
	if(_debug) {
		tcout << error << endl;
	}
}

//======================================================================================================================

int main(int argc, char* argv[]) {
	PipeServiceHost self;
	self.run(argc, argv);
	return 0;
}

//======================================================================================================================
