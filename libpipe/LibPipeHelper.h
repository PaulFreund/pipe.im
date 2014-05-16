//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeDataTypes.h"

//======================================================================================================================

inline std::shared_ptr<PipeArray> newArray(PipeArray&& data = PipeArray {}) {
	return std::make_shared<PipeArray>(std::move(data));
}

inline PipeArrayPtr parseArray(const tstring& data) {
	tstring err;
	PipeArrayPtr result = std::make_shared<PipeArray>(PipeJson::parse(data, err).array_items());
	if(!err.empty()) { throw err; }
	return result;
}

inline tstring dumpArray(const PipeArray& array) { return std::move(PipeJson(array).dump()); }
inline tstring dumpArray(PipeArrayPtr array) { return std::move(dumpArray(*array)); }

//----------------------------------------------------------------------------------------------------------------------

inline std::shared_ptr<PipeObject> newObject(PipeObject&& data = PipeObject {}) {
	return std::make_shared<PipeObject>(std::move(data));
}

inline PipeObjectPtr parseObject(const tstring& data) {
	tstring err;
	PipeObjectPtr result = std::make_shared<PipeObject>(PipeJson::parse(data).object_items());
	if(!err.empty()) { throw err; }
	return result;
}

inline tstring dumpObject(const PipeObject& object) { return std::move(PipeJson(object).dump()); }
inline tstring dumpObject(PipeObjectPtr object) { return std::move(dumpObject(*object)); }

//----------------------------------------------------------------------------------------------------------------------

inline tstring schemaTypeString(SchemaValueType type) {
	switch(type) {
		case SchemaValueTypeString   : { return TokenSchemaTypeString    ; }
		case SchemaValueTypeBool     : { return TokenSchemaTypeBool      ; }
		case SchemaValueTypeInteger  : { return TokenSchemaTypeInteger   ; }
		case SchemaValueTypeFloat    : { return TokenSchemaTypeFloat     ; }
		case SchemaValueTypeBinary   : { return TokenSchemaTypeBinary    ; }
	}

	return TokenSchemaTypeString;
}

//----------------------------------------------------------------------------------------------------------------------

inline PipeObject& schemaAddObject(PipeObject& schema, const tstring& key, const tstring& description, bool optional = false) {
	schema[key] = PipeObject();
	auto& schemaData = schema[key].object_items();
	schemaData[TokenSchemaType] = TokenSchemaTypeObject;
	schemaData[TokenSchemaDescription] = description;
	schemaData[TokenSchemaOptional] = optional;
	schemaData[TokenSchemaFields] = PipeObject();
	return schemaData[TokenSchemaFields].object_items();
}

inline void schemaAddValue(PipeObject& schema, const tstring& key, const SchemaValueType type, const tstring& description, bool optional = false) {
	schema[key] = PipeObject {
		{ TokenSchemaType, schemaTypeString(type) },
		{ TokenSchemaDescription, description },
		{ TokenSchemaOptional, optional },
	};
}

inline PipeObject& schemaAddObjectArray(PipeObject& schema, const tstring& key, const tstring& arrayDescription, const tstring& objectDescription) {
	schema[key] = PipeObject();
	auto& schemaData = schema[key].object_items();
	schemaData[TokenSchemaType] = TokenSchemaTypeArray;
	schemaData[TokenSchemaDescription] = arrayDescription;
	schemaData[TokenSchemaOptional] = false;
	schemaData[TokenSchemaItems] = PipeObject();

	auto& schemaItemData = schemaData[TokenSchemaItems].object_items();
	schemaItemData[TokenSchemaType] = TokenSchemaTypeObject;
	schemaItemData[TokenSchemaDescription] = objectDescription;
	schemaItemData[TokenSchemaOptional] = false;
	schemaItemData[TokenSchemaFields] = PipeObject();

	return schemaItemData[TokenSchemaFields].object_items();
}

inline void schemaAddValueArray(PipeObject& schema, const tstring& key, const tstring& description, const SchemaValueType itemType, const tstring& itemDescription) {
	schema[key] = PipeObject();
	auto& schemaData = schema[key].object_items();
	schemaData[TokenSchemaType] = TokenSchemaTypeArray;
	schemaData[TokenSchemaDescription] = description;
	schemaData[TokenSchemaOptional] = false;
	schemaData[TokenSchemaItems] = PipeObject();

	auto& schemaItemData = schemaData[TokenSchemaItems].object_items();
	schemaItemData[TokenSchemaType] = schemaTypeString(itemType);
	schemaItemData[TokenSchemaDescription] = itemDescription;
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
