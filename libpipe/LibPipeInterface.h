//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeAPI.h"

#include <vector>
#include <string>
#include <map>
#include <memory>

#define _TCHAR_DEFINED
#ifdef UNICODE
#define _T(x) L ##x
#define TCHAR wchar_t
#else
#define _T(x) x
#define TCHAR char
#endif

typedef std::basic_string<TCHAR> tstring;

//======================================================================================================================

struct LibPipeMessage {
	tstring address;
	tstring type;
	std::vector<tstring> parameters;
};

//======================================================================================================================

class ILibPipe {
public:
	virtual ~ILibPipe() {};

public:
	virtual void send(const std::vector<LibPipeMessage>& messages) = 0;
	virtual std::vector<LibPipeMessage> receive() = 0;
};

//======================================================================================================================
