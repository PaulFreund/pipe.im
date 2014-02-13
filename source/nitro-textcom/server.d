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
//###################################################################################################

module nitro_textcom.server;

//###################################################################################################

import nitro;

//###################################################################################################

enum TextComPortType {
    WebSocket,
    TCP
}

@Component struct TextComPort {
    TextComPortType type;
    string name;
    string address;
    ushort port;
    bool servePath;
    string path;    
}

@Component struct TextComConfig {
    TextComPort[] ports;
}

enum TextComConnectionStatus {
    None,
    Connected,
    Disconnected,
    Connecting,
    Disconnecting
}

enum TextComConnectionError {
    None,
    SendFailed,
    ReceiveFailed,
    UpdateFailed
}

@Component struct TextComConnectionChange {
    string server;
    string client;
    TextComConnectionStatus newStatus;
}

@Component struct TextComError {
    string server;
    string client;
    TextComConnectionStatus status;
    TextComConnectionError error;
}

@Component struct TextComOut {
    string server;
    string[] clients;
    string data;
}

@Component struct TextComOutLater {
    string server;
    string[] clients;
    string data;
}

@Component struct TextComIn {
    string server;
    string client;
    string data;
}

//###################################################################################################

@System final class TextComServer(ECM) {
    import std.socket;
    struct Port {
        TextComPort config;
        TextComConnectionStatus status;
        Socket socket;
        Socket[string] clients;
    }

    Port[string] ports;

    void run(ECM ecm) {
        // Check connection status and read data
        foreach(port; ports) {
            //if(port.status != TextComConnectionStatus.Connected)
                //port.update();
            
            //port.read();
        }

        mixin AutoQueryMapper!ecm;
    }

    bool loadConfig(Qry!TextComConfig config) {
        import std.stdio;
        foreach(portConfig; config.ports) {
            // Todo: check if name exists
            this.ports[portConfig.name] = Port(portConfig, TextComConnectionStatus.Connecting);
        }
        return true;
    }

    bool sendData(Qry!TextComOut data) {
        bool deletePacket = false;
        if(data.clients.length > 1 && ports.length >= 1) {
            // Send to all
        }
        //else if {
        //    
        //}

        return deletePacket;
        // Only delete if data bas been sent
    }

	~this() {
        foreach(port; ports) {
            //port.update(TextComConnectionStatus.Disconnecting);
        }
	}

private:
    TextComConnectionStatus update(ref Port port, TextComConnectionStatus newStatus = TextComConnectionStatus.None) {
        return newStatus;
    }

    void read(ref Port port) {

    }


}

//###################################################################################################

/*
interface TextComConnection {
    TextComConnectionStatus Update(TextComConnectionStatus setStatus);
    string Receive();
    void Send(string data);
}

class TextComConnectionTCP : TextComConnection {

}

class TextComConnectionWebsocket : TextComConnection {

}
*/

//###################################################################################################
