//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"

//======================================================================================================================

class PipeExtensionPurple : public IPipeExtension {
public:
	static PipeExtensionPurple ExtensionInstance;

private:
	std::map<tstring, IPipeExtensionService*> _services;
	bool _libpurple_init_done;

public:
	PipeExtensionPurple();
	virtual ~PipeExtensionPurple();

public:
	virtual PipeJsonArray serviceTypes();
	virtual PipeJsonObject serviceTypeSettings(const tstring& serviceType);
	virtual IPipeExtensionService* create(const tstring& serviceType, const tstring& address, const tstring& path, PipeJsonObject settings);
	virtual void destroy(IPipeExtensionService* service);
};

//======================================================================================================================
