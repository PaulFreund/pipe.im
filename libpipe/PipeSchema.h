//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeDataTypes.h"

/*
TODO: ADD DEFAULT VALUES

TODO: Rewrite in this style:

Schema sInfo;
	auto&& sInfoFields = sInfo.obj(TokenMessageData, _T("Information about the node"));
	sInfoFields.val(SchemaValueTypeString, TokenMessageAddress, _T("Address of the node"));



*/

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


//======================================================================================================================


//======================================================================================================================
