#include "../bin/include/string.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

int main(int argc, char **argv)
{
    printf("Running tests...\n");

    // test initialization from nothing
	String *s1 = string_new();
	assert(s1 != NULL);
	assert(s1->length == 0);
	assert(strcmp(s1->value, "") == 0);
	string_free(s1);

	// test initialization from char*
	String *s2 = string_from("Hello, world!");
	assert(s2 != NULL);
	assert(s2->length == 13);
	assert(strcmp(s2->value, "Hello, world!") == 0);
	string_free(s2);

	// test initialization from char
	String *s3 = string_from_char('W');
	assert(s3 != NULL);
	assert(s3->length == 1);
	assert(strcmp(s3->value, "W") == 0);
	string_free(s3);

	// test from string
	String *s4 = string_from("foo");
	String *s5 = string_from("bar");
	string_from_string(s4, s5);
	assert(strcmp(s4->value, "bar") == 0);
	assert(strcmp(s5->value, "bar") == 0);
	string_free(s4);
	string_free(s5);

	// test value and length
	String *s6 = string_from("hello!");
	assert(strcmp(string_value(s6), "hello!") == 0);
	assert(string_length(s6) == 6);
	string_free(s6);

	// test get and set
	String *s7 = string_from("ABCDEFG");
	assert(string_get(s7, 2) == 'C');
	string_set(s7, 2, 'Z');
	assert(string_get(s7, 2) == 'Z');
	string_free(s7);

	// test concat
	String *s8 = string_from("Hello,");
	String *s9 = string_from_char(' ');
	String *s10 = string_from("world!");
	String *s11 = string_concat(s8, s9);
	string_free(s8);
	string_free(s9);
	String *s12 = string_concat(s11, s10);
	string_free(s10);
	string_free(s11);
	assert(strcmp(string_value(s12), "Hello, world!") == 0);
	string_free(s12);

	// test slice, slice start, and slice end
	String *s13 = string_from("Hello, world!");
	String *s14 = string_slice(s13, 3, 8);
	assert(strcmp(string_value(s14), "lo, w") == 0);
	String *s15 = string_slice(s13, 8, 3);
	assert(strcmp(string_value(s15), "") == 0);
	String *s16 = string_slice(s13, -20, 3);
	assert(strcmp(string_value(s16), "Hel") == 0);
	String *s17 = string_slice(s13, -3, 20);
	assert(strcmp(string_value(s17), "ld!") == 0);
	String *s18 = string_slice_start(s13, 5);
	assert(strcmp(string_value(s18), "Hello") == 0);
	String *s19 = string_slice_end(s13, 7);
	assert(strcmp(string_value(s19), "world!") == 0);
	string_free(s13);
	string_free(s14);
	string_free(s15);
	string_free(s16);
	string_free(s17);
	string_free(s18);
	string_free(s19);

	// test index, count, replace, and replace all
	String *s20 = string_from("127.0.0.1");
	String *s21 = string_from_char('.');
	String *s22 = string_from_char('0');
	String *s23 = string_from("27");
	String *s24 = string_from("3");
	assert(string_index(s20, s21) == 3);
	assert(string_index(s20, s22) == 4);
	assert(string_index(s20, s23) == 1);
	assert(string_index(s20, s24) == -1);
	assert(string_count(s20, s21) == 3);
	assert(string_count(s20, s22) == 2);
	assert(string_count(s20, s23) == 1);
	assert(string_count(s20, s24) == 0);
	String *s25 = string_replace(s20, s21, s24);
	assert(strcmp(string_value(s25), "12730.0.1") == 0);
	String *s26 = string_replace_all(s20, s21, s24);
	assert(strcmp(string_value(s26), "127303031") == 0);
	String *s27 = string_replace_all(s20, s24, s21);
	assert(strcmp(string_value(s27), "127.0.0.1") == 0);
	string_free(s20);
	string_free(s21);
	string_free(s22);
	string_free(s23);
	string_free(s24);
	string_free(s25);
	string_free(s26);
	string_free(s27);

    printf("Successfully passed all tests\n");
    return 0;
}
