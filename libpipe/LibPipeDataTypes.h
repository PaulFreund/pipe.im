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

//======================================================================================================================

#include "json11.h"
typedef Json PipeJson;

//----------------------------------------------------------------------------------------------------------------------

typedef PipeJson::array                                     PipeJsonArrayData;
typedef std::shared_ptr<PipeJsonArrayData>					PipeJsonArray;

inline std::shared_ptr<PipeJsonArrayData> newArray(PipeJsonArrayData&& data = PipeJsonArrayData {}) {
	return std::make_shared<PipeJsonArrayData>(std::move(data));
}

//----------------------------------------------------------------------------------------------------------------------

typedef PipeJson::object                                    PipeJsonObjectData;
typedef std::shared_ptr<PipeJsonObjectData>					PipeJsonObject;

inline std::shared_ptr<PipeJsonObjectData> newObject(PipeJsonObjectData&& data = PipeJsonObjectData {}) {
	return std::make_shared<PipeJsonObjectData>(std::move(data));
}

//======================================================================================================================
