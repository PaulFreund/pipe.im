//======================================================================================================================

#pragma once

//======================================================================================================================

#include <vector>
#include <string>

#define _TCHAR_DEFINED
#ifdef UNICODE
#define _T(x) L ##x
#define TCHAR wchar_t
#else
#define _T(x) x
#define TCHAR char
#endif
typedef std::basic_string<TCHAR> tstring;
typedef unsigned char ubyte;

#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/OptionSet.h>

#include <libpipe/PipeShell.h>

/*
// Find way to cross platform background start apps
auto bRet = _tspawnl(_P_NOWAITO, path_to_app, path, NULL);
*/
//======================================================================================================================

class ServerApplication;
class PipeServiceHostApplication : public Poco::Util::ServerApplication {
public:
	bool _help;
	bool _debug;

	tstring _appPath;
	tstring _extdir;
	tstring _datadir;
	tstring _staticdir;
	int _port = 9980;
	tstring _address;
	tstring _uripath;
	tstring _authToken;


public:
	PipeServiceHostApplication();
	~PipeServiceHostApplication();

public:
	void defineOptions(Poco::Util::OptionSet& options);
	
	int main(const std::vector<tstring>& args);
	void displayHelp(const tstring& name, const tstring& value);
};

//======================================================================================================================
