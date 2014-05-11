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

const TCHAR     TokenAddressSeparator   = _T('.');

const tstring   TokenMessageRef         = _T("ref");
const tstring   TokenMessageAddress     = _T("address");
const tstring   TokenMessageCommand     = _T("command");
const tstring   TokenMessageMessage     = _T("message");
const tstring   TokenMessageData        = _T("data");

//----------------------------------------------------------------------------------------------------------------------

enum SchemaValueType {
	SchemaValueTypeString,
	SchemaValueTypeBool,
	SchemaValueTypeInteger,
	SchemaValueTypeFloat,
	SchemaValueTypeBinary
};

const tstring TokenSchema               = _T("schema");

const tstring TokenSchemaType           = _T("type");
const tstring TokenSchemaDescription    = _T("description");
const tstring TokenSchemaOptional       = _T("optional");
const tstring TokenSchemaFields         = _T("fields");
const tstring TokenSchemaItems          = _T("items");

const tstring TokenSchemaTypeObject     = _T("object");
const tstring TokenSchemaTypeArray      = _T("array");
const tstring TokenSchemaTypeString     = _T("string");
const tstring TokenSchemaTypeBool       = _T("bool");
const tstring TokenSchemaTypeInteger    = _T("integer");
const tstring TokenSchemaTypeFloat      = _T("float");
const tstring TokenSchemaTypeBinary     = _T("binary");

//----------------------------------------------------------------------------------------------------------------------

const tstring TokenBoolTrue     = _T("true");
const tstring TokenBoolFalse    = _T("false");

//======================================================================================================================
