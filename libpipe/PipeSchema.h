//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeDataTypes.h"

/*
TODO: ADD DEFAULT VALUES

TODO: Rewrite in this style:

Schema sInfo;
	auto&& sInfoProperties = sInfo.obj(TokenMessageData, _T("Information about the node"));
	sInfoProperties.val(PipeSchemaTypeString, TokenMessageAddress, _T("Address of the node"));

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

const tstring TokenSchema = _T("schema");

const tstring TokenSchemaType = _T("type");
const tstring TokenSchemaDescription = _T("description");
const tstring TokenSchemaOptional = _T("optional");
const tstring TokenSchemaProperties = _T("properties");
const tstring TokenSchemaItems = _T("items");

//----------------------------------------------------------------------------------------------------------------------

enum PipeSchemaType {
	PipeSchemaTypeArray,
	PipeSchemaTypeBoolean,
	PipeSchemaTypeInteger,
	PipeSchemaTypeNumber,
	PipeSchemaTypeNull,
	PipeSchemaTypeObject,
	PipeSchemaTypeString
};

//----------------------------------------------------------------------------------------------------------------------

const tstring TokenSchemaTypeArray = _T("array");
const tstring TokenSchemaTypeBoolean = _T("boolean");
const tstring TokenSchemaTypeInteger = _T("integer");
const tstring TokenSchemaTypeNumber = _T("number");
const tstring TokenSchemaTypeNull = _T("null");
const tstring TokenSchemaTypeObject = _T("object");
const tstring TokenSchemaTypeString = _T("string");

//----------------------------------------------------------------------------------------------------------------------

inline tstring schemaTypeString(PipeSchemaType type) {
	     if(type == PipeSchemaTypeArray)    { return TokenSchemaTypeArray;	}
	else if(type == PipeSchemaTypeBoolean)  { return TokenSchemaTypeBoolean; }
	else if(type == PipeSchemaTypeInteger)  { return TokenSchemaTypeInteger; }
	else if(type == PipeSchemaTypeNumber)   { return TokenSchemaTypeNumber;  }
	else if(type == PipeSchemaTypeNull)     { return TokenSchemaTypeNull;    }
	else if(type == PipeSchemaTypeObject)   { return TokenSchemaTypeObject;  }
	else if(type == PipeSchemaTypeString)   { return TokenSchemaTypeString;  }
	
	return TokenSchemaTypeNull;
}

//----------------------------------------------------------------------------------------------------------------------

inline PipeSchemaType schemaTypeIdentifier(tstring type) {
	     if(type == TokenSchemaTypeArray)    { return PipeSchemaTypeArray;	}
	else if(type == TokenSchemaTypeBoolean)  { return PipeSchemaTypeBoolean; }
	else if(type == TokenSchemaTypeInteger)  { return PipeSchemaTypeInteger; }
	else if(type == TokenSchemaTypeNumber)   { return PipeSchemaTypeNumber;  }
	else if(type == TokenSchemaTypeNull)     { return PipeSchemaTypeNull;    }
	else if(type == TokenSchemaTypeObject)   { return PipeSchemaTypeObject;  }
	else if(type == TokenSchemaTypeString)   { return PipeSchemaTypeString;  }
	
	return PipeSchemaTypeNull;
}

//======================================================================================================================

// Not implemented: patternProperties, additionalProperties, additionalItems, dependencies, definitions, ref, id, not, anyOf, allOf

class PipeSchemaNode;
typedef std::shared_ptr<PipeSchemaNode> PipeSchemaNodePtr;
class PipeSchemaNode : public PipeObject {
private:
	PipeJson _emptyValue;
	PipeArray _emptyArray;
	PipeObject _emptyObject;

public:
	PipeSchemaNode(PipeSchemaType type) {
		this->operator[](_T("type")) = schemaTypeString(type);
	}

	PipeSchemaNode(PipeObjectPtr source) {}

public: // Keywords for all nodes
	PipeSchemaType type() { if(isDefined(_T("type"))) { return schemaTypeIdentifier(this->operator[](_T("type")).string_value()); } return PipeSchemaTypeNull; }

	tstring title() { if(isDefined(_T("title"))) { return this->operator[](_T("title")).string_value(); } return 0; }
	PipeSchemaNode& title(tstring newTitle) { this->operator[](_T("title")) = newTitle; return *this; }

	tstring description() { if(isDefined(_T("description"))) { return this->operator[](_T("description")).string_value(); } return 0; }
	PipeSchemaNode& description(tstring newDescription) { this->operator[](_T("description")) = newDescription; return *this; }

	tstring format() { if(isDefined(_T("format"))) { return this->operator[](_T("format")).string_value(); } return 0; }
	PipeSchemaNode& format(tstring newFormat) { this->operator[](_T("format")) = newFormat; return *this; }

	// TODO
	PipeArray& enumTypes() { if(isDefined(_T("enum"))) { return this->operator[](_T("enum")).array_items(); } return _emptyArray; } // TODO: Test
	PipeSchemaNode& enumTypes(PipeArray& newEnumTypes) { this->operator[](_T("enum")) = newEnumTypes; return *this; } // TODO: Test

	PipeJson& defaultValue() { if(isDefined(_T("default"))) { return this->operator[](_T("default")); } return _emptyValue; }
	PipeSchemaNode& defaultValue(PipeJson newDefaultValue) { this->operator[](_T("default")) = newDefaultValue; return *this; }

	// TODO
	PipeArray& oneOf() { if(isDefined(_T("oneOf"))) { return this->operator[](_T("oneOf")).array_items(); } return _emptyArray; } // TODO: Test
	PipeSchemaNode& oneOf(PipeArray& newOneOf) { this->operator[](_T("oneOf")) = newOneOf; return *this; } // TODO: Test

public: // Keywords for objects
	int maxProperties() { if(type() == PipeSchemaTypeObject && isDefined(_T("maxProperties"))) { return this->operator[](_T("maxProperties")).int_value(); } return 0; }
	PipeSchemaNode& maxProperties(int newMaxProperties) { if(type() == PipeSchemaTypeObject) { this->operator[](_T("maxProperties")) = newMaxProperties; } return *this; }

	int minProperties() { if(type() == PipeSchemaTypeObject && isDefined(_T("minProperties"))) { return this->operator[](_T("minProperties")).int_value(); } return 0; }
	PipeSchemaNode& minProperties(int newMinProperties) { if(type() == PipeSchemaTypeObject) { this->operator[](_T("minProperties")) = newMinProperties; } return *this; }

	// TODO: String interface
	PipeArray& requried() { if(type() == PipeSchemaTypeObject && isDefined(_T("requried"))) { return this->operator[](_T("requried")).array_items(); } _emptyArray; }
	PipeSchemaNode& requried(PipeArray& newRequired) { this->operator[](_T("requried")) = newRequired; return *this; } // TODO: Test

	PipeSchemaNode& property(tstring name) { 
		if(type() != PipeSchemaTypeObject) { return static_cast<PipeSchemaNode&>(_emptyObject); }
		if(!isDefined(_T("properties"))) { this->operator[](_T("properties")) = PipeObject(); }

		auto&& properties = this->operator[](_T("properties")).object_items();
		if(properties.count(name) == 1)
			return static_cast<PipeSchemaNode&>(properties[name].object_items());

		return static_cast<PipeSchemaNode&>(_emptyObject);
	}

	PipeSchemaNode& property(tstring name, PipeSchemaType newPropertyType) { return property(name, PipeSchemaNode(newPropertyType)); }
	PipeSchemaNode& property(tstring name, PipeSchemaNode& newProperty) {
		if(type() != PipeSchemaTypeObject) { return static_cast<PipeSchemaNode&>(_emptyObject); }
		if(!isDefined(_T("properties"))) { this->operator[](_T("properties")) = PipeObject(); }

		auto&& properties = this->operator[](_T("properties")).object_items();
		properties[name] = newProperty;
		return static_cast<PipeSchemaNode&>(properties[name].object_items());
	}

public: // Keywords for arrays
	PipeSchemaNode& items() { if(type() == PipeSchemaTypeArray && isDefined(_T("items"))) { return static_cast<PipeSchemaNode&>(this->operator[](_T("items")).object_items()); } return static_cast<PipeSchemaNode&>(_emptyObject); } // TODO: Test
	PipeSchemaNode& items(PipeSchemaType newItemsType) { return items(PipeSchemaNode(newItemsType)); }
	PipeSchemaNode& items(PipeSchemaNode& newItems) { if(type() == PipeSchemaTypeArray) { this->operator[](_T("items")) = newItems; } return static_cast<PipeSchemaNode&>(this->operator[](_T("items")).object_items()); } // TODO: Test

	int maxItems() { if(type() == PipeSchemaTypeArray && isDefined(_T("maxItems"))) { return this->operator[](_T("maxItems")).int_value(); } return 0; }
	PipeSchemaNode& maxItems(int newMaxItems) { if(type() == PipeSchemaTypeArray) { this->operator[](_T("maxItems")) = newMaxItems; } return *this; }

	int minItems() { if(type() == PipeSchemaTypeArray && isDefined(_T("minItems"))) { return this->operator[](_T("minItems")).int_value(); } return 0; }
	PipeSchemaNode& minItems(int newMinItems) { if(type() == PipeSchemaTypeArray) { this->operator[](_T("minItems")) = newMinItems; } return *this; }

	bool uniqueItems() { if(type() == PipeSchemaTypeArray && isDefined(_T("uniqueItems"))) { return this->operator[](_T("uniqueItems")).bool_value(); } return false; }
	PipeSchemaNode& uniqueItems(bool newUniqueItems) { if(type() == PipeSchemaTypeArray) { this->operator[](_T("uniqueItems")) = newUniqueItems; } return *this; }

public: // Keywords for strings
	int maxLength() { if(type() == PipeSchemaTypeString && isDefined(_T("maxLength"))) { return this->operator[](_T("maxLength")).int_value(); } return 0; }
	PipeSchemaNode& maxLength(int newMaxLength) { if(type() == PipeSchemaTypeString) { this->operator[](_T("maxLength")) = newMaxLength; } return *this; }
	
	int minLength() { if(type() == PipeSchemaTypeString && isDefined(_T("minLength"))) { return this->operator[](_T("minLength")).int_value(); } return 0; }
	PipeSchemaNode& minLength(int newMinLength) { if(type() == PipeSchemaTypeString) { this->operator[](_T("minLength")) = newMinLength; } return *this; }

	tstring pattern() { if(type() == PipeSchemaTypeString && isDefined(_T("pattern"))) { return this->operator[](_T("pattern")).string_value(); } return 0; }
	PipeSchemaNode& pattern(tstring newPattern) { if(type() == PipeSchemaTypeString) { this->operator[](_T("pattern")) = newPattern; } return *this; }
	
public: // Keywords for number, integer
	int multipleOf() { if((type() == PipeSchemaTypeInteger || type() == PipeSchemaTypeNumber) && isDefined(_T("multipleOf"))) { return this->operator[](_T("multipleOf")).int_value(); } return 0; }
	PipeSchemaNode& multipleOf(int newMultipleOf) { if((type() == PipeSchemaTypeInteger || type() == PipeSchemaTypeNumber)) { this->operator[](_T("multipleOf")) = newMultipleOf; } return *this; }

	int maximum() { if((type() == PipeSchemaTypeInteger || type() == PipeSchemaTypeNumber) && isDefined(_T("maximum"))) { return this->operator[](_T("maximum")).int_value(); } return 0; }
	PipeSchemaNode& maximum(int newMaximum) { if((type() == PipeSchemaTypeInteger || type() == PipeSchemaTypeNumber)) { this->operator[](_T("maximum")) = newMaximum; } return *this; }

	bool exclusiveMaximum() { if((type() == PipeSchemaTypeInteger || type() == PipeSchemaTypeNumber) && isDefined(_T("exclusiveMaximum"))) { return this->operator[](_T("exclusiveMaximum")).bool_value(); } return false; }
	PipeSchemaNode& exclusiveMaximum(bool newExclusiveMaximum) { if((type() == PipeSchemaTypeInteger || type() == PipeSchemaTypeNumber)) { this->operator[](_T("exclusiveMaximum")) = newExclusiveMaximum; } return *this; }

	int minimum() { if((type() == PipeSchemaTypeInteger || type() == PipeSchemaTypeNumber) && isDefined(_T("minimum"))) { return this->operator[](_T("minimum")).int_value(); } return 0; }
	PipeSchemaNode& minimum(int newMinimum) { if((type() == PipeSchemaTypeInteger || type() == PipeSchemaTypeNumber)) { this->operator[](_T("minimum")) = newMinimum; } return *this; }

	bool exclusiveMinimum() { if((type() == PipeSchemaTypeInteger || type() == PipeSchemaTypeNumber) && isDefined(_T("exclusiveMinimum"))) { return this->operator[](_T("exclusiveMinimum")).bool_value(); } return false; }
	PipeSchemaNode& exclusiveMinimum(bool newExclusiveMinimum) { if((type() == PipeSchemaTypeInteger || type() == PipeSchemaTypeNumber)) { this->operator[](_T("exclusiveMinimum")) = newExclusiveMinimum; } return *this; }

private:
	bool isDefined(tstring name) {
		if(count(name) == 1)
			return true;

		return false;
	}
};






//======================================================================================================================


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

inline void schemaAddValue(PipeObject& schema, const tstring& key, const PipeSchemaType type, const tstring& description, bool optional = false) {
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

inline void schemaAddValueArray(PipeObject& schema, const tstring& key, const tstring& description, const PipeSchemaType itemType, const tstring& itemDescription) {
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
