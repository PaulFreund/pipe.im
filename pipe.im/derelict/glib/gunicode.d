module derelict.glib.gunicode;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.gerror;
import core.stdc.config;

extern (C):

alias uint gunichar;
alias ushort gunichar2;
alias _Anonymous_0 GUnicodeType;
alias _Anonymous_1 GUnicodeBreakType;
alias _Anonymous_2 GUnicodeScript;
alias _Anonymous_3 GNormalizeMode;

extern __gshared const gchar* g_utf8_skip;

enum _Anonymous_0
{
	G_UNICODE_CONTROL = 0,
	G_UNICODE_FORMAT = 1,
	G_UNICODE_UNASSIGNED = 2,
	G_UNICODE_PRIVATE_USE = 3,
	G_UNICODE_SURROGATE = 4,
	G_UNICODE_LOWERCASE_LETTER = 5,
	G_UNICODE_MODIFIER_LETTER = 6,
	G_UNICODE_OTHER_LETTER = 7,
	G_UNICODE_TITLECASE_LETTER = 8,
	G_UNICODE_UPPERCASE_LETTER = 9,
	G_UNICODE_SPACING_MARK = 10,
	G_UNICODE_ENCLOSING_MARK = 11,
	G_UNICODE_NON_SPACING_MARK = 12,
	G_UNICODE_DECIMAL_NUMBER = 13,
	G_UNICODE_LETTER_NUMBER = 14,
	G_UNICODE_OTHER_NUMBER = 15,
	G_UNICODE_CONNECT_PUNCTUATION = 16,
	G_UNICODE_DASH_PUNCTUATION = 17,
	G_UNICODE_CLOSE_PUNCTUATION = 18,
	G_UNICODE_FINAL_PUNCTUATION = 19,
	G_UNICODE_INITIAL_PUNCTUATION = 20,
	G_UNICODE_OTHER_PUNCTUATION = 21,
	G_UNICODE_OPEN_PUNCTUATION = 22,
	G_UNICODE_CURRENCY_SYMBOL = 23,
	G_UNICODE_MODIFIER_SYMBOL = 24,
	G_UNICODE_MATH_SYMBOL = 25,
	G_UNICODE_OTHER_SYMBOL = 26,
	G_UNICODE_LINE_SEPARATOR = 27,
	G_UNICODE_PARAGRAPH_SEPARATOR = 28,
	G_UNICODE_SPACE_SEPARATOR = 29
}

enum _Anonymous_1
{
	G_UNICODE_BREAK_MANDATORY = 0,
	G_UNICODE_BREAK_CARRIAGE_RETURN = 1,
	G_UNICODE_BREAK_LINE_FEED = 2,
	G_UNICODE_BREAK_COMBINING_MARK = 3,
	G_UNICODE_BREAK_SURROGATE = 4,
	G_UNICODE_BREAK_ZERO_WIDTH_SPACE = 5,
	G_UNICODE_BREAK_INSEPARABLE = 6,
	G_UNICODE_BREAK_NON_BREAKING_GLUE = 7,
	G_UNICODE_BREAK_CONTINGENT = 8,
	G_UNICODE_BREAK_SPACE = 9,
	G_UNICODE_BREAK_AFTER = 10,
	G_UNICODE_BREAK_BEFORE = 11,
	G_UNICODE_BREAK_BEFORE_AND_AFTER = 12,
	G_UNICODE_BREAK_HYPHEN = 13,
	G_UNICODE_BREAK_NON_STARTER = 14,
	G_UNICODE_BREAK_OPEN_PUNCTUATION = 15,
	G_UNICODE_BREAK_CLOSE_PUNCTUATION = 16,
	G_UNICODE_BREAK_QUOTATION = 17,
	G_UNICODE_BREAK_EXCLAMATION = 18,
	G_UNICODE_BREAK_IDEOGRAPHIC = 19,
	G_UNICODE_BREAK_NUMERIC = 20,
	G_UNICODE_BREAK_INFIX_SEPARATOR = 21,
	G_UNICODE_BREAK_SYMBOL = 22,
	G_UNICODE_BREAK_ALPHABETIC = 23,
	G_UNICODE_BREAK_PREFIX = 24,
	G_UNICODE_BREAK_POSTFIX = 25,
	G_UNICODE_BREAK_COMPLEX_CONTEXT = 26,
	G_UNICODE_BREAK_AMBIGUOUS = 27,
	G_UNICODE_BREAK_UNKNOWN = 28,
	G_UNICODE_BREAK_NEXT_LINE = 29,
	G_UNICODE_BREAK_WORD_JOINER = 30,
	G_UNICODE_BREAK_HANGUL_L_JAMO = 31,
	G_UNICODE_BREAK_HANGUL_V_JAMO = 32,
	G_UNICODE_BREAK_HANGUL_T_JAMO = 33,
	G_UNICODE_BREAK_HANGUL_LV_SYLLABLE = 34,
	G_UNICODE_BREAK_HANGUL_LVT_SYLLABLE = 35,
	G_UNICODE_BREAK_CLOSE_PARANTHESIS = 36,
	G_UNICODE_BREAK_CONDITIONAL_JAPANESE_STARTER = 37,
	G_UNICODE_BREAK_HEBREW_LETTER = 38
}

enum _Anonymous_2
{
	G_UNICODE_SCRIPT_INVALID_CODE = -1,
	G_UNICODE_SCRIPT_COMMON = 0,
	G_UNICODE_SCRIPT_INHERITED = 1,
	G_UNICODE_SCRIPT_ARABIC = 2,
	G_UNICODE_SCRIPT_ARMENIAN = 3,
	G_UNICODE_SCRIPT_BENGALI = 4,
	G_UNICODE_SCRIPT_BOPOMOFO = 5,
	G_UNICODE_SCRIPT_CHEROKEE = 6,
	G_UNICODE_SCRIPT_COPTIC = 7,
	G_UNICODE_SCRIPT_CYRILLIC = 8,
	G_UNICODE_SCRIPT_DESERET = 9,
	G_UNICODE_SCRIPT_DEVANAGARI = 10,
	G_UNICODE_SCRIPT_ETHIOPIC = 11,
	G_UNICODE_SCRIPT_GEORGIAN = 12,
	G_UNICODE_SCRIPT_GOTHIC = 13,
	G_UNICODE_SCRIPT_GREEK = 14,
	G_UNICODE_SCRIPT_GUJARATI = 15,
	G_UNICODE_SCRIPT_GURMUKHI = 16,
	G_UNICODE_SCRIPT_HAN = 17,
	G_UNICODE_SCRIPT_HANGUL = 18,
	G_UNICODE_SCRIPT_HEBREW = 19,
	G_UNICODE_SCRIPT_HIRAGANA = 20,
	G_UNICODE_SCRIPT_KANNADA = 21,
	G_UNICODE_SCRIPT_KATAKANA = 22,
	G_UNICODE_SCRIPT_KHMER = 23,
	G_UNICODE_SCRIPT_LAO = 24,
	G_UNICODE_SCRIPT_LATIN = 25,
	G_UNICODE_SCRIPT_MALAYALAM = 26,
	G_UNICODE_SCRIPT_MONGOLIAN = 27,
	G_UNICODE_SCRIPT_MYANMAR = 28,
	G_UNICODE_SCRIPT_OGHAM = 29,
	G_UNICODE_SCRIPT_OLD_ITALIC = 30,
	G_UNICODE_SCRIPT_ORIYA = 31,
	G_UNICODE_SCRIPT_RUNIC = 32,
	G_UNICODE_SCRIPT_SINHALA = 33,
	G_UNICODE_SCRIPT_SYRIAC = 34,
	G_UNICODE_SCRIPT_TAMIL = 35,
	G_UNICODE_SCRIPT_TELUGU = 36,
	G_UNICODE_SCRIPT_THAANA = 37,
	G_UNICODE_SCRIPT_THAI = 38,
	G_UNICODE_SCRIPT_TIBETAN = 39,
	G_UNICODE_SCRIPT_CANADIAN_ABORIGINAL = 40,
	G_UNICODE_SCRIPT_YI = 41,
	G_UNICODE_SCRIPT_TAGALOG = 42,
	G_UNICODE_SCRIPT_HANUNOO = 43,
	G_UNICODE_SCRIPT_BUHID = 44,
	G_UNICODE_SCRIPT_TAGBANWA = 45,
	G_UNICODE_SCRIPT_BRAILLE = 46,
	G_UNICODE_SCRIPT_CYPRIOT = 47,
	G_UNICODE_SCRIPT_LIMBU = 48,
	G_UNICODE_SCRIPT_OSMANYA = 49,
	G_UNICODE_SCRIPT_SHAVIAN = 50,
	G_UNICODE_SCRIPT_LINEAR_B = 51,
	G_UNICODE_SCRIPT_TAI_LE = 52,
	G_UNICODE_SCRIPT_UGARITIC = 53,
	G_UNICODE_SCRIPT_NEW_TAI_LUE = 54,
	G_UNICODE_SCRIPT_BUGINESE = 55,
	G_UNICODE_SCRIPT_GLAGOLITIC = 56,
	G_UNICODE_SCRIPT_TIFINAGH = 57,
	G_UNICODE_SCRIPT_SYLOTI_NAGRI = 58,
	G_UNICODE_SCRIPT_OLD_PERSIAN = 59,
	G_UNICODE_SCRIPT_KHAROSHTHI = 60,
	G_UNICODE_SCRIPT_UNKNOWN = 61,
	G_UNICODE_SCRIPT_BALINESE = 62,
	G_UNICODE_SCRIPT_CUNEIFORM = 63,
	G_UNICODE_SCRIPT_PHOENICIAN = 64,
	G_UNICODE_SCRIPT_PHAGS_PA = 65,
	G_UNICODE_SCRIPT_NKO = 66,
	G_UNICODE_SCRIPT_KAYAH_LI = 67,
	G_UNICODE_SCRIPT_LEPCHA = 68,
	G_UNICODE_SCRIPT_REJANG = 69,
	G_UNICODE_SCRIPT_SUNDANESE = 70,
	G_UNICODE_SCRIPT_SAURASHTRA = 71,
	G_UNICODE_SCRIPT_CHAM = 72,
	G_UNICODE_SCRIPT_OL_CHIKI = 73,
	G_UNICODE_SCRIPT_VAI = 74,
	G_UNICODE_SCRIPT_CARIAN = 75,
	G_UNICODE_SCRIPT_LYCIAN = 76,
	G_UNICODE_SCRIPT_LYDIAN = 77,
	G_UNICODE_SCRIPT_AVESTAN = 78,
	G_UNICODE_SCRIPT_BAMUM = 79,
	G_UNICODE_SCRIPT_EGYPTIAN_HIEROGLYPHS = 80,
	G_UNICODE_SCRIPT_IMPERIAL_ARAMAIC = 81,
	G_UNICODE_SCRIPT_INSCRIPTIONAL_PAHLAVI = 82,
	G_UNICODE_SCRIPT_INSCRIPTIONAL_PARTHIAN = 83,
	G_UNICODE_SCRIPT_JAVANESE = 84,
	G_UNICODE_SCRIPT_KAITHI = 85,
	G_UNICODE_SCRIPT_LISU = 86,
	G_UNICODE_SCRIPT_MEETEI_MAYEK = 87,
	G_UNICODE_SCRIPT_OLD_SOUTH_ARABIAN = 88,
	G_UNICODE_SCRIPT_OLD_TURKIC = 89,
	G_UNICODE_SCRIPT_SAMARITAN = 90,
	G_UNICODE_SCRIPT_TAI_THAM = 91,
	G_UNICODE_SCRIPT_TAI_VIET = 92,
	G_UNICODE_SCRIPT_BATAK = 93,
	G_UNICODE_SCRIPT_BRAHMI = 94,
	G_UNICODE_SCRIPT_MANDAIC = 95,
	G_UNICODE_SCRIPT_CHAKMA = 96,
	G_UNICODE_SCRIPT_MEROITIC_CURSIVE = 97,
	G_UNICODE_SCRIPT_MEROITIC_HIEROGLYPHS = 98,
	G_UNICODE_SCRIPT_MIAO = 99,
	G_UNICODE_SCRIPT_SHARADA = 100,
	G_UNICODE_SCRIPT_SORA_SOMPENG = 101,
	G_UNICODE_SCRIPT_TAKRI = 102
}

enum _Anonymous_3
{
	G_NORMALIZE_DEFAULT = 0,
	G_NORMALIZE_NFD = 0,
	G_NORMALIZE_DEFAULT_COMPOSE = 1,
	G_NORMALIZE_NFC = 1,
	G_NORMALIZE_ALL = 2,
	G_NORMALIZE_NFKD = 2,
	G_NORMALIZE_ALL_COMPOSE = 3,
	G_NORMALIZE_NFKC = 3
}

guint32 g_unicode_script_to_iso15924 (GUnicodeScript script);
GUnicodeScript g_unicode_script_from_iso15924 (guint32 iso15924);
gboolean g_unichar_isalnum (gunichar c);
gboolean g_unichar_isalpha (gunichar c);
gboolean g_unichar_iscntrl (gunichar c);
gboolean g_unichar_isdigit (gunichar c);
gboolean g_unichar_isgraph (gunichar c);
gboolean g_unichar_islower (gunichar c);
gboolean g_unichar_isprint (gunichar c);
gboolean g_unichar_ispunct (gunichar c);
gboolean g_unichar_isspace (gunichar c);
gboolean g_unichar_isupper (gunichar c);
gboolean g_unichar_isxdigit (gunichar c);
gboolean g_unichar_istitle (gunichar c);
gboolean g_unichar_isdefined (gunichar c);
gboolean g_unichar_iswide (gunichar c);
gboolean g_unichar_iswide_cjk (gunichar c);
gboolean g_unichar_iszerowidth (gunichar c);
gboolean g_unichar_ismark (gunichar c);
gunichar g_unichar_toupper (gunichar c);
gunichar g_unichar_tolower (gunichar c);
gunichar g_unichar_totitle (gunichar c);
gint g_unichar_digit_value (gunichar c);
gint g_unichar_xdigit_value (gunichar c);
GUnicodeType g_unichar_type (gunichar c);
GUnicodeBreakType g_unichar_break_type (gunichar c);
gint g_unichar_combining_class (gunichar uc);
gboolean g_unichar_get_mirror_char (gunichar ch, gunichar* mirrored_ch);
GUnicodeScript g_unichar_get_script (gunichar ch);
gboolean g_unichar_validate (gunichar ch);
gboolean g_unichar_compose (gunichar a, gunichar b, gunichar* ch);
gboolean g_unichar_decompose (gunichar ch, gunichar* a, gunichar* b);
gsize g_unichar_fully_decompose (gunichar ch, gboolean compat, gunichar* result, gsize result_len);
void g_unicode_canonical_ordering (gunichar* string, gsize len);
gunichar* g_unicode_canonical_decomposition (gunichar ch, gsize* result_len);
gunichar g_utf8_get_char (const(gchar)* p);
gunichar g_utf8_get_char_validated (const(gchar)* p, gssize max_len);
gchar* g_utf8_offset_to_pointer (const(gchar)* str, glong offset);
glong g_utf8_pointer_to_offset (const(gchar)* str, const(gchar)* pos);
gchar* g_utf8_prev_char (const(gchar)* p);
gchar* g_utf8_find_next_char (const(gchar)* p, const(gchar)* end);
gchar* g_utf8_find_prev_char (const(gchar)* str, const(gchar)* p);
glong g_utf8_strlen (const(gchar)* p, gssize max);
gchar* g_utf8_substring (const(gchar)* str, glong start_pos, glong end_pos);
gchar* g_utf8_strncpy (gchar* dest, const(gchar)* src, gsize n);
gchar* g_utf8_strchr (const(gchar)* p, gssize len, gunichar c);
gchar* g_utf8_strrchr (const(gchar)* p, gssize len, gunichar c);
gchar* g_utf8_strreverse (const(gchar)* str, gssize len);
gunichar2* g_utf8_to_utf16 (const(gchar)* str, glong len, glong* items_read, glong* items_written, GError** error);
gunichar* g_utf8_to_ucs4 (const(gchar)* str, glong len, glong* items_read, glong* items_written, GError** error);
gunichar* g_utf8_to_ucs4_fast (const(gchar)* str, glong len, glong* items_written);
gunichar* g_utf16_to_ucs4 (const(gunichar2)* str, glong len, glong* items_read, glong* items_written, GError** error);
gchar* g_utf16_to_utf8 (const(gunichar2)* str, glong len, glong* items_read, glong* items_written, GError** error);
gunichar2* g_ucs4_to_utf16 (const(gunichar)* str, glong len, glong* items_read, glong* items_written, GError** error);
gchar* g_ucs4_to_utf8 (const(gunichar)* str, glong len, glong* items_read, glong* items_written, GError** error);
gint g_unichar_to_utf8 (gunichar c, gchar* outbuf);
gboolean g_utf8_validate (const(gchar)* str, gssize max_len, const(gchar*)* end);
gchar* g_utf8_strup (const(gchar)* str, gssize len);
gchar* g_utf8_strdown (const(gchar)* str, gssize len);
gchar* g_utf8_casefold (const(gchar)* str, gssize len);
gchar* g_utf8_normalize (const(gchar)* str, gssize len, GNormalizeMode mode);
gint g_utf8_collate (const(gchar)* str1, const(gchar)* str2);
gchar* g_utf8_collate_key (const(gchar)* str, gssize len);
gchar* g_utf8_collate_key_for_filename (const(gchar)* str, gssize len);
gchar* _g_utf8_make_valid (const(gchar)* name);