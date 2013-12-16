module derelict.purple.mime;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.gstring;
import derelict.glib.glist;
import core.stdc.config;
import core.stdc.string;

extern (C):

alias _PurpleMimeDocument PurpleMimeDocument;
alias _PurpleMimePart PurpleMimePart;

struct _PurpleMimeDocument;


struct _PurpleMimePart;


alias da_purple_mime_document_new = PurpleMimeDocument* function();																																																						/* da_purple_mime_document_new purple_mime_document_new; */
alias da_purple_mime_document_free = void function(PurpleMimeDocument* doc);																																																						/* da_purple_mime_document_free purple_mime_document_free; */
alias da_purple_mime_document_parse = PurpleMimeDocument* function(const(char)* buf);																																																						/* da_purple_mime_document_parse purple_mime_document_parse; */
alias da_purple_mime_document_parsen = PurpleMimeDocument* function(const(char)* buf, gsize len);																																																						/* da_purple_mime_document_parsen purple_mime_document_parsen; */
alias da_purple_mime_document_write = void function(PurpleMimeDocument* doc, GString* str);																																																						/* da_purple_mime_document_write purple_mime_document_write; */
alias da_purple_mime_document_get_fields = GList* function(PurpleMimeDocument* doc);																																																						/* da_purple_mime_document_get_fields purple_mime_document_get_fields; */
alias da_purple_mime_document_get_field = const(char)* function(PurpleMimeDocument* doc, const(char)* field);																																																						/* da_purple_mime_document_get_field purple_mime_document_get_field; */
alias da_purple_mime_document_set_field = void function(PurpleMimeDocument* doc, const(char)* field, const(char)* value);																																																						/* da_purple_mime_document_set_field purple_mime_document_set_field; */
alias da_purple_mime_document_get_parts = GList* function(PurpleMimeDocument* doc);																																																						/* da_purple_mime_document_get_parts purple_mime_document_get_parts; */
alias da_purple_mime_part_new = PurpleMimePart* function(PurpleMimeDocument* doc);																																																						/* da_purple_mime_part_new purple_mime_part_new; */
alias da_purple_mime_part_get_fields = GList* function(PurpleMimePart* part);																																																						/* da_purple_mime_part_get_fields purple_mime_part_get_fields; */
alias da_purple_mime_part_get_field = const(char)* function(PurpleMimePart* part, const(char)* field);																																																						/* da_purple_mime_part_get_field purple_mime_part_get_field; */
alias da_purple_mime_part_get_field_decoded = char* function(PurpleMimePart* part, const(char)* field);																																																						/* da_purple_mime_part_get_field_decoded purple_mime_part_get_field_decoded; */
alias da_purple_mime_part_set_field = void function(PurpleMimePart* part, const(char)* field, const(char)* value);																																																						/* da_purple_mime_part_set_field purple_mime_part_set_field; */
alias da_purple_mime_part_get_data = const(char)* function(PurpleMimePart* part);																																																						/* da_purple_mime_part_get_data purple_mime_part_get_data; */
alias da_purple_mime_part_get_data_decoded = void function(PurpleMimePart* part, guchar** data, gsize* len);																																																						/* da_purple_mime_part_get_data_decoded purple_mime_part_get_data_decoded; */
alias da_purple_mime_part_get_length = gsize function(PurpleMimePart* part);																																																						/* da_purple_mime_part_get_length purple_mime_part_get_length; */
alias da_purple_mime_part_set_data = void function(PurpleMimePart* part, const(char)* data);																																																						/* da_purple_mime_part_set_data purple_mime_part_set_data; */
