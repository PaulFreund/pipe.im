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

#pragma once

//======================================================================================================================

#include <vector>
#include <map>
#include <string>
#include <functional>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <streambuf>
#include <algorithm>
#include <mutex>
#include <cmath>
#include <exception>

//======================================================================================================================

#define _TCHAR_DEFINED
#ifdef UNICODE
#define _T(x) L ##x
#define TCHAR wchar_t
#define to_tstring std::to_wstring
#else
#define _T(x) x
#define TCHAR char
#define to_tstring std::to_string
#endif

#ifdef UNICODE
#define tcout std::wcout
#else
#define tcout std::cout
#endif

//======================================================================================================================

typedef std::basic_string<TCHAR> tstring;

inline tstring safe_tstring(const TCHAR* str) {
	return (str == nullptr) ? tstring(_T("")) : tstring(str);
}

typedef std::basic_stringstream<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> > tstringstream;

typedef unsigned char ubyte;

//======================================================================================================================

#include "json11.h"
typedef Json PipeJson;

//----------------------------------------------------------------------------------------------------------------------

typedef PipeJson::array PipeArray;
typedef PipeJson::object PipeObject;

typedef std::shared_ptr<PipeArray> PipeArrayPtr;
typedef std::shared_ptr<PipeObject> PipeObjectPtr;

//----------------------------------------------------------------------------------------------------------------------

const TCHAR     TokenAddressSeparator   = _T('.');

const tstring   TokenPipe               = _T("pipe");

const tstring   TokenMessageAddress     = _T("address");
const tstring   TokenMessageTimestamp   = _T("timestamp");
const tstring   TokenMessageRef         = _T("ref");
const tstring   TokenMessageCommand     = _T("command");
const tstring   TokenMessageMessage     = _T("message");
const tstring   TokenMessageData        = _T("data");

//----------------------------------------------------------------------------------------------------------------------

const tstring TokenBoolTrue     = _T("true");
const tstring TokenBoolFalse    = _T("false");

//======================================================================================================================

#if defined(_WIN32) || defined(_WIN64) || defined(_WIN32_WCE)
	const tstring PathSeparator = _T("\\");
	const TCHAR PathSeparatorChar = _T('\\');

	#if defined(_DEBUG)
		const tstring LibrarySuffix = _T("d.dll");
	#else
		const tstring LibrarySuffix = _T(".dll");
	#endif
#else
	const tstring PathSeparator = _T("/");
	const TCHAR PathSeparatorChar = _T('/');

	#if defined(__APPLE__)
		#if defined(_DEBUG)
			const tstring LibrarySuffix = _T("d.dylib");
		#else
			const tstring LibrarySuffix = _T(".dylib");
		#endif
	#elif defined(__CYGWIN__)
		#if defined(_DEBUG)
			const tstring LibrarySuffix = _T("d.dll");
		#else
			const tstring LibrarySuffix = _T(".dll");
		#endif
	#else
		#if defined(_DEBUG)
			const tstring LibrarySuffix = _T("d.so");
		#else
			const tstring LibrarySuffix = _T(".so");
		#endif
	#endif
#endif

//======================================================================================================================
