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

import nitro;
import std.stdio;

//###################################################################################################

//---------------------------------------------------------------------------------------------------

int outputTest(string str) { writeln(str); return 0; }

//---------------------------------------------------------------------------------------------------

// Generate code to add delegates to the EventEmitter

string generateQueryIterators(alias ECM, bool isBool, PARAMS...)() {
    string code = "";

	string ecmIdentifier = __traits(identifier, ECM); 
	static if(PARAMS[0] == typeof(ECM).stringof) {
        enum ecmDefined = true;
		alias TYPES = PARAMS[1..$];
    }
    else {
        enum ecmDefined = false;
		alias TYPES = PARAMS;
    }

	string typeList = "";
	foreach(TYPE; TYPES) {
		if(typeList.length != 0) { typeList ~= ","; }
		typeList ~= TYPE;
	}

	code ~= "foreach(e;" ~ ecmIdentifier ~ ".query!(" ~ typeList ~ ")()) {\n";
	foreach(TYPE; TYPES) {
		code ~= "auto param" ~ TYPE ~ " = " ~ ecmIdentifier ~ ".getComponent!" ~ TYPE ~ "(e);";
	}

	if(isBool) {
		code ~= "deleteEntity = ";
	}

	code ~= "query(";
	static if(ecmDefined) { code ~= ecmIdentifier ~ ","; }
	
	foreach(i, TYPE; TYPES) {
		code ~= "*param" ~ TYPE;
		code ~= (i < (TYPES.length-1)) ? "," : ");";
	}

	if(isBool) {
		code ~= "if(deleteEntity){" ~ ecmIdentifier ~ ".removeComponent!(" ~ typeList ~ ")(e); }";
	}

	code ~= "}";

	/*
	auto es = ecm.query!TestComponent();
	foreach(e;es) {
		auto c = ecm.getComponent!TestComponent(e);
		writeln(__FUNCTION__ ~ " : " ~ c.msg);
		ecm.removeComponent!TestComponent(e);
	}
	*/

	//code ~= "int do(int a){ writeln(\"RUN RUNNING\"); return a; } int __done = do(1);";
    /*foreach(i, element; subscriberList) {
        if((i%2) == 0) { event = element; continue; }

        code ~= "int __dispatcher_add_" ~ element ~ "_result = ";
        code ~= dispatcher ~ ".addSubscriber(\"" ~ event ~ "\"";
        code ~= ", this, cast(void delegate())&this." ~ element ~ ");";
        event = "";
    }*/

    return code;
}

//---------------------------------------------------------------------------------------------------

// Mixin to add add subscribers to 
mixin template AutoQuery(alias ECM) {

    // Generate mixin text for all query functions
    private template IterateQueryFkts(PARENT, LIST...) if(LIST.length > 0) {
        private import std.traits : ParameterTypeTuple, ReturnType;
        private import std.typetuple : TypeTuple, staticMap;
		private import std.typecons : tuple;

		alias ELEMENT = LIST[0];
		alias RETURN_TYPE = ReturnType!(ELEMENT);

		static if(is(RETURN_TYPE == void) || is(RETURN_TYPE == bool)) {
			alias ELEMENT_PARAMS = ParameterTypeTuple!(ELEMENT);
			enum ToString(T) = T.stringof;
			//enum RESULT = generateQueryIterators!(ECM)(is(RETURN_TYPE==bool), staticMap!(ToString, ELEMENT_PARAMS));
			enum RESULT = generateQueryIterators!(ECM, is(RETURN_TYPE==bool), staticMap!(ToString, ELEMENT_PARAMS));
		}

        static if(!__traits(compiles, RESULT)) { enum RESULT = ""; }
		static if(LIST.length > 1)
			enum IterateQueryFkts = RESULT ~ " " ~ IterateQueryFkts!(PARENT, LIST[1..$]);
		else
			enum IterateQueryFkts = RESULT;
    }

	private enum res = IterateQueryFkts!(typeof(this), __traits(getOverloads, typeof(this), "query"));
	enum fkt = "bool AutoQueryFkt() { bool deleteEntity = false; " ~ res ~ "return true; }";
    pragma(msg, "RESULT:\n", fkt);
    mixin(fkt);
	bool autoQueryFktExecuted = AutoQueryFkt();
}

//###################################################################################################

@Component struct TestComponent {
	string msg;
}

@System final class ServiceGenerator(ECM) {

	bool added = false;
	void run(ECM)(ECM ecm) {
		if(added) return;

		ecm.addComponent(ecm.createEntity(), TestComponent("Message"));
		added = true;
	}

}

@System final class ServiceCmd(ECM) {

	void run(ECM)(ECM ecm) {
		mixin AutoQuery!(ecm);
	}

	//void query(ref TestComponent comp) {
	//}

	//void query(ECM ecm, TestComponent comp, ref TestComponent comp2) {
	//}

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