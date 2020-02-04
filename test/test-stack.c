#include "../bin/include/stack.h"
#include <stdio.h>
#include <assert.h>

int main(int argc, char **argv)
{
    printf("Running tests...\n");

    // test initialization
    // []
    Stack s = stack_new();
    assert(stack_size(&s) == 0);
    assert(stack_is_empty(&s));
    assert(s.head == NULL);

    // test int push and peek
    // [7]
    int value1 = 7;
    stack_push(&s, &value1);
    assert(stack_size(&s) == 1);
    assert(!stack_is_empty(&s));
    assert(*(int *)stack_peek(&s) == value1);

    // test string push and peek
    // [7, "hello"]
    char *value2 = "hello";
    stack_push(&s, &value2);
    assert(stack_size(&s) == 2);
    assert(!stack_is_empty(&s));
    assert(*(char **)stack_peek(&s) == value2);

    // test float push and peek
    // [7, "hello", 3.14]
    float value3 = 3.14;
    stack_push(&s, &value3);
    assert(stack_size(&s) == 3);
    assert(!stack_is_empty(&s));
    assert(*(float *)stack_peek(&s) == value3);

    // test float pop and peek
    // [7, "hello"]
    assert(*(float *)stack_pop(&s) == value3);
    assert(stack_size(&s) == 2);
    assert(!stack_is_empty(&s));
    assert(*(char **)stack_peek(&s) == value2);

    // test string pop and peek
    // [7]
    assert(*(char **)stack_pop(&s) == value2);
    assert(stack_size(&s) == 1);
    assert(!stack_is_empty(&s));
    assert(*(int *)stack_peek(&s) == value1);
    
    // test int pop and peek
    // []
    assert(*(int *)stack_pop(&s) == value1);
    assert(stack_size(&s) == 0);
    assert(stack_is_empty(&s));
    assert(stack_peek(&s) == NULL);

    // test memory deallocation
    stack_push(&s, &value1);
    stack_push(&s, &value2);
    stack_push(&s, &value3);
    assert(stack_size(&s) == 3);
    stack_free(&s);
    assert(stack_size(&s) == 0);
    assert(stack_is_empty(&s));
    assert(s.head == NULL);
    
    printf("Successfully passed all tests\n");
    return 0;
}
