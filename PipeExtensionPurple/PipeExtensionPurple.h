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
	virtual std::vector<PipeExtensionServiceType> serviceTypes();

	virtual IPipeExtensionService* create(tstring serviceTypeId, tstring id, tstring path, std::map<tstring, tstring> settings);

	virtual void destroy(IPipeExtensionService* service);
};

//======================================================================================================================
