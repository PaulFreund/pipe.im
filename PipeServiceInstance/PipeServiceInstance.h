//======================================================================================================================

#pragma once

//======================================================================================================================

#include <libpipe/LibPipe.h>

#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/OptionSet.h>

//======================================================================================================================

class PipeServiceInstanceApplication : public Poco::Util::ServerApplication {
public:
	bool _debug;

private:
	bool _help;
	tstring _account;
	tstring _address;
	int _port;
	tstring _extdir;
	tstring _userdir;
	PipeArrayPtr _resultServices;

	const int _retryLimit;
	int _retryCount;
	bool _shutdown;


public:
	PipeServiceInstanceApplication();
	~PipeServiceInstanceApplication();

public:
	int main(const std::vector<tstring>& args);

	void defineOptions(Poco::Util::OptionSet& options);
	void readOptions();

	void displayHelp(const tstring& name, const tstring& value);
};

//======================================================================================================================
