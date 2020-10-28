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
	char value[2];
	value[0] = chr;
	value[1] = '\0';
	s->value = strdup(value);
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
	if (index1 < 0)
		index1 = 0;
	if (index2 > s->length)
		index2 = s->length;
	if (index1 >= s->length || index2 <= 0 || index1 >= index2)
		return string_new();
	char *value = malloc(sizeof(char) * (index2 - index1 + 1));
	for (idx i = 0; i < index2 - index1; i++)
		value[i] = s->value[index1 + i];
	value[index2 - index1] = '\0';
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

idx string_index_after(String *s1, String *s2, idx start_index)
{
	idx s2idx = 0;
	for (idx i = start_index; i < s1->length; i++)
	{
		if (s1->value[i] == s2->value[s2idx])
			s2idx++;
		else
			s2idx = 0;
		if (s2idx >= s2->length)
			return i - s2idx + 1;
	}
	return -1;
}

EXPORT idx string_index(String *s1, String *s2)
{
	return string_index_after(s1, s2, 0);
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

String *string_replace_after(String *s1, String *s2, String *s3, idx start_index)
{
	idx index = string_index_after(s1, s2, start_index);
	String *result1 = string_slice_start(s1, index);
	String *result2 = string_concat(result1, s3);
	string_free(result1);
	String *result3 = string_slice_end(s1, index + string_length(s2));
	String *result4 = string_concat(result2, result3);
	string_free(result2);
	string_free(result3);
	return result4;
}

EXPORT String *string_replace(String *s1, String *s2, String *s3)
{
	return string_replace_after(s1, s2, s3, 0);
}

EXPORT String *string_replace_all(String *s1, String *s2, String *s3)
{
	idx prev_index = 0;
	idx index = string_index(s1, s2);
	String *result = string_copy(s1);
	while (index != -1)
	{
		String *new_result = string_replace_after(result, s2, s3, prev_index);
		string_from_string(result, new_result);
		string_free(new_result);
		prev_index = index + string_length(s2);
		index = string_index_after(s1, s2, index + string_length(s2));
	}
	return result;
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
	String *lower_string = string_copy(s);
	for (idx i = 0; i < lower_string->length; i++)
		if (lower_string->value[i] >= 'A' && lower_string->value[i] <= 'Z')
			lower_string->value[i] += 'a' - 'A';
	return lower_string;
}

EXPORT String *string_upper(String *s)
{
	String *upper_string = string_copy(s);
	for (idx i = 0; i < upper_string->length; i++)
		if (upper_string->value[i] >= 'a' && upper_string->value[i] <= 'z')
			upper_string->value[i] += 'A' - 'a';
	return upper_string;
}

EXPORT String *string_swap_case(String *s)
{
	String *swapped_string = string_copy(s);
	for (idx i = 0; i < swapped_string->length; i++)
		if (swapped_string->value[i] >= 'A' && swapped_string->value[i] <= 'Z')
			swapped_string->value[i] += 'a' - 'A';
		else if (swapped_string->value[i] >= 'a' && swapped_string->value[i] <= 'z')
			swapped_string->value[i] += 'A' - 'a';
	return swapped_string;
}

EXPORT String *string_copy(String *s)
{
	return string_from(s->value);
}

EXPORT String *string_reverse(String *s)
{
	String *reversed_string = string_copy(s);
	char tmp;
	for (idx i = 0; i < reversed_string->length / 2; i++)
	{
		tmp = reversed_string->value[i];
		reversed_string->value[i] = reversed_string->value[reversed_string->length - i - 1];
		reversed_string->value[reversed_string->length - i - 1] = tmp;
	}
	return reversed_string;
}

EXPORT void string_foreach(String *s, void (*fptr)(char, void *), void *args)
{
	for (idx i = 0; i < s->length; i++)
		(*fptr)(s->value[i], args);
}

EXPORT void string_free(String *s)
{
	free(s->value);
	free(s);
}
