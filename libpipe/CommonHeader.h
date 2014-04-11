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

//======================================================================================================================

#include <chaiscript\chaiscript.hpp>

//======================================================================================================================

#include <Poco/DirectoryIterator.h>
#include <Poco/SharedLibrary.h>
#include <Poco/String.h>
using namespace Poco;

//======================================================================================================================

#include "LibPipeAPI.h"
#include "PipeExtensionAPI.h"
#include "LibPipeInterface.h"

//======================================================================================================================