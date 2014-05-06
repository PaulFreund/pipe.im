//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeDataTypes.h"

//======================================================================================================================

inline std::shared_ptr<PipeArray> newArray(PipeArray&& data = PipeArray {}) {
	return std::make_shared<PipeArray>(std::move(data));
}

inline PipeArrayPtr parseArray(const tstring& data) {
	return std::make_shared<PipeArray>(PipeJson::parse(data).array_items());
}

inline tstring dumpArray(const PipeArray& array) { return std::move(PipeJson(array).dump()); }
inline tstring dumpArray(PipeArrayPtr array) { return std::move(dumpArray(*array)); }

//----------------------------------------------------------------------------------------------------------------------

inline std::shared_ptr<PipeObject> newObject(PipeObject&& data = PipeObject {}) {
	return std::make_shared<PipeObject>(std::move(data));
}

inline PipeObjectPtr parseObject(const tstring& data) {
	return std::make_shared<PipeObject>(PipeJson::parse(data).object_items());
}

inline tstring dumpObject(const PipeObject& object) { return std::move(PipeJson(object).dump()); }
inline tstring dumpObject(PipeObjectPtr object) { return std::move(dumpObject(*object)); }

//----------------------------------------------------------------------------------------------------------------------

inline PipeObject& schemaAddObject(PipeObject& schema, const tstring& key, const tstring& description, bool optional = false) {
	schema[key] = PipeObject();
	auto& schemaData = schema[key].object_items();
	schemaData[_T("type")] = _T("object");
	schemaData[_T("description")] = description;
	schemaData[_T("optional")] = optional;
	schemaData[_T("fields")] = PipeObject();
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

inline PipeObject& schemaAddObjectArray(PipeObject& schema, const tstring& key, const tstring& description) {
	schema[key] = PipeObject();
	auto& schemaData = schema[key].object_items();
	schemaData[_T("type")] = _T("array");
	schemaData[_T("description")] = description;
	schemaData[_T("optional")] = false; // Arrays may not be optional
	schemaData[_T("items")] = PipeObject();
	return schemaData[_T("items")].object_items();
}

inline void schemaAddValueArray(PipeObject& schema, const tstring& key, const tstring& description, const SchemaValueType itemType, const tstring& itemDescription) {
	schema[key] = PipeObject();
	auto& schemaData = schema[key].object_items();
	schemaData[_T("type")] = _T("array");
	schemaData[_T("description")] = description;
	schemaData[_T("optional")] = false; // Arrays may not be optional
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

//----------------------------------------------------------------------------------------------------------------------

inline tstring timplode(const std::vector<tstring>& fragments, const TCHAR delimiter) {
	tstring result;

	for(size_t i = 0, c = fragments.size(); i < c; i++) {
		result.append(fragments[i]);
		if(i < (c - 1)) {
			result += delimiter;
		}
	}

	return result;
}

//----------------------------------------------------------------------------------------------------------------------

inline std::vector<tstring> texplode(const tstring& data, const TCHAR delimiter) {
	std::vector<tstring> result;

	tstring fragment;
	for(auto it = begin(data); it != end(data); it++) {
		if((*it) == delimiter) {
			if(!fragment.empty()) {
				result.push_back(fragment);
				fragment.clear();
			}
		}
		else {
			fragment += (*it);
		}
	}

	if(!fragment.empty()) {
		result.push_back(fragment);
	}

	return result;
}

//======================================================================================================================
