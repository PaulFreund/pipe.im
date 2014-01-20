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

module purple.client;

/*
    Todo  
    ====    
    * Create "event" based API
    * Iterate and make list of protocols available
    * Remove debug code
    * Add config for steam account
        * purple_account_set_string(account, "steam_guard_code", steam_guard_token);
        * purple_account_set_string(sa->account, "access_token", access_token);
*/

//###################################################################################################

import purple.callbacks;
import derelict.glib.glib;
import derelict.purple.purple;
import core.sys.posix.signal;
import core.stdc.stdio;
import std.string;
import std.container;
import std.path;
import std.file;
import std.stdio;
import std.conv;
import nitro;

//###################################################################################################

void push_back(T)(Array!T list, T element) {
    list.insertBefore(list[], element);
}

T pop_front(T)(Array!T list) {
    if(!list.empty) {
        auto retVal = list.back;
        list.removeBack();
        return retVal;
    }
    return T.init;
}

//===================================================================================================

final class PurpleClient {

public:
    @property string interfaceID () { return _interfaceID; }
    @property string configDir () { return _configDir; }

public: 
    void process() {
        g_main_context_iteration(g_main_context_default(), false);
    }

private:
    string _configDir = "";
    string _interfaceID = "purple.d";

public:
    this(bool debug_ = false, string configDir = ".pipe.im", string interfaceID = "purple.d") {

        // Load derelict symbols
        version(Derelict_Link_Static) {}
        else {
            DerelictGlib.load();
            DerelictPurple.load();
        }

        // Add directory name if empty
        if(configDir.length == 0) configDir = ".pipe.im";

        // Create path to user data dir if not absolute
        if(configDir.indexOf(dirSeparator) == -1)
            configDir = to!string(purple_home_dir()) ~ dirSeparator ~ configDir;
        
        // Delete old folder
        clearConfigDir(configDir);

        purple_util_set_user_dir(configDir.toStringz);
        purple_debug_set_enabled(debug_);
        _interfaceID = interfaceID;

        // Setup runtime
        version(Win32) {} else { signal(SIGCHLD, SIG_IGN); }

        // Init libpurple
        ConnectUiOpsCallbacks(this);

        purple_core_init(_interfaceID.toStringz);

        ConnectSignalsCallbacks();

        purple_set_blist(purple_blist_new());
    }
    
    ~this() {
        clearConfigDir(to!string(purple_user_dir()));
    }

private:
    void clearConfigDir(string configDir) {
        try {
            if(exists(configDir)) rmdirRecurse(configDir);
        } catch { }
    }
}