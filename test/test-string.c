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

    printf("Successfully passed all tests\n");
    return 0;
}
