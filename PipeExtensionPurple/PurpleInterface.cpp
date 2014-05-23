//======================================================================================================================

#include "CommonHeader.h"
#include "PurpleInterface.h"
#include "PipeExtensionPurple.h"

#include <glib.h>
#include <purple.h>

#ifndef _WIN32
#include <unistd.h>
#else
#pragma warning(push)
#pragma warning(disable:4005)
#include "win32/win32dep.h"
#pragma warning(pop)
#endif

using namespace std;

//======================================================================================================================



//======================================================================================================================

PurpleInterface::PurpleInterface(const tstring& path) {
	try {
		typedef struct _PurpleGLibIOClosure { PurpleInputFunction function; guint result; gpointer data; } PurpleGLibIOClosure;

		auto glib_input_add = [](gint fd, PurpleInputCondition condition, PurpleInputFunction function, gpointer data) -> guint {
			PurpleGLibIOClosure *closure = g_new0(PurpleGLibIOClosure, 1);
			GIOChannel *channel;
			GIOCondition cond = static_cast<GIOCondition>(0);

			closure->function = function;
			closure->data = data;

			if(condition & PURPLE_INPUT_READ) { cond = static_cast<GIOCondition>(cond | (G_IO_IN | G_IO_HUP | G_IO_ERR)); }
			if(condition & PURPLE_INPUT_WRITE) { cond = static_cast<GIOCondition>(cond | (G_IO_OUT | G_IO_HUP | G_IO_ERR | G_IO_NVAL)); }

#if defined _WIN32 && !defined WINPIDGIN_USE_GLIB_IO_CHANNEL
			channel = wpurple_g_io_channel_win32_new_socket(fd);
#else
			channel = g_io_channel_unix_new(fd);
#endif

			auto purple_glib_io_invoke = [](GIOChannel *source, GIOCondition condition, gpointer data) -> gboolean {
				PurpleGLibIOClosure* closure = reinterpret_cast<PurpleGLibIOClosure*>(data);
				PurpleInputCondition purple_cond = static_cast<PurpleInputCondition>(0);

				if(condition & (G_IO_IN | G_IO_HUP | G_IO_ERR)) { purple_cond = static_cast<PurpleInputCondition>(purple_cond | PURPLE_INPUT_READ); }
				if(condition & (G_IO_OUT | G_IO_HUP | G_IO_ERR | G_IO_NVAL)) { purple_cond = static_cast<PurpleInputCondition>(purple_cond | PURPLE_INPUT_WRITE); }

				closure->function(closure->data, g_io_channel_unix_get_fd(source), purple_cond);

				return TRUE;
			};

			auto purple_glib_io_destroy = [](gpointer data) {
				g_free(data);
			};

			closure->result = g_io_add_watch_full(channel, G_PRIORITY_DEFAULT, cond, purple_glib_io_invoke, closure, purple_glib_io_destroy);

			g_io_channel_unref(channel);
			return closure->result;
		};

		PurpleEventLoopUiOps glib_eventloops = {
			g_timeout_add,
			g_source_remove,
			glib_input_add,
			g_source_remove,
			NULL,
			g_timeout_add_seconds,
			NULL,
			NULL,
			NULL
		};

		purple_util_set_user_dir(path.c_str());

		purple_debug_set_enabled(FALSE);

		purple_eventloop_set_ui_ops(&glib_eventloops);

		if(!purple_core_init(_T("pipe.im"))) {
			throw tstring(_T("libpurple initialization failed. Dumping core.\n" "Please report this!"));
		}

		purple_set_blist(purple_blist_new());
	}
	
	catch(tstring error) { if(PipeExtensionPurple::ErrorCallback != nullptr) { PipeExtensionPurple::ErrorCallback(error.c_str()); } }
	catch(...) { if(PipeExtensionPurple::ErrorCallback != nullptr) { PipeExtensionPurple::ErrorCallback(_T("PipeExtensionSetPath: Unknown error")); } }
}

//----------------------------------------------------------------------------------------------------------------------

PurpleInterface::~PurpleInterface() {
}

//----------------------------------------------------------------------------------------------------------------------

PipeArrayPtr PurpleInterface::getProtocols() {
	PipeArrayPtr protocolsList = newArray();

	GList * protocols = purple_plugins_get_protocols();
	for(; protocols; protocols = protocols->next) {
		PurplePlugin* plugin = reinterpret_cast<PurplePlugin*>(protocols->data);
		PurplePluginInfo *info = plugin->info;

		PipeObject def;
		tstring defTypeName = timplode(texplode(info->name, _T(' ')), _T('_'));
		transform(begin(defTypeName), end(defTypeName), begin(defTypeName), ::tolower);
		def[_T("type")] = tstring(defTypeName);
		def[_T("description")] = tstring(info->description);
		def[_T("settings_schema")] = PipeObject();
		auto& settingsSchema = def[_T("settings_schema")].object_items();
		schemaAddValue(settingsSchema, _T("testvalue"), SchemaValueTypeString, _T("test setting"), false);
		protocolsList->push_back(def);
	}

	return protocolsList;
}


//======================================================================================================================
