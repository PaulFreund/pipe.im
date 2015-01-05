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

#include "CommonHeader.h"
#include "GatewayPipe.h"

using namespace std;
using namespace Poco;
using namespace Poco::Util;

//======================================================================================================================

const tstring GatewayPipe::GatewayPipeFolderName = _T("gateway_pipe");
const tstring GatewayPipe::GatewayPipeAccountName = _T("host_gateway");
const tstring GatewayPipe::GatewayAddressIdentifier = _T("pipe.gateway_");

//======================================================================================================================

GatewayPipe::GatewayPipe() 
	: _connection(nullptr) 
{
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());
	InstanceManager::spawnInstance(GatewayPipe::GatewayPipeAccountName, pApp->_datadir + Path::separator() + GatewayPipe::GatewayPipeFolderName);


	// TODO: Iterate over all accounts and create gateway instances according to gateways
}

//----------------------------------------------------------------------------------------------------------------------

GatewayPipe::~GatewayPipe() {}

//----------------------------------------------------------------------------------------------------------------------

void GatewayPipe::addIncoming(const tstring& message) {
	if(!_sessions.empty()) {
		for(auto& session : _sessions) {
			session.second->accountIncomingAdd(message);
		}
	}

	PipeObjectPtr msg = parseObject(message);
	tstring address = (*msg)[TokenMessageAddress].string_value();
	if(!startsWith(address, GatewayAddressIdentifier)) { return; }

	vector<tstring> addressParts = texplode(address.substr(GatewayAddressIdentifier.size()), TokenAddressSeparator);
	if(addressParts.empty()) { return; }

	tstring gatewayName = addressParts[0];
	tstring msgType = (*msg)[TokenMessageMessage].string_value();
	// Add new gateways
	if(addressParts.size() == 1) {
		if(msgType == _T("signed_on")) {
			addGateway(gatewayName, _T("TODO: Add description"));
		}
		else if(msgType == _T("signed_off")) {
			removeGateway(gatewayName);
		}
	}
	else if(addressParts.size() >= 2) {
		auto& gatewaySessions = _accountSessions[gatewayName];
		if(gatewaySessions.empty()) { return; }
		if(msgType == _T("message")) {
			if(gatewaySessions.count(addressParts[1]) == 1) {
				if(msg->count(TokenMessageData) && (*msg)[TokenMessageData].is_string()) { 
					// TODO: Implement properly after purple plugin is done
					tstring data = (*msg)[TokenMessageData].string_value();
					data = data.substr(addressParts[1].size() + 2);
					gatewaySessions[addressParts[1]]->clientInputAdd(data);
				}
			}
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------

std::vector<tstring> GatewayPipe::getOutgoing() {
	_mutexQueue.lock();
	vector<tstring> result = _outgoing; // TODO: Inefficient
	_outgoing.clear();
	_mutexQueue.unlock();
	return result;
}

//----------------------------------------------------------------------------------------------------------------------

void GatewayPipe::setConnection(InstanceConnection* connection) {
	_connection = connection;
}

//----------------------------------------------------------------------------------------------------------------------

void GatewayPipe::addOutgoing(const tstring& message) {
	_mutexQueue.lock();
	_outgoing.push_back(message);
	_mutexQueue.unlock();
}

//----------------------------------------------------------------------------------------------------------------------

void GatewayPipe::addSession(tstring id, InstanceSession* session) {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	if(_sessions.count(id) != 0) {
		pApp->logger().warning(tstring(_T("[GatewayPipe::addSession] InstanceSession already exists: ")) + id);
		return;
	}

	_sessions[id] = session;
}

//----------------------------------------------------------------------------------------------------------------------

void GatewayPipe::removeSession(tstring id) {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	if(_sessions.count(id) == 0) {
		pApp->logger().warning(tstring(_T("[GatewayPipe::removeSession] InstanceSession could not be removed: ")) + id);
		return;
	}

	_sessions.erase(id);
}

//----------------------------------------------------------------------------------------------------------------------

const map<tstring, tstring>& GatewayPipe::gateways() {
	return _gateways;
}

//----------------------------------------------------------------------------------------------------------------------

void GatewayPipe::addGateway(const tstring& name, const tstring& description) {
	_gateways[name] = description;
	auto& gatewaySessions = _accountSessions[name];

	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	for(auto& account : pApp->_accountManager->accounts()) {
		tstring handle = account.second->getGatewayHandle(name);
		if(handle.empty()) { continue; }

		tstring sessionId = pApp->generateUUID();

		tstring handleName = timplode(texplode(handle, TokenAddressSeparator), _T('_'));
		tstring handleAddress = GatewayPipe::GatewayAddressIdentifier + name + TokenAddressSeparator + handleName;
		gatewaySessions[handleName] = make_shared<InstanceSession>(sessionId, account.second, [handleAddress, this](tstring output) {
			PipeJson msg = PipeJson(PipeObject());
			PipeObject& msgObj = msg.object_items();
			msgObj[TokenMessageAddress] = handleAddress;
			msgObj[TokenMessageTimestamp] = currentTimestamp();
			msgObj[TokenMessageRef] = GatewayPipe::GatewayPipeAccountName;
			msgObj[TokenMessageCommand] = _T("say");
			msgObj[TokenMessageData] = output;
			addOutgoing(msg.dump());
		}, true);
	}
}

//----------------------------------------------------------------------------------------------------------------------

void GatewayPipe::removeGateway(const tstring& name) {
	if(_gateways.count(name) == 1)
		_gateways.erase(name);

	if(_accountSessions.count(name) == 1)
		_accountSessions.erase(name);
}

//======================================================================================================================
