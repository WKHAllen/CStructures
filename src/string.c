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
		return '\0';
	return s->value[index];
}

EXPORT void string_set(String *s, idx index, char chr)
{
	if (index < 0)
		index += s->length;
	if (index < 0 || index >= s->length)
		return;
	s->value[index] = chr;
}

EXPORT String *string_concat(String *s1, String *s2)
{
	char *value = malloc(sizeof(char) * (s1->length + s2->length + 1));
	strcpy(value, s1->value);
	strcat(value, s2->value);
	String *string_value = string_from(value);
	free(value);
	return string_value;
}

EXPORT String *string_slice(String *s, idx index1, idx index2)
{
	if (index1 < 0)
		index1 += s->length;
	if (index2 < 0)
		index2 += s->length;
	if (index1 < 0 || index1 >= s->length || index2 < 0 || index2 >= s->length || index1 > index2)
		return NULL;
	char *value = malloc(sizeof(char) * (index2 - index1 + 1));
	for (idx i = 0; i < index2 - index1; i++)
		value[i] = s->value[index1 + i];
	String *string_value = string_from(value);
	free(value);
	return string_value;
}

EXPORT String *string_slice_start(String *s, idx index)
{
	return string_slice(s, 0, index);
}

EXPORT String *string_slice_end(String *s, idx index)
{
	return string_slice(s, index, s->length);
}

EXPORT idx string_index(String *s1, String *s2)
{
	idx s2idx = 0;
	for (idx i = 0; i < s1->length; i++)
	{
		if (s1->value[i] == s2->value[s2idx])
			s2idx++;
		else
			s2idx = 0;
		if (s2idx >= s2->length)
			return i - s2idx;
	}
	return -1;
}

EXPORT idx string_count(String *s1, String *s2)
{
	idx count = 0;
	idx s2idx = 0;
	for (idx i = 0; i < s1->length; i++)
	{
		if (s1->value[i] == s2->value[s2idx])
			s2idx++;
		else
			s2idx = 0;
		if (s2idx >= s2->length)
		{
			s2idx = 0;
			count++;
		}
	}
	return count;
}

EXPORT String *string_replace(String *s1, String *s2)
{

}

EXPORT String *string_replace_all(String *s1, String *s2)
{

}

EXPORT int string_equal(String *s1, String *s2)
{
	if (s1->length != s2->length)
		return 0;
	for (idx i = 0; i < s1->length; i++)
		if (s1->value[i] != s2->value[i])
			return 0;
	return 1;
}

EXPORT int string_compare(String *s1, String *s2)
{
	return strcmp(s1->value, s2->value);
}

EXPORT int string_starts_with(String *s1, String *s2)
{
	if (s2->length > s1->length)
		return 0;
	for (idx i = 0; i < s2->length; i++)
		if (s1->value[i] != s2->value[i])
			return 0;
	return 1;
}

EXPORT int string_ends_with(String *s1, String *s2)
{
	if (s2->length > s1->length)
		return 0;
	for (idx i = 0; i < s2->length; i++)
		if (s1->value[s1->length - s2->length + i] != s2->value[i])
			return 0;
	return 1;
}

EXPORT String *string_lower(String *s)
{
	for (idx i = 0; i < s->length; i++)
		if (s->value[i] >= 'A' && s->value[i] <= 'Z')
			s->value[i] += 'a' - 'A';
}

EXPORT String *string_upper(String *s)
{
	for (idx i = 0; i < s->length; i++)
		if (s->value[i] >= 'a' && s->value[i] <= 'z')
			s->value[i] += 'A' - 'a';
}

EXPORT String *string_swap_case(String *s)
{
	for (idx i = 0; i < s->length; i++)
		if (s->value[i] >= 'A' && s->value[i] <= 'Z')
			s->value[i] += 'a' - 'A';
		else if (s->value[i] >= 'a' && s->value[i] <= 'z')
			s->value[i] += 'A' - 'a';
}

EXPORT String *string_copy(String *s)
{
	return string_from(s->value);
}

EXPORT String *string_reverse(String *s)
{
	char tmp;
	for (idx i = 0; i < s->length / 2; i++)
	{
		tmp = s->value[i];
		s->value[i] = s->value[s->length - i - 1];
		s->value[s->length - i - 1] = tmp;
	}
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
