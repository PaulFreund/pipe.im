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
import std.path;
import std.file;
import std.stdio;
import std.conv;

//###################################################################################################

//struct Account

//===================================================================================================

final class PurpleClient {

    public {
        string outputString;
        string _interfaceID = "purple.d";
    }

    private {
        string _configDir = "";
    }

    public {
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

            GList* lstNames = null;
            GList* iterPlugins = purple_plugins_get_protocols();
            int idxPlugin = 0;
            for(idxPlugin = 0; iterPlugins; iterPlugins = iterPlugins.next)
            {
                PurplePlugin *plugin = cast(PurplePlugin *)(iterPlugins.data);
                PurplePluginInfo *info = plugin.info;
                if(info && info.name)
                {
                    printf("\t%d: %s\n".toStringz, idxPlugin++, info.name);
                    lstNames = g_list_append(lstNames, info.id);
                }
            }

            bool debugAccount = true;
            string protocol = "prpl-jabber"; 
            string username = "pipetest@lvl3.org";
            string password = "333333"; 

            if(!debugAccount)
            {
                printf("Select the protocol [0-%d]: ".toStringz, idxPlugin - 1);
                int idxProtocol = to!int(strip(readln()));
                char* ptrProtocol = cast(char*)g_list_nth_data(lstNames, idxProtocol);
                protocol = to!string(ptrProtocol);

                printf("Username: ".toStringz);
                username = strip(readln());

                // Read password
                printf("Password: ".toStringz);
                password = strip(readln());
            }        

            PurpleAccount* account = purple_account_new(username.toStringz, protocol.toStringz);
            purple_account_set_password(account, password.toStringz);
            
            purple_account_set_enabled(account, _interfaceID.toStringz, true);

            PurpleSavedStatus* status = purple_savedstatus_new(null, PurpleStatusPrimitive.PURPLE_STATUS_AVAILABLE);
            purple_savedstatus_activate(status);
        }
    
        ~this() {
            clearConfigDir(to!string(purple_user_dir()));
        }
    }

    public {
        string getData() {
            outputString = "";
            g_main_context_iteration(g_main_context_default(), false);
            return outputString;
        }
    }

    private {
        void clearConfigDir(string configDir) {
            try {
                if(exists(configDir)) rmdirRecurse(configDir);
            } catch { }
        }
    }
}