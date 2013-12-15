module derelict.purple.cipher;

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


const(gchar)* purple_cipher_get_name (PurpleCipher* cipher);
guint purple_cipher_get_capabilities (PurpleCipher* cipher);
gboolean purple_cipher_digest_region (const(gchar)* name, const(guchar)* data, size_t data_len, size_t in_len, guchar* digest, size_t* out_len);
PurpleCipher* purple_ciphers_find_cipher (const(gchar)* name);
PurpleCipher* purple_ciphers_register_cipher (const(gchar)* name, PurpleCipherOps* ops);
gboolean purple_ciphers_unregister_cipher (PurpleCipher* cipher);
GList* purple_ciphers_get_ciphers ();
gpointer purple_ciphers_get_handle ();
void purple_ciphers_init ();
void purple_ciphers_uninit ();
void purple_cipher_context_set_option (PurpleCipherContext* context, const(gchar)* name, gpointer value);
gpointer purple_cipher_context_get_option (PurpleCipherContext* context, const(gchar)* name);
PurpleCipherContext* purple_cipher_context_new (PurpleCipher* cipher, void* extra);
PurpleCipherContext* purple_cipher_context_new_by_name (const(gchar)* name, void* extra);
void purple_cipher_context_reset (PurpleCipherContext* context, gpointer extra);
void purple_cipher_context_destroy (PurpleCipherContext* context);
void purple_cipher_context_set_iv (PurpleCipherContext* context, guchar* iv, size_t len);
void purple_cipher_context_append (PurpleCipherContext* context, const(guchar)* data, size_t len);
gboolean purple_cipher_context_digest (PurpleCipherContext* context, size_t in_len, guchar* digest, size_t* out_len);
gboolean purple_cipher_context_digest_to_str (PurpleCipherContext* context, size_t in_len, gchar* digest_s, size_t* out_len);
gint purple_cipher_context_encrypt (PurpleCipherContext* context, const(guchar)* data, size_t len, guchar* output, size_t* outlen);
gint purple_cipher_context_decrypt (PurpleCipherContext* context, const(guchar)* data, size_t len, guchar* output, size_t* outlen);
void purple_cipher_context_set_salt (PurpleCipherContext* context, guchar* salt);
size_t purple_cipher_context_get_salt_size (PurpleCipherContext* context);
void purple_cipher_context_set_key (PurpleCipherContext* context, const(guchar)* key);
size_t purple_cipher_context_get_key_size (PurpleCipherContext* context);
void purple_cipher_context_set_batch_mode (PurpleCipherContext* context, PurpleCipherBatchMode mode);
PurpleCipherBatchMode purple_cipher_context_get_batch_mode (PurpleCipherContext* context);
size_t purple_cipher_context_get_block_size (PurpleCipherContext* context);
void purple_cipher_context_set_key_with_len (PurpleCipherContext* context, const(guchar)* key, size_t len);
void purple_cipher_context_set_data (PurpleCipherContext* context, gpointer data);
gpointer purple_cipher_context_get_data (PurpleCipherContext* context);
gchar* purple_cipher_http_digest_calculate_session_key (const(gchar)* algorithm, const(gchar)* username, const(gchar)* realm, const(gchar)* password, const(gchar)* nonce, const(gchar)* client_nonce);
gchar* purple_cipher_http_digest_calculate_response (const(gchar)* algorithm, const(gchar)* method, const(gchar)* digest_uri, const(gchar)* qop, const(gchar)* entity, const(gchar)* nonce, const(gchar)* nonce_count, const(gchar)* client_nonce, const(gchar)* session_key);