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
import std.conv;
import std.array;
import std.string;

//###################################################################################################

struct subscribe {
    string event;
}

void publish(Args...)(Args args) {
    static if(is(Args[0] == EventDispatcher)) {
        alias dispatcher = args[0];
        alias event = args[1];
        alias parameters = args[2..$];
    }
    else {
        alias dispatcher = StaticEventDispatcher;
        alias event = args[0];
        alias parameters = args[1..$];
    }

    dispatcher.callSubscribers(event, parameters);
}

//---------------------------------------------------------------------------------------------------

struct Subscriber {
    Object object;
    void* ptrData;
    void* ptrFunc;
}

/*
struct SubscriberList {
private:
    Subscriber[] _subscribers;

public:
    void addSubscriber(Subscriber subscriber) {
        _subscribers ~= subscriber;
    }

    void opCall(Args...)(Args args) {

    }
}
*/

//---------------------------------------------------------------------------------------------------

alias StaticEventDispatcher = EventDispatcher._staticInstance;


class EventDispatcher {
public:
    static EventDispatcher _staticInstance;

    static this() {
        _staticInstance = new EventDispatcher();
    }

private:
    alias SubscriberList = Subscriber[];
    SubscriberList[string] _subscribers;

public:
    int addSubscriber(string event, Object obj, void delegate() dg) {
        _subscribers[event] ~= Subscriber(obj, dg.ptr, dg.funcptr);
        return 0;
    }

    void callSubscribers(Args...)(string event, Args args) {
        SubscriberList listeners;

        // Get wildcard listeners
        int idxSeparator = event.lastIndexOf('.');
        if(idxSeparator != -1) {
            string eventWildcard = event[0..(idxSeparator+1)] ~ '*';
            if((eventWildcard in _subscribers) !is null)
                listeners ~= _subscribers[eventWildcard];
        }

        // Get direct listeners
        if((event in _subscribers) !is null)
            listeners ~= _subscribers[event];

        // Call all listeners
        if(listeners.length > 0) {
            void delegate(Object, Args) dg;
            foreach(listener; listeners) {
                dg.ptr = listener.ptrData;
                dg.funcptr = cast(void function(Object, Args)) listener.ptrFunc;
                dg(cast(Object)(listener.object), args);
            }
        }
    }
}

//---------------------------------------------------------------------------------------------------

// Generate code to add delegates to the EventEmitter
string generateBindingCode(T)(string dispatcher, T subscriberList) {
    string code = "", event = "";
    foreach(i, element; subscriberList) {
        if((i%2) == 0) { event = element; continue; }

        code ~= "int __dispatcher_add_" ~ element ~ "_result = ";
        code ~= dispatcher ~ ".addSubscriber(\"" ~ event ~ "\"";
        code ~= ", this, cast(void delegate())&this." ~ element ~ ");";
        event = "";
    }

    return code;
}

//---------------------------------------------------------------------------------------------------

// Mixin to add add subscribers to 
mixin template EventEmitter(DISPATCHER_PARAM...) {
    // Generate a list of symbols that have a subscriber attribute
    private template GetSubscriberList(PARENT, LIST...) if(LIST.length > 0) {
        private import std.traits : MemberFunctionsTuple;
        private import std.typetuple : TypeTuple;

        // Get current member function and attributes (if any)
        alias CURRENT = MemberFunctionsTuple!(PARENT, LIST[0]);
        static if(CURRENT.length == 1) {
            enum ATTRS = __traits(getAttributes, CURRENT[0]);
            static if(ATTRS.length == 1)
                alias RESULT = TypeTuple!(mixin('"'~ATTRS[0].event~'"'), mixin('"'~__traits(identifier, CURRENT[0])~'"'));
        }

        // Warning for overloaded functions
        static if(CURRENT.length > 1) pragma(msg, "[Error] Subscribing functions must not be overloaded (", CURRENT, ")");

        // Recursive Iteration ( and set result to empty if missing )
        static if(!__traits(compiles, RESULT)) { alias RESULT = TypeTuple!(); }
        static if(LIST.length > 1)
            alias GetSubscriberList = TypeTuple!(RESULT, GetSubscriberList!(PARENT, LIST[1..$]));
        else
            alias GetSubscriberList = RESULT;
    }

    // Determine dispatcher object
    static if(DISPATCHER_PARAM.length == 1)
        enum DISPATCHER = __traits(identifier, DISPATCHER_PARAM[0]);
    else
        enum DISPATCHER = "StaticEventDispatcher";

    // Build and mixin code to add subscriptions, not so nice but leaves no symbols
    private import std.typecons : tuple;
    mixin(generateBindingCode(DISPATCHER, tuple(GetSubscriberList!(typeof(this), __traits(allMembers, typeof(this))))));
}

//###################################################################################################
