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

typedef PipeJson::array PipeArray;
typedef std::shared_ptr<PipeArray> PipeArrayPtr;

inline std::shared_ptr<PipeArray> newArray(PipeArray&& data = PipeArray {}) {
	return std::make_shared<PipeArray>(std::move(data));
}

inline PipeArrayPtr parseArray(const tstring& data) {
	return std::make_shared<PipeArray>(PipeJson::parse(data).array_items());
}

inline tstring dumpArray(const PipeArray& array) { return std::move(PipeJson(array).dump()); }
inline tstring dumpArray(PipeArrayPtr array) { return std::move(dumpArray(*array)); }

//----------------------------------------------------------------------------------------------------------------------

typedef PipeJson::object PipeObject;
typedef std::shared_ptr<PipeObject> PipeObjectPtr;

inline std::shared_ptr<PipeObject> newObject(PipeObject&& data = PipeObject {}) {
	return std::make_shared<PipeObject>(std::move(data));
}

inline PipeObjectPtr parseObject(const tstring& data) {
	return std::make_shared<PipeObject>(PipeJson::parse(data).object_items());
}

inline tstring dumpObject(const PipeObject& object) { return std::move(PipeJson(object).dump()); }
inline tstring dumpObject(PipeObjectPtr object) { return std::move(dumpObject(*object)); }

//----------------------------------------------------------------------------------------------------------------------

enum SchemaValueType {
	SchemaString,
	SchemaBool,
	SchemaNumber
};

inline PipeObject& schemaAddObject(PipeObject& schema, const tstring& key, const tstring& description, bool optional = false) {
	schema[key] = PipeObject ();
	auto& schemaData = schema[key].object_items();
	schemaData[_T("type")] = _T("object");
	schemaData[_T("description")] = description;
	schemaData[_T("optional")] = optional;
	schemaData[_T("fields")] = PipeObject ();
	return schemaData[_T("fields")].object_items();
}

inline void schemaAddValue(PipeObject& schema, const tstring& key, const SchemaValueType type, const tstring& description, bool optional = false) {
	tstring typeString = _T("");
	switch(type) {
		case SchemaString:     { typeString = _T("string");    break; }
		case SchemaBool:       { typeString = _T("bool");      break; }
		case SchemaNumber:     { typeString = _T("number");    break; }
	}

	schema[key] = PipeObject {
		{ _T("type"), typeString },
		{ _T("description"), description },
		{ _T("optional"), optional },
	};
}

inline PipeObject& schemaAddObjectArray(PipeObject& schema, const tstring& key, const tstring& description, bool optional = false) {
	schema[key] = PipeObject();
	auto& schemaData = schema[key].object_items();
	schemaData[_T("type")] = _T("array");
	schemaData[_T("description")] = description;
	schemaData[_T("optional")] = optional;
	schemaData[_T("items")] = PipeObject();
	return schemaData[_T("items")].object_items();
}

inline void schemaAddValueArray(PipeObject& schema, const tstring& key, const tstring& description, const SchemaValueType itemType, const tstring& itemDescription, bool optional = false) {
	schema[key] = PipeObject();
	auto& schemaData = schema[key].object_items();
	schemaData[_T("type")] = _T("array");
	schemaData[_T("description")] = description;
	schemaData[_T("optional")] = optional;
	schemaData[_T("items")] = PipeObject();

	tstring typeString = _T("");
	switch(itemType) {
		case SchemaString:     { typeString = _T("string");    break; }
		case SchemaBool:       { typeString = _T("bool");      break; }
		case SchemaNumber:     { typeString = _T("number");    break; }
	}

	auto& schemaItemData = schemaData[_T("items")].object_items();
	schemaItemData[_T("type")] = typeString;
	schemaItemData[_T("description")] = itemDescription;
}

//======================================================================================================================
