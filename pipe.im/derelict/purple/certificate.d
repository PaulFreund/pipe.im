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

void purple_certificate_verify (PurpleCertificateVerifier* verifier, const(gchar)* subject_name, GList* cert_chain, PurpleCertificateVerifiedCallback cb, gpointer cb_data);
void purple_certificate_verify_complete (PurpleCertificateVerificationRequest* vrq, PurpleCertificateVerificationStatus st);
PurpleCertificate* purple_certificate_copy (PurpleCertificate* crt);
GList* purple_certificate_copy_list (GList* crt_list);
void purple_certificate_destroy (PurpleCertificate* crt);
void purple_certificate_destroy_list (GList* crt_list);
gboolean purple_certificate_signed_by (PurpleCertificate* crt, PurpleCertificate* issuer);
gboolean purple_certificate_check_signature_chain_with_failing (GList* chain, PurpleCertificate** failing);
gboolean purple_certificate_check_signature_chain (GList* chain);
PurpleCertificate* purple_certificate_import (PurpleCertificateScheme* scheme, const(gchar)* filename);
GSList* purple_certificates_import (PurpleCertificateScheme* scheme, const(gchar)* filename);
gboolean purple_certificate_export (const(gchar)* filename, PurpleCertificate* crt);
GByteArray* purple_certificate_get_fingerprint_sha1 (PurpleCertificate* crt);
gchar* purple_certificate_get_unique_id (PurpleCertificate* crt);
gchar* purple_certificate_get_issuer_unique_id (PurpleCertificate* crt);
gchar* purple_certificate_get_subject_name (PurpleCertificate* crt);
gboolean purple_certificate_check_subject_name (PurpleCertificate* crt, const(gchar)* name);
gboolean purple_certificate_get_times (PurpleCertificate* crt, time_t* activation, time_t* expiration);
gchar* purple_certificate_pool_mkpath (PurpleCertificatePool* pool, const(gchar)* id);
gboolean purple_certificate_pool_usable (PurpleCertificatePool* pool);
PurpleCertificateScheme* purple_certificate_pool_get_scheme (PurpleCertificatePool* pool);
gboolean purple_certificate_pool_contains (PurpleCertificatePool* pool, const(gchar)* id);
PurpleCertificate* purple_certificate_pool_retrieve (PurpleCertificatePool* pool, const(gchar)* id);
gboolean purple_certificate_pool_store (PurpleCertificatePool* pool, const(gchar)* id, PurpleCertificate* crt);
gboolean purple_certificate_pool_delete (PurpleCertificatePool* pool, const(gchar)* id);
GList* purple_certificate_pool_get_idlist (PurpleCertificatePool* pool);
void purple_certificate_pool_destroy_idlist (GList* idlist);
void purple_certificate_init ();
void purple_certificate_uninit ();
gpointer purple_certificate_get_handle ();
PurpleCertificateScheme* purple_certificate_find_scheme (const(gchar)* name);
GList* purple_certificate_get_schemes ();
gboolean purple_certificate_register_scheme (PurpleCertificateScheme* scheme);
gboolean purple_certificate_unregister_scheme (PurpleCertificateScheme* scheme);
PurpleCertificateVerifier* purple_certificate_find_verifier (const(gchar)* scheme_name, const(gchar)* ver_name);
GList* purple_certificate_get_verifiers ();
gboolean purple_certificate_register_verifier (PurpleCertificateVerifier* vr);
gboolean purple_certificate_unregister_verifier (PurpleCertificateVerifier* vr);
PurpleCertificatePool* purple_certificate_find_pool (const(gchar)* scheme_name, const(gchar)* pool_name);
GList* purple_certificate_get_pools ();
gboolean purple_certificate_register_pool (PurpleCertificatePool* pool);
gboolean purple_certificate_unregister_pool (PurpleCertificatePool* pool);
void purple_certificate_display_x509 (PurpleCertificate* crt);
void purple_certificate_add_ca_search_path (const(char)* path);