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

#include <libpipe/LibPipeAPI.h>
#include <libpipe/PipeExtensionAPI.h>
#include <libpipe/PipeExtensionInterface.h>

//======================================================================================================================