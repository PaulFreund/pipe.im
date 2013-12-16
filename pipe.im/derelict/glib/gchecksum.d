module derelict.glib.gchecksum;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import core.stdc.config;

extern (C):

alias _Anonymous_0 GChecksumType;
alias _GChecksum GChecksum;

enum _Anonymous_0
{
	G_CHECKSUM_MD5 = 0,
	G_CHECKSUM_SHA1 = 1,
	G_CHECKSUM_SHA256 = 2
}

struct _GChecksum;


gssize g_checksum_type_get_length (GChecksumType checksum_type);
GChecksum* g_checksum_new (GChecksumType checksum_type);
void g_checksum_reset (GChecksum* checksum);
GChecksum* g_checksum_copy (const(GChecksum)* checksum);
void g_checksum_free (GChecksum* checksum);
void g_checksum_update (GChecksum* checksum, const(guchar)* data, gssize length);
const(gchar)* g_checksum_get_string (GChecksum* checksum);
void g_checksum_get_digest (GChecksum* checksum, guint8* buffer, gsize* digest_len);
gchar* g_compute_checksum_for_data (GChecksumType checksum_type, const(guchar)* data, gsize length);
gchar* g_compute_checksum_for_string (GChecksumType checksum_type, const(gchar)* str, gssize length);