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
	NotConnected
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
		string name = "";
		TextComClientStatus status = TextComClientStatus.None;
		Socket socket;
		string[] outQueue;
	}

    struct TextComSocket {
		string name = "";
		TextComSocketType type = TextComSocketType.None;

		string address = "";
		ushort port = 0;
		bool servePath = false;
		string path = "";    

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

        foreach_reverse(ref socket; sockets) {
            if(socket.status != TextComSocketStatus.Listening) {
                this.update(socket);
			}
            else {
				this.read(socket);
				this.write(socket);
			}
        }
    }

    bool createSocket(Qry!TextComSocketConfig socket) {

		if(socket.name in this.sockets) {
			this._ecm.pushEntity(TextComSocketUpdate(socket.name, TextComSocketStatus.Error, TextComSocketError.SocketExists));
		}
		else {
			this.sockets[socket.name] = TextComSocket(
				socket.name,
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

		update(this.sockets[change.socket], change.action);
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

		if(change.action == TextComClientAction.Disconnect)
			this.sockets[change.socket].clients.remove(change.client);

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
        foreach(socket; sockets) {
            update(socket, TextComSocketAction.Delete);
        }
	}

private:
    void update(ref TextComSocket socket, TextComSocketAction action = TextComSocketAction.None) {

    }

    void read(ref TextComSocket socket) {

    }

	void write(ref TextComSocket socket) {

	}
}

//###################################################################################################
