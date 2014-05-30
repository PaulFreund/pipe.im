//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeDataTypes.h"

/*
TODO: ADD DEFAULT VALUES

TODO: Rewrite in this style:

Schema sInfo;
	auto&& sInfoProperties = sInfo.obj(TokenMessageData, _T("Information about the node"));
	sInfoProperties.val(SchemaValueTypeString, TokenMessageAddress, _T("Address of the node"));

	// Choice


	// Properties in objects are called keywords
	// Schemas must start with an object
	// Types: array, boolean, integer, number, null, string, object
	// The described "data" objects are called instances
	// "$schema" keyword must be present in root of schema and should link to : http://json-schema.org/schema#
	// Ignore ID
	// Ignore references? 

	Keywords:

	number, integer
		* multipleOf (>0, value%of=0)
		* maximum, exclusiveMaximum
		* minimum, exclusiveMinimum
	string
		* maxLength
		* minLength
		* pattern
	array
		* items
		* additionalItems
		* maxItems
		* minItems
		* uniqueItems
	object
		* maxProperties
		* minProperties
		* required
		* properties
		* additionalProperties
		* patternProperties
	
	all
		* enum
		* type
		* allOf
		* anyOf
		* oneOf
		* not
		* title
		* description
		* default
		* format
	
	Format types:

	* date-time
	* email
	* hostname
	* ipv4
	* ipv6
	* uri


*/


enum SchemaValueType {
	SchemaValueTypeString,
	SchemaValueTypeBool,
	SchemaValueTypeInteger,
	SchemaValueTypeFloat,
	SchemaValueTypeBinary
};

const tstring TokenSchema = _T("schema");

const tstring TokenSchemaType = _T("type");
const tstring TokenSchemaDescription = _T("description");
const tstring TokenSchemaOptional = _T("optional");
const tstring TokenSchemaProperties = _T("properties");
const tstring TokenSchemaItems = _T("items");

const tstring TokenSchemaTypeObject = _T("object");
const tstring TokenSchemaTypeArray = _T("array");
const tstring TokenSchemaTypeString = _T("string");
const tstring TokenSchemaTypeBool = _T("bool");
const tstring TokenSchemaTypeInteger = _T("integer");
const tstring TokenSchemaTypeFloat = _T("float");
const tstring TokenSchemaTypeBinary = _T("binary");

//======================================================================================================================

inline tstring schemaTypeString(SchemaValueType type) {
	switch(type) {
		case SchemaValueTypeString: { return TokenSchemaTypeString; }
		case SchemaValueTypeBool: { return TokenSchemaTypeBool; }
		case SchemaValueTypeInteger: { return TokenSchemaTypeInteger; }
		case SchemaValueTypeFloat: { return TokenSchemaTypeFloat; }
		case SchemaValueTypeBinary: { return TokenSchemaTypeBinary; }
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
	schemaData[TokenSchemaProperties] = PipeObject();
	return schemaData[TokenSchemaProperties].object_items();
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
	schemaItemData[TokenSchemaProperties] = PipeObject();

	return schemaItemData[TokenSchemaProperties].object_items();
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


//======================================================================================================================


//======================================================================================================================
