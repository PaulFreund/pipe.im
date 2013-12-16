module derelict.glib.ghmac;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.gchecksum;
import core.stdc.config;

extern (C):

alias _GHmac GHmac;

struct _GHmac;


alias da_g_hmac_new = GHmac* function(GChecksumType digest_type, const(guchar)* key, gsize key_len);																																																						/* da_g_hmac_new g_hmac_new; */
alias da_g_hmac_copy = GHmac* function(const(GHmac)* hmac);																																																						/* da_g_hmac_copy g_hmac_copy; */
alias da_g_hmac_ref = GHmac* function(GHmac* hmac);																																																						/* da_g_hmac_ref g_hmac_ref; */
alias da_g_hmac_unref = void function(GHmac* hmac);																																																						/* da_g_hmac_unref g_hmac_unref; */
alias da_g_hmac_update = void function(GHmac* hmac, const(guchar)* data, gssize length);																																																						/* da_g_hmac_update g_hmac_update; */
alias da_g_hmac_get_string = const(gchar)* function(GHmac* hmac);																																																						/* da_g_hmac_get_string g_hmac_get_string; */
alias da_g_hmac_get_digest = void function(GHmac* hmac, guint8* buffer, gsize* digest_len);																																																						/* da_g_hmac_get_digest g_hmac_get_digest; */
alias da_g_compute_hmac_for_data = gchar* function(GChecksumType digest_type, const(guchar)* key, gsize key_len, const(guchar)* data, gsize length);																																																						/* da_g_compute_hmac_for_data g_compute_hmac_for_data; */
alias da_g_compute_hmac_for_string = gchar* function(GChecksumType digest_type, const(guchar)* key, gsize key_len, const(gchar)* str, gssize length);																																																						/* da_g_compute_hmac_for_string g_compute_hmac_for_string; */
