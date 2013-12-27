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

import derelict.glib.glib;
import derelict.purple.purple;
import core.sys.posix.signal;
import core.stdc.stdio;
import std.string;
import std.stdio;
import std.conv;

//###################################################################################################

final class PurpleClient {

private:
    const string UI_ID = "purple.d";
    const int PURPLE_GLIB_READ_COND = GIOCondition.G_IO_IN | GIOCondition.G_IO_HUP | GIOCondition.G_IO_ERR;
    const int PURPLE_GLIB_WRITE_COND = GIOCondition.G_IO_OUT | GIOCondition.G_IO_HUP | GIOCondition.G_IO_ERR | GIOCondition.G_IO_NVAL;
    
    struct PurpleGLibIOClosure {
        PurpleInputFunction fkt;
        guint result;
        gpointer data;
    }

public:
    this() {
        version(Derelict_Link_Static) {}
        else {
            DerelictGlib.load();
            DerelictPurple.load();
        }

        // TODO: Make sure config dir works

        init();
    }

private:
    void init () {
        version(Win32) {} else { signal(SIGCHLD, SIG_IGN); }

        purple_debug_set_enabled(false);

        version(Derelict_Link_Static)
            glib_eventloops = PurpleEventLoopUiOps(&g_timeout_add, &g_source_remove, &null_input_add, &g_source_remove, null, &g_timeout_add_seconds, null, null, null);
        else
            glib_eventloops = PurpleEventLoopUiOps(g_timeout_add, g_source_remove, &null_input_add, g_source_remove, null, g_timeout_add_seconds, null, null, null);

        purple_eventloop_set_ui_ops(&glib_eventloops);

        if(!purple_core_init(UI_ID.toStringz))
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

        printf("libpurple initialized.\n");

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

        purple_account_set_enabled(account, UI_ID.toStringz, true);

        PurpleSavedStatus* status = purple_savedstatus_new(null, PurpleStatusPrimitive.PURPLE_STATUS_AVAILABLE);
        purple_savedstatus_activate(status);

        static int handle;
        purple_signal_connect(purple_connections_get_handle(),  cast(const(char)*)"signed-on".toStringz, cast(void*)(&handle), cast(PurpleCallback)(&signed_on), cast(void*)null);
        purple_signal_connect(purple_conversations_get_handle(), cast(const(char)*)"received-im-msg".toStringz, cast(void*)(&handle), cast(PurpleCallback)(&received_im_msg), cast(void*)null);

    }

    static string outputString;

public:
    string getData() {
        outputString = "";
        g_main_context_iteration(g_main_context_default(), false);
        return outputString;
    }

private:
    extern( C ) static void purple_glib_io_destroy(gpointer data) {
        //g_free(data);
    }

    extern( C ) static gboolean purple_glib_io_invoke(GIOChannel *source, GIOCondition condition, gpointer data) {
        PurpleGLibIOClosure *closure = cast(PurpleGLibIOClosure *)data;
        PurpleInputCondition purple_cond = cast(PurpleInputCondition)0;

        if(condition & this.PURPLE_GLIB_READ_COND)
            purple_cond = cast(PurpleInputCondition)(purple_cond | PurpleInputCondition.PURPLE_INPUT_READ);
        if(condition & PURPLE_GLIB_WRITE_COND)
            purple_cond = cast(PurpleInputCondition)(purple_cond | PurpleInputCondition.PURPLE_INPUT_WRITE);

        closure.fkt(closure.data, g_io_channel_unix_get_fd(source), purple_cond);

        return true;
    }

    extern( C ) static guint null_input_add(gint fd, PurpleInputCondition condition, PurpleInputFunction fkt, gpointer data) {

        PurpleGLibIOClosure *closure = new PurpleGLibIOClosure();
        GIOChannel *channel;
        GIOCondition cond = cast(GIOCondition)0;

        closure.fkt = fkt;
        closure.data = data;

        if(condition & PurpleInputCondition.PURPLE_INPUT_READ)
            cond = cast(GIOCondition)(cond | cast(int)(this.PURPLE_GLIB_READ_COND));
        if(condition & PurpleInputCondition.PURPLE_INPUT_WRITE)
            cond = cast(GIOCondition)(cond | cast(int)(this.PURPLE_GLIB_WRITE_COND));

        version(Win32)
            channel = wpurple_g_io_channel_win32_new_socket(fd);
        else
            channel = g_io_channel_unix_new(fd);

        closure.result = g_io_add_watch_full(channel, 0, cond, &purple_glib_io_invoke, cast(void*)closure, &purple_glib_io_destroy);

        g_io_channel_unref(channel);
        return closure.result;
    }

    static PurpleEventLoopUiOps glib_eventloops; 

    extern( C ) static void signed_on(PurpleConnection *gc, gpointer null_) {
        printf("Connected\n");
    }


    extern( C ) static void received_im_msg(PurpleAccount *account, char *sender, char *message, PurpleConversation *conv, PurpleMessageFlags flags) {

        if (conv==null) {
            conv = purple_conversation_new(PurpleConversationType.PURPLE_CONV_TYPE_IM, account, sender);
        }

        this.outputString ~= "(" ~ to!string(purple_utf8_strftime("%H:%M:%S", null)) ~ ") ";
        this.outputString ~= to!string(sender);
        this.outputString ~= "(" ~ to!string(purple_conversation_get_name(conv)) ~ "): ";
        this.outputString ~= to!string(message);
    }
}