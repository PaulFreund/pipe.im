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
    * Create API
*/

//###################################################################################################

import purple.callbacks;
import derelict.glib.glib;
import derelict.purple.purple;
import core.sys.posix.signal;
import core.stdc.stdio;
import std.string;
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
        int _signalHandler = 0;
        PurpleEventLoopUiOps _eventloopUiOps; 
    }

public:
    this(bool debug_ = false, string configDir = "", string interfaceID = "purple.d") {
        _interfaceID = interfaceID;
 
        version(Derelict_Link_Static) {}
        else {
            DerelictGlib.load();
            DerelictPurple.load();
        }

        purple_debug_set_enabled(debug_);
        if(configDir.length != 0) purple_util_set_user_dir(configDir.toStringz);


        //if(_instance is null)
        //    _instance = this;
        //else
        //    throw new Exception("PurpleClient can only be instanciated once");

        version(Win32) {} else { signal(SIGCHLD, SIG_IGN); }



        version(Derelict_Link_Static)
            _eventloopUiOps = PurpleEventLoopUiOps(&g_timeout_add, &g_source_remove, &cb_input_add, &g_source_remove, null, &g_timeout_add_seconds, null, null, null);
        else
            _eventloopUiOps = PurpleEventLoopUiOps(g_timeout_add, g_source_remove, &purple_cb_input_add, g_source_remove, null, g_timeout_add_seconds, null, null, null);

        purple_eventloop_set_ui_ops(&_eventloopUiOps);

        if(!purple_core_init(_interfaceID.toStringz))
        {
            fprintf(core.stdc.stdio.stderr, "libpurple initialization failed. Dumping core.\n" "Please report this!\n");
            return;
        }

        purple_set_blist(purple_blist_new());
        purple_blist_load();

        purple_prefs_load();

        purple_plugins_init();
        purple_plugins_probe(null);
        GList * list = purple_plugins_get_all();
        GList * list2 = purple_plugins_get_protocols();

        purple_pounces_load();

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

        purple_signal_connect(purple_connections_get_handle(),  "signed-on".toStringz, cast(void*)(&_signalHandler), cast(PurpleCallback)&purple_cb_signed_on, cast(void*)this);
        purple_signal_connect(purple_conversations_get_handle(),"received-im-msg".toStringz, cast(void*)(&_signalHandler), cast(PurpleCallback)&purple_cb_received_im_msg, cast(void*)this);
    }


public:
    string getData() {
        outputString = "";
        g_main_context_iteration(g_main_context_default(), false);
        return outputString;
    }


}