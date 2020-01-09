#include "../src/queue.h"
#include <stdio.h>
#include <assert.h>

int main(int argc, char **argv)
{
    printf("Running tests...\n");

    // test initialization
    // []
    Queue q = queue_new();
    assert(queue_size(&q) == 0);
    assert(queue_is_empty(&q));
    assert(q.head == NULL);
    assert(q.tail == NULL);

    // test int push and peek
    // [7]
    int value1 = 7;
    queue_push(&q, &value1);
    assert(queue_size(&q) == 1);
    assert(!queue_is_empty(&q));
    assert(*(int *)queue_peek(&q) == value1);

    // test string push and peek
    // [7, "hello"]
    char *value2 = "hello";
    queue_push(&q, &value2);
    assert(queue_size(&q) == 2);
    assert(!queue_is_empty(&q));
    assert(*(int *)queue_peek(&q) == value1);

    // test float push and peek
    // [7, "hello", 3.14]
    float value3 = 3.14;
    queue_push(&q, &value3);
    assert(queue_size(&q) == 3);
    assert(!queue_is_empty(&q));
    assert(*(int *)queue_peek(&q) == value1);

    // test float pop and peek
    // ["hello", 3.14]
    assert(*(int *)queue_pop(&q) == value1);
    assert(queue_size(&q) == 2);
    assert(!queue_is_empty(&q));
    assert(*(char **)queue_peek(&q) == value2);

    // test string pop and peek
    // [3.14]
    assert(*(char **)queue_pop(&q) == value2);
    assert(queue_size(&q) == 1);
    assert(!queue_is_empty(&q));
    assert(*(float *)queue_peek(&q) == value3);
    
    // test int pop and peek
    // []
    assert(*(float *)queue_pop(&q) == value3);
    assert(queue_size(&q) == 0);
    assert(queue_is_empty(&q));
    assert(queue_peek(&q) == NULL);

    // test memory deallocation
    queue_push(&q, &value1);
    queue_push(&q, &value2);
    queue_push(&q, &value3);
    assert(queue_size(&q) == 3);
    queue_free(&q);
    assert(queue_size(&q) == 0);
    assert(queue_is_empty(&q));
    assert(q.head == NULL);
    assert(q.tail == NULL);

    printf("Successfully passed all tests\n");
    return 0;
}
