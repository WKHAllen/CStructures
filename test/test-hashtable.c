#include "../src/hashtable.h"
#include <stdio.h>
#include <assert.h>

void print_hashtable_int(void *key, void *value, void *_)
{
    printf("%d: %d, ", *(int *)key, *(int *)value);
}

void print_hashtable(HashTable ht)
{
    printf("{ ");
    hashtable_foreach(&ht, print_hashtable_int, NULL);
    if (ht.size == 0)
        printf("}\n");
    else
        printf("\b\b }\n");
}

void sum_ints(void *key, void *value, void *total)
{
    *(int *)total += *(int *)value;
}

int main(int argc, char **argv)
{
    printf("Running tests...\n");

    // test initialization
    // { }
    HashTable ht = hashtable_new();
    assert(hashtable_size(&ht) == 0);
    assert(hashtable_is_empty(&ht));
    assert(ht.size == 0);
    assert(ht.allocated == HASHTABLE_MIN_SIZE);

    // test set
    // { 0: 0, 1: 1, 2: 4, 3: 9, 4: 16, 5: 25, 6: 36, 7: 49, 8: 64, 9: 81, 10: 100, 11: 121, 12: 144, 13: 169, 14: 196, 15: 225 }
    int indices[17];
    int squares[17];
    for (int i = 0; i < 17; i++)
    {
        indices[i] = i;
        squares[i] = i * i;
        if (i < 16)
            hashtable_set(&ht, &(indices[i]), &(squares[i]), sizeof(indices[i]));
    }
    assert(hashtable_size(&ht) == 16);
    assert(!hashtable_is_empty(&ht));
    assert(ht.size == 16);
    assert(ht.allocated == 16);

    // test get
    // { 0: 0, 1: 1, 2: 4, 3: 9, 4: 16, 5: 25, 6: 36, 7: 49, 8: 64, 9: 81, 10: 100, 11: 121, 12: 144, 13: 169, 14: 196, 15: 225 }
    for (int i = 0; i < 16; i++)
        assert(*(int *)hashtable_get(&ht, &(indices[i]), sizeof(indices[i])) == squares[i]);

    // test resize_up
    // { 0: 0, 1: 1, 2: 4, 3: 9, 4: 16, 5: 25, 6: 36, 7: 49, 8: 64, 9: 81, 10: 100, 11: 121, 12: 144, 13: 169, 14: 196, 15: 225, 16: 256 }
    hashtable_set(&ht, &(indices[16]), &(squares[16]), sizeof(indices[16]));
    assert(hashtable_size(&ht) == 17);
    assert(ht.size == 17);
    assert(ht.allocated == 32);
    for (int i = 0; i < 17; i++)
        assert(*(int *)hashtable_get(&ht, &(indices[i]), sizeof(indices[i])) == squares[i]);

    // test pop and resize_down
    // { 0: 0, 1: 1, 2: 4, 3: 9, 4: 16, 5: 25, 6: 36, 7: 49, 8: 64, 9: 81, 10: 100, 11: 121, 12: 144, 13: 169, 14: 196, 15: 225 }
    assert(*(int *)hashtable_pop(&ht, &(indices[16]), sizeof(indices[16])));
    assert(hashtable_size(&ht) == 16);
    assert(ht.size == 16);
    assert(ht.allocated == 16);
    for (int i = 0; i < 16; i++)
        assert(*(int *)hashtable_get(&ht, &(indices[i]), sizeof(indices[i])) == squares[i]);

    // test key
    // { 0: 0, 1: 1, 2: 4, 3: 9, 4: 16, 5: 25, 6: 36, 7: 49, 8: 64, 9: 81, 10: 100, 11: 121, 12: 144, 13: 169, 14: 196, 15: 225 }
    for (int i = 0; i < 16; i++)
        assert(*(int *)hashtable_key(&ht, &(squares[i])) == indices[i]);

    // test copy and equal
    // { 0: 0, 1: 1, 2: 4, 3: 9, 4: 16, 5: 25, 6: 36, 7: 49, 8: 64, 9: 81, 10: 100, 11: 121, 12: 144, 13: 169, 14: 196, 15: 225 }
    HashTable ht2 = hashtable_copy(&ht);
    for (int i = 0; i < 16; i++)
        assert(*(int *)hashtable_get(&ht2, &(indices[i]), sizeof(indices[i])) == squares[i]);
    assert(hashtable_equal(&ht, &ht2));

    // test extend
    // { 0: 0, 1: 1, 2: 4, 3: 21, 4: 16, 5: 25, 6: 36, 7: 49, 8: 64, 9: 81, 10: 100, 11: 121, 12: 144, 13: 169, 14: 196, 15: 225, 16: 37 }
    int ht3value1 = 21;
    int ht3value2 = 37;
    HashTable ht3 = hashtable_new();
    hashtable_set(&ht3, &(indices[3]), &(ht3value1), sizeof(ht3value1));
    hashtable_set(&ht3, &(indices[16]), &(ht3value2), sizeof(ht3value2));
    hashtable_extend(&ht2, &ht3);
    assert(!hashtable_equal(&ht, &ht2));
    assert(!hashtable_equal(&ht, &ht3));
    assert(!hashtable_equal(&ht2, &ht3));
    assert(*(int *)hashtable_get(&ht2, &(indices[3]), sizeof(indices[3])) == ht3value1);
    assert(*(int *)hashtable_get(&ht2, &(indices[16]), sizeof(indices[16])) == ht3value2);
    assert(hashtable_size(&ht2) == 17);

    // test keys and values
    // { 0: 0, 1: 1, 2: 4, 3: 9, 4: 16, 5: 25, 6: 36, 7: 49, 8: 64, 9: 81, 10: 100, 11: 121, 12: 144, 13: 169, 14: 196, 15: 225 }
    int indices2[16];
    int squares2[16];
    for (int i = 0; i < 16; i++)
    {
        indices[i] = i;
        squares[i] = i * i;
    }
    void **ht_keys = hashtable_keys(&ht);
    void **ht_values = hashtable_values(&ht);
    for (int i = 0; i < hashtable_size(&ht); i++)
    {
        indices2[*(int *)(ht_keys[i])] = -1;
        squares2[*(int *)(ht_values[i])] = -1;
    }
    for (int i = 0; i < 16; i++)
    {
        assert(indices2[i] == -1);
        assert(squares2[i] == -1);
    }
    free(ht_keys);
    free(ht_values);

    // test delete
    // { 0: 0, 1: 1, 2: 4, 3: 9, 4: 16, 5: 25, 6: 36, 7: 49, 8: 64, 9: 81, 10: 100, 11: 121, 12: 144, 13: 169, 14: 196, 15: 225, 16: 256 }
    hashtable_set(&ht, &(indices[16]), &(squares[16]), sizeof(indices[16]));
    assert(hashtable_size(&ht) == 17);
    assert(ht.size == 17);
    assert(ht.allocated == 32);
    hashtable_delete(&ht, &(indices[16]), sizeof(indices[16]));
    assert(hashtable_size(&ht) == 16);
    assert(ht.size == 16);
    assert(ht.allocated == 16);
    for (int i = 0; i < 16; i++)
        assert(*(int *)hashtable_get(&ht, &(indices[i]), sizeof(indices[i])) == squares[i]);

    // test contains
    // { 0: 0, 1: 1, 2: 4, 3: 9, 4: 16, 5: 25, 6: 36, 7: 49, 8: 64, 9: 81, 10: 100, 11: 121, 12: 144, 13: 169, 14: 196, 15: 225 }
    for (int i = 0; i < 16; i++)
        assert(hashtable_contains(&ht, &(indices[i]), sizeof(indices[i])));
    assert(!hashtable_contains(&ht, &(indices[16]), sizeof(indices[16])));

    // test count
    // { 0: 0, 1: 1, 2: 4, 3: 9, 4: 16, 5: 25, 6: 36, 7: 49, 8: 64, 9: 81, 10: 100, 11: 121, 12: 144, 13: 169, 14: 196, 15: 225 16: 49}
    for (int i = 0; i < 16; i++)
        assert(hashtable_count(&ht, &(squares[i])) == 1);
    hashtable_set(&ht, &(indices[16]), &(squares[7]), sizeof(indices[16]));
    assert(hashtable_count(&ht, &(squares[7])) == 2);
    assert(hashtable_count(&ht, &(squares[16])) == 0);

    // test clear
    // { }
    hashtable_clear(&ht);
    assert(hashtable_size(&ht) == 0);
    assert(hashtable_is_empty(&ht));
    assert(ht.size == 0);
    assert(ht.allocated == HASHTABLE_MIN_SIZE);

    // test foreach
    int intvals[] = {1, 3, 7, 9};
    int arraylen = sizeof(intvals) / sizeof(intvals[0]);
    int expected = 0;
    for (int i = 0; i < arraylen; i++)
    {
        hashtable_set(&ht, &(indices[i]), &(intvals[i]), sizeof(indices[i]));
        expected += intvals[i];
    }
    int result = 0;
    hashtable_foreach(&ht, sum_ints, &result);
    assert(result == expected);

    // test memory deallocation
    hashtable_free(&ht);
    assert(hashtable_size(&ht) == 0);
    assert(hashtable_is_empty(&ht));
    assert(ht.size == 0);
    assert(ht.allocated == 0);

    printf("Successfully passed all tests\n");
    return 0;
}
