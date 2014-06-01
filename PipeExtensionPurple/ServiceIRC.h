//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"

//======================================================================================================================

class ServiceIRC : public PipeServiceNodeBase {
public:
	ServiceIRC(const tstring& address, const tstring& path, PipeObjectPtr settings) : PipeServiceNodeBase(_T("irc"), _T("Internet relay Chat"), address, path, settings) {
		PipeSchemaNode info(PipeSchemaTypeObject);
		auto& infoData = info.property(TokenMessageData, PipeSchemaTypeObject).title(_T("Info")).description(_T("Information about the node"));
		infoData.property(TokenMessageAddress, PipeSchemaTypeString).title(_T("Address")).description(_T("Address of the node"));
		infoData.property(TokenSchemaType, PipeSchemaTypeString).title(_T("Type")).description(_T("Unique type of this node"));
		infoData.property(TokenSchemaDescription, PipeSchemaTypeString).title(_T("Description")).description(_T("Description of the node"));
		auto& infoDataState = infoData.property(_T("states"), PipeSchemaTypeArray).title(_T("States")).description(_T("Runtime states of the node")).items(PipeSchemaTypeObject).title(_T("State")).description(_T("Runtime state"));
		infoDataState.property(_T("key"), PipeSchemaTypeString).title(_T("Key")).description(_T("Name of the state"));
		infoDataState.property(_T("value"), PipeSchemaTypeString).title(_T("Value")).description(_T("Value of the state"));
		
		std::cout << _T("Schema: ") << std::endl << dumpObject(info);

		
		PipeObjectPtr schemaInfo = newObject();
		auto&& schemaInfoProperties = schemaAddObject(*schemaInfo, TokenMessageData, _T("Information about the node")); {
			schemaAddValue(schemaInfoProperties, TokenMessageAddress, PipeSchemaTypeString, _T("Address of the node"));
			schemaAddValue(schemaInfoProperties, TokenSchemaType, PipeSchemaTypeString, _T("Unique type of this node"));
			schemaAddValue(schemaInfoProperties, TokenSchemaDescription, PipeSchemaTypeString, _T("Description of the node"));
			auto&& schemaInfoPropertiesItems = schemaAddObjectArray(schemaInfoProperties, _T("properties"), _T("Runtime properties of the node"), _T("Runtime property")); {
				schemaAddValue(schemaInfoPropertiesItems, _T("key"), PipeSchemaTypeString, _T("Name of the property"));
				schemaAddValue(schemaInfoPropertiesItems, _T("value"), PipeSchemaTypeString, _T("Value of the property"));
			}
		}
		
		std::cout << std::endl << _T("Schema Old: ") << std::endl << dumpObject(schemaInfo);


	}
	
	virtual ~ServiceIRC() {}
};

//======================================================================================================================
