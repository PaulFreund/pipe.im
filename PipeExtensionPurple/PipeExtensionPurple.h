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
	virtual void process();
	virtual PipeArrayPtr serviceTypes();
	virtual IPipeExtensionService* create(const tstring& serviceType, const tstring& address, const tstring& path, PipeObjectPtr settings);
	virtual void destroy(IPipeExtensionService* service);

public:
	PurpleInterfaceAccount* account(PurpleAccount* account);
	PurpleInterfaceAccount* accountByRequestHandle(void* requestHandle);
};

//======================================================================================================================
