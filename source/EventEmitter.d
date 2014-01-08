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

//###################################################################################################

struct subscribe {
    string event;
    this(string event_) {
        this.event = event_;
    }
}

struct Subscriber {
    Object _object;
    void* _ptrData;
    void* _ptrFunc;

    this(Object object, void* ptrData, void* ptrFunc) {
        _object = object;
        _ptrData = ptrData;
        _ptrFunc = ptrFunc;
    }

    void opCall(Args...)(Args args) {
        void delegate(Object, Args) dg;
        dg.ptr = _ptrData;
        dg.funcptr = cast(void function(Object, Args)) _ptrFunc;
        dg(cast(Object)(_object), args);
    }
}

void publish(Args...)(string event, Args args) {
    PublicEventDispatcher._subscribers[event](args);
}

alias PublicEventDispatcher = EventDispatcher._publicInstance;

class EventDispatcher {
    public {
        static EventDispatcher _publicInstance;

        static this() {
            _publicInstance = new EventDispatcher();
        }

        Subscriber[string] _subscribers;

        int addSubscriber(string event, Object obj, void delegate() dg) {
            this._subscribers[event] = Subscriber(obj, dg.ptr, dg.funcptr);
            return 0;
        }
    }
}

// Generate code to add delegates to the EventEmitter
string generateBindingCode(T)(T subscriberList) {
    string code = "";

    bool isEvent = true;
    string currentEvent = "";
    string currentSubscriber = "";
    foreach(element; subscriberList) {
        if(isEvent) {
            currentEvent = element;
        }
        else {
            currentSubscriber = element;
            code = code ~ "int add_" ~ currentSubscriber ~ "_result = ";
            code = code ~ "PublicEventDispatcher.addSubscriber(\"" ~ currentEvent ~ "\"";
            code = code ~ ", this, cast(void delegate())&this." ~ currentSubscriber ~ ");";
            currentEvent = "";
            currentSubscriber = "";
        }

        isEvent = !isEvent;
    }

    return code;
}

// Mixin to add add subscribers to 
mixin template EventEmitter() {
    private import std.traits : MemberFunctionsTuple;
    private import std.typecons : tuple;
    private import std.typetuple : TypeTuple;

    // Generate a list of symbols that have a subscriber attribute
    template GetSubscriberList(PARENT, CANDIDATES...) if(CANDIDATES.length > 0) {
        alias CANDIDATE_SYMBOLS = MemberFunctionsTuple!(PARENT, CANDIDATES[0]);
        static if(CANDIDATE_SYMBOLS.length == 1) {
            enum CANDIDATE_ATTRIBUTES = __traits(getAttributes, CANDIDATE_SYMBOLS[0]);
            static if(CANDIDATE_ATTRIBUTES.length == 1) {
                alias CANDIDATE = TypeTuple!(
                    mixin("\"" ~ CANDIDATE_ATTRIBUTES[0].event ~ "\""), 
                    mixin("\"" ~ __traits(identifier, CANDIDATE_SYMBOLS[0]) ~ "\"")
                );
            }
            else {
                alias CANDIDATE = TypeTuple!();
            }
        }
        else {
            alias CANDIDATE = TypeTuple!();
            static if(CANDIDATE_SYMBOLS.length > 1) {
                pragma(msg, "[Error] Member function names must not be overloaded (", CANDIDATE_SYMBOLS, ")");
            }
        }

        static if(CANDIDATES.length > 1) {
            alias NEXT_CANDIDATE = GetSubscriberList!(PARENT, CANDIDATES[1..$]);
            alias GetSubscriberList = TypeTuple!(CANDIDATE, NEXT_CANDIDATE);
        }
        else {
            alias GetSubscriberList = CANDIDATE;
        }
    }

    // Not so nice but leaves no symbols
    mixin(generateBindingCode(tuple(GetSubscriberList!(typeof(this), __traits(allMembers, typeof(this))))));
}

