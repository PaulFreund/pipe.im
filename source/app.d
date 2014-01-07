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

/*
import std.conv;
import std.stdio;
import std.typecons;

//struct listen(string eventName) {
//    
//}
alias Proxy(T) = T;

int WriteIt() {
    writeln("Yes I'm here");
    return 0;
}

void WriteIt(string what, int value) {
    writeln("Event: " ~ what ~ "(" ~ to!string(value) ~ ")");
}

int WriteIt(string what, TestType value) {
    writeln("Event: " ~ what ~ "(" ~ value.message ~ ")");
    return 0;
}

void WriteIt(string what, int value, int value2) {
    writeln("Event: " ~ what ~ "(" ~ to!string(value) ~ ", " ~ to!string(value2) ~ ")");
}

void WriteIt(string what, int value, string value2) {
    writeln("Event: " ~ what ~ "(" ~ to!string(value) ~ ", " ~ value2 ~ ")");
}



//template emit(string event, alias value) {
//    pragma(msg, "Event: ", event, "(", value, ")");
//    //alias test = Proxy!(mixin("writeln(\"Event: \" ~ " ~ event ~ " ~ " ~ value ~ ");" ));
//    alias emit = Proxy!( mixin("WriteIt();") );
//    //pragma(msg, test);
//
//}


string parameterList(T)(T value_tuple) {
    string list = "";

    foreach(i, value; value_tuple) {
        list = list ~ ", " ~ to!string(value);
    }

    return list;
}

mixin template emit(string event, value_tuple...) {
//    pragma(msg, value_tuple.toString);
//    pragma(msg, to!string(value_tuple));
    enum parameters = parameterList(__traits(identifier, value_tuple));
    pragma(msg, "Parameters: ", parameters);
//    enum call = "WriteIt(\"" ~ event ~ "\"" ~ parameters ~ ");";
//    pragma(msg, "Call: ", call);
//    void emit() {
//        mixin(call);
//        mixin("WriteIt(\"Manual\", asdf);");
        //mixin("writeln(\"Event: \" ~ " ~ event ~ " ~ " ~ value ~ ");" );
//    }
//    mixin("emit();");
    //int a = WriteIt();
    mixin("int a = WriteIt(\"Manual\", asdf);");
    //mixin("WriteIt(\"Manual\", asdf);");
}

//template GenerateLinkList(TYPES...) {
//    alias GenerateLinkList = TYPES;
//}

//enum list = GenerateLinkList!(listenaaa, Listener.listenfkt);
//pragma(msg, list);

*/

import EventEmitter;

import std.stdio;

class Member01 {
public:
    string _name;

    this() {
        void delegate(string) del = &this.listen;
        void delegate() del2 = cast(void delegate())del;
        EventEmitterInstance.setDelegate(del2);
    }
    //mixin EventEmitter!Member01;

    void emit(string message) {
    //    publish!("event02")(message);
    }


    @subscribe("event01") void listen(string message) {
        writeln("Member01.listen: " ~ message);
    }
}

class Member02 {
public:
    //mixin asdf;
    //mixin EventEmitter!Member02;

    void emit(string message) {
    //    publish!("event01")(message);
        publish(message);
    }

    @subscribe("event02") void listen(string message) {
        writeln("Member02.listen: " ~ message);
    }

}


int initializer(int i) {
    writeln("Initializer");
    return i;
}

int main(string[] argv)
{
    //Member01 m01i01 = new Member01("one");
    Member01 m01 = new Member01();
    Member02 m02 = new Member02();

    //m01.emit("Hi");
    m02.emit("Ho");

/*
	PipeServer server = new PipeServer();
    server.runLoop();
	server.destroy(); 
*/
    return 0;
}

