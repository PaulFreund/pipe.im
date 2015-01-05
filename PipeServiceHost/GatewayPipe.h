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

class GatewayPipe : public InstanceClient {
private:
	InstanceConnection* _connection;
	std::map <tstring, InstanceSession*> _sessions;

	std::mutex _mutexQueue;
	std::vector<tstring> _outgoing;

	std::map<tstring, tstring> _gateways;
	std::map < tstring, std::map < tstring, std::shared_ptr < InstanceSession > > > _accountSessions;

public:
	static const tstring GatewayPipeFolderName;
	static const tstring GatewayPipeAccountName;
	static const tstring GatewayAddressIdentifier;
	
public:
	GatewayPipe();
	~GatewayPipe();

public:
	virtual void addIncoming(const tstring& message);
	virtual std::vector<tstring> getOutgoing();
	virtual void setConnection(InstanceConnection* connection);

	virtual void addOutgoing(const tstring& message);

public:
	virtual void addSession(tstring id, InstanceSession* session);
	virtual void removeSession(tstring id);

public:
	const std::map<tstring, tstring>& gateways();

private:
	void addGateway(const tstring& name, const tstring& description);
	void removeGateway(const tstring& name);
};

//======================================================================================================================
