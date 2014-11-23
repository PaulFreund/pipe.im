//======================================================================================================================

#include "CommonHeader.h"
#include "FileHelper.h"


//======================================================================================================================

#if defined(_WIN32) || defined(_WIN64) || defined(_WIN32_WCE)
	#include <Windows.h>

	bool fileExists(tstring& path) {
		if(path.empty()) { return false; }
		return (GetFileAttributes(path.c_str()) != 0xFFFFFFFF);
	}
#else
	#include <sys/types.h>
	#include <sys/stat.h>

	bool fileExists(tstring& path) {
		if(path.empty()) { return false; }
		struct stat st;
		return stat(path.c_str(), &st) == 0;
	}
#endif

//======================================================================================================================
