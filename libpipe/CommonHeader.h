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

/*
	pipe.irc.#shadowmind say "hey wie gehts \"euch\""
	pipe.irc commands 
	pipe.irc commands "[[commands,Requests all available commands,],[info,Requests info about node,],[messages,Requests all available messages,],[children,Requests all children of node,]]"
	pipe.irc messages 
	pipe.irc messages "[commands,Returns all available commands,[commandlist...]]"

	pipe.service settings irc
	pipe.service settings irc [[key:value]]

	Lists: [a,b,c]
	Key-Value pairs: [key,value]

	Special chars: " [ ] \ , 
	Special address chars: .

	schnitstelle von LibPipeMessage auf string aendern? was mache ich um auf verschiedene client anforderungen zu reagieren?

	client in jeder nachricht?

	[<reference>,<reference>] <rcpt> <cmd> [nestable parameters]
*/

const TCHAR PAS = _T('.'); // Pipe Address Separator

//======================================================================================================================

#include <chaiscript/chaiscript.hpp>

//======================================================================================================================

#include <Poco/DirectoryIterator.h>
#include <Poco/SharedLibrary.h>
#include <Poco/String.h>

//======================================================================================================================

#include "LibPipeAPI.h"
#include "PipeExtensionAPI.h"
#include "LibPipeInterface.h"

//======================================================================================================================

tstring timplode(const std::vector<tstring>& fragments, const TCHAR delimiter);
std::vector<tstring> texplode(const tstring& fragments, const TCHAR delimiter);

//======================================================================================================================
