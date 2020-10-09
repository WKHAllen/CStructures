#ifndef _STRING_H_
#define _STRING_H_

#include <stdlib.h>

typedef struct _String {
	char *value;
	size_t length;
} String;

String *string_new(void);

String *string_from(char *string);

String *string_from_char(char chr);

char *string_value(String *s);

size_t string_length(String *s);

char string_get(String *s, int index);

void string_set(String *s, int index, char chr);

void string_concat(String *s1, String *s2);

void string_slice(String *s, int index1, int index2);

void string_delete(String *s, int index);

int string_index(String *s1, String *s2);

int string_count(String *s1, String *s2);

void string_remove(String *s1, String *s2);

void string_remove_all(String *s1, String *s2);

void string_replace(String *s1, String *s2);

void string_replace_all(String *s1, String *s2);

int string_equal(String *s1, String *s2);

int string_compare(String *s1, String *s2);

int string_starts_with(String *s1, String *s2);

int string_ends_with(String *s1, String *s2);

void string_lower(String *s);

void string_upper(String *s);

void string_swap_case(String *s);

String *string_copy(String *s);

void string_reverse(String *s);

void string_foreach(String *s, void (*fptr)(void *, void *), void *args);

void string_free(String *s);

#endif /* _STRING_H_ */
