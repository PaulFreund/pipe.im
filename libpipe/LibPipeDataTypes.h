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
	const tstring basicMsgKeyAddress					= _T("address");
	const tstring basicMsgKeyType						= _T("type");
	const tstring basicMsgTypeCommands					= _T("commands");
	const tstring basicMsgTypeMessages					= _T("messages");
	const tstring basicMsgTypeChildren					= _T("children");
	const tstring basicMsgTypeInfo						= _T("info");
	const tstring basicMsgTypeError						= _T("error");

	const tstring errorMsgKeyDescription				= _T("description");
	const tstring errorMsgDescriptionMissingAddress		= _T("Missing address field");
	const tstring errorMsgDescriptionMissingType		= _T("Missing type field");

};



//======================================================================================================================

#include "json11.hpp"

typedef json11::Json PipeJSON;

//======================================================================================================================
