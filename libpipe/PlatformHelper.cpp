//======================================================================================================================
/*
	Copyright (c) since 2015 - Paul Freund (freund.paul@lvl3.org)
	
	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:
	
	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/
//======================================================================================================================

#include "CommonHeader.h"
#include "PlatformHelper.h"

//======================================================================================================================

#if defined(_WIN32) || defined(_WIN64) || defined(_WIN32_WCE)
	#include <Windows.h>

	bool fileExists(const tstring& path) {
		if(path.empty()) { return false; }
		return (GetFileAttributes(path.c_str()) != 0xFFFFFFFF);
	}

	bool fileIsDirectory(const tstring& path) {
		if(path.empty()) { return false; }

		DWORD attr = GetFileAttributes(path.c_str());
		if(attr == 0xFFFFFFFF) { return false; }
		return (attr & FILE_ATTRIBUTE_DIRECTORY) != 0;
	}

	bool fileCanRead(const tstring& path) {
		if(path.empty()) { return false; }

		DWORD attr = GetFileAttributes(path.c_str());
		if(attr == 0xFFFFFFFF) { return false; }
		return true;
	}

	bool fileCanWrite(const tstring& path) {
		if(path.empty()) { return false; }

		DWORD attr = GetFileAttributes(path.c_str());
		if(attr == 0xFFFFFFFF) { return false; }
		return (attr & FILE_ATTRIBUTE_READONLY) == 0;
	}

	bool fileCreateFile(const tstring& path) {
		if(path.empty()) { return false; }

		HANDLE hFile = CreateFile(path.c_str(), GENERIC_WRITE, 0, 0, CREATE_NEW, 0, 0);
		if(hFile != INVALID_HANDLE_VALUE) {
			CloseHandle(hFile);
			return true;
		}

		return false;
	}

	bool fileCreateDirectory(const tstring& path) {
		if(path.empty()) { return false; }

		if(fileExists(path) && fileIsDirectory(path))
			return false;

		if(CreateDirectory(path.c_str(), 0) == 0)
			return false;

		return true;
	}

	std::vector<tstring> fileDirectoryContents(const tstring& path) {

		if(path.empty()) { return {}; }
		tstring findPath = path;
		if(!endsWith(findPath, PathSeparator)) { findPath += PathSeparator; }
		findPath.append("*");

		WIN32_FIND_DATA findData;
		auto handle = FindFirstFile(findPath.c_str(), &findData);
		if(handle == INVALID_HANDLE_VALUE) { return {}; }

		std::vector<tstring> result;
		tstring current;
		do {
			current = tstring(findData.cFileName);
			if(!current.empty() && current != _T(".") && current != _T("..")) { result.push_back(path + PathSeparator + current); }
		}
		while(FindNextFile(handle, &findData) != 0);

		return std::move(result);
	}

	void* libraryLoad(const tstring& path) {
		if(path.empty()) { return nullptr; }
		return LoadLibrary(path.c_str());
	}

	void libraryUnload(void* handle) {
		if(handle == nullptr) { return; }
		FreeLibrary((HMODULE)handle);
	}

	void* libraryGetSymbol(void* handle, const tstring& name) {
		return (void*)GetProcAddress((HMODULE)handle, name.c_str());
	}

#else
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <dirent.h>
	#include <dlfcn.h>
	#include <fcntl.h>

	bool fileExists(const tstring& path) {
		if(path.empty()) { return false; }
		struct stat st;
		return stat(path.c_str(), &st) == 0;
	}

	bool fileIsDirectory(const tstring& path) {
		if(path.empty()) { return false; }
		struct stat st;
		if(stat(path.c_str(), &st) == 0)
			return S_ISDIR(st.st_mode);

		return false;
	}

	bool fileCanRead(const tstring& path) {
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

	bool fileCanWrite(const tstring& path) {
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

	bool fileCreateFile(const tstring& path) {
		if(path.empty()) { return false; }

		int n = open(path.c_str(), O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		if (n != -1) {
			close(n);
			return true;
		}

		return false;
	}

	bool fileCreateDirectory(const tstring& path) {
		if(path.empty()) { return false; }

		if (fileExists(path) && fileIsDirectory(path))
			return false;

		if (mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IRWXO) != 0) 
			return false;

		return true;
	}

	std::vector<tstring> fileDirectoryContents(const tstring& path) {
		if(path.empty()) { return {}; }

		tstring findPath = path;
		if(!endsWith(findPath, PathSeparator)) { findPath += PathSeparator; }

		DIR* directory = opendir(findPath.c_str());
		if (!directory) { return {}; }

		std::vector<tstring> result;
		struct dirent* entry = nullptr;
		while(entry = readdir(directory)) {
			tstring current = tstring(entry->d_name);
			if(!current.empty() && current != _T(".") && current != _T("..")) { result.push_back(path + PathSeparator + current); }
		}

		closedir(directory);
		return std::move(result);
	}

	void* libraryLoad(const tstring& path) {
		if(path.empty()) { return nullptr; }
		return dlopen(path.c_str(), RTLD_LAZY);
	}

	void libraryUnload(void* handle) {
		if(handle == nullptr) { return; }
		dlclose(handle);
	}

	void* libraryGetSymbol(void* handle, const tstring& name) {
		return (void*)dlsym(handle, name.c_str());
	}

#endif

bool fileIsFile(const tstring& path) {
	if(path.empty()) { return false; }

	return fileExists(path) && !fileIsDirectory(path);
}

bool fileCreateDirectories(const tstring& path) {
	if(fileExists(path)) { return true; }

	auto pathParts = texplode(path, PathSeparatorChar);
	pathParts.pop_back();
	if(fileCreateDirectories(timplode(pathParts, PathSeparatorChar))) {
		return fileCreateDirectory(path);
	}
	else {
		return false;
	}
}

bool libraryHasSymbol(void* handle, const tstring& name) {
	return (libraryGetSymbol(handle, name) != nullptr);
}

//======================================================================================================================
