//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeServiceNodeBase.h"

//======================================================================================================================

class PipeScript {
public:
	int _priority;
	tstring _name;

private:
	tstring _data;
	duk_context* _context;

public:
	PipeScript(const tstring& name, int priority, const tstring& data, duk_context* context);
	~PipeScript();

public:
	static std::shared_ptr<PipeScript> create(PipeServiceNodeBase* serviceRoot, const tstring& name, bool preSend, bool postReceive, int priority, const tstring& data);

public:
	void execute(tstring function, PipeObject& message);
};