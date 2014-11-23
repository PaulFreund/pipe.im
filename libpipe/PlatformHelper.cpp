//======================================================================================================================

#include "CommonHeader.h"
#include "PlatformHelper.h"

//======================================================================================================================

#if defined(_WIN32) || defined(_WIN64) || defined(_WIN32_WCE)
	#include <Windows.h>

	bool fileExists(tstring& path) {
		if(path.empty()) { return false; }
		return (GetFileAttributes(path.c_str()) != 0xFFFFFFFF);
	}

	bool fileIsDirectory(tstring& path) {
		if(path.empty()) { return false; }

		DWORD attr = GetFileAttributes(path.c_str());
		if(attr == 0xFFFFFFFF) { return false; }
		return (attr & FILE_ATTRIBUTE_DIRECTORY) != 0;
	}

	bool fileCanRead(tstring& path) {
		if(path.empty()) { return false; }

		DWORD attr = GetFileAttributes(path.c_str());
		if(attr == 0xFFFFFFFF) { return false; }
		return true;
	}

	bool fileCanWrite(tstring& path) {
		if(path.empty()) { return false; }

		DWORD attr = GetFileAttributes(path.c_str());
		if(attr == 0xFFFFFFFF) { return false; }
		return (attr & FILE_ATTRIBUTE_READONLY) == 0;
	}

#else
	#include <sys/types.h>
	#include <sys/stat.h>

	bool fileExists(tstring& path) {
		if(path.empty()) { return false; }
		struct stat st;
		return stat(path.c_str(), &st) == 0;
	}

	bool fileIsDirectory(tstring& path) {
		if(path.empty()) { return false; }
		struct stat st;
		if(stat(path.c_str(), &st) == 0)
			return S_ISDIR(st.st_mode);

		return false;
	}

	bool fileCanRead(tstring& path) {
		if(path.empty()) { return false; }
		struct stat st;
		if (stat(path.c_str(), &st) == 0) {
			if (st.st_uid == geteuid()) {
				return (st.st_mode & S_IRUSR) != 0;
			}
			else if (st.st_gid == getegid()) {
				return (st.st_mode & S_IRGRP) != 0;
			}
			else {
				return (st.st_mode & S_IROTH) != 0 || geteuid() == 0;
			}
		}

		return false;
	}

	bool fileCanWrite(tstring& path) {
		if(path.empty()) { return false; }
		struct stat st;
		if (stat(path.c_str(), &st) == 0)
		{
			if (st.st_uid == geteuid()) {
				return (st.st_mode & S_IWUSR) != 0;
			}
			else if (st.st_gid == getegid()) {
				return (st.st_mode & S_IWGRP) != 0;
			}
			else {
				return (st.st_mode & S_IWOTH) != 0 || geteuid() == 0;
			}
		}

		return false;
	}
#endif

bool fileIsFile(tstring& path) {
	if(path.empty()) { return false; }

	return fileExists(path) && !fileIsDirectory(path);
}

//======================================================================================================================
