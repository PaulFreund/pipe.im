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

module pipe.services.cmd;

//###################################################################################################

import pipe.services;
import std.stdio;
import std.conv;

//###################################################################################################

@Component struct DebugMessage { string message; }
@Component struct WarningMessage { string message; }

//---------------------------------------------------------------------------------------------------

@System final class ServiceCmd(ECM) {

	mixin AutoQuery;

	bool query(ref DebugMessage c) {
		writeln(__FUNCTION__ ~ " : " ~ c.message);
		return false;
	}

	bool query(ECM ecm, ref DebugMessage c) {
		writeln(__FUNCTION__ ~ " : " ~ c.message);
		return false;
	}

	bool query(ref DebugMessage c, ref WarningMessage d) {
		writeln(__FUNCTION__ ~ " - Debug: " ~ c.message ~ ", Warning: " ~ d.message);
		return true;
	}

    bool query(ECM ecm, Entity e, ref DebugMessage c) {
		writeln(__FUNCTION__ ~ " : " ~ c.message ~ "(" ~ to!string(e) ~ ")");
		return true;
	}

    this(ECM ecm) {
        writeln("CMD INIT");
    }

	//~this() {
	//}

    //@subscribe("server.update") void update() {   
	//}
}