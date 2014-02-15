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

import pipe;
import nitro;
import nitro.textcom;
import core.thread;

//###################################################################################################

int main(string[] argv)
{


	auto pipeECS = makeECS!("nitro.textcom.server", "pipe.services.cmd", "pipe.services.purple", "pipe.services.config")();

	string listenerRaw = "tcp";
	string listenerWebsocket = "websocket";
    pipeECS.ecm.pushEntity(TextComSocketConfig(TextComSocketType.TCP, listenerRaw, "0.0.0.0", 8042, false));
    pipeECS.ecm.pushEntity(TextComSocketConfig(TextComSocketType.WebSocket, listenerWebsocket, "0.0.0.0", 8080, true, "public"));

    pipeECS.ecm.pushEntity(TextComSocketChange(listenerRaw, TextComSocketAction.StartListen));
    pipeECS.ecm.pushEntity(TextComSocketChange(listenerWebsocket, TextComSocketAction.StartListen));

	bool bRun = true;
	while(bRun) {
		Thread.sleep(dur!("msecs")( 1 ));
		pipeECS.run();
	}

    return 0;
}

