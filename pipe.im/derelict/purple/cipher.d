module derelict.purple.cipher;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.glist;

extern (C):

alias _PurpleCipher PurpleCipher;
alias _PurpleCipherOps PurpleCipherOps;
alias _PurpleCipherContext PurpleCipherContext;
alias _PurpleCipherBatchMode PurpleCipherBatchMode;
alias _PurpleCipherCaps PurpleCipherCaps;

enum _PurpleCipherBatchMode
{
	PURPLE_CIPHER_BATCH_MODE_ECB = 0,
	PURPLE_CIPHER_BATCH_MODE_CBC = 1
}

enum _PurpleCipherCaps
{
	PURPLE_CIPHER_CAPS_SET_OPT = 2,
	PURPLE_CIPHER_CAPS_GET_OPT = 4,
	PURPLE_CIPHER_CAPS_INIT = 8,
	PURPLE_CIPHER_CAPS_RESET = 16,
	PURPLE_CIPHER_CAPS_UNINIT = 32,
	PURPLE_CIPHER_CAPS_SET_IV = 64,
	PURPLE_CIPHER_CAPS_APPEND = 128,
	PURPLE_CIPHER_CAPS_DIGEST = 256,
	PURPLE_CIPHER_CAPS_ENCRYPT = 512,
	PURPLE_CIPHER_CAPS_DECRYPT = 1024,
	PURPLE_CIPHER_CAPS_SET_SALT = 2048,
	PURPLE_CIPHER_CAPS_GET_SALT_SIZE = 4096,
	PURPLE_CIPHER_CAPS_SET_KEY = 8192,
	PURPLE_CIPHER_CAPS_GET_KEY_SIZE = 16384,
	PURPLE_CIPHER_CAPS_SET_BATCH_MODE = 32768,
	PURPLE_CIPHER_CAPS_GET_BATCH_MODE = 65536,
	PURPLE_CIPHER_CAPS_GET_BLOCK_SIZE = 131072,
	PURPLE_CIPHER_CAPS_SET_KEY_WITH_LEN = 262144,
	PURPLE_CIPHER_CAPS_UNKNOWN = 524288
}

struct _PurpleCipherOps
{
	void function (PurpleCipherContext*, const(gchar)*, void*) set_option;
	void* function (PurpleCipherContext*, const(gchar)*) get_option;
	void function (PurpleCipherContext*, void*) init;
	void function (PurpleCipherContext*, void*) reset;
	void function (PurpleCipherContext*) uninit;
	void function (PurpleCipherContext*, guchar*, size_t) set_iv;
	void function (PurpleCipherContext*, const(guchar)*, size_t) append;
	gboolean function (PurpleCipherContext*, size_t, guchar*, size_t*) digest;
	int function (PurpleCipherContext*, const(guchar)*, size_t, guchar*, size_t*) encrypt;
	int function (PurpleCipherContext*, const(guchar)*, size_t, guchar*, size_t*) decrypt;
	void function (PurpleCipherContext*, guchar*) set_salt;
	size_t function (PurpleCipherContext*) get_salt_size;
	void function (PurpleCipherContext*, const(guchar)*) set_key;
	size_t function (PurpleCipherContext*) get_key_size;
	void function (PurpleCipherContext*, PurpleCipherBatchMode) set_batch_mode;
	PurpleCipherBatchMode function (PurpleCipherContext*) get_batch_mode;
	size_t function (PurpleCipherContext*) get_block_size;
	void function (PurpleCipherContext*, const(guchar)*, size_t) set_key_with_len;
}

struct _PurpleCipherContext;


struct _PurpleCipher;


alias da_purple_cipher_get_name = const(gchar)* function(PurpleCipher* cipher);																																																						/* da_purple_cipher_get_name purple_cipher_get_name; */
alias da_purple_cipher_get_capabilities = guint function(PurpleCipher* cipher);																																																						/* da_purple_cipher_get_capabilities purple_cipher_get_capabilities; */
alias da_purple_cipher_digest_region = gboolean function(const(gchar)* name, const(guchar)* data, size_t data_len, size_t in_len, guchar* digest, size_t* out_len);																																																						/* da_purple_cipher_digest_region purple_cipher_digest_region; */
alias da_purple_ciphers_find_cipher = PurpleCipher* function(const(gchar)* name);																																																						/* da_purple_ciphers_find_cipher purple_ciphers_find_cipher; */
alias da_purple_ciphers_register_cipher = PurpleCipher* function(const(gchar)* name, PurpleCipherOps* ops);																																																						/* da_purple_ciphers_register_cipher purple_ciphers_register_cipher; */
alias da_purple_ciphers_unregister_cipher = gboolean function(PurpleCipher* cipher);																																																						/* da_purple_ciphers_unregister_cipher purple_ciphers_unregister_cipher; */
alias da_purple_ciphers_get_ciphers = GList* function();																																																						/* da_purple_ciphers_get_ciphers purple_ciphers_get_ciphers; */
alias da_purple_ciphers_get_handle = gpointer function();																																																						/* da_purple_ciphers_get_handle purple_ciphers_get_handle; */
alias da_purple_ciphers_init = void function();																																																						/* da_purple_ciphers_init purple_ciphers_init; */
alias da_purple_ciphers_uninit = void function();																																																						/* da_purple_ciphers_uninit purple_ciphers_uninit; */
alias da_purple_cipher_context_set_option = void function(PurpleCipherContext* context, const(gchar)* name, gpointer value);																																																						/* da_purple_cipher_context_set_option purple_cipher_context_set_option; */
alias da_purple_cipher_context_get_option = gpointer function(PurpleCipherContext* context, const(gchar)* name);																																																						/* da_purple_cipher_context_get_option purple_cipher_context_get_option; */
alias da_purple_cipher_context_new = PurpleCipherContext* function(PurpleCipher* cipher, void* extra);																																																						/* da_purple_cipher_context_new purple_cipher_context_new; */
alias da_purple_cipher_context_new_by_name = PurpleCipherContext* function(const(gchar)* name, void* extra);																																																						/* da_purple_cipher_context_new_by_name purple_cipher_context_new_by_name; */
alias da_purple_cipher_context_reset = void function(PurpleCipherContext* context, gpointer extra);																																																						/* da_purple_cipher_context_reset purple_cipher_context_reset; */
alias da_purple_cipher_context_destroy = void function(PurpleCipherContext* context);																																																						/* da_purple_cipher_context_destroy purple_cipher_context_destroy; */
alias da_purple_cipher_context_set_iv = void function(PurpleCipherContext* context, guchar* iv, size_t len);																																																						/* da_purple_cipher_context_set_iv purple_cipher_context_set_iv; */
alias da_purple_cipher_context_append = void function(PurpleCipherContext* context, const(guchar)* data, size_t len);																																																						/* da_purple_cipher_context_append purple_cipher_context_append; */
alias da_purple_cipher_context_digest = gboolean function(PurpleCipherContext* context, size_t in_len, guchar* digest, size_t* out_len);																																																						/* da_purple_cipher_context_digest purple_cipher_context_digest; */
alias da_purple_cipher_context_digest_to_str = gboolean function(PurpleCipherContext* context, size_t in_len, gchar* digest_s, size_t* out_len);																																																						/* da_purple_cipher_context_digest_to_str purple_cipher_context_digest_to_str; */
alias da_purple_cipher_context_encrypt = gint function(PurpleCipherContext* context, const(guchar)* data, size_t len, guchar* output, size_t* outlen);																																																						/* da_purple_cipher_context_encrypt purple_cipher_context_encrypt; */
alias da_purple_cipher_context_decrypt = gint function(PurpleCipherContext* context, const(guchar)* data, size_t len, guchar* output, size_t* outlen);																																																						/* da_purple_cipher_context_decrypt purple_cipher_context_decrypt; */
alias da_purple_cipher_context_set_salt = void function(PurpleCipherContext* context, guchar* salt);																																																						/* da_purple_cipher_context_set_salt purple_cipher_context_set_salt; */
alias da_purple_cipher_context_get_salt_size = size_t function(PurpleCipherContext* context);																																																						/* da_purple_cipher_context_get_salt_size purple_cipher_context_get_salt_size; */
alias da_purple_cipher_context_set_key = void function(PurpleCipherContext* context, const(guchar)* key);																																																						/* da_purple_cipher_context_set_key purple_cipher_context_set_key; */
alias da_purple_cipher_context_get_key_size = size_t function(PurpleCipherContext* context);																																																						/* da_purple_cipher_context_get_key_size purple_cipher_context_get_key_size; */
alias da_purple_cipher_context_set_batch_mode = void function(PurpleCipherContext* context, PurpleCipherBatchMode mode);																																																						/* da_purple_cipher_context_set_batch_mode purple_cipher_context_set_batch_mode; */
alias da_purple_cipher_context_get_batch_mode = PurpleCipherBatchMode function(PurpleCipherContext* context);																																																						/* da_purple_cipher_context_get_batch_mode purple_cipher_context_get_batch_mode; */
alias da_purple_cipher_context_get_block_size = size_t function(PurpleCipherContext* context);																																																						/* da_purple_cipher_context_get_block_size purple_cipher_context_get_block_size; */
alias da_purple_cipher_context_set_key_with_len = void function(PurpleCipherContext* context, const(guchar)* key, size_t len);																																																						/* da_purple_cipher_context_set_key_with_len purple_cipher_context_set_key_with_len; */
alias da_purple_cipher_context_set_data = void function(PurpleCipherContext* context, gpointer data);																																																						/* da_purple_cipher_context_set_data purple_cipher_context_set_data; */
alias da_purple_cipher_context_get_data = gpointer function(PurpleCipherContext* context);																																																						/* da_purple_cipher_context_get_data purple_cipher_context_get_data; */
alias da_purple_cipher_http_digest_calculate_session_key = gchar* function(const(gchar)* algorithm, const(gchar)* username, const(gchar)* realm, const(gchar)* password, const(gchar)* nonce, const(gchar)* client_nonce);																																																						/* da_purple_cipher_http_digest_calculate_session_key purple_cipher_http_digest_calculate_session_key; */
alias da_purple_cipher_http_digest_calculate_response = gchar* function(const(gchar)* algorithm, const(gchar)* method, const(gchar)* digest_uri, const(gchar)* qop, const(gchar)* entity, const(gchar)* nonce, const(gchar)* nonce_count, const(gchar)* client_nonce, const(gchar)* session_key);																																																						/* da_purple_cipher_http_digest_calculate_response purple_cipher_http_digest_calculate_response; */
