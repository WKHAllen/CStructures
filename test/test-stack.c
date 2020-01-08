#include "../src/stack.h"
#include <stdio.h>
#include <assert.h>

int main(int argc, char **argv)
{
    printf("Running tests...\n");

    // test initialization
    Stack s = stack_new();
    assert(stack_size(&s) == 0);
    assert(stack_is_empty(&s));
    assert(s.head == NULL);

    // test int push and peek
    int value1 = 7;
    stack_push(&s, &value1, sizeof(value1));
    assert(stack_size(&s) == 1);
    assert(!stack_is_empty(&s));
    assert(*(int *)stack_peek(&s) == value1);

    // test string push and peek
    char *value2 = "hello";
    stack_push(&s, &value2, sizeof(value2));
    assert(stack_size(&s) == 2);
    assert(!stack_is_empty(&s));
    assert(*(char **)stack_peek(&s) == value2);

    // test float push and peek
    float value3 = 3.14;
    stack_push(&s, &value3, sizeof(value3));
    assert(stack_size(&s) == 3);
    assert(!stack_is_empty(&s));
    assert(*(float *)stack_peek(&s) == value3);

    // test float pop
    assert(*(float *)stack_pop(&s) == value3);
    assert(stack_size(&s) == 2);
    assert(!stack_is_empty(&s));

    // test string pop
    assert(*(char **)stack_pop(&s) == value2);
    assert(stack_size(&s) == 1);
    assert(!stack_is_empty(&s));
    
    // test int pop
    assert(*(int *)stack_pop(&s) == value1);
    assert(stack_size(&s) == 0);
    assert(stack_is_empty(&s));

    // test memory deallocation
    stack_push(&s, &value1, sizeof(value1));
    stack_push(&s, &value2, sizeof(value2));
    stack_push(&s, &value3, sizeof(value3));
    stack_free(&s);
    assert(stack_size(&s) == 0);
    assert(stack_is_empty(&s));
    assert(s.head == NULL);
    
    printf("Successfully passed all tests\n");
    return 0;
}
