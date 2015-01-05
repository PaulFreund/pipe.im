//======================================================================================================================
/*
	Copyright (c) since 2015 - Paul Freund (freund.paul@lvl3.org)
	
	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:
	
	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/
//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeScript.h"
#include "PipeServiceNode.h"
#include "PipeExtensionInstance.h"

//======================================================================================================================

class ServiceRoot : public PipeServiceNode {
public:
	static std::vector<std::shared_ptr<PipeExtensionInstance>> Extensions;

private:
	std::mutex _mutexQueue;
	PipeArrayPtr _queueIncoming;
	PipeArrayPtr _queueOutgoing;

	PipeObjectPtr _config;

	std::vector<tstring> _providerTypes;

	PipeArrayPtr _scriptIncomingQueue; // TODO: Recap/Cleanup
	PipeArrayPtr _scriptOutgoingQueue; // TODO: Recap/Cleanup
	std::vector<std::shared_ptr<PipeScript>> _scriptsPreSend; // TODO: Recap/Cleanup
	std::vector<std::shared_ptr<PipeScript>> _scriptsPostReceive; // TODO: Recap/Cleanup

	std::shared_ptr<PipeServiceNode> _serviceScripts;
	std::shared_ptr<PipeServiceNode> _serviceServices;
	std::shared_ptr<PipeServiceNode> _serviceServicesProviders;
	std::shared_ptr<PipeServiceNode> _serviceServicesInstances;

public:
	ServiceRoot(const tstring& path, PipeObjectPtr settings);
	virtual ~ServiceRoot();

	void scriptPushIncoming(PipeObjectPtr message); // TODO: Recap/Cleanup
	void scriptPushOutgoing(PipeObjectPtr message); // TODO: Recap/Cleanup

public:
	void process();

	virtual void addIncoming(PipeArrayPtr messages);
	virtual PipeArrayPtr getOutgoing();

private:
	void loadConfig();
	bool readConfig();
	void writeConfig();
	tstring configPath();

private:
	void initServices();
	tstring createService(const tstring& type, const tstring& name, PipeObject& settings);
	void deleteService(const tstring& name);

private:
	void initScripts();
	tstring createScript(const tstring& name, bool preSend, bool postReceive, int priority, const tstring& data);
	void deleteScript(const tstring& name);
	void executeScripts(PipeArrayPtr messages, bool preSend, bool postReceive);
};

//======================================================================================================================
