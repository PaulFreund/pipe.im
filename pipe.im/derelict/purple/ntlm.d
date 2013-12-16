module derelict.purple.ntlm;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import core.stdc.config;

extern (C):

alias da_purple_ntlm_gen_type1 = gchar* function(const(gchar)* hostname, const(gchar)* domain);																																																						/* da_purple_ntlm_gen_type1 purple_ntlm_gen_type1; */
alias da_purple_ntlm_parse_type2 = guint8* function(const(gchar)* type2, guint32* flags);																																																						/* da_purple_ntlm_parse_type2 purple_ntlm_parse_type2; */
alias da_purple_ntlm_gen_type3 = gchar* function(const(gchar)* username, const(gchar)* passw, const(gchar)* hostname, const(gchar)* domain, const(guint8)* nonce, guint32* flags);																																																						/* da_purple_ntlm_gen_type3 purple_ntlm_gen_type3; */
