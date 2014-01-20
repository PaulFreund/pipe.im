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

//###################################################################################################

@Component struct TestComponent {
	string msg;
}

//---------------------------------------------------------------------------------------------------

@System final class ServiceGenerator(ECM) {

	bool added = false;
	void run(ECM)(ECM ecm) {
		if(added) return;

		ecm.addComponent(ecm.createEntity(), TestComponent("Message"));
		added = true;
	}

}

@System final class ServiceCmd(ECM) {

	mixin AutoQuery;

	bool query(ref TestComponent c) {
		writeln(__FUNCTION__ ~ " : " ~ c.msg);
		return false;
	}

	bool query(ECM ecm, ref TestComponent c) {
		writeln(__FUNCTION__ ~ " : " ~ c.msg);
		return true;
	}

    //this(PipeServer server) {
    //    super(server);
    //mixin DispatchMapper!_server;
    //}

	//~this() {
	//}

    //@subscribe("server.update") void update() {   
	//}
}