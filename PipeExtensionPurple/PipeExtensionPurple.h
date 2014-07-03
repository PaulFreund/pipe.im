//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"

//======================================================================================================================

class PurpleInterfaceAccount;
class PurpleInterface;

//======================================================================================================================

class PipeExtensionPurple : public IPipeExtension {
public:
	static PipeExtensionPurple ExtensionInstance;
	static tstring ExtensionInstancePath;
	static PipeExtensionCbErr ErrorCallback;
	static std::shared_ptr<PurpleInterface> Purple;
public:
	std::map<tstring, PurpleInterfaceAccount*> _services;

public:
	PipeExtensionPurple();
	virtual ~PipeExtensionPurple();

public:
	virtual PipeArrayPtr serviceTypes();

	virtual HPipeExtensionService create(const tstring& serviceType, const tstring& address, const tstring& path, PipeObjectPtr settings);
	virtual void destroy(HPipeExtensionService service);

	virtual void process();

	virtual void push(PipeArrayPtr messages);
	virtual PipeArrayPtr pull();

public:
	PurpleInterfaceAccount* account(PurpleAccount* account);
	PurpleInterfaceAccount* accountByRequestHandle(void* requestHandle);
};

//======================================================================================================================
