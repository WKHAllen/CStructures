#include "../src/list.h"
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
    List l = list_new();
    assert(list_size(&l) == 0);
    assert(list_is_empty(&l));
    assert(sizeof(l.items) / sizeof(l.items[0]) == 1);
    assert(l.size == 0);
    assert(l.allocated == 1);

    // test int append and get
    // [7]
    int value1 = 7;
    list_append(&l, &value1);
    assert(list_size(&l) == 1);
    assert(!list_is_empty(&l));
    assert(*(int *)list_get(&l, 0) == value1);

    // test string append and get
    // [7, "hello"]
    char *value2 = "hello";
    list_append(&l, &value2);
    assert(list_size(&l) == 2);
    assert(!list_is_empty(&l));
    assert(*(char **)list_get(&l, 1) == value2);

    // test float append and get
    // [7, "hello", 3.14]
    float value3 = 3.14;
    list_append(&l, &value3);
    assert(list_size(&l) == 3);
    assert(!list_is_empty(&l));
    assert(*(float *)list_get(&l, 2) == value3);

    // test set
    // [7, "hello", 'C']
    char value4 = 'C';
    list_set(&l, 2, &value4);
    assert(list_size(&l) == 3);
    assert(!list_is_empty(&l));
    assert(*(float *)list_get(&l, 2) != value3);
    assert(*(char *)list_get(&l, 2) == value4);

    // test insert at start
    // [2.718, 7, "hello", 'C']
    float value5 = 2.718;
    list_insert(&l, 0, &value5);
    assert(list_size(&l) == 4);
    assert(!list_is_empty(&l));
    assert(*(float *)list_get(&l, 0) == value5);
    assert(*(int *)list_get(&l, 1) == value1);

    // test insert at end
    // [2.718, 7, "hello", 'C', 1.618]
    float value6 = 1.618;
    list_insert(&l, list_size(&l), &value6);
    assert(list_size(&l) == 5);
    assert(!list_is_empty(&l));
    assert(*(float *)list_get(&l, list_size(&l) - 1) == value6);
    assert(*(char *)list_get(&l, list_size(&l) - 2) == value4);

    // test insert in the middle
    // [2.718, 7, "hello", 1.306377, 'C', 1.618]
    float value7 = 1.306377;
    list_insert(&l, 3, &value7);
    assert(list_size(&l) == 6);
    assert(!list_is_empty(&l));
    assert(*(float *)list_get(&l, 3) == value7);
    assert(*(char **)list_get(&l, 2) == value2);
    assert(*(char *)list_get(&l, 4) == value4);

    // test pop at start
    // [7, "hello", 1.306377, 'C', 1.618]
    assert(*(float *)list_pop(&l, 0) == value5);
    assert(list_size(&l) == 5);
    assert(!list_is_empty(&l));
    assert(*(int *)list_get(&l, 0) == value1);

    // test pop at end
    // [7, "hello", 1.306377, 'C']
    assert(*(float *)list_pop(&l, list_size(&l) - 1) == value6);
    assert(list_size(&l) == 4);
    assert(!list_is_empty(&l));
    assert(*(char *)list_get(&l, list_size(&l) - 1) == value4);

    // test pop in the middle
    // [7, "hello", 'C']
    assert(*(float *)list_pop(&l, 2) == value7);
    assert(list_size(&l) == 3);
    assert(!list_is_empty(&l));
    assert(*(char **)list_get(&l, 1) == value2);
    assert(*(char *)list_get(&l, 2) == value4);

    // test extend
    // [7, "hello", 'C', 2.718, 1.618, 1.306377]
    List l2 = list_new();
    list_append(&l2, &value5);
    list_append(&l2, &value6);
    list_append(&l2, &value7);
    list_extend(&l, &l2);
    assert(*(int *)list_get(&l, 0) == value1);
    assert(*(char **)list_get(&l, 1) == value2);
    assert(*(char *)list_get(&l, 2) == value4);
    assert(*(float *)list_get(&l, 3) == value5);
    assert(*(float *)list_get(&l, 4) == value6);
    assert(*(float *)list_get(&l, 5) == value7);

    // test index
    // [7, "hello", 'C', 2.718, 1.618, 1.306377]
    assert(list_index(&l, &value1) == 0);
    assert(list_index(&l, &value2) == 1);
    assert(list_index(&l, &value3) == -1);
    assert(list_index(&l, &value4) == 2);
    assert(list_index(&l, &value5) == 3);
    assert(list_index(&l, &value6) == 4);
    assert(list_index(&l, &value7) == 5);

    // test count
    // [7, "hello", 'C', 2.718, 1.618, 1.306377, 'C']
    list_append(&l, &value4);
    assert(list_count(&l, &value3) == 0);
    assert(list_count(&l, &value5) == 1);
    assert(list_count(&l, &value4) == 2);

    // test replace
    // [7, "hello", 'C', 1.306377, 1.618, 1.306377, 'C']
    list_replace(&l, &value5, &value7);
    assert(*(float *)list_get(&l, 3) == value7);

    // test replace_all
    // [7, "hello", 'C', 2.718, 1.618, 2.718, 'C']
    list_replace_all(&l, &value7, &value5);
    assert(*(float *)list_get(&l, 3) == value5);
    assert(*(float *)list_get(&l, 5) == value5);

    // test remove
    // [7, "hello", 'C', 1.618, 2.718, 'C']
    list_remove(&l, &value5);
    assert(list_index(&l, &value5) == 4);
    assert(*(float *)list_get(&l, 3) == value6);

    // test remove_all
    // [7, "hello", 1.618, 2.718]
    list_remove_all(&l, &value4);
    assert(list_index(&l, &value4) == -1);
    assert(*(float *)list_get(&l, 2) == value6);
    assert(list_get(&l, 5) == NULL);

    // test copy
    // [7, "hello", 1.618, 2.718]
    List l3 = list_copy(&l);
    assert(list_size(&l3) == 4);
    assert(!list_is_empty(&l3));
    assert(*(int *)list_get(&l3, 0) == value1);
    assert(*(char **)list_get(&l3, 1) == value2);
    assert(*(float *)list_get(&l3, 2) == value6);
    assert(*(float *)list_get(&l3, 3) == value5);

    // test equal
    // [7, "hello", 1.618, 2.718]
    assert(!list_equal(&l, &l2));
    assert(list_equal(&l, &l3));
    List l4 = list_new();
    list_append(&l4, &value1);
    list_append(&l4, &value2);
    list_append(&l4, &value6);
    list_append(&l4, &value5);
    assert(list_equal(&l, &l4));
    assert(list_equal(&l3, &l4));

    // test slice
    // ["hello", 1.618]
    List l5 = list_slice(&l, 1, 3);
    assert(list_size(&l5) == 2);
    assert(!list_is_empty(&l5));
    assert(*(char **)list_get(&l5, 0) == value2);
    assert(*(float *)list_get(&l5, 1) == value6);
    assert(!list_equal(&l, &l5));
    List l6 = list_slice(&l, 0, list_size(&l));
    assert(list_size(&l6) == 4);
    assert(!list_is_empty(&l6));
    assert(*(int *)list_get(&l3, 0) == value1);
    assert(*(char **)list_get(&l3, 1) == value2);
    assert(*(float *)list_get(&l3, 2) == value6);
    assert(*(float *)list_get(&l3, 3) == value5);
    assert(list_equal(&l, &l6));
    assert(!list_equal(&l5, &l6));

    // test reverse
    // [2.718, 1.618, "hello", 7]
    list_reverse(&l);
    assert(*(float *)list_get(&l, 0) == value5);
    assert(*(float *)list_get(&l, 1) == value6);
    assert(*(char **)list_get(&l, 2) == value2);
    assert(*(int *)list_get(&l, 3) == value1);
    assert(!list_equal(&l, &l3));
    assert(!list_equal(&l, &l4));
    assert(list_equal(&l3, &l4));
    list_reverse(&l3);
    assert(list_equal(&l, &l3));
    assert(!list_equal(&l, &l4));
    assert(!list_equal(&l3, &l4));
    list_reverse(&l);
    assert(!list_equal(&l, &l3));
    assert(list_equal(&l, &l4));
    assert(!list_equal(&l3, &l4));

    // test delete
    // [7, "hello", 2.718]
    list_delete(&l, 2);
    assert(list_size(&l) == 3);
    assert(!list_is_empty(&l));
    assert(*(int *)list_get(&l, 0) == value1);
    assert(*(char **)list_get(&l, 1) == value2);
    assert(*(float *)list_get(&l, 2) == value5);

    // test clear
    // []
    list_clear(&l);
    assert(list_size(&l) == 0);
    assert(list_is_empty(&l));
    assert(l.size == 0);
    assert(l.allocated == 1);

    // test foreach
    int intvals[] = {1, 3, 7, 9};
    int arraylen = sizeof(intvals) / sizeof(intvals[0]);
    int expected = 0;
    for (int i = 0; i < arraylen; i++)
    {
        list_append(&l, &(intvals[i]));
        expected += intvals[i];
    }
    int result = 0;
    list_foreach(&l, sum_ints, &result);
    assert(result == expected);

    // test memory deallocation
    list_free(&l);
    assert(list_size(&l) == 0);
    assert(list_is_empty(&l));
    assert(l.size == 0);
    assert(l.allocated == 0);

    printf("Successfully passed all tests\n");
    return 0;
}
