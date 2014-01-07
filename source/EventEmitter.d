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

module EventEmitter;

//###################################################################################################

import std.stdio;
import std.traits;
import std.typecons;
import std.typetuple;

//###################################################################################################


void publish(Args...)(Args args) {
    void delegate(Object, Args) dg;
    dg.ptr = cast(void*)EventEmitterInstance.ptrData;
    dg.funcptr = cast(void function(Object, Args)) EventEmitterInstance.ptrFunc;
    dg(cast(Object)(dg.ptr), args);
}

alias EventEmitterInstance = EventEmitter._instance;

class EventEmitter {
public:
    static EventEmitter _instance;


    static this() {
        _instance = new EventEmitter();
    }

    void* ptrFunc;
    void* ptrData;

    void setDelegate(void delegate() dg) {
        ptrFunc = dg.funcptr;
        ptrData = dg.ptr;
    }

    
}



/*

Better Concept:
    definition of publish function global 

    mixin in constructor
        iterate over members and get function names with property
        access static eventemitter and add delegates of all definitions ( like stdx.signals )

*/

/*

Concept:
mixin in constructor: 
    call to register object with dispatcher

mixin in class: 
    dispatch function which knows all subscribers and calls them 
    publish function which calls dispatcher

*/


/*
private void _isQueryImpl(T...)(Query!(T) n) {}
enum isSubscriber(T...) = is(typeof(_isQueryImpl(T.init)));

private alias GetSubscriberList(CLIENT) = Filter!(isSubscriber, __traits(getAttributes, CLIENT));

private template _GEN_QUERIES(SYSTEMS...) if(SYSTEMS.length > 0) {
    alias Q = _ExtractQueries!(SYSTEMS[0]);
    static if(SYSTEMS.length > 1) {
        alias NEXT = _GEN_QUERIES!(SYSTEMS[1..$]);
        alias _GEN_QUERIES = TypeTuple!(Q, NEXT);
    }
    else {
        alias _GEN_QUERIES = Q;
    }
}
*/

/*
alias TypeProxy(T) = T;





string listMembers(T)(T client) {
    string list = "";


    //foreach(i, member; members) {
    //    list = list ~ ", " ~ to!string(value);
    //}

    return list;
}

template ValidType(CLIENT, string name) {
    
    enum compiles = __traits(compiles, __traits(getAttributes, MemberFunctionsTuple!(CLIENT, name)));
    pragma(msg, name, " - Compiles: ", compiles);
    static if(compiles) {
        pragma(msg, name, " - Attributes: ", __traits(getAttributes, __traits(getMember, CLIENT, name)));
    }
//    enum truth = isSomeFunction!();
//    pragma(msg, "Truth for ", name, ": ", truth);
    //enum member = __traits(getMember, CLIENT, name);
    //static if(compiles)
    //    enum ValidType = true;
    //else
        enum ValidType = false;
}

import std.traits;
import std.typecons;
import std.typetuple;
mixin template EventEmitter(CLIENT) {
    import std.traits;
    import std.typecons;
    import std.typetuple;
    template GetSubscriberList(CLIENT, CANDIDATES...) if(CANDIDATES.length > 0) {
        
        enum CANDIDATE_NAME = CANDIDATES[0];
        static if(CANDIDATE_NAME != "subscribers" && CANDIDATE_NAME != "publish" && ValidType!(CLIENT, CANDIDATE_NAME)) {
            enum CANDIDATE_SYMBOL = __traits(getMember, CLIENT, CANDIDATE_NAME);
            pragma(msg, "Candidate: ", CANDIDATE_SYMBOL);
            //enum ATTRIBUTES = __traits(getAttributes, CANDIDATE_SYMBOL);
            //pragma(msg, "Attributes: ", ATTRIBUTES);

            alias CANDIDATE = CANDIDATE_SYMBOL;

            //static if(ATTRIBUTES)
            //    alias CANDIDATE = CANDIDATE_SYMBOL;
            //else 
            //    alias CANDIDATE = TypeTuple!();
        }
        else {
            alias CANDIDATE = TypeTuple!();
        }



        // Recursive iterate
        static if(CANDIDATES.length > 1) {
            alias NEXT_CANDIDATE = GetSubscriberList!(CLIENT, CANDIDATES[1..$]);
            alias GetSubscriberList = TypeTuple!(CANDIDATE, NEXT_CANDIDATE);
        }
        else {
            alias GetSubscriberList = CANDIDATE;
        }
    }

    //enum subscribers = listMembers(MemberFunctionsTuple!CLIENT); 
    alias subscribers = GetSubscriberList!(CLIENT, __traits(allMembers, CLIENT));
    pragma(msg, subscribers);

    void publish(string event)(...) {

    }
}

*/

struct subscribe {
    string event;
    this(string eventName) {
        this.event = eventName;
    }
}