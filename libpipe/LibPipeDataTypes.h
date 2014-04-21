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

//======================================================================================================================

#include "rapidjson/Document.h"
#include "rapidjson/filestream.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/reader.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

class PipeJSON : public rapidjson::GenericDocument<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<> > {
public:
	PipeJSON(rapidjson::MemoryPoolAllocator<>* allocator = 0, size_t stackCapacity = 1024) : rapidjson::Document(allocator, stackCapacity) {}


public:
	ValueIterator begin() { return Begin(); }
	ValueIterator end() { return End(); }
	ConstValueIterator begin() const { return Begin(); }
	ConstValueIterator end() const { return End(); }

public:
	tstring toString() {
		rapidjson::StringBuffer strbuf;
		rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
		this->Accept(writer);
		return strbuf.GetString();
	}

private:
	// Prohibit assignment
	PipeJSON& operator=(const PipeJSON&);
	friend class rapidjson::GenericReader<typename rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<> >;
};

//typedef rapidjson::Document PipeJSON;
// TODO: typedef for json and helper functions/class

//======================================================================================================================
