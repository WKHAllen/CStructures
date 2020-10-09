#include "string.h"
#include "defs.h"
#include <stdlib.h>
#include <string.h>

EXPORT String *string_new(void)
{
	String *s = malloc(sizeof(*s));
	s->value = strdup("");
	s->length = 0;
	return s;
}

EXPORT String *string_from(char *string)
{
	String *s = malloc(sizeof(*s));
	s->value = strdup(string);
	s->length = strlen(string);
	return s;
}

EXPORT String *string_from_char(char chr)
{
	String *s = malloc(sizeof(*s));
	s->value = strdup(&chr);
	s->length = 1;
	return s;
}

EXPORT char *string_value(String *s)
{

}

EXPORT size_t string_length(String *s)
{

}

EXPORT char string_get(String *s, int index)
{

}

EXPORT void string_set(String *s, int index, char chr)
{

}

EXPORT void string_concat(String *s1, String *s2)
{

}

EXPORT void string_slice(String *s, int index1, int index2)
{

}

EXPORT void string_delete(String *s, int index)
{

}

EXPORT int string_index(String *s1, String *s2)
{

}

EXPORT int string_count(String *s1, String *s2)
{

}

EXPORT void string_remove(String *s1, String *s2)
{

}

EXPORT void string_remove_all(String *s1, String *s2)
{

}

EXPORT void string_replace(String *s1, String *s2)
{

}

EXPORT void string_replace_all(String *s1, String *s2)
{

}

EXPORT int string_equal(String *s1, String *s2)
{

}

EXPORT int string_compare(String *s1, String *s2)
{

}

EXPORT int string_starts_with(String *s1, String *s2)
{

}

EXPORT int string_ends_with(String *s1, String *s2)
{

}

EXPORT void string_lower(String *s)
{

}

EXPORT void string_upper(String *s)
{

}

EXPORT void string_swap_case(String *s)
{

}

EXPORT String *string_copy(String *s)
{

}

EXPORT void string_reverse(String *s)
{

}

EXPORT void string_foreach(String *s, void (*fptr)(void *, void *), void *args)
{
	for (int i = 0; i < s->length; i++)
		(*fptr)(s->value[i], args);
}

EXPORT void string_free(String *s)
{
	free(s->value);
	free(s);
}
