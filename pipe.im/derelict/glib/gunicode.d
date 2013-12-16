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

alias da_g_unicode_script_to_iso15924 = guint32 function(GUnicodeScript script);																																																						/* da_g_unicode_script_to_iso15924 g_unicode_script_to_iso15924; */
alias da_g_unicode_script_from_iso15924 = GUnicodeScript function(guint32 iso15924);																																																						/* da_g_unicode_script_from_iso15924 g_unicode_script_from_iso15924; */
alias da_g_unichar_isalnum = gboolean function(gunichar c);																																																						/* da_g_unichar_isalnum g_unichar_isalnum; */
alias da_g_unichar_isalpha = gboolean function(gunichar c);																																																						/* da_g_unichar_isalpha g_unichar_isalpha; */
alias da_g_unichar_iscntrl = gboolean function(gunichar c);																																																						/* da_g_unichar_iscntrl g_unichar_iscntrl; */
alias da_g_unichar_isdigit = gboolean function(gunichar c);																																																						/* da_g_unichar_isdigit g_unichar_isdigit; */
alias da_g_unichar_isgraph = gboolean function(gunichar c);																																																						/* da_g_unichar_isgraph g_unichar_isgraph; */
alias da_g_unichar_islower = gboolean function(gunichar c);																																																						/* da_g_unichar_islower g_unichar_islower; */
alias da_g_unichar_isprint = gboolean function(gunichar c);																																																						/* da_g_unichar_isprint g_unichar_isprint; */
alias da_g_unichar_ispunct = gboolean function(gunichar c);																																																						/* da_g_unichar_ispunct g_unichar_ispunct; */
alias da_g_unichar_isspace = gboolean function(gunichar c);																																																						/* da_g_unichar_isspace g_unichar_isspace; */
alias da_g_unichar_isupper = gboolean function(gunichar c);																																																						/* da_g_unichar_isupper g_unichar_isupper; */
alias da_g_unichar_isxdigit = gboolean function(gunichar c);																																																						/* da_g_unichar_isxdigit g_unichar_isxdigit; */
alias da_g_unichar_istitle = gboolean function(gunichar c);																																																						/* da_g_unichar_istitle g_unichar_istitle; */
alias da_g_unichar_isdefined = gboolean function(gunichar c);																																																						/* da_g_unichar_isdefined g_unichar_isdefined; */
alias da_g_unichar_iswide = gboolean function(gunichar c);																																																						/* da_g_unichar_iswide g_unichar_iswide; */
alias da_g_unichar_iswide_cjk = gboolean function(gunichar c);																																																						/* da_g_unichar_iswide_cjk g_unichar_iswide_cjk; */
alias da_g_unichar_iszerowidth = gboolean function(gunichar c);																																																						/* da_g_unichar_iszerowidth g_unichar_iszerowidth; */
alias da_g_unichar_ismark = gboolean function(gunichar c);																																																						/* da_g_unichar_ismark g_unichar_ismark; */
alias da_g_unichar_toupper = gunichar function(gunichar c);																																																						/* da_g_unichar_toupper g_unichar_toupper; */
alias da_g_unichar_tolower = gunichar function(gunichar c);																																																						/* da_g_unichar_tolower g_unichar_tolower; */
alias da_g_unichar_totitle = gunichar function(gunichar c);																																																						/* da_g_unichar_totitle g_unichar_totitle; */
alias da_g_unichar_digit_value = gint function(gunichar c);																																																						/* da_g_unichar_digit_value g_unichar_digit_value; */
alias da_g_unichar_xdigit_value = gint function(gunichar c);																																																						/* da_g_unichar_xdigit_value g_unichar_xdigit_value; */
alias da_g_unichar_type = GUnicodeType function(gunichar c);																																																						/* da_g_unichar_type g_unichar_type; */
alias da_g_unichar_break_type = GUnicodeBreakType function(gunichar c);																																																						/* da_g_unichar_break_type g_unichar_break_type; */
alias da_g_unichar_combining_class = gint function(gunichar uc);																																																						/* da_g_unichar_combining_class g_unichar_combining_class; */
alias da_g_unichar_get_mirror_char = gboolean function(gunichar ch, gunichar* mirrored_ch);																																																						/* da_g_unichar_get_mirror_char g_unichar_get_mirror_char; */
alias da_g_unichar_get_script = GUnicodeScript function(gunichar ch);																																																						/* da_g_unichar_get_script g_unichar_get_script; */
alias da_g_unichar_validate = gboolean function(gunichar ch);																																																						/* da_g_unichar_validate g_unichar_validate; */
alias da_g_unichar_compose = gboolean function(gunichar a, gunichar b, gunichar* ch);																																																						/* da_g_unichar_compose g_unichar_compose; */
alias da_g_unichar_decompose = gboolean function(gunichar ch, gunichar* a, gunichar* b);																																																						/* da_g_unichar_decompose g_unichar_decompose; */
alias da_g_unichar_fully_decompose = gsize function(gunichar ch, gboolean compat, gunichar* result, gsize result_len);																																																						/* da_g_unichar_fully_decompose g_unichar_fully_decompose; */
alias da_g_unicode_canonical_ordering = void function(gunichar* string, gsize len);																																																						/* da_g_unicode_canonical_ordering g_unicode_canonical_ordering; */
alias da_g_unicode_canonical_decomposition = gunichar* function(gunichar ch, gsize* result_len);																																																						/* da_g_unicode_canonical_decomposition g_unicode_canonical_decomposition; */
alias da_g_utf8_get_char = gunichar function(const(gchar)* p);																																																						/* da_g_utf8_get_char g_utf8_get_char; */
alias da_g_utf8_get_char_validated = gunichar function(const(gchar)* p, gssize max_len);																																																						/* da_g_utf8_get_char_validated g_utf8_get_char_validated; */
alias da_g_utf8_offset_to_pointer = gchar* function(const(gchar)* str, glong offset);																																																						/* da_g_utf8_offset_to_pointer g_utf8_offset_to_pointer; */
alias da_g_utf8_pointer_to_offset = glong function(const(gchar)* str, const(gchar)* pos);																																																						/* da_g_utf8_pointer_to_offset g_utf8_pointer_to_offset; */
alias da_g_utf8_prev_char = gchar* function(const(gchar)* p);																																																						/* da_g_utf8_prev_char g_utf8_prev_char; */
alias da_g_utf8_find_next_char = gchar* function(const(gchar)* p, const(gchar)* end);																																																						/* da_g_utf8_find_next_char g_utf8_find_next_char; */
alias da_g_utf8_find_prev_char = gchar* function(const(gchar)* str, const(gchar)* p);																																																						/* da_g_utf8_find_prev_char g_utf8_find_prev_char; */
alias da_g_utf8_strlen = glong function(const(gchar)* p, gssize max);																																																						/* da_g_utf8_strlen g_utf8_strlen; */
alias da_g_utf8_substring = gchar* function(const(gchar)* str, glong start_pos, glong end_pos);																																																						/* da_g_utf8_substring g_utf8_substring; */
alias da_g_utf8_strncpy = gchar* function(gchar* dest, const(gchar)* src, gsize n);																																																						/* da_g_utf8_strncpy g_utf8_strncpy; */
alias da_g_utf8_strchr = gchar* function(const(gchar)* p, gssize len, gunichar c);																																																						/* da_g_utf8_strchr g_utf8_strchr; */
alias da_g_utf8_strrchr = gchar* function(const(gchar)* p, gssize len, gunichar c);																																																						/* da_g_utf8_strrchr g_utf8_strrchr; */
alias da_g_utf8_strreverse = gchar* function(const(gchar)* str, gssize len);																																																						/* da_g_utf8_strreverse g_utf8_strreverse; */
alias da_g_utf8_to_utf16 = gunichar2* function(const(gchar)* str, glong len, glong* items_read, glong* items_written, GError** error);																																																						/* da_g_utf8_to_utf16 g_utf8_to_utf16; */
alias da_g_utf8_to_ucs4 = gunichar* function(const(gchar)* str, glong len, glong* items_read, glong* items_written, GError** error);																																																						/* da_g_utf8_to_ucs4 g_utf8_to_ucs4; */
alias da_g_utf8_to_ucs4_fast = gunichar* function(const(gchar)* str, glong len, glong* items_written);																																																						/* da_g_utf8_to_ucs4_fast g_utf8_to_ucs4_fast; */
alias da_g_utf16_to_ucs4 = gunichar* function(const(gunichar2)* str, glong len, glong* items_read, glong* items_written, GError** error);																																																						/* da_g_utf16_to_ucs4 g_utf16_to_ucs4; */
alias da_g_utf16_to_utf8 = gchar* function(const(gunichar2)* str, glong len, glong* items_read, glong* items_written, GError** error);																																																						/* da_g_utf16_to_utf8 g_utf16_to_utf8; */
alias da_g_ucs4_to_utf16 = gunichar2* function(const(gunichar)* str, glong len, glong* items_read, glong* items_written, GError** error);																																																						/* da_g_ucs4_to_utf16 g_ucs4_to_utf16; */
alias da_g_ucs4_to_utf8 = gchar* function(const(gunichar)* str, glong len, glong* items_read, glong* items_written, GError** error);																																																						/* da_g_ucs4_to_utf8 g_ucs4_to_utf8; */
alias da_g_unichar_to_utf8 = gint function(gunichar c, gchar* outbuf);																																																						/* da_g_unichar_to_utf8 g_unichar_to_utf8; */
alias da_g_utf8_validate = gboolean function(const(gchar)* str, gssize max_len, const(gchar*)* end);																																																						/* da_g_utf8_validate g_utf8_validate; */
alias da_g_utf8_strup = gchar* function(const(gchar)* str, gssize len);																																																						/* da_g_utf8_strup g_utf8_strup; */
alias da_g_utf8_strdown = gchar* function(const(gchar)* str, gssize len);																																																						/* da_g_utf8_strdown g_utf8_strdown; */
alias da_g_utf8_casefold = gchar* function(const(gchar)* str, gssize len);																																																						/* da_g_utf8_casefold g_utf8_casefold; */
alias da_g_utf8_normalize = gchar* function(const(gchar)* str, gssize len, GNormalizeMode mode);																																																						/* da_g_utf8_normalize g_utf8_normalize; */
alias da_g_utf8_collate = gint function(const(gchar)* str1, const(gchar)* str2);																																																						/* da_g_utf8_collate g_utf8_collate; */
alias da_g_utf8_collate_key = gchar* function(const(gchar)* str, gssize len);																																																						/* da_g_utf8_collate_key g_utf8_collate_key; */
alias da_g_utf8_collate_key_for_filename = gchar* function(const(gchar)* str, gssize len);																																																						/* da_g_utf8_collate_key_for_filename g_utf8_collate_key_for_filename; */
alias da__g_utf8_make_valid = gchar* function(const(gchar)* name);																																																						/* da__g_utf8_make_valid _g_utf8_make_valid; */
