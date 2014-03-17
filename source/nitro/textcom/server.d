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
import std.conv;
import std.bitmanip;

//###################################################################################################

enum TextComSocketType {
	None,
    TCP,
	WebSocket
}

enum TextComError {
    None,
    SendFailed,
    ReceiveFailed,
    UpdateFailed,
	SocketExists,
	SocketUnknown,
	NotConnected,
	InitializeFailed,
    ConnectionLost,
    InvalidBlockLength,
    Disconnected
}

enum TextComStatus {
    None,
	Error,
	Working
}

enum TextComSocketAction {
	None,
	Delete,
	StartListen,
	StopListen
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
    TextComStatus status = TextComStatus.None;
    TextComError error = TextComError.None;
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
    TextComStatus status = TextComStatus.None;
    TextComError error = TextComError.None;
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
//---------------------------------------------------------------------------------------------------
// Definition of internal entities
private:
    import std.socket;
	struct TextComClient {
		TextComClientAction action = TextComClientAction.None;
		TextComStatus status = TextComStatus.None;
		TextComError error = TextComError.None;
		Socket socket;
		bool connectionInitialized = false;
		string[] outQueue;

        uint currentBlockLength = 0;
        ubyte[] currentBlockBuffer;
	}

    struct TextComSocket {
		TextComSocketType type = TextComSocketType.None;

		string address = "";
		ushort port = 0;
		bool servePath = false;
		string path = "";    

		TextComSocketAction action = TextComSocketAction.None;
        TextComStatus status = TextComStatus.None;
        TextComError error = TextComError.None;
        Socket socket;
        TextComClient[string] clients;
    }

//---------------------------------------------------------------------------------------------------
// Interface
public:
    TextComSocket[string] sockets;
	private ECM _ecm;

	this(ECM ecm) {
		this._ecm = ecm;
	}

    void run(ECM ecm) {
        mixin AutoQueryMapper!ecm;
		this.processSockets();
    }

	~this() {
        foreach(socket; sockets) 
			socket.action = TextComSocketAction.Delete;

		this.processSockets();
	}
//---------------------------------------------------------------------------------------------------
// Query handling
public:
    // TextComSocketConfig components contain new socket definitions
    bool createSocket(Qry!TextComSocketConfig socket) {

		if(socket.name in this.sockets) {
			this._ecm.pushEntity(TextComSocketUpdate(socket.name, TextComStatus.Error, TextComError.SocketExists));
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

    // Set action for a socket on next processing
	bool updateSocket(Qry!TextComSocketChange change) {
		if(change.action == TextComSocketAction.None)
			return true; 

        // Error checking
        {
		    if((change.socket in this.sockets) == null) {
			    this._ecm.pushEntity(TextComSocketUpdate(change.socket, TextComStatus.Error, TextComError.SocketUnknown));
			    return true;
		    }
        }

		this.sockets[change.socket].action = change.action;
		return true;
	}

    // Set action for a client on next processing
	bool updateClient(Qry!TextComClientChange change) {
		if(change.action == TextComClientAction.None)
			return true; 

        // Error checking
        { 
		    if((change.socket in this.sockets) == null) {
			    this._ecm.pushEntity(TextComSocketUpdate(change.socket, TextComStatus.Error, TextComError.SocketUnknown));
			    return true;
		    }

		    if((change.client in this.sockets[change.socket].clients) == null) {
			    this._ecm.pushEntity(TextComClientUpdate(change.socket, change.client, TextComStatus.Error, TextComError.NotConnected));
			    return true;
		    }
        }

		this.sockets[change.socket].clients[change.client].action = change.action;
		return true;
	}

    // Data to send to a client or all clients 
    bool sendData(Qry!TextComOut data) {
		import std.string : empty;
		if(data.data.empty)
			return true;

        // Error checking
        {
		    if((data.socket in this.sockets) == null) {
			    this._ecm.pushEntity(TextComSocketUpdate(data.socket, TextComStatus.Error, TextComError.SocketUnknown));
			    return true;
		    }

		    if(this.sockets[data.socket].status != TextComStatus.Working) {
			    this._ecm.pushEntity(TextComSocketUpdate(data.socket, TextComStatus.Error, TextComError.NotConnected));
			    return true;
		    }
        }

        // If no client is set, send to all
        if(data.clients.length == 0) {
            foreach(ref socket; this.sockets) {
                foreach(ref client; socket.clients) {
                    client.outQueue ~= data.data;
                }
            }
        }
		else {
			foreach(ref client; data.clients) {
				if (client in this.sockets[data.socket].clients)
					this.sockets[data.socket].clients[client].outQueue ~= data.data;
				else
					this._ecm.pushEntity(TextComClientUpdate(data.socket, client, TextComStatus.Error, TextComError.NotConnected));
			}
		}

        return true;
    }



//---------------------------------------------------------------------------------------------------
// Internal processing
private:
    void processSockets() {
        // Process all sockets
		string[] deleteSockets;
        foreach(string socketName, ref socket; this.sockets) {
            // Process actions
			if(socket.action != TextComSocketAction.None) {
				switch(socket.action) {
					case TextComSocketAction.Delete:		{ deleteSockets ~= socketName;  break; }
					case TextComSocketAction.StartListen:	{ this.initializeSocket(socketName, socket); break; }
					case TextComSocketAction.StopListen:	{ this.disconnectSocket(socketName, socket); break; }
					default: { break; }
				}
				socket.action = TextComSocketAction.None;
			}

            // Check if socket is intact
            if(socket.socket is null || !socket.socket.isAlive()) {
                socket.status = TextComStatus.Error;
                socket.error = TextComError.ConnectionLost;
                this._ecm.pushEntity(TextComSocketUpdate(socketName, socket.status, socket.error));
            }

            // If socket is not listening, disconect
			if(socket.status != TextComStatus.Working) 
                continue;
            else
                processClients(socketName, socket);
        }

        // Cleanup deleted sockets
		foreach(socket; deleteSockets) {
			this.disconnectSocket(socket, this.sockets[socket]);
			this.sockets.remove(socket);
		}
    }

    void processClients(string socketName, ref TextComSocket socket) {
        // Accept one new connection if any and creates a new client
        socket.socket.listen(1);
        Socket clientSocket = socket.socket.accept();
        if(clientSocket !is null && clientSocket.isAlive()) {
            import std.uuid : randomUUID;
            string clientName = randomUUID.toString();
            auto newClient = TextComClient();
            newClient.status = TextComStatus.Working;
            newClient.socket = clientSocket;
            if(socket.type == TextComSocketType.TCP)
                newClient.connectionInitialized = true;

            socket.clients[clientName] = newClient;
            this._ecm.pushEntity(TextComClientUpdate(socketName, clientName, newClient.status, newClient.error));
        }

        string[] deleteClients;
        foreach(string clientName, ref client; socket.clients) {
			if(client.action == TextComClientAction.Disconnect) {
                deleteClients ~= clientName;
				client.action = TextComClientAction.None;
			}

            // Check if  client socket is intact
            if(client.socket is null || !client.socket.isAlive()) {
                client.status = TextComStatus.Error;
                client.error = TextComError.ConnectionLost;
                this._ecm.pushEntity(TextComClientUpdate(socketName, clientName, client.status, client.error));
            }

            // If socket is not listening, disconect
			if(client.status != TextComStatus.Working) 
                continue;

            // Check if connection is ready
            if(!client.connectionInitialized) {
                if(socket.type == TextComSocketType.WebSocket) {
                    websocketInitialize(socketName, clientName, client);
                }
                continue;
            }

            clientSend(socketName, clientName, client);
            clientReceive(socketName, clientName, client);
        }

        // Cleanup deleted clients
		foreach(client; deleteClients) {
			this.disconnectClient(client, socket.clients[client]);
			socket.clients.remove(client);
		}
    }

    void clientReceive(ref string socketName, ref string clientName, ref TextComClient client) {
        try {
            ubyte[8192] receiveBuffer;
            ptrdiff_t receivedBytes = client.socket.receive(receiveBuffer);


            if(receivedBytes > 0) {
                ubyte[] receivedData = receiveBuffer[0..receivedBytes];
                while(receivedData.length > 0) {
                    // Get new block size
                    if(client.currentBlockLength == 0 && receivedData.length >= 8) {
                        client.currentBlockBuffer.clear();
                        client.currentBlockLength = bigEndianToNative!uint(receivedData[0..uint.sizeof]);
                        receivedData = receivedData[8..$];
                    }
                    // Read block data
                    else {
                        uint bytesMissing = client.currentBlockLength - client.currentBlockBuffer.length;
                        uint bytesToCopy = bytesMissing >= receivedData.length ? receivedData.length :  bytesMissing;

                        client.currentBlockBuffer ~= receivedData[0..bytesToCopy];
                        receivedData = receivedData[bytesToCopy..$];

                        if(client.currentBlockLength == client.currentBlockBuffer.length) {
                            this._ecm.pushEntity(TextComIn(socketName, clientName, to!string(client.currentBlockBuffer)));
                        }
                    }
                }
            }
            else if(receivedBytes == 0) {
                client.action = TextComClientAction.Disconnect;
                client.status = TextComStatus.Error;
                client.error = TextComError.Disconnected;
                this._ecm.pushEntity(TextComClientUpdate(socketName, clientName, client.status, client.error));
            }
            else if(!wouldHaveBlocked()) {
                throw new Exception(client.socket.getErrorText());
            }
        }
        catch(Exception e) {
            client.status = TextComStatus.Error;
            client.error = TextComError.ReceiveFailed;
            this._ecm.pushEntity(TextComClientUpdate(socketName, clientName, client.status, client.error, e.msg));
        }
    }

	void clientSend(ref string socketName, ref string clientName, ref TextComClient client) {
        try {
            foreach(ref string message; client.outQueue) {
                uint blockSize = to!uint(message.length);
                client.socket.send(nativeToBigEndian(blockSize));
                client.socket.send(message);
            }
        }
        catch(Exception e) {
            client.status = TextComStatus.Error;
            client.error = TextComError.SendFailed;
            this._ecm.pushEntity(TextComClientUpdate(socketName, clientName, client.status, client.error, e.msg));
        }
        
        client.outQueue.clear();
	}

    void websocketInitialize(ref string socketName, ref string clientName, ref TextComClient client) {
        try {
            ubyte[8192] receiveBuffer;
            ptrdiff_t receivedBytes = client.socket.receive(receiveBuffer);

            if(receivedBytes > 0) {
                ubyte[] receivedData = receiveBuffer[0..receivedBytes];

                // TODO
                import std.stdio;
                writeln(cast(string)receiveBuffer);
            }
            else if(receivedBytes == 0) {
                client.action = TextComClientAction.Disconnect;
                client.status = TextComStatus.Error;
                client.error = TextComError.Disconnected;
                this._ecm.pushEntity(TextComClientUpdate(socketName, clientName, client.status, client.error));
            }
            else if(!wouldHaveBlocked()) {
                throw new Exception(client.socket.getErrorText());
            }
        }
        catch(Exception e) {
            client.status = TextComStatus.Error;
            client.error = TextComError.ReceiveFailed;
            this._ecm.pushEntity(TextComClientUpdate(socketName, clientName, client.status, client.error, e.msg));
        }
    }

//---------------------------------------------------------------------------------------------------
// Helpers
private:
	void initializeSocket(string name, ref TextComSocket socket) {
		this.disconnectSocket(name, socket);
		socket.socket = new TcpSocket();
		socket.socket.blocking = false;
		try {
			foreach(address; getAddress(socket.address, socket.port))
				socket.socket.bind(address);

			socket.status = TextComStatus.Working;
			socket.error = TextComError.None;
			this._ecm.pushEntity(TextComSocketUpdate(name, socket.status, socket.error));
		}
		catch(Exception e) {
			socket.status = TextComStatus.Error;
			socket.error = TextComError.InitializeFailed;
			this._ecm.pushEntity(TextComSocketUpdate(name, socket.status, socket.error, e.msg));
		}
	}

	void disconnectSocket(string name, ref TextComSocket socket) {
        foreach(string nameClient, ref client; socket.clients) {
            disconnectClient(nameClient, client);
        }

        socket.action = TextComSocketAction.None;
        socket.status = TextComStatus.None;
        socket.error = TextComError.None;
        
        if(socket.socket !is null) {
            socket.socket.shutdown(SocketShutdown.BOTH);
            socket.socket.close();
        }
        socket.socket = null;

		socket.clients.clear();
	}

	void disconnectClient(string name, ref TextComClient client) {
        if(client.socket !is null) {
            client.socket.shutdown(SocketShutdown.BOTH);
            client.socket.close();
        }

        client.action = TextComClientAction.None;
        client.status = TextComStatus.None;
        client.error = TextComError.None;

        client.connectionInitialized = false;
        client.outQueue.clear();
        client.currentBlockLength = 0;
        client.currentBlockBuffer.clear();
	}
}

//###################################################################################################
