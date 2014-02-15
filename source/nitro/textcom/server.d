//###################################################################################################
/*
    Copyright (c) since 2013 - Paul Freund 

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial socketions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/
//###################################################################################################
/*
	Changes to think about after a stable, tested version:	
	* Speed improvements (iteration optimization, control flow etc.)
	* Simplify states
*/
//###################################################################################################

module nitro.textcom.server;

//###################################################################################################

import nitro.gen;

//###################################################################################################

enum TextComSocketType {
	None,
    TCP,
	WebSocket
}

enum TextComSocketError {
    None,
    SendFailed,
    ReceiveFailed,
    UpdateFailed,
	SocketExists,
	SocketUnknown,
	NotConnected,
	InitializeFailed
}

enum TextComSocketStatus {
    None,
	Error,
	Listening
}

enum TextComSocketAction {
	None,
	Delete,
	StartListen,
	StopListen
}

enum TextComClientError {
	None,
	NotConnected
}

enum TextComClientStatus {
	None,
	Error,
	Connected
}

enum TextComClientAction {
	None,
	Disconnect
}

//###################################################################################################

@Component struct TextComSocketConfig {
    TextComSocketType type = TextComSocketType.None;
    string name = "";
    string address = "";
    ushort port = 0;
    bool servePath = false;
    string path = "";
}

@Component struct TextComSocketUpdate {
    string socket = "";
    TextComSocketStatus status = TextComSocketStatus.None;
    TextComSocketError error = TextComSocketError.None;
	string message = "";
}

@Component struct TextComSocketChange {
    string socket = "";
    TextComSocketAction action = TextComSocketAction.None;
}

@Component struct TextComClientChange {
    string socket = "";
    string client = "";
    TextComClientAction action = TextComClientAction.None;
}

@Component struct TextComClientUpdate {
    string socket = "";
    string client = "";
    TextComClientStatus status = TextComClientStatus.None;
    TextComClientError error = TextComClientError.None;
	string message = "";
}

@Component struct TextComOut {
    string socket = "";
    string[] clients;
    string data = "";
}

@Component struct TextComIn {
    string socket = "";
    string client;
    string data = "";
}

//###################################################################################################



@System final class TextComServer(ECM) {
    import std.socket;
	struct TextComClient {
		TextComClientAction action = TextComClientAction.None;
		TextComClientStatus status = TextComClientStatus.None;
		TextComClientError error = TextComClientError.None;
		Socket socket;
		bool connectionInitialized = false;
		string[] outQueue;
	}

    struct TextComSocket {
		TextComSocketType type = TextComSocketType.None;

		string address = "";
		ushort port = 0;
		bool servePath = false;
		string path = "";    

		TextComSocketAction action = TextComSocketAction.None;
        TextComSocketStatus status = TextComSocketStatus.None;
        TextComSocketError error = TextComSocketError.None;
        Socket socket;
        TextComClient[string] clients;
		string[] broadcastQueue;
    }

    TextComSocket[string] sockets;
	private ECM _ecm;

	this(ECM ecm) {
		this._ecm = ecm;
	}

    void run(ECM ecm) {
        mixin AutoQueryMapper!ecm;
		this.process();
    }

    bool createSocket(Qry!TextComSocketConfig socket) {

		if(socket.name in this.sockets) {
			this._ecm.pushEntity(TextComSocketUpdate(socket.name, TextComSocketStatus.Error, TextComSocketError.SocketExists));
		}
		else {
			this.sockets[socket.name] = TextComSocket(
				socket.type,
				socket.address,
				socket.port,
				socket.servePath,
				socket.path
			);
		}

        return true;
    }

	bool updateSocket(Qry!TextComSocketChange change) {
		if(change.action == TextComSocketAction.None)
			return true; 

		if((change.socket in this.sockets) == null) {
			this._ecm.pushEntity(TextComSocketUpdate(change.socket, TextComSocketStatus.Error, TextComSocketError.SocketUnknown));
			return true;
		}

		this.sockets[change.socket].action = change.action;
		return true;
	}

	bool updateClient(Qry!TextComClientChange change) {
		if(change.action == TextComClientAction.None)
			return true; 

		if((change.socket in this.sockets) == null) {
			this._ecm.pushEntity(TextComSocketUpdate(change.socket, TextComSocketStatus.Error, TextComSocketError.SocketUnknown));
			return true;
		}

		if((change.client in this.sockets[change.socket].clients) == null) {
			this._ecm.pushEntity(TextComClientUpdate(change.socket, change.client, TextComClientStatus.Error, TextComClientError.NotConnected));
			return true;
		}

		this.sockets[change.socket].clients[change.client].action = change.action;
		return true;
	}

    bool sendData(Qry!TextComOut data) {
		import std.string : empty;
		if(data.data.empty)
			return true;

		if((data.socket in this.sockets) == null) {
			this._ecm.pushEntity(TextComSocketUpdate(data.socket, TextComSocketStatus.Error, TextComSocketError.SocketUnknown));
			return true;
		}

		if(this.sockets[data.socket].status != TextComSocketStatus.Listening) {

			this._ecm.pushEntity(TextComSocketUpdate(data.socket, TextComSocketStatus.Error, TextComSocketError.NotConnected));
			return true;
		}

        if(data.clients.length == 0) {
            this.sockets[data.socket].broadcastQueue ~= data.data;
        }
		else {
			foreach(ref client; data.clients) {
				if (client in this.sockets[data.socket].clients)
					this.sockets[data.socket].clients[client].outQueue ~= data.data;
				else
					this._ecm.pushEntity(TextComClientUpdate(data.socket, client, TextComClientStatus.Error, TextComClientError.NotConnected));
			}
		}

        return true;
    }

	~this() {
        foreach(socket; sockets) 
			socket.action = TextComSocketAction.Delete;

		this.process();
	}

private:
    void process() {
		string[] deleteSockets;
        foreach(string socketName, ref socket; this.sockets) {
			if(socket.action != TextComSocketAction.None) {
				switch(socket.action) {
					case TextComSocketAction.Delete:		{ deleteSockets ~= socketName;  break; }
					case TextComSocketAction.StartListen:	{ this.initialize(socketName, socket); break; }
					case TextComSocketAction.StopListen:	{ this.destroySocket(socketName, socket); break; }
					default: { break; }
				}
				socket.action = TextComSocketAction.None;
			}

			if(socket.status != TextComSocketStatus.Listening) continue;

			socket.socket.listen(1);
			Socket clientSocket = socket.socket.accept();
			if(clientSocket !is null && clientSocket.isAlive()) {
				import std.uuid : randomUUID;
				string clientName = randomUUID.toString();
				auto newClient = TextComClient();
				newClient.status = TextComClientStatus.Connected;
				newClient.socket = clientSocket;
				socket.clients[clientName] = newClient;
				this._ecm.pushEntity(TextComClientUpdate(socketName, clientName, newClient.status, newClient.error));
			}
				
			if(socket.clients.length > 0) {
				
				foreach(string nameClient, ref client; socket.clients) {

				}
			}
        }

		foreach(socket; deleteSockets) {
			this.destroySocket(socket, this.sockets[socket]);
			this.sockets.remove(socket);
		}
    }

    void read(ref TextComSocket socket) {

    }

	void write(ref TextComSocket socket) {

	}

private:
	void initialize(string name, ref TextComSocket socket) {
		this.destroySocket(name, socket);
		socket.socket = new TcpSocket();
		socket.socket.blocking = false;
		try {
			foreach(address; getAddress(socket.address, socket.port))
				socket.socket.bind(address);

			socket.status = TextComSocketStatus.Listening;
			socket.error = TextComSocketError.None;
			this._ecm.pushEntity(TextComSocketUpdate(name, socket.status, socket.error));
		}
		catch(Exception e) {
			socket.status = TextComSocketStatus.Error;
			socket.error = TextComSocketError.InitializeFailed;
			this._ecm.pushEntity(TextComSocketUpdate(name, socket.status, socket.error, e.msg));
		}
	}

	void destroySocket(string name, ref TextComSocket socket) {
		socket.status = TextComSocketStatus.None;
		//socket.clients.clear();
	}

	void destroyClient(string name, ref TextComClient client) {

	}
}

//###################################################################################################
