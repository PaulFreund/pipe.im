module derelict.glib.gtestutils;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.gmessages;
import derelict.glib.gslist;
import derelict.glib.gstring;
import derelict.glib.gquark;
import derelict.glib.gerror;
import core.stdc.config;
import core.stdc.string;

extern (C):

//alias GTestCase GTestCase;
//alias GTestSuite GTestSuite;
alias void function () GTestFunc;
alias void function (const(void)*) GTestDataFunc;
alias void function (void*, const(void)*) GTestFixtureFunc;
alias _Anonymous_0 GTestTrapFlags;
alias _Anonymous_1 GTestConfig;
alias _Anonymous_2 GTestLogType;
alias _Anonymous_3 GTestLogMsg;
alias _Anonymous_4 GTestLogBuffer;
alias int function (const(char)*, GLogLevelFlags, const(char)*, void*) GTestLogFatalFunc;

extern __gshared const GTestConfig* g_test_config_vars;

enum _Anonymous_0
{
	G_TEST_TRAP_SILENCE_STDOUT = 128,
	G_TEST_TRAP_SILENCE_STDERR = 256,
	G_TEST_TRAP_INHERIT_STDIN = 512
}

enum _Anonymous_2
{
	G_TEST_LOG_NONE = 0,
	G_TEST_LOG_ERROR = 1,
	G_TEST_LOG_START_BINARY = 2,
	G_TEST_LOG_LIST_CASE = 3,
	G_TEST_LOG_SKIP_CASE = 4,
	G_TEST_LOG_START_CASE = 5,
	G_TEST_LOG_STOP_CASE = 6,
	G_TEST_LOG_MIN_RESULT = 7,
	G_TEST_LOG_MAX_RESULT = 8,
	G_TEST_LOG_MESSAGE = 9
}

struct _Anonymous_1
{
	gboolean test_initialized;
	gboolean test_quick;
	gboolean test_perf;
	gboolean test_verbose;
	gboolean test_quiet;
	gboolean test_undefined;
}

struct _Anonymous_3
{
	GTestLogType log_type;
	guint n_strings;
	gchar** strings;
	guint n_nums;
	real* nums;
}

struct _Anonymous_4
{
	GString* data;
	GSList* msgs;
}

struct GTestCase;


struct GTestSuite;


alias da_g_strcmp0 = int function(const(char)* str1, const(char)* str2);																																																						/* da_g_strcmp0 g_strcmp0; */
alias da_g_test_minimized_result = void function(double minimized_quantity, const(char)* format, ...);																																																						/* da_g_test_minimized_result g_test_minimized_result; */
alias da_g_test_maximized_result = void function(double maximized_quantity, const(char)* format, ...);																																																						/* da_g_test_maximized_result g_test_maximized_result; */
alias da_g_test_init = void function(int* argc, char*** argv, ...);																																																						/* da_g_test_init g_test_init; */
alias da_g_test_run = int function();																																																						/* da_g_test_run g_test_run; */
alias da_g_test_add_func = void function(const(char)* testpath, GTestFunc test_func);																																																						/* da_g_test_add_func g_test_add_func; */
alias da_g_test_add_data_func = void function(const(char)* testpath, gconstpointer test_data, GTestDataFunc test_func);																																																						/* da_g_test_add_data_func g_test_add_data_func; */
alias da_g_test_fail = void function();																																																						/* da_g_test_fail g_test_fail; */
alias da_g_test_message = void function(const(char)* format, ...);																																																						/* da_g_test_message g_test_message; */
alias da_g_test_bug_base = void function(const(char)* uri_pattern);																																																						/* da_g_test_bug_base g_test_bug_base; */
alias da_g_test_bug = void function(const(char)* bug_uri_snippet);																																																						/* da_g_test_bug g_test_bug; */
alias da_g_test_timer_start = void function();																																																						/* da_g_test_timer_start g_test_timer_start; */
alias da_g_test_timer_elapsed = double function();																																																						/* da_g_test_timer_elapsed g_test_timer_elapsed; */
alias da_g_test_timer_last = double function();																																																						/* da_g_test_timer_last g_test_timer_last; */
alias da_g_test_queue_free = void function(gpointer gfree_pointer);																																																						/* da_g_test_queue_free g_test_queue_free; */
alias da_g_test_queue_destroy = void function(GDestroyNotify destroy_func, gpointer destroy_data);																																																						/* da_g_test_queue_destroy g_test_queue_destroy; */
alias da_g_test_trap_fork = gboolean function(guint64 usec_timeout, GTestTrapFlags test_trap_flags);																																																						/* da_g_test_trap_fork g_test_trap_fork; */
alias da_g_test_trap_has_passed = gboolean function();																																																						/* da_g_test_trap_has_passed g_test_trap_has_passed; */
alias da_g_test_trap_reached_timeout = gboolean function();																																																						/* da_g_test_trap_reached_timeout g_test_trap_reached_timeout; */
alias da_g_test_rand_int = gint32 function();																																																						/* da_g_test_rand_int g_test_rand_int; */
alias da_g_test_rand_int_range = gint32 function(gint32 begin, gint32 end);																																																						/* da_g_test_rand_int_range g_test_rand_int_range; */
alias da_g_test_rand_double = double function();																																																						/* da_g_test_rand_double g_test_rand_double; */
alias da_g_test_rand_double_range = double function(double range_start, double range_end);																																																						/* da_g_test_rand_double_range g_test_rand_double_range; */
alias da_g_test_create_case = GTestCase* function(const(char)* test_name, gsize data_size, gconstpointer test_data, GTestFixtureFunc data_setup, GTestFixtureFunc data_test, GTestFixtureFunc data_teardown);																																																						/* da_g_test_create_case g_test_create_case; */
alias da_g_test_create_suite = GTestSuite* function(const(char)* suite_name);																																																						/* da_g_test_create_suite g_test_create_suite; */
alias da_g_test_get_root = GTestSuite* function();																																																						/* da_g_test_get_root g_test_get_root; */
alias da_g_test_suite_add = void function(GTestSuite* suite, GTestCase* test_case);																																																						/* da_g_test_suite_add g_test_suite_add; */
alias da_g_test_suite_add_suite = void function(GTestSuite* suite, GTestSuite* nestedsuite);																																																						/* da_g_test_suite_add_suite g_test_suite_add_suite; */
alias da_g_test_run_suite = int function(GTestSuite* suite);																																																						/* da_g_test_run_suite g_test_run_suite; */
alias da_g_test_trap_assertions = void function(const(char)* domain, const(char)* file, int line, const(char)* func, guint64 assertion_flags, const(char)* pattern);																																																						/* da_g_test_trap_assertions g_test_trap_assertions; */
alias da_g_assertion_message = void function(const(char)* domain, const(char)* file, int line, const(char)* func, const(char)* message);																																																						/* da_g_assertion_message g_assertion_message; */
alias da_g_assertion_message_expr = void function(const(char)* domain, const(char)* file, int line, const(char)* func, const(char)* expr);																																																						/* da_g_assertion_message_expr g_assertion_message_expr; */
alias da_g_assertion_message_cmpstr = void function(const(char)* domain, const(char)* file, int line, const(char)* func, const(char)* expr, const(char)* arg1, const(char)* cmp, const(char)* arg2);																																																						/* da_g_assertion_message_cmpstr g_assertion_message_cmpstr; */
alias da_g_assertion_message_cmpnum = void function(const(char)* domain, const(char)* file, int line, const(char)* func, const(char)* expr, real arg1, const(char)* cmp, real arg2, char numtype);																																																						/* da_g_assertion_message_cmpnum g_assertion_message_cmpnum; */
alias da_g_assertion_message_error = void function(const(char)* domain, const(char)* file, int line, const(char)* func, const(char)* expr, const(GError)* error, GQuark error_domain, int error_code);																																																						/* da_g_assertion_message_error g_assertion_message_error; */
alias da_g_test_add_vtable = void function(const(char)* testpath, gsize data_size, gconstpointer test_data, GTestFixtureFunc data_setup, GTestFixtureFunc data_test, GTestFixtureFunc data_teardown);																																																						/* da_g_test_add_vtable g_test_add_vtable; */
alias da_g_test_log_type_name = const(char)* function(GTestLogType log_type);																																																						/* da_g_test_log_type_name g_test_log_type_name; */
alias da_g_test_log_buffer_new = GTestLogBuffer* function();																																																						/* da_g_test_log_buffer_new g_test_log_buffer_new; */
alias da_g_test_log_buffer_free = void function(GTestLogBuffer* tbuffer);																																																						/* da_g_test_log_buffer_free g_test_log_buffer_free; */
alias da_g_test_log_buffer_push = void function(GTestLogBuffer* tbuffer, guint n_bytes, const(guint8)* bytes);																																																						/* da_g_test_log_buffer_push g_test_log_buffer_push; */
alias da_g_test_log_buffer_pop = GTestLogMsg* function(GTestLogBuffer* tbuffer);																																																						/* da_g_test_log_buffer_pop g_test_log_buffer_pop; */
alias da_g_test_log_msg_free = void function(GTestLogMsg* tmsg);																																																						/* da_g_test_log_msg_free g_test_log_msg_free; */
alias da_g_test_log_set_fatal_handler = void function(GTestLogFatalFunc log_func, gpointer user_data);																																																						/* da_g_test_log_set_fatal_handler g_test_log_set_fatal_handler; */
