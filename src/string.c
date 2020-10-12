#include "string.h"
#include "defs.h"
#include <stdlib.h>
#include <string.h>

EXPORT String *string_new(void)
{
	String *s = malloc(sizeof(String));
	s->value = strdup("");
	s->length = 0;
	return s;
}

EXPORT String *string_from(char *string)
{
	String *s = malloc(sizeof(String));
	s->value = strdup(string);
	s->length = strlen(string);
	return s;
}

EXPORT String *string_from_char(char chr)
{
	String *s = malloc(sizeof(String));
	s->value = strdup(&chr);
	s->length = 1;
	return s;
}

EXPORT void string_from_string(String *s1, String *s2)
{
	free(s1->value);
	s1->value = strdup(s2->value);
	s1->length = s2->length;
}

EXPORT char *string_value(String *s)
{
	return strdup(s->value);
}

EXPORT idx string_length(String *s)
{
	return s->length;
}

EXPORT char string_get(String *s, idx index)
{
	if (index < 0)
		index += s->length;
	if (index < 0 || index >= s->length)
		return NULL;
	return s->value[index];
}

EXPORT void string_set(String *s, idx index, char chr)
{
	if (index < 0)
		index += s->length;
	if (index < 0 || index >= s->length)
		return;
	return s->value[index] = chr;
}

EXPORT void string_concat(String *s1, String *s2)
{

}

EXPORT String *string_slice(String *s, idx index1, idx index2)
{

}

EXPORT String *string_slice_start(String *s, idx index)
{

}

EXPORT String *string_slice_end(String *s, idx index)
{

}

EXPORT void string_delete(String *s, idx index)
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

EXPORT void string_foreach(String *s, void (*fptr)(char, void *), void *args)
{
	for (int i = 0; i < s->length; i++)
		(*fptr)(s->value[i], args);
}

EXPORT void string_free(String *s)
{
	free(s->value);
	free(s);
}
