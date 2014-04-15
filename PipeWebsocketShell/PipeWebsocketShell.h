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

#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/OptionSet.h"

//======================================================================================================================

class ServerApplication;
class PipeWebsocketShellApplication : public Poco::Util::ServerApplication {
public:
	bool _help;

	tstring _appPath;
	tstring _extdir;
	tstring _datadir;
	tstring _staticdir;
	int _port = 9980;
	tstring _address;
	tstring _uripath;

public:
	PipeWebsocketShellApplication();
	~PipeWebsocketShellApplication();

public:
	void defineOptions(Poco::Util::OptionSet& options);
	
	int main(const std::vector<tstring>& args);
	void displayHelp(const tstring& name, const tstring& value);
};

//======================================================================================================================
