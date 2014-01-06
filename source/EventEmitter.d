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

import std.typecons;
import std.typetuple;

//###################################################################################################

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
string listMembers(T)(T members) {
    string list = "";

    foreach(i, member; members) {
        list = list ~ ", " ~ to!string(value);
    }

    return list;
}
*/

mixin template EventEmitter(CLIENT) {

    alias TypeProxy(T) = T;

    template ValidType(string name) {
        static if(__traits(compiles, (TypeProxy!(mixin(name))).sizeof))
            enum ValidType = true;
        else
            enum ValidType = false;
    }

    template GetSubscriberList(CLIENT, CANDIDATES...) if(CANDIDATES.length > 0) {

        static if(ValidType!(CANDIDATES[0])) {
            alias MEMBER_TYPE = TypeProxy!(mixin(CANDIDATES[0]));
            static if(IsStruct!MEMBER_TYPE)
                alias CANDIDATE = MEMBER_TYPE;
            else 
                alias CANDIDATE = TypeTuple!();
        }
        else {
            alias CANDIDATE = TypeTuple!();
        }

        enum CANDIDATE_SYMBOL = __traits(getMember, CLIENT, CANDIDATES[0]); //TypeProxy!(__traits(getMember(CANDIDATES[0]));
        pragma(msg, "Candidate: ", CANDIDATE_SYMBOL);
        enum ATTRIBUTES = __traits(getAttributes, CANDIDATE_SYMBOL);
        pragma(msg, "Attributes: ", ATTRIBUTES);

        static if(ATTRIBUTES)
            alias CANDIDATE = CANDIDATE_SYMBOL;
        else 
            alias CANDIDATE = TypeTuple!();

        // Recursive iterate
        static if(CANDIDATES.length > 1) {
            alias NEXT_CANDIDATE = GetSubscriberList!(CANDIDATES[1..$]);
            alias GetSubscriberList = TypeTuple!(CANDIDATE, NEXT_CANDIDATE);
        }
        else {
            alias GetSubscriberList = CANDIDATE;
        }
    }

    alias subscribers = GetSubscriberList!(CLIENT, __traits(allMembers, CLIENT));
    pragma(msg, subscribers);

    void publish(string event)(...) {

    }
}

struct subscribe {
    string event;
    this(string eventName) {
        this.event = eventName;
    }
}