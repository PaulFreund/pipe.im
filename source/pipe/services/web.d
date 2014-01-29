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

module pipe.services.web;

//###################################################################################################

import pipe.services;
import vibe.vibe;

//###################################################################################################

@System final class ServiceWeb(ECM) {
	//VibeWrapper _vibe = null;

    mixin AutoQuery;

    this(ECM ecm) {
		import std.stdio;
        writeln("WEB INIT");

		//this._vibe = new VibeWrapper();	   
		//assert(this._vibe !is null);	 
    }

	~this() {
		//this._vibe.destroy();
	}
}

//===================================================================================================

final class VibeWrapper
{

public:
    this() {
        lowerPrivileges();
        auto settings = new HTTPServerSettings;
        settings.port = 8080;
        listenHTTP(settings, &handleRequest);
    }

    static string outputString;

    void update() {
        outputString = "";
        processEvents();

        //if(outputString.length != 0)
        //    writeln("< " ~ outputString ~ " >");
    }

private:
    void handleRequest(HTTPServerRequest req, HTTPServerResponse res) {
        outputString = "Website called";
        res.writeBody("Hello, World!", "text/plain");
    }
}