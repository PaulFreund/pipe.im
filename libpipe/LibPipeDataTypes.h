//======================================================================================================================

#pragma once

//======================================================================================================================

#include <vector>
#include <map>
#include <string>
#include <functional>

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

namespace PipeConstants {
	const tstring basicMsgKeyAddress					= _T("address");
	const tstring basicMsgKeyType						= _T("type");
	const tstring basicMsgKeyReference					= _T("reference");
	const tstring basicMsgTypeCommands					= _T("commands");
	const tstring basicMsgTypeMessages					= _T("messages");
	const tstring basicMsgTypeChildren					= _T("children");
	const tstring basicMsgTypeInfo						= _T("info");
	const tstring basicMsgTypeError						= _T("error");

	const tstring errorMsgKeyDescription				= _T("description");
	const tstring errorMsgDescriptionInvalidAddress		= _T("Missing or invalid address field");
	const tstring errorMsgDescriptionInvalidType		= _T("Missing or invalid type field");
	const tstring errorMsgDescriptionInvalidReference	= _T("Missing or invalid reference field");
	const tstring errorMsgDescriptionUnknownAddress		= _T("Address not found");
	const tstring errorMsgDescriptionUnknownCommand		= _T("Command not found");
	
	
	const tstring basicInfoKeyAddress					= _T("address");
	const tstring basicInfoKeyType						= _T("type");
	const tstring basicInfoKeyDescription				= _T("description");
	const tstring basicInfoKeyProperties				= _T("properties");
};



//======================================================================================================================

#include "json11.hpp"

typedef json11::Json PipeJSON;

//======================================================================================================================
