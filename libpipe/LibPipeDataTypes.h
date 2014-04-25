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

typedef Json PipeJSON;

typedef PipeJSON::object                                    PipeMessageData;
typedef std::shared_ptr<PipeMessageData>                    PipeMessage;

typedef PipeJSON::array                                     PipeMessageListData;
typedef std::shared_ptr<PipeMessageListData>                PipeMessageList;

typedef PipeJSON::array                                     PipeServiceTypesData;
typedef std::shared_ptr<PipeServiceTypesData>               PipeServiceTypes;

typedef PipeJSON::object                                    PipeServiceTypeSettingsData;
typedef std::shared_ptr<PipeServiceTypeSettingsData>        PipeServiceTypeSettings;

typedef PipeJSON::object                                    PipeServiceSettingsData;
typedef std::shared_ptr<PipeServiceSettingsData>            PipeServiceSettings;

typedef PipeJSON::array                                     PipeServiceNodeChildrenData;
typedef std::shared_ptr<PipeServiceNodeChildrenData>        PipeServiceNodeChildren;

typedef PipeJSON::object                                    PipeServiceNodeMessageTypeData;
typedef std::shared_ptr<PipeServiceNodeMessageTypeData>     PipeServiceNodeMessageType;

typedef PipeJSON::array                                     PipeServiceNodeMessageTypesData;
typedef std::shared_ptr<PipeServiceNodeMessageTypesData>    PipeServiceNodeMessageTypes;

typedef PipeJSON::object                                    PipeServiceNodeInfoData;
typedef std::shared_ptr<PipeServiceNodeInfoData>            PipeServiceNodeInfo;

typedef PipeJSON::object                                    PipeServiceNodePropertiesData;
typedef std::shared_ptr<PipeServiceNodePropertiesData>      PipeServiceNodeProperties;

//======================================================================================================================
