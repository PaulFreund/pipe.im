//======================================================================================================================

#include "PipeExtensionPurple.h"

#include "ServiceIRC.h"

#include <iostream>
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

PurpleEventLoopUiOps _glib_eventloops;

typedef struct _PurpleGLibIOClosure {
	PurpleInputFunction function;
	guint result;
	gpointer data;
} PurpleGLibIOClosure;

#define PURPLE_GLIB_READ_COND  (G_IO_IN | G_IO_HUP | G_IO_ERR)
#define PURPLE_GLIB_WRITE_COND (G_IO_OUT | G_IO_HUP | G_IO_ERR | G_IO_NVAL)

static void purple_glib_io_destroy(gpointer data) {
	g_free(data);
}

static gboolean purple_glib_io_invoke(GIOChannel *source, GIOCondition condition, gpointer data) {
	PurpleGLibIOClosure* closure = reinterpret_cast<PurpleGLibIOClosure*>(data);
	PurpleInputCondition purple_cond = static_cast<PurpleInputCondition>(0);

	if(condition & PURPLE_GLIB_READ_COND)
		purple_cond = static_cast<PurpleInputCondition>(purple_cond | PURPLE_INPUT_READ);
	if(condition & PURPLE_GLIB_WRITE_COND)
		purple_cond = static_cast<PurpleInputCondition>(purple_cond | PURPLE_INPUT_WRITE);

	closure->function(closure->data, g_io_channel_unix_get_fd(source),
					  purple_cond);

	return TRUE;
}

guint glib_input_add(gint fd, PurpleInputCondition condition, PurpleInputFunction function,
					 gpointer data) {
	PurpleGLibIOClosure *closure = g_new0(PurpleGLibIOClosure, 1);
	GIOChannel *channel;
	GIOCondition cond = static_cast<GIOCondition>(0);

	closure->function = function;
	closure->data = data;

	if(condition & PURPLE_INPUT_READ)
		cond = static_cast<GIOCondition>(cond | PURPLE_GLIB_READ_COND);
	if(condition & PURPLE_INPUT_WRITE)
		cond = static_cast<GIOCondition>(cond | PURPLE_GLIB_WRITE_COND);

#if defined _WIN32 && !defined WINPIDGIN_USE_GLIB_IO_CHANNEL
	channel = wpurple_g_io_channel_win32_new_socket(fd);
#else
	channel = g_io_channel_unix_new(fd);
#endif
	closure->result = g_io_add_watch_full(channel, G_PRIORITY_DEFAULT, cond,
										  purple_glib_io_invoke, closure, purple_glib_io_destroy);

	g_io_channel_unref(channel);
	return closure->result;
}

//======================================================================================================================

PipeExtensionPurple::PipeExtensionPurple() {
	_glib_eventloops = {
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
}

PipeExtensionPurple::~PipeExtensionPurple() {
	for(auto it = begin(_services); it != end(_services); it++) {
		delete it->second;
	}
}

vector<tstring> PipeExtensionPurple::providers() {
	tstring userDir = tstring(purple_user_dir());
	tstring replaceName = _T(".pipe.im");
	auto idx = userDir.find(_T(".purple"));
	if(idx != string::npos) {
		userDir.replace(idx, replaceName.length(), replaceName);
	}
	
	purple_util_set_user_dir(userDir.c_str());

	purple_debug_set_enabled(FALSE);

	purple_eventloop_set_ui_ops(&_glib_eventloops);

	if(!purple_core_init(_T("pipe.im"))) {
		cout << _T("libpurple initialization failed. Dumping core.\n" "Please report this!") << endl;
		return {};
	}

	//purple_plugins_init();

	vector<tstring> serviceNames;
	GList * protocols = purple_plugins_get_protocols();
	for(; protocols; protocols = protocols->next) {
		PurplePlugin* plugin = reinterpret_cast<PurplePlugin*>(protocols->data);
		PurplePluginInfo *info = plugin->info;
		serviceNames.push_back(tstring(info->name));
	}

	return serviceNames;
}



map<tstring, tstring> PipeExtensionPurple::providerSettings(tstring provider) {
	if(provider == _T("irc")) {
		return ServiceIRC::settingTypes();
	}

	return {};
}

IPipeExtensionService* PipeExtensionPurple::create(tstring provider, tstring id, std::map<tstring, tstring> settings) {
	if(provider == _T("irc")) {
		return (_services[id] = new ServiceIRC(id, settings));
	}

	return nullptr;
}

void PipeExtensionPurple::destroy(IPipeExtensionService* service) {
	for(auto it = begin(_services); it != end(_services); it++) {
		if(it->second == service) {
			delete it->second;
			_services.erase(it);
			return;
		}
	}
}

