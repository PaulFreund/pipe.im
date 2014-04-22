//======================================================================================================================

#pragma once

//======================================================================================================================

#include <vector>
#include <map>
#include <string>

//======================================================================================================================

#define _TCHAR_DEFINED
#ifdef UNICODE
#define _T(x) L ##x
#define TCHAR wchar_t
#else
#define _T(x) x
#define TCHAR char
#endif

//======================================================================================================================

typedef std::basic_string<TCHAR> tstring;
typedef unsigned char ubyte;

const TCHAR PAS = _T('.'); // Pipe Address Separator

namespace PipeMessageConstants {
	const tstring msgKeyAddress = _T("address");
	const tstring msgKeyType = _T("type");
	const tstring msgTypeBasicCommands = _T("commands");
	const tstring msgTypeBasicMessages = _T("messages");
	const tstring msgTypeBasicChildren = _T("children");
	const tstring msgTypeBasicInfo = _T("info");
	const tstring msgTypeBasicError = _T("error");
};



//======================================================================================================================

#include "json11.hpp"

typedef json11::Json PipeJSON;

//======================================================================================================================
