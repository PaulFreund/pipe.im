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

const tstring   TokenMessageRef         = _T("ref");
const tstring   TokenMessageAddress     = _T("address");
const tstring   TokenMessageCommand     = _T("command");
const tstring   TokenMessageMessage     = _T("message");
const tstring   TokenMessageData        = _T("data");

//----------------------------------------------------------------------------------------------------------------------

const tstring TokenBoolTrue     = _T("true");
const tstring TokenBoolFalse    = _T("false");

//======================================================================================================================
