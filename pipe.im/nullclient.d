module nullclient;

import derelict.glib.gtypes;
import derelict.glib.giochannel;
import derelict.glib.gmain;
import derelict.glib.gmem;
import derelict.glib.glist;
import derelict.purple.core;
import derelict.purple.util;
import derelict.purple.blist;
import derelict.purple.account;
import derelict.purple.pounce;
import derelict.purple.savedstatuses;
import derelict.purple.conversation;
import derelict.purple.eventloop;
import derelict.purple.connection;
import derelict.purple.plugin;
import derelict.purple._debug;
import derelict.purple.win32;
import core.stdc.stdio;
import core.stdc.time;

string UI_ID = "nullclient";

int PURPLE_GLIB_READ_COND = GIOCondition.G_IO_IN | GIOCondition.G_IO_HUP | GIOCondition.G_IO_ERR;
int PURPLE_GLIB_WRITE_COND = GIOCondition.G_IO_OUT | GIOCondition.G_IO_HUP | GIOCondition.G_IO_ERR | GIOCondition.G_IO_NVAL;

struct PurpleGLibIOClosure
{
    PurpleInputFunction fkt;
    guint result;
    gpointer data;
}

static void purple_glib_io_destroy(gpointer data)
{
    g_free(data);
}

static gboolean purple_glib_io_invoke(GIOChannel *source, GIOCondition condition, gpointer data)
{
    PurpleGLibIOClosure *closure = cast(PurpleGLibIOClosure *)data;
    PurpleInputCondition purple_cond = cast(PurpleInputCondition)0;

    if(condition & PURPLE_GLIB_READ_COND)
        purple_cond = cast(PurpleInputCondition)(purple_cond | PurpleInputCondition.PURPLE_INPUT_READ);
    if(condition & PURPLE_GLIB_WRITE_COND)
        purple_cond = cast(PurpleInputCondition)(purple_cond | PurpleInputCondition.PURPLE_INPUT_WRITE);

    closure.fkt(closure.data, g_io_channel_unix_get_fd(source), purple_cond);

    return true;
}

static guint glib_input_add(gint fd, PurpleInputCondition condition, PurpleInputFunction fkt, gpointer data)
{
    PurpleGLibIOClosure *closure = new PurpleGLibIOClosure();
    GIOChannel *channel;
    GIOCondition cond = cast(GIOCondition)0;

    closure.fkt = fkt;
    closure.data = data;

    if(condition & PurpleInputCondition.PURPLE_INPUT_READ)
        cond = cast(GIOCondition)(cond | cast(int)(PURPLE_GLIB_READ_COND));
    if(condition & PurpleInputCondition.PURPLE_INPUT_WRITE)
        cond = cast(GIOCondition)(cond | cast(int)(PURPLE_GLIB_WRITE_COND));

    version(Win32)
    {
        channel = wpurple_g_io_channel_win32_new_socket(fd);
    }
    else
    {
        channel = g_io_channel_unix_new(fd);
    }

    closure.result = g_io_add_watch_full(channel, 0, cond, purple_glib_io_invoke, closure, purple_glib_io_destroy);

    g_io_channel_unref(channel);
    return closure.result;
}

static PurpleEventLoopUiOps glib_eventloops; 

/*** Conversation uiops ***/
static void null_write_conv(PurpleConversation *conv, const char *who, const char *_alias, const char *message, PurpleMessageFlags flags, time_t mtime)
{
    char *name;
    if(_alias && *_alias)
        name = cast(char*)_alias;
    else if(who && *who)
        name = cast(char*)who;
    else
        name = cast(char*)null;

    printf("(%s) %s %s: %s\n", purple_conversation_get_name(conv), purple_utf8_strftime("(%H:%M:%S)", localtime(&mtime)), name, message);
}

static PurpleConversationUiOps null_conv_uiops;

static void null_ui_init()
{
    /**
    * This should initialize the UI components for all the modules. Here we
    * just initialize the UI for conversations.
    */
    purple_conversations_set_ui_ops(null_conv_uiops);
}

static PurpleCoreUiOps null_core_uiops;

void PluginLoadCB(PurplePlugin * plugin, void * data)
{
    GList * list = purple_plugins_get_all();
    GList * list2 = purple_plugins_get_protocols();
    int j = 0;
}

void PluginProbeCB(void * data)
{
    GList * list = purple_plugins_get_all();
    GList * list2 = purple_plugins_get_protocols();
    int j = 0;
}

void PluginUnloadCB(PurplePlugin * plugin, void * data)
{
    GList * list = purple_plugins_get_all();
    GList * list2 = purple_plugins_get_protocols();
    int j = 0;
}


static void init_libpurple()
{


    /* Set a custom user directory (optional) */
    purple_util_set_user_dir("/dev/null");

    /* We do not want any debugging for now to keep the noise to a minimum. */
    purple_debug_set_enabled(false);

    null_conv_uiops = PurpleConversationUiOps 
    (
        null,                      /* create_conversation  */
        null,                      /* destroy_conversation */
        null,                      /* write_chat           */
        null,                      /* write_im             */
        null_write_conv,           /* write_conv           */
        null,                      /* chat_add_users       */
        null,                      /* chat_rename_user     */
        null,                      /* chat_remove_users    */
        null,                      /* chat_update_user     */
        null,                      /* present              */
        null,                      /* has_focus            */
        null,                      /* custom_smiley_add    */
        null,                      /* custom_smiley_write  */
        null,                      /* custom_smiley_close  */
        null,                      /* send_confirm         */
        null,
        null,
        null,
        null
    );

    /* Set the core-uiops, which is used to
    *         - initialize the ui specific preferences.
    *         - initialize the debug ui.
    *         - initialize the ui components for all the modules.
    *         - uninitialize the ui components for all the modules when the core terminates.
    */
    null_core_uiops = PurpleCoreUiOps(null, null, &null_ui_init, null, null, null, null, null);
    purple_core_set_ui_ops(&null_core_uiops);

    /* Set the uiops for the eventloop. If your client is glib-based, you can safely
    * copy this verbatim. */
    glib_eventloops = PurpleEventLoopUiOps(g_timeout_add, g_source_remove, glib_input_add, g_source_remove, null, g_timeout_add_seconds, null, null, null);
    purple_eventloop_set_ui_ops(&glib_eventloops);

    /* Set path to search for plugins. The core (libpurple) takes care of loading the
    * core-plugins, which includes the protocol-plugins. So it is not essential to add
    * any path here, but it might be desired, especially for ui-specific plugins. */
    purple_plugins_add_search_path("plugins");
    //purple_plugins_add_search_path(CUSTOM_PLUGIN_PATH);

    /* Now that all the essential stuff has been set, let's try to init the core. It's
    * necessary to provide a non-NULL name for the current ui to the core. This name
    * is used by stuff that depends on this ui, for example the ui-specific plugins. */
    if(!purple_core_init(UI_ID))
    {
        /* Initializing the core failed. Terminate. */
        fprintf(stderr, "libpurple initialization failed. Dumping core.\n" "Please report this!\n");
        return -1;
    }

    /* Create and load the buddylist. */
    purple_set_blist(purple_blist_new());
    purple_blist_load();

    /* Load the preferences. */
    purple_prefs_load();

    /* Load the desired plugins. The client should save the list of loaded plugins in
    * the preferences using purple_plugins_save_loaded(PLUGIN_SAVE_PREF) */
    purple_plugins_register_load_notify_cb(&PluginLoadCB, cast(void*)null);
    purple_plugins_register_probe_notify_cb(&PluginProbeCB, null);
    purple_plugins_register_unload_notify_cb(&PluginUnloadCB, null);


    purple_plugins_init();
    purple_plugins_probe(null);
    GList * list = purple_plugins_get_all();
    GList * list2 = purple_plugins_get_protocols();

    /* Load the pounces. */
    purple_pounces_load();
}

static void signed_on(PurpleConnection *gc, gpointer _null)
{
    PurpleAccount *account = purple_connection_get_account(gc);
    printf("Account connected: %s %s\n", account.username, account.protocol_id);
}

static void connect_to_signals_for_demonstration_purposes_only()
{
    static int handle;
    purple_signal_connect(purple_connections_get_handle(), "signed-on", &handle, PURPLE_CALLBACK(signed_on), null);
}

int nullclient()
{
    GList *iter;
    int i, num;
    GList *names = null;
    const char *prpl;
    char name[128];
    char *password;
    GMainLoop *loop = g_main_loop_new(null, false);
    PurpleAccount *account;
    PurpleSavedStatus *status;
    char *res;

    version(Win32)
    {}
    else
    {
        signal(SIGCHLD, SIG_IGN);
    }

    init_libpurple();

    printf("libpurple initialized.\n");

    iter = purple_plugins_get_protocols();
    for(i = 0; iter; iter = iter.next)
    {
        PurplePlugin *plugin = cast(PurplePlugin *)(iter.data);
        PurplePluginInfo *info = plugin.info;
        if(info && info.name)
        {
            printf("\t%d: %s\n", i++, info.name);
            names = g_list_append(names, info.id);
        }
    }
    printf("Select the protocol [0-%d]: ", i - 1);
    res = fgets(name, sizeof(name), stdin);
    if(!res)
    {
        fprintf(stderr, "Failed to gets protocol selection.");
        abort();
    }
    sscanf(name, "%d", &num);
    prpl = cast(const char*)(g_list_nth_data(names, num));

    printf("Username: ");
    res = fgets(name, sizeof(name), stdin);
    if(!res)
    {
        fprintf(stderr, "Failed to read user name.");
        abort();
    }
    name[strlen(name) - 1] = 0;  /* strip the \n at the end */

    /* Create the account */
    account = purple_account_new(name, prpl);

    /* Get the password for the account */
    password = "";//getpass("Password: ");
    purple_account_set_password(account, password);

    /* It's necessary to enable the account first. */
    purple_account_set_enabled(account, UI_ID, TRUE);

    /* Now, to connect the account(s), create a status and activate it. */
    status = purple_savedstatus_new(NULL, PURPLE_STATUS_AVAILABLE);
    purple_savedstatus_activate(status);

    connect_to_signals_for_demonstration_purposes_only();

    g_main_loop_run(loop);

    return 0;
}