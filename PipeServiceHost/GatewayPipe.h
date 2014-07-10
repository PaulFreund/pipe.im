//======================================================================================================================

#pragma once

//======================================================================================================================

class GatewayPipe : public InstanceClient {
public:
	static const tstring GatewayPipeFolderName;
	static const tstring GatewayPipeAccountName;

public:
	GatewayPipe();
	~GatewayPipe();

public:
	void addIncoming(const tstring& message);
	std::vector<tstring> getOutgoing();
	void setConnection(InstanceConnection* connection);
};

//======================================================================================================================
