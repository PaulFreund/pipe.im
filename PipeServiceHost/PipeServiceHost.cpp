//======================================================================================================================

#include "CommonHeader.h"
#include "PipeServiceHost.h"
#include "WebService.h"

#include <Poco/ErrorHandler.h>
#include <Poco/Util/HelpFormatter.h>

using namespace std;
using namespace Poco;
using namespace Poco::Util;

//======================================================================================================================

class PipeServiceHostErrorHandler : public ErrorHandler {
public:
	PipeServiceHostErrorHandler() : ErrorHandler() {}

	virtual void exception(const Exception& exc) { cout << _T("[POCO ERROR] ") << exc.message() << endl; }
	virtual void exception(const std::exception& exc) { cout << _T("[POCO ERROR] ") << exc.what() << endl; }
	virtual void exception() { cout << _T("[POCO ERROR] Unknown") << endl; }
};

//======================================================================================================================

PipeServiceHostApplication::PipeServiceHostApplication()
	: _help(false)
	, _debug(false)
{
	setUnixOptions(true); 
}

//----------------------------------------------------------------------------------------------------------------------

PipeServiceHostApplication::~PipeServiceHostApplication() {}

//----------------------------------------------------------------------------------------------------------------------

int PipeServiceHostApplication::main(const vector<tstring>& args) {
	ErrorHandler* origHandler = ErrorHandler::get();
	ErrorHandler* newHandler = new PipeServiceHostErrorHandler();
	ErrorHandler::set(newHandler);

	if(_help) {
		HelpFormatter helpFormatter(options());
		helpFormatter.setUnixStyle(true);
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader("PipeServiceHost");
		helpFormatter.format(cout);
		return Application::EXIT_OK;
	}

	try {
		readOptions();
	}
	catch(...) {
		return EXIT_USAGE;
	}

	//// TODO:
	// Update settings
		// Base folder
		// instance socket
		// webservice socket
		// other

	// Create instance of UserInstanceManager
		

	// Creeate instance of WebService
		// Authentication and registration layer

		// Create Administration
			// Configuration of bots
			// Configuration for user management

		// Create user management
	
	waitForTerminationRequest();

	ErrorHandler::set(origHandler);
	delete newHandler;

	return EXIT_OK;
}

//----------------------------------------------------------------------------------------------------------------------

void PipeServiceHostApplication::defineOptions(OptionSet& options) {
	options.addOption(
		Option(_T("help"), _T("h"), _T("Display help"))
		.required(false)
		.repeatable(false)
		.callback(OptionCallback<PipeServiceHostApplication>(this, &PipeServiceHostApplication::displayHelp))
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
		Option(_T("port"), _T("p"), _T("Port on which application will listen"))
		.required(false)
		.repeatable(false)
		.binding(_T("port"))
		.argument(_T("[port]"))
	);
	options.addOption(
		Option(_T("address"), _T("a"), _T("Address to bind"))
		.required(false)
		.repeatable(false)
		.binding(_T("address"))
		.argument(_T("[address]"))
	);
	options.addOption(
		Option(_T("uripath"), _T("u"), _T("Subpath where application will be served"))
		.required(false)
		.repeatable(false)
		.binding(_T("uripath"))
		.argument(_T("[uripath]"))
	);
	options.addOption(
		Option(_T("authtoken"), _T("t"), _T("Authentication information in CRYPT form"))
		.required(false)
		.repeatable(false)
		.binding(_T("authtoken"))
		.argument(_T("[authtoken]"))
	);
}

//----------------------------------------------------------------------------------------------------------------------

void PipeServiceHostApplication::readOptions() {
	_appPath = Path(commandPath()).parent().toString();
	_extdir = config().getString(_T("extdir"), _appPath);
	_datadir = config().getString(_T("datadir"), _appPath + _T("Data"));
	_staticdir = config().getString(_T("staticdir"), _appPath + _T("static"));
	_port = config().getInt(_T("port"), 9980);
	_address = config().getString(_T("address"), _T("127.0.0.1"));
	_uripath = config().getString(_T("uripath"), _T(""));
	_authToken = config().getString(_T("authtoken"), _T(""));
	if(_uripath[0] != _T('/'))
		_uripath = _T("/") + _uripath;
}

//----------------------------------------------------------------------------------------------------------------------

void PipeServiceHostApplication::displayHelp(const tstring& name, const tstring& value) {
	_help = true;
	stopOptionsProcessing();
}

//======================================================================================================================

int main(int argc, char* argv[]) {
	PipeServiceHostApplication self;
	self.run(argc, argv);
	return 0;
}

//======================================================================================================================
