//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeDataTypes.h"

//======================================================================================================================

enum PipeSchemaType {
	PipeSchemaTypeNone,
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
	
	return _T("");
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
	
	return PipeSchemaTypeNone;
}

//======================================================================================================================

// Not implemented: patternProperties, additionalProperties, additionalItems, dependencies, definitions, ref, id, not, anyOf, allOf, oneOf
namespace PipeSchemaConstants {
	static PipeJson EmptyValue;
	static PipeArray EmptyArray;
	static PipeObject EmptyObject;
};

class PipeSchema;
typedef std::shared_ptr<PipeSchema> PipeSchemaNodePtr;
class PipeSchema : public PipeObject {
public:


public:
	static PipeSchema Create(PipeSchemaType type) { return PipeSchema(type); }

public:
	PipeSchema(PipeSchemaType type) {
		(*this)[_T("type")] = schemaTypeString(type);
	}

public: // Keywords for all nodes
	PipeSchemaType type() { if(isDefined(_T("type"))) { return schemaTypeIdentifier((*this)[_T("type")].string_value()); } return PipeSchemaTypeNone; }

	tstring title() { if(isDefined(_T("title"))) { return (*this)[_T("title")].string_value(); } return _T(""); }
	PipeSchema& title(tstring newTitle) { (*this)[_T("title")] = newTitle; return *this; }

	tstring description() { if(isDefined(_T("description"))) { return (*this)[_T("description")].string_value(); } return _T(""); }
	PipeSchema& description(tstring newDescription) { (*this)[_T("description")] = newDescription; return *this; }

	tstring format() { if(isDefined(_T("format"))) { return (*this)[_T("format")].string_value(); } return _T(""); }
	PipeSchema& format(tstring newFormat) { (*this)[_T("format")] = newFormat; return *this; }

	PipeArray& enumTypes() { if(isDefined(_T("enum"))) { return (*this)[_T("enum")].array_items(); } PipeSchemaConstants::EmptyArray.clear(); return PipeSchemaConstants::EmptyArray; }
	PipeSchema& enumTypes(PipeArray& newEnumTypes) { (*this)[_T("enum")] = newEnumTypes; return *this; }

	PipeJson& defaultValue() { if(isDefined(_T("default"))) { return (*this)[_T("default")]; } return PipeSchemaConstants::EmptyValue; }
	PipeSchema& defaultValue(PipeJson newDefaultValue) { (*this)[_T("default")] = newDefaultValue; return *this; }

public: // Keywords for objects
	int maxProperties() { if(type() == PipeSchemaTypeObject && isDefined(_T("maxProperties"))) { return (*this)[_T("maxProperties")].int_value(); } return 0; }
	PipeSchema& maxProperties(int newMaxProperties) { if(type() == PipeSchemaTypeObject) { (*this)[_T("maxProperties")] = newMaxProperties; } return *this; }

	int minProperties() { if(type() == PipeSchemaTypeObject && isDefined(_T("minProperties"))) { return (*this)[_T("minProperties")].int_value(); } return 0; }
	PipeSchema& minProperties(int newMinProperties) { if(type() == PipeSchemaTypeObject) { (*this)[_T("minProperties")] = newMinProperties; } return *this; }

	std::vector<tstring> required() {
		std::vector<tstring> result;
		if(type() == PipeSchemaTypeObject && isDefined(_T("required"))) {
			auto&& required = (*this)[_T("required")].array_items();
			for(auto&& item : required) { result.push_back(item.string_value()); }
		} 
		return result;
	}

	PipeSchema& required(std::vector<tstring> newRequired) {
		if(!isDefined(_T("required"))) { (*this)[_T("required")] = PipeArray(); }
		auto&& required = (*this)[_T("required")].array_items();
		for(auto&& item : newRequired) { required.push_back(item); }
		return *this; 
	}

	PipeSchema& property(tstring name) { 
		if(type() != PipeSchemaTypeObject) { PipeSchemaConstants::EmptyObject.clear(); return static_cast<PipeSchema&>(PipeSchemaConstants::EmptyObject); }
		if(!isDefined(_T("properties"))) { (*this)[_T("properties")] = PipeObject(); }

		auto&& properties = (*this)[_T("properties")].object_items();
		if(properties.count(name) == 1)
			return static_cast<PipeSchema&>(properties[name].object_items());
		
		PipeSchemaConstants::EmptyObject.clear();
		return static_cast<PipeSchema&>(PipeSchemaConstants::EmptyObject);
	}

	PipeSchema& property(tstring name, PipeSchemaType newPropertyType) { auto schema = PipeSchema(newPropertyType); return property(name, schema); }
	PipeSchema& property(tstring name, PipeSchema& newProperty) {
		if(type() != PipeSchemaTypeObject) { PipeSchemaConstants::EmptyObject.clear(); return static_cast<PipeSchema&>(PipeSchemaConstants::EmptyObject); }
		if(!isDefined(_T("properties"))) { (*this)[_T("properties")] = PipeObject(); }

		auto&& properties = (*this)[_T("properties")].object_items();
		properties[name] = newProperty;
		return static_cast<PipeSchema&>(properties[name].object_items());
	}

	PipeObject& properties() {
		if(type() == PipeSchemaTypeObject && isDefined(_T("properties")))
			return (*this)[_T("properties")].object_items();
		
		PipeSchemaConstants::EmptyObject.clear();
		return PipeSchemaConstants::EmptyObject;
	}

public: // Keywords for arrays
	PipeSchema& items() { if(type() == PipeSchemaTypeArray && isDefined(_T("items"))) { return static_cast<PipeSchema&>((*this)[_T("items")].object_items()); } PipeSchemaConstants::EmptyObject.clear(); return static_cast<PipeSchema&>(PipeSchemaConstants::EmptyObject); }
	PipeSchema& items(PipeSchemaType newItemsType) { auto schema = PipeSchema(newItemsType); return items(schema); }
	PipeSchema& items(PipeSchema& newItems) { if(type() == PipeSchemaTypeArray) { (*this)[_T("items")] = newItems; } return static_cast<PipeSchema&>((*this)[_T("items")].object_items()); }

	int maxItems() { if(type() == PipeSchemaTypeArray && isDefined(_T("maxItems"))) { return (*this)[_T("maxItems")].int_value(); } return 0; }
	PipeSchema& maxItems(int newMaxItems) { if(type() == PipeSchemaTypeArray) { (*this)[_T("maxItems")] = newMaxItems; } return *this; }

	int minItems() { if(type() == PipeSchemaTypeArray && isDefined(_T("minItems"))) { return (*this)[_T("minItems")].int_value(); } return 0; }
	PipeSchema& minItems(int newMinItems) { if(type() == PipeSchemaTypeArray) { (*this)[_T("minItems")] = newMinItems; } return *this; }

	bool uniqueItems() { if(type() == PipeSchemaTypeArray && isDefined(_T("uniqueItems"))) { return (*this)[_T("uniqueItems")].bool_value(); } return false; }
	PipeSchema& uniqueItems(bool newUniqueItems) { if(type() == PipeSchemaTypeArray) { (*this)[_T("uniqueItems")] = newUniqueItems; } return *this; }

public: // Keywords for strings
	int maxLength() { if(type() == PipeSchemaTypeString && isDefined(_T("maxLength"))) { return (*this)[_T("maxLength")].int_value(); } return 0; }
	PipeSchema& maxLength(int newMaxLength) { if(type() == PipeSchemaTypeString) { (*this)[_T("maxLength")] = newMaxLength; } return *this; }
	
	int minLength() { if(type() == PipeSchemaTypeString && isDefined(_T("minLength"))) { return (*this)[_T("minLength")].int_value(); } return 0; }
	PipeSchema& minLength(int newMinLength) { if(type() == PipeSchemaTypeString) { (*this)[_T("minLength")] = newMinLength; } return *this; }

	tstring pattern() { if(type() == PipeSchemaTypeString && isDefined(_T("pattern"))) { return (*this)[_T("pattern")].string_value(); } return _T(""); }
	PipeSchema& pattern(tstring newPattern) { if(type() == PipeSchemaTypeString) { (*this)[_T("pattern")] = newPattern; } return *this; }
	
public: // Keywords for number, integer
	int multipleOf() { if(type() == PipeSchemaTypeInteger && isDefined(_T("multipleOf"))) { return (*this)[_T("multipleOf")].int_value(); } return 0; }
	PipeSchema& multipleOf(int newMultipleOf) { if(type() == PipeSchemaTypeInteger) { (*this)[_T("multipleOf")] = newMultipleOf; } return *this; }

	double fmultipleOf() { if(type() == PipeSchemaTypeNumber && isDefined(_T("multipleOf"))) { return (*this)[_T("multipleOf")].number_value(); } return 0.0; }
	PipeSchema& fmultipleOf(double newMultipleOf) { if(type() == PipeSchemaTypeNumber) { (*this)[_T("multipleOf")] = newMultipleOf; } return *this; }

	int maximum() { if(type() == PipeSchemaTypeInteger && isDefined(_T("maximum"))) { return (*this)[_T("maximum")].int_value(); } return 0; }
	PipeSchema& maximum(int newMaximum) { if(type() == PipeSchemaTypeInteger) { (*this)[_T("maximum")] = newMaximum; } return *this; }

	float fmaximum() { if(type() == PipeSchemaTypeNumber && isDefined(_T("maximum"))) { return (*this)[_T("maximum")].number_value(); } return 0.0; }
	PipeSchema& fmaximum(float newMaximum) { if(type() == PipeSchemaTypeNumber) { (*this)[_T("maximum")] = newMaximum; } return *this; }

	bool exclusiveMaximum() { if((type() == PipeSchemaTypeInteger || type() == PipeSchemaTypeNumber) && isDefined(_T("exclusiveMaximum"))) { return (*this)[_T("exclusiveMaximum")].bool_value(); } return false; }
	PipeSchema& exclusiveMaximum(bool newExclusiveMaximum) { if((type() == PipeSchemaTypeInteger || type() == PipeSchemaTypeNumber)) { (*this)[_T("exclusiveMaximum")] = newExclusiveMaximum; } return *this; }

	int minimum() { if(type() == PipeSchemaTypeInteger && isDefined(_T("minimum"))) { return (*this)[_T("minimum")].int_value(); } return 0; }
	PipeSchema& minimum(int newMinimum) { if(type() == PipeSchemaTypeInteger) { (*this)[_T("minimum")] = newMinimum; } return *this; }

	double fminimum() { if(type() == PipeSchemaTypeNumber && isDefined(_T("minimum"))) { return (*this)[_T("minimum")].number_value(); } return 0.0; }
	PipeSchema& fminimum(double newMinimum) { if(type() == PipeSchemaTypeNumber) { (*this)[_T("minimum")] = newMinimum; } return *this; }

	bool exclusiveMinimum() { if((type() == PipeSchemaTypeInteger || type() == PipeSchemaTypeNumber) && isDefined(_T("exclusiveMinimum"))) { return (*this)[_T("exclusiveMinimum")].bool_value(); } return false; }
	PipeSchema& exclusiveMinimum(bool newExclusiveMinimum) { if((type() == PipeSchemaTypeInteger || type() == PipeSchemaTypeNumber)) { (*this)[_T("exclusiveMinimum")] = newExclusiveMinimum; } return *this; }

public:
	bool isDefined(tstring name) {
		if(count(name) == 1)
			return true;

		return false;
	}
};

//======================================================================================================================
