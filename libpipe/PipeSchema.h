//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeDataTypes.h"

/*
TODO: ADD DEFAULT VALUES

TODO: Rewrite in this style:

Schema sInfo;
	auto&& sInfoProperties = sInfo.obj(TokenMessageData, _T("Information about the node"));
	sInfoProperties.val(PipeSchemaNodeTypeString, TokenMessageAddress, _T("Address of the node"));

	// Choice


	// Properties in objects are called keywords
	// Schemas must start with an object
	// Types: array, boolean, integer, number, null, string, object
	// The described "data" objects are called instances
	// "$schema" keyword must be present in root of schema and should link to : http://json-schema.org/schema#
	// Ignore ID
	// Ignore references? 

	Keywords:



	


*/

enum PipeSchemaNodeType {
	PipeSchemaNodeTypeString,
	PipeSchemaNodeTypeBool,
	PipeSchemaNodeTypeInteger,
	PipeSchemaNodeTypeFloat,
	PipeSchemaNodeTypeBinary
};

// Not implemented: patternProperties, additionalProperties, additionalItems, dependencies, definitions, ref, id, not

class PipeSchemaNode;
class PipeSchemaNode : PipeObjectPtr {
private:
	std::shared_ptr<PipeSchemaNode> _parent;

public:
	PipeSchemaNode() {}
	PipeSchemaNode(PipeObjectPtr source) {}

public:
	PipeSchemaNode add(PipeSchemaNodeType type);
	void remove(PipeSchemaNode child);

public:
	PipeSchemaNode next();
	bool isValid(PipeJson instance);

public: // Keywords for all nodes
	PipeSchemaNodeType type();

	tstring schemaBase();
	PipeSchemaNode schemaBase(tstring uri);

	tstring title();
	PipeSchemaNode title(tstring newTitle);

	tstring description();
	PipeSchemaNode description(tstring newDescription);

	tstring format();
	PipeSchemaNode format(tstring newFormat);

	PipeArrayPtr enumTypes();
	PipeSchemaNode enumTypes(PipeArrayPtr newEnumTypes);

	PipeJson defaultValue();
	PipeSchemaNode defaultValue(PipeJson defaultValue);

	std::vector<PipeSchemaNode> allOf();
	PipeSchemaNode allOf(std::vector<PipeSchemaNode> newAllOf);

	std::vector<PipeSchemaNode> anyOf();
	PipeSchemaNode anyOf(std::vector<PipeSchemaNode> newAnyOf);

	std::vector<PipeSchemaNode> oneOf();
	PipeSchemaNode oneOf(std::vector<PipeSchemaNode> newOneOf);

public: // Keywords for objects
	int maxProperties();
	PipeSchemaNode maxProperties(int newMaxProperties);

	int minProperties();
	PipeSchemaNode minProperties(int newMinProperties);

	PipeArrayPtr requried();
	PipeSchemaNode requried(PipeArrayPtr newRequired);

	std::vector<PipeSchemaNode> properties();
	PipeSchemaNode properties(std::vector<PipeSchemaNode> newProperties);

public: // Keywords for arrays
	PipeSchemaNode items();
	PipeSchemaNode items(PipeSchemaNode newItems);

	int maxItems();
	PipeSchemaNode maxItems(int newMaxItems);

	int minItems();
	PipeSchemaNode minItems(int newMinItems);

	bool uniqueItems();
	PipeSchemaNode uniqueItems(bool newUniqueItems);

public: // Keywords for strings
	int maxLength();
	PipeSchemaNode maxLength(int newMaxLength);
	
	int minLength();
	PipeSchemaNode minLength(int newMinLength);

	tstring pattern();
	PipeSchemaNode pattern(tstring newPattern);

public: // Keywords for number, integer
	int multipleOf();
	PipeSchemaNode multipleOf(int newMultipleOf);

	int maximum();
	PipeSchemaNode maximum(int newMaximum);

	bool exclusiveMaximum();
	PipeSchemaNode exclusiveMaximum(bool newExclusiveMaximum);

	int minimum();
	PipeSchemaNode minimum(int newMinimum);

	bool exclusiveMinimum();
	PipeSchemaNode exclusiveMinimum(bool newExclusiveMinimum);
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

inline tstring schemaTypeString(PipeSchemaNodeType type) {
	switch(type) {
		case PipeSchemaNodeTypeString: { return TokenSchemaTypeString; }
		case PipeSchemaNodeTypeBool: { return TokenSchemaTypeBool; }
		case PipeSchemaNodeTypeInteger: { return TokenSchemaTypeInteger; }
		case PipeSchemaNodeTypeFloat: { return TokenSchemaTypeFloat; }
		case PipeSchemaNodeTypeBinary: { return TokenSchemaTypeBinary; }
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

inline void schemaAddValue(PipeObject& schema, const tstring& key, const PipeSchemaNodeType type, const tstring& description, bool optional = false) {
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

inline void schemaAddValueArray(PipeObject& schema, const tstring& key, const tstring& description, const PipeSchemaNodeType itemType, const tstring& itemDescription) {
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
