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

private:
	std::map<tstring, PurpleInterfaceAccount*> _services;

public:
	PipeExtensionPurple();
	virtual ~PipeExtensionPurple();

public:
	virtual PipeArrayPtr serviceTypes();

	virtual IPipeExtensionService* create(const tstring& serviceType, const tstring& address, const tstring& path, PipeObjectPtr settings);
	virtual void destroy(IPipeExtensionService* service);

	virtual void process();

public:
	PurpleInterfaceAccount* account(PurpleAccount* account);
	PurpleInterfaceAccount* accountByRequestHandle(void* requestHandle);
};

//======================================================================================================================
