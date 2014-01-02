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

module purple.events;

//###################################################################################################

//import std.traits;
import std.typetuple;

//###################################################################################################

alias TypeProxy(T) = T;

template IsStruct(T) {
    static if(is(T == struct)) 
        enum IsStruct = true;
    else
        enum IsStruct = false;
}

template ValidType(string name) {
    static if(__traits(compiles, (TypeProxy!(mixin(name))).sizeof))
        enum ValidType = true;
    else
        enum ValidType = false;
}

template GetStructTypes(MEMBERS...) if(MEMBERS.length > 0) {
    // Convert from name string to type and Filter valid members
    static if(ValidType!(MEMBERS[0])) {
        alias MEMBER_TYPE = TypeProxy!(mixin(MEMBERS[0]));
        static if(IsStruct!MEMBER_TYPE)
            alias MEMBER = MEMBER_TYPE;
        else 
            alias MEMBER = TypeTuple!();
    }
    else {
        alias MEMBER = TypeTuple!();
    }

    // Recursive iterate
    static if(MEMBERS.length > 1) {
        alias NEXT_MEMBER = GetStructTypes!(MEMBERS[1..$]);
        alias GetStructTypes = TypeTuple!(MEMBER, NEXT_MEMBER);
    }
    else {
        alias GetStructTypes = MEMBER;
    }
}

alias EVENT_TYPES = GetStructTypes!(__traits(allMembers, mixin(__MODULE__)));
pragma(msg, EVENT_TYPES);

//###################################################################################################

struct PurpleEvent {
    string element;
}

struct ConnectionUpdate {
    enum ConnectionUpdateType {
        None,
        SigningOn,
        SignedOn,
        SigningOff,
        SignedOff,
        ConnectionError,
        AutoJoin
    }
}
