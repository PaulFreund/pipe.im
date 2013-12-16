module derelict.purple.certificate;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.glist;
import derelict.glib.gslist;
import derelict.glib.garray;
import core.stdc.time;

extern (C):

alias _Anonymous_0 PurpleCertificateVerificationStatus;
alias _PurpleCertificate PurpleCertificate;
alias _PurpleCertificatePool PurpleCertificatePool;
alias _PurpleCertificateScheme PurpleCertificateScheme;
alias _PurpleCertificateVerifier PurpleCertificateVerifier;
alias _PurpleCertificateVerificationRequest PurpleCertificateVerificationRequest;
alias void function (_Anonymous_0, void*) PurpleCertificateVerifiedCallback;

enum _Anonymous_0
{
	PURPLE_CERTIFICATE_INVALID = 0,
	PURPLE_CERTIFICATE_VALID = 1
}

struct _PurpleCertificate
{
	PurpleCertificateScheme* scheme;
	gpointer data;
}

struct _PurpleCertificatePool
{
	gchar* scheme_name;
	gchar* name;
	gchar* fullname;
	gpointer data;
	gboolean function () init;
	void function () uninit;
	gboolean function (const(gchar)*) cert_in_pool;
	PurpleCertificate* function (const(gchar)*) get_cert;
	gboolean function (const(gchar)*, PurpleCertificate*) put_cert;
	gboolean function (const(gchar)*) delete_cert;
	GList* function () get_idlist;
	void function () _purple_reserved1;
	void function () _purple_reserved2;
	void function () _purple_reserved3;
	void function () _purple_reserved4;
}

struct _PurpleCertificateScheme
{
	gchar* name;
	gchar* fullname;
	PurpleCertificate* function (const(gchar)*) import_certificate;
	gboolean function (const(gchar)*, PurpleCertificate*) export_certificate;
	PurpleCertificate* function (PurpleCertificate*) copy_certificate;
	void function (PurpleCertificate*) destroy_certificate;
	gboolean function (PurpleCertificate*, PurpleCertificate*) signed_by;
	GByteArray* function (PurpleCertificate*) get_fingerprint_sha1;
	gchar* function (PurpleCertificate*) get_unique_id;
	gchar* function (PurpleCertificate*) get_issuer_unique_id;
	gchar* function (PurpleCertificate*) get_subject_name;
	gboolean function (PurpleCertificate*, const(gchar)*) check_subject_name;
	gboolean function (PurpleCertificate*, time_t*, time_t*) get_times;
	GSList* function (const(gchar)*) import_certificates;
	void function () _purple_reserved1;
	void function () _purple_reserved2;
	void function () _purple_reserved3;
}

struct _PurpleCertificateVerifier
{
	gchar* scheme_name;
	gchar* name;
	void function (PurpleCertificateVerificationRequest*) start_verification;
	void function (PurpleCertificateVerificationRequest*) destroy_request;
	void function () _purple_reserved1;
	void function () _purple_reserved2;
	void function () _purple_reserved3;
	void function () _purple_reserved4;
}

struct _PurpleCertificateVerificationRequest
{
	PurpleCertificateVerifier* verifier;
	PurpleCertificateScheme* scheme;
	gchar* subject_name;
	GList* cert_chain;
	gpointer data;
	PurpleCertificateVerifiedCallback cb;
	gpointer cb_data;
}

alias da_purple_certificate_verify = void function(PurpleCertificateVerifier* verifier, const(gchar)* subject_name, GList* cert_chain, PurpleCertificateVerifiedCallback cb, gpointer cb_data);																																																						/* da_purple_certificate_verify purple_certificate_verify; */
alias da_purple_certificate_verify_complete = void function(PurpleCertificateVerificationRequest* vrq, PurpleCertificateVerificationStatus st);																																																						/* da_purple_certificate_verify_complete purple_certificate_verify_complete; */
alias da_purple_certificate_copy = PurpleCertificate* function(PurpleCertificate* crt);																																																						/* da_purple_certificate_copy purple_certificate_copy; */
alias da_purple_certificate_copy_list = GList* function(GList* crt_list);																																																						/* da_purple_certificate_copy_list purple_certificate_copy_list; */
alias da_purple_certificate_destroy = void function(PurpleCertificate* crt);																																																						/* da_purple_certificate_destroy purple_certificate_destroy; */
alias da_purple_certificate_destroy_list = void function(GList* crt_list);																																																						/* da_purple_certificate_destroy_list purple_certificate_destroy_list; */
alias da_purple_certificate_signed_by = gboolean function(PurpleCertificate* crt, PurpleCertificate* issuer);																																																						/* da_purple_certificate_signed_by purple_certificate_signed_by; */
alias da_purple_certificate_check_signature_chain_with_failing = gboolean function(GList* chain, PurpleCertificate** failing);																																																						/* da_purple_certificate_check_signature_chain_with_failing purple_certificate_check_signature_chain_with_failing; */
alias da_purple_certificate_check_signature_chain = gboolean function(GList* chain);																																																						/* da_purple_certificate_check_signature_chain purple_certificate_check_signature_chain; */
alias da_purple_certificate_import = PurpleCertificate* function(PurpleCertificateScheme* scheme, const(gchar)* filename);																																																						/* da_purple_certificate_import purple_certificate_import; */
alias da_purple_certificates_import = GSList* function(PurpleCertificateScheme* scheme, const(gchar)* filename);																																																						/* da_purple_certificates_import purple_certificates_import; */
alias da_purple_certificate_export = gboolean function(const(gchar)* filename, PurpleCertificate* crt);																																																						/* da_purple_certificate_export purple_certificate_export; */
alias da_purple_certificate_get_fingerprint_sha1 = GByteArray* function(PurpleCertificate* crt);																																																						/* da_purple_certificate_get_fingerprint_sha1 purple_certificate_get_fingerprint_sha1; */
alias da_purple_certificate_get_unique_id = gchar* function(PurpleCertificate* crt);																																																						/* da_purple_certificate_get_unique_id purple_certificate_get_unique_id; */
alias da_purple_certificate_get_issuer_unique_id = gchar* function(PurpleCertificate* crt);																																																						/* da_purple_certificate_get_issuer_unique_id purple_certificate_get_issuer_unique_id; */
alias da_purple_certificate_get_subject_name = gchar* function(PurpleCertificate* crt);																																																						/* da_purple_certificate_get_subject_name purple_certificate_get_subject_name; */
alias da_purple_certificate_check_subject_name = gboolean function(PurpleCertificate* crt, const(gchar)* name);																																																						/* da_purple_certificate_check_subject_name purple_certificate_check_subject_name; */
alias da_purple_certificate_get_times = gboolean function(PurpleCertificate* crt, time_t* activation, time_t* expiration);																																																						/* da_purple_certificate_get_times purple_certificate_get_times; */
alias da_purple_certificate_pool_mkpath = gchar* function(PurpleCertificatePool* pool, const(gchar)* id);																																																						/* da_purple_certificate_pool_mkpath purple_certificate_pool_mkpath; */
alias da_purple_certificate_pool_usable = gboolean function(PurpleCertificatePool* pool);																																																						/* da_purple_certificate_pool_usable purple_certificate_pool_usable; */
alias da_purple_certificate_pool_get_scheme = PurpleCertificateScheme* function(PurpleCertificatePool* pool);																																																						/* da_purple_certificate_pool_get_scheme purple_certificate_pool_get_scheme; */
alias da_purple_certificate_pool_contains = gboolean function(PurpleCertificatePool* pool, const(gchar)* id);																																																						/* da_purple_certificate_pool_contains purple_certificate_pool_contains; */
alias da_purple_certificate_pool_retrieve = PurpleCertificate* function(PurpleCertificatePool* pool, const(gchar)* id);																																																						/* da_purple_certificate_pool_retrieve purple_certificate_pool_retrieve; */
alias da_purple_certificate_pool_store = gboolean function(PurpleCertificatePool* pool, const(gchar)* id, PurpleCertificate* crt);																																																						/* da_purple_certificate_pool_store purple_certificate_pool_store; */
alias da_purple_certificate_pool_delete = gboolean function(PurpleCertificatePool* pool, const(gchar)* id);																																																						/* da_purple_certificate_pool_delete purple_certificate_pool_delete; */
alias da_purple_certificate_pool_get_idlist = GList* function(PurpleCertificatePool* pool);																																																						/* da_purple_certificate_pool_get_idlist purple_certificate_pool_get_idlist; */
alias da_purple_certificate_pool_destroy_idlist = void function(GList* idlist);																																																						/* da_purple_certificate_pool_destroy_idlist purple_certificate_pool_destroy_idlist; */
alias da_purple_certificate_init = void function();																																																						/* da_purple_certificate_init purple_certificate_init; */
alias da_purple_certificate_uninit = void function();																																																						/* da_purple_certificate_uninit purple_certificate_uninit; */
alias da_purple_certificate_get_handle = gpointer function();																																																						/* da_purple_certificate_get_handle purple_certificate_get_handle; */
alias da_purple_certificate_find_scheme = PurpleCertificateScheme* function(const(gchar)* name);																																																						/* da_purple_certificate_find_scheme purple_certificate_find_scheme; */
alias da_purple_certificate_get_schemes = GList* function();																																																						/* da_purple_certificate_get_schemes purple_certificate_get_schemes; */
alias da_purple_certificate_register_scheme = gboolean function(PurpleCertificateScheme* scheme);																																																						/* da_purple_certificate_register_scheme purple_certificate_register_scheme; */
alias da_purple_certificate_unregister_scheme = gboolean function(PurpleCertificateScheme* scheme);																																																						/* da_purple_certificate_unregister_scheme purple_certificate_unregister_scheme; */
alias da_purple_certificate_find_verifier = PurpleCertificateVerifier* function(const(gchar)* scheme_name, const(gchar)* ver_name);																																																						/* da_purple_certificate_find_verifier purple_certificate_find_verifier; */
alias da_purple_certificate_get_verifiers = GList* function();																																																						/* da_purple_certificate_get_verifiers purple_certificate_get_verifiers; */
alias da_purple_certificate_register_verifier = gboolean function(PurpleCertificateVerifier* vr);																																																						/* da_purple_certificate_register_verifier purple_certificate_register_verifier; */
alias da_purple_certificate_unregister_verifier = gboolean function(PurpleCertificateVerifier* vr);																																																						/* da_purple_certificate_unregister_verifier purple_certificate_unregister_verifier; */
alias da_purple_certificate_find_pool = PurpleCertificatePool* function(const(gchar)* scheme_name, const(gchar)* pool_name);																																																						/* da_purple_certificate_find_pool purple_certificate_find_pool; */
alias da_purple_certificate_get_pools = GList* function();																																																						/* da_purple_certificate_get_pools purple_certificate_get_pools; */
alias da_purple_certificate_register_pool = gboolean function(PurpleCertificatePool* pool);																																																						/* da_purple_certificate_register_pool purple_certificate_register_pool; */
alias da_purple_certificate_unregister_pool = gboolean function(PurpleCertificatePool* pool);																																																						/* da_purple_certificate_unregister_pool purple_certificate_unregister_pool; */
alias da_purple_certificate_display_x509 = void function(PurpleCertificate* crt);																																																						/* da_purple_certificate_display_x509 purple_certificate_display_x509; */
alias da_purple_certificate_add_ca_search_path = void function(const(char)* path);																																																						/* da_purple_certificate_add_ca_search_path purple_certificate_add_ca_search_path; */
