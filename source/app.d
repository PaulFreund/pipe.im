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

//import pipe;

//###################################################################################################

import std.stdio;
import EventEmitter;

//###################################################################################################


class Member01 {
public:
    this() { mixin EventEmitter; }

    @subscribe("something") void listen(string message) {
        writeln(__PRETTY_FUNCTION__  ~ ": " ~ message);
    }
}

class Member02 {
public:
    void emit(string message) {
        publish("something", message);
    }
}


int main(string[] argv)
{
    Member01 m01 = new Member01();
    Member02 m02 = new Member02();

    m02.emit("Works");

/*
	PipeServer server = new PipeServer();
    server.runLoop();
	server.destroy(); 
*/
        return 0;
}

/*
Static demo



*/

/*
Non-Static demo

class Member01 {
public:
this(EventDispatcher _dispatcher) { mixin EventEmitter!(_dispatcher); }
//this() { mixin EventEmitter; }

@subscribe("something") void listen(string message) {
writeln(__PRETTY_FUNCTION__  ~ ": " ~ message);
}
}

class Member02 {
public:
void emit(EventDispatcher _dispatcher, string message) {
publish(_dispatcher, "something", message);
}
}


int main(string[] argv)
{
EventDispatcher _dispatcher = new EventDispatcher();

Member01 m01 = new Member01(_dispatcher);
Member02 m02 = new Member02();

m02.emit(_dispatcher, "Works");

return 0;
}


*/