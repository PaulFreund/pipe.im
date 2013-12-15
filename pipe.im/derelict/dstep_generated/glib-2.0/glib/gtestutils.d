import core.stdc.config;
import core.stdc.string;
import core.stdc.config;

extern (C):

alias GTestCase GTestCase;
alias GTestSuite GTestSuite;
alias void function () GTestFunc;
alias void function (const(void)*) GTestDataFunc;
alias void function (void*, const(void)*) GTestFixtureFunc;
alias _Anonymous_0 GTestTrapFlags;
alias _Anonymous_1 GTestConfig;
alias _Anonymous_2 GTestLogType;
alias _Anonymous_3 GTestLogMsg;
alias _Anonymous_4 GTestLogBuffer;
alias int function (const(char)*, , const(char)*, void*) GTestLogFatalFunc;

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


int g_strcmp0 (const(char)* str1, const(char)* str2);
void g_test_minimized_result (double minimized_quantity, const(char)* format, ...);
void g_test_maximized_result (double maximized_quantity, const(char)* format, ...);
void g_test_init (int* argc, char*** argv, ...);
int g_test_run ();
void g_test_add_func (const(char)* testpath, GTestFunc test_func);
void g_test_add_data_func (const(char)* testpath, gconstpointer test_data, GTestDataFunc test_func);
void g_test_fail ();
void g_test_message (const(char)* format, ...);
void g_test_bug_base (const(char)* uri_pattern);
void g_test_bug (const(char)* bug_uri_snippet);
void g_test_timer_start ();
double g_test_timer_elapsed ();
double g_test_timer_last ();
void g_test_queue_free (gpointer gfree_pointer);
void g_test_queue_destroy (GDestroyNotify destroy_func, gpointer destroy_data);
gboolean g_test_trap_fork (guint64 usec_timeout, GTestTrapFlags test_trap_flags);
gboolean g_test_trap_has_passed ();
gboolean g_test_trap_reached_timeout ();
gint32 g_test_rand_int ();
gint32 g_test_rand_int_range (gint32 begin, gint32 end);
double g_test_rand_double ();
double g_test_rand_double_range (double range_start, double range_end);
GTestCase* g_test_create_case (const(char)* test_name, gsize data_size, gconstpointer test_data, GTestFixtureFunc data_setup, GTestFixtureFunc data_test, GTestFixtureFunc data_teardown);
GTestSuite* g_test_create_suite (const(char)* suite_name);
GTestSuite* g_test_get_root ();
void g_test_suite_add (GTestSuite* suite, GTestCase* test_case);
void g_test_suite_add_suite (GTestSuite* suite, GTestSuite* nestedsuite);
int g_test_run_suite (GTestSuite* suite);
void g_test_trap_assertions (const(char)* domain, const(char)* file, int line, const(char)* func, guint64 assertion_flags, const(char)* pattern);
void g_assertion_message (const(char)* domain, const(char)* file, int line, const(char)* func, const(char)* message);
void g_assertion_message_expr (const(char)* domain, const(char)* file, int line, const(char)* func, const(char)* expr);
void g_assertion_message_cmpstr (const(char)* domain, const(char)* file, int line, const(char)* func, const(char)* expr, const(char)* arg1, const(char)* cmp, const(char)* arg2);
void g_assertion_message_cmpnum (const(char)* domain, const(char)* file, int line, const(char)* func, const(char)* expr, real arg1, const(char)* cmp, real arg2, char numtype);
void g_assertion_message_error (const(char)* domain, const(char)* file, int line, const(char)* func, const(char)* expr, const(GError)* error, GQuark error_domain, int error_code);
void g_test_add_vtable (const(char)* testpath, gsize data_size, gconstpointer test_data, GTestFixtureFunc data_setup, GTestFixtureFunc data_test, GTestFixtureFunc data_teardown);
const(char)* g_test_log_type_name (GTestLogType log_type);
GTestLogBuffer* g_test_log_buffer_new ();
void g_test_log_buffer_free (GTestLogBuffer* tbuffer);
void g_test_log_buffer_push (GTestLogBuffer* tbuffer, guint n_bytes, const(guint8)* bytes);
GTestLogMsg* g_test_log_buffer_pop (GTestLogBuffer* tbuffer);
void g_test_log_msg_free (GTestLogMsg* tmsg);
void g_test_log_set_fatal_handler (GTestLogFatalFunc log_func, gpointer user_data);