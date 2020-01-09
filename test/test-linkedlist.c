#include "../src/linkedlist.h"
#include <stdio.h>
#include <assert.h>

void sum_ints(void *value, void *total)
{
    *(int *)total += *(int *)value;
}

int main(int argc, char **argv)
{
    printf("Running tests...\n");

    // test initialization
    // []
    LinkedList ll = linkedlist_new();
    assert(linkedlist_size(&ll) == 0);
    assert(linkedlist_is_empty(&ll));
    assert(ll.head == NULL);
    assert(ll.tail == NULL);

    // test int append and get
    // [7]
    int value1 = 7;
    linkedlist_append(&ll, &value1);
    assert(linkedlist_size(&ll) == 1);
    assert(!linkedlist_is_empty(&ll));
    assert(*(int *)linkedlist_get(&ll, 0) == value1);

    // test string append and get
    // [7, "hello"]
    char *value2 = "hello";
    linkedlist_append(&ll, &value2);
    assert(linkedlist_size(&ll) == 2);
    assert(!linkedlist_is_empty(&ll));
    assert(*(char **)linkedlist_get(&ll, 1) == value2);

    // test float append and get
    // [7, "hello", 3.14]
    float value3 = 3.14;
    linkedlist_append(&ll, &value3);
    assert(linkedlist_size(&ll) == 3);
    assert(!linkedlist_is_empty(&ll));
    assert(*(float *)linkedlist_get(&ll, 2) == value3);

    // test set
    // [7, "hello", 'C']
    char value4 = 'C';
    linkedlist_set(&ll, 2, &value4);
    assert(linkedlist_size(&ll) == 3);
    assert(!linkedlist_is_empty(&ll));
    assert(*(float *)linkedlist_get(&ll, 2) != value3);
    assert(*(char *)linkedlist_get(&ll, 2) == value4);

    // test insert at start
    // [2.718, 7, "hello", 'C']
    float value5 = 2.718;
    linkedlist_insert(&ll, 0, &value5);
    assert(linkedlist_size(&ll) == 4);
    assert(!linkedlist_is_empty(&ll));
    assert(*(float *)linkedlist_get(&ll, 0) == value5);
    assert(*(int *)linkedlist_get(&ll, 1) == value1);

    // test insert at end
    // [2.718, 7, "hello", 'C', 1.618]
    float value6 = 1.618;
    linkedlist_insert(&ll, linkedlist_size(&ll), &value6);
    assert(linkedlist_size(&ll) == 5);
    assert(!linkedlist_is_empty(&ll));
    assert(*(float *)linkedlist_get(&ll, linkedlist_size(&ll) - 1) == value6);
    assert(*(char *)linkedlist_get(&ll, linkedlist_size(&ll) - 2) == value4);

    // test insert in the middle
    // [2.718, 7, "hello", 1.306377, 'C', 1.618]
    float value7 = 1.306377;
    linkedlist_insert(&ll, 3, &value7);
    assert(linkedlist_size(&ll) == 6);
    assert(!linkedlist_is_empty(&ll));
    assert(*(float *)linkedlist_get(&ll, 3) == value7);
    assert(*(char **)linkedlist_get(&ll, 2) == value2);
    assert(*(char *)linkedlist_get(&ll, 4) == value4);

    // test pop at start
    // [7, "hello", 1.306377, 'C', 1.618]
    assert(*(float *)linkedlist_pop(&ll, 0) == value5);
    assert(linkedlist_size(&ll) == 5);
    assert(!linkedlist_is_empty(&ll));
    assert(*(int *)linkedlist_get(&ll, 0) == value1);

    // test pop at end
    // [7, "hello", 1.306377, 'C']
    assert(*(float *)linkedlist_pop(&ll, linkedlist_size(&ll) - 1) == value6);
    assert(linkedlist_size(&ll) == 4);
    assert(!linkedlist_is_empty(&ll));
    assert(*(char *)linkedlist_get(&ll, linkedlist_size(&ll) - 1) == value4);

    // test pop in the middle
    // [7, "hello", 'C']
    assert(*(float *)linkedlist_pop(&ll, 2) == value7);
    assert(linkedlist_size(&ll) == 3);
    assert(!linkedlist_is_empty(&ll));
    assert(*(char **)linkedlist_get(&ll, 1) == value2);
    assert(*(char *)linkedlist_get(&ll, 2) == value4);

    // test remove
    // [7, 'C']
    linkedlist_remove(&ll, 1);
    assert(linkedlist_size(&ll) == 2);
    assert(!linkedlist_is_empty(&ll));
    assert(*(int *)linkedlist_get(&ll, 0) == value1);
    assert(*(char *)linkedlist_get(&ll, 1) == value4);

    // test clear
    // []
    linkedlist_clear(&ll);
    assert(linkedlist_size(&ll) == 0);
    assert(linkedlist_is_empty(&ll));
    assert(ll.head == NULL);
    assert(ll.tail == NULL);

    // test foreach
    int intvals[] = {1, 3, 7, 9};
    int arraylen = sizeof(intvals) / sizeof(intvals[0]);
    int expected = 0;
    for (int i = 0; i < arraylen; i++)
    {
        linkedlist_append(&ll, &(intvals[i]));
        expected += intvals[i];
    }
    int result = 0;
    linkedlist_foreach(&ll, sum_ints, &result);
    assert(result == expected);

    // test memory deallocation
    assert(linkedlist_size(&ll) == arraylen);
    linkedlist_free(&ll);
    assert(linkedlist_size(&ll) == 0);
    assert(linkedlist_is_empty(&ll));
    assert(ll.head == NULL);
    assert(ll.tail == NULL);

    printf("Successfully passed all tests\n");
    return 0;
}
