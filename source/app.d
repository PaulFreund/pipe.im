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

/* TODO  ============================================================================

* Create pipe.im pakage
    * Test on Linux
    * Publish dub package

===================================================================================*/ 

import derelict.glib.glib;
import derelict.purple.purple;
import std.stdio;
import nullclient;
import core.thread;
import vibe.vibe;

void handleRequest(HTTPServerRequest req, HTTPServerResponse res)
{
	res.writeBody("Hello, World!", "text/plain");
}

int main(string[] argv)
{
    version(Derelict_Link_Static) 
    {}
    else
    {
        DerelictGlib.load();
        DerelictPurple.load();
    }

    lowerPrivileges();
	auto settings = new HTTPServerSettings;
	settings.port = 8080;
	listenHTTP(settings, &handleRequest);

    writeln("pipe.im initialize");
    
    int ret = nullclient.nullclient();

    while(true)
    {
        //Thread.sleep( dur!("msecs")( 10 ) );  // sleep for 50 milliseconds
        g_main_context_iteration(g_main_context_default(), 0);
        processEvents();
    }

    return 0;
}

