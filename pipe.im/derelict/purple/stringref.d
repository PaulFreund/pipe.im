module derelict.purple.stringref;

extern (C):

alias _PurpleStringref PurpleStringref;

struct _PurpleStringref;


alias da_purple_stringref_new = PurpleStringref* function(const(char)* value);																																																						/* da_purple_stringref_new purple_stringref_new; */
alias da_purple_stringref_new_noref = PurpleStringref* function(const(char)* value);																																																						/* da_purple_stringref_new_noref purple_stringref_new_noref; */
alias da_purple_stringref_printf = PurpleStringref* function(const(char)* format, ...);																																																						/* da_purple_stringref_printf purple_stringref_printf; */
alias da_purple_stringref_ref = PurpleStringref* function(PurpleStringref* stringref);																																																						/* da_purple_stringref_ref purple_stringref_ref; */
alias da_purple_stringref_unref = void function(PurpleStringref* stringref);																																																						/* da_purple_stringref_unref purple_stringref_unref; */
alias da_purple_stringref_value = const(char)* function(const(PurpleStringref)* stringref);																																																						/* da_purple_stringref_value purple_stringref_value; */
alias da_purple_stringref_cmp = int function(const(PurpleStringref)* s1, const(PurpleStringref)* s2);																																																						/* da_purple_stringref_cmp purple_stringref_cmp; */
alias da_purple_stringref_len = size_t function(const(PurpleStringref)* stringref);																																																						/* da_purple_stringref_len purple_stringref_len; */
