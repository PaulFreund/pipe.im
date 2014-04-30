//======================================================================================================================

#pragma once

//======================================================================================================================

#include <vector>
#include <map>
#include <string>
#include <functional>
#include <sstream>
#include <iomanip>

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

//======================================================================================================================

typedef std::basic_string<TCHAR> tstring;
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

enum SchemaValueType {
	SchemaString,
	SchemaBool,
	SchemaNumber
};

//======================================================================================================================
