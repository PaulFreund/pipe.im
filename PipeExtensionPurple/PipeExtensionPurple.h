//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"

//======================================================================================================================

class PipeExtensionPurple : public IPipeExtension {
public:
	static PipeExtensionPurple ExtensionInstance;
	static PipeExtensionCbErr ErrorCallback;
private:
	std::map<tstring, IPipeExtensionService*> _services;
	bool _libpurple_init_done;

public:
	PipeExtensionPurple();
	virtual ~PipeExtensionPurple();

public:
	virtual PipeArrayPtr serviceTypes();
	virtual IPipeExtensionService* create(const tstring& serviceType, const tstring& address, const tstring& path, PipeObjectPtr settings);
	virtual void destroy(IPipeExtensionService* service);
};

//======================================================================================================================
