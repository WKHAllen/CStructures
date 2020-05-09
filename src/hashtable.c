#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT __attribute__((visibility("default")))
#endif

EXPORT HashTable hashtable_new(void)
{
    HashTable ht;
    ht.size = 0;
    ht.allocated = HASHTABLE_MIN_SIZE;
    ht.items = (HashTableItem *)malloc(HASHTABLE_MIN_SIZE * sizeof(HashTableItem));
    if (ht.items == NULL)
    {
        printf("Failed to allocate memory while initializing\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < ht.allocated; i++)
        ht.items[i].is_allocated = HASHTABLE_UNALLOCATED;
    return ht;
}

EXPORT int hashtable_hash(HashTable *ht, void *key, size_t key_size)
{
    int hashvalue = 0;
    for (int i = 0; i < sizeof(key_size); i++)
        hashvalue += (int)(*(char *)(&key + i));
    return hashvalue % ht->allocated;
}

EXPORT size_t hashtable_size(HashTable *ht)
{
    return ht->size;
}

EXPORT int hashtable_is_empty(HashTable *ht)
{
    return ht->size == 0;
}

EXPORT void **hashtable_keys(HashTable *ht)
{
    void **ht_keys = (void **)malloc(ht->size * sizeof(void *));
    int found = 0;
    for (int i = 0; i < ht->allocated; i++)
        if (ht->items[i].is_allocated == HASHTABLE_ALLOCATED)
            ht_keys[found++] = ht->items[i].key;
    return ht_keys;
}

EXPORT void **hashtable_values(HashTable *ht)
{
    void **ht_values = malloc(ht->size * sizeof(void *));
    int found = 0;
    for (int i = 0; i < ht->allocated; i++)
        if (ht->items[i].is_allocated == HASHTABLE_ALLOCATED)
            ht_values[found++] = ht->items[i].key;
    return ht_values;
}

EXPORT void hashtable_resize(HashTable *ht, size_t new_size)
{
    void **ht_keys = malloc(ht->size * sizeof(void *));
    void **ht_values = malloc(ht->size * sizeof(void *));
    size_t *ht_key_sizes = malloc(ht->size * sizeof(size_t));
    int found = 0;
    for (int i = 0; i < ht->allocated; i++)
    {
        if (ht->items[i].is_allocated == HASHTABLE_ALLOCATED)
        {
            ht_keys[found] = ht->items[i].key;
            ht_values[found] = ht->items[i].value;
            ht_key_sizes[found] = ht->items[i].key_size;
            found++;
        }
    }
    ht->items = (HashTableItem *)realloc(ht->items, new_size * sizeof(HashTableItem));
    if (ht->items == NULL)
    {
        printf("Failed to reallocate memory while resizing\n");
        exit(EXIT_FAILURE);
    }
    ht->allocated = new_size;
    ht->size = 0;
    for (int i = 0; i < ht->allocated; i++)
        ht->items[i].is_allocated = HASHTABLE_UNALLOCATED;
    for (int i = 0; i < found; i++)
        hashtable_set(ht, ht_keys[i], ht_values[i], ht_key_sizes[i]);
    free(ht_keys);
    free(ht_values);
    free(ht_key_sizes);
}

EXPORT void hashtable_resize_up(HashTable *ht)
{
    size_t new_size = ht->allocated * 2;
    hashtable_resize(ht, new_size);
}

EXPORT void hashtable_resize_down(HashTable *ht)
{
    size_t new_size = ht->allocated / 2;
    if (new_size < HASHTABLE_MIN_SIZE)
        new_size = HASHTABLE_MIN_SIZE;
    hashtable_resize(ht, new_size);
}

EXPORT void *hashtable_get(HashTable *ht, void *key, size_t key_size)
{
    int hashvalue = hashtable_hash(ht, key, key_size);
    int current;
    for (int i = 0; i < ht->allocated; i++)
    {
        current = (hashvalue + i) % ht->allocated;
        if (key == ht->items[current].key && ht->items[current].is_allocated == HASHTABLE_ALLOCATED)
            return ht->items[current].value;
    }
    return NULL;
}

EXPORT void hashtable_set(HashTable *ht, void *key, void *value, size_t key_size)
{
    int hashvalue = hashtable_hash(ht, key, key_size);
    int current;
    for (int i = 0; i < ht->allocated; i++)
    {
        current = (hashvalue + i) % ht->allocated;
        if (ht->items[current].is_allocated == HASHTABLE_UNALLOCATED)
        {
            ht->items[current].key = key;
            ht->items[current].value = value;
            ht->items[current].is_allocated = HASHTABLE_ALLOCATED;
            ht->items[current].key_size = key_size;
            ht->size++;
            return;
        }
        else if (key == ht->items[current].key)
        {
            ht->items[current].value = value;
            return;
        }
    }
    hashtable_resize_up(ht);
    hashtable_set(ht, key, value, key_size);
}

EXPORT void hashtable_extend(HashTable *ht1, HashTable *ht2)
{
    for (int i = 0; i < ht2->allocated; i++)
        if (ht2->items[i].is_allocated)
            hashtable_set(ht1, ht2->items[i].key, ht2->items[i].value, ht2->items[i].key_size);
}

EXPORT void *hashtable_pop(HashTable *ht, void *key, size_t key_size)
{
    int hashvalue = hashtable_hash(ht, key, key_size);
    int current;
    for (int i = 0; i < ht->allocated; i++)
    {
        current = (hashvalue + i) % ht->allocated;
        if (key == ht->items[current].key && ht->items[current].is_allocated == HASHTABLE_ALLOCATED)
        {
            ht->items[current].is_allocated = HASHTABLE_UNALLOCATED;
            ht->size--;
            if (ht->size <= ht->allocated / 2 && ht->allocated > HASHTABLE_MIN_SIZE)
                hashtable_resize_down(ht);
            return ht->items[current].value;
        }
    }
    return NULL;
}

EXPORT void hashtable_delete(HashTable *ht, void *key, size_t key_size)
{
    hashtable_pop(ht, key, key_size);
}

EXPORT void *hashtable_key(HashTable *ht, void *value)
{
    for (int i = 0; i < ht->allocated; i++)
        if (value == ht->items[i].value && ht->items[i].is_allocated == HASHTABLE_ALLOCATED)
            return ht->items[i].key;
    return NULL;
}

EXPORT int hashtable_contains(HashTable *ht, void *key, size_t key_size)
{
    int hashvalue = hashtable_hash(ht, key, key_size);
    int current;
    for (int i = 0; i < ht->allocated; i++)
    {
        current = (hashvalue + i) % ht->allocated;
        if (key == ht->items[current].key && ht->items[current].is_allocated == HASHTABLE_ALLOCATED)
            return 1;
    }
    return 0;
}

EXPORT int hashtable_count(HashTable *ht, void *value)
{
    int count = 0;
    for (int i = 0; i < ht->allocated; i++)
        if (value == ht->items[i].value && ht->items[i].is_allocated == HASHTABLE_ALLOCATED)
            count++;
    return count;
}

EXPORT int hashtable_equal(HashTable *ht1, HashTable *ht2)
{
    if (ht1->size != ht2->size)
        return 0;
    for (int i = 0; i < ht1->allocated; i++)
        if (ht1->items[i].is_allocated == HASHTABLE_ALLOCATED && (!hashtable_contains(ht2, ht1->items[i].key, ht1->items[i].key_size) || ht1->items[i].value != hashtable_get(ht2, ht1->items[i].key, ht1->items[i].key_size)))
            return 0;
    return 1;
}

EXPORT void hashtable_clear(HashTable *ht)
{
    ht->items = (HashTableItem *)realloc(ht->items, HASHTABLE_MIN_SIZE * sizeof(HashTableItem));
    ht->size = 0;
    ht->allocated = HASHTABLE_MIN_SIZE;
    for (int i = 0; i < ht->allocated; i++)
        ht->items[i].is_allocated = HASHTABLE_UNALLOCATED;
}

EXPORT HashTable hashtable_copy(HashTable *ht)
{
    HashTable new_hashtable = hashtable_new();
    for (int i = 0; i < ht->allocated; i++)
        if (ht->items[i].is_allocated == HASHTABLE_ALLOCATED)
            hashtable_set(&new_hashtable, ht->items[i].key, ht->items[i].value, ht->items[i].key_size);
    return new_hashtable;
}

EXPORT void hashtable_foreach(HashTable *ht, void (*fptr)(void *, void *, void *), void *args)
{
    for (int i = 0; i < ht->allocated; i++)
        if (ht->items[i].is_allocated)
            (*fptr)(ht->items[i].key, ht->items[i].value, args);
}

EXPORT void hashtable_free(HashTable *ht)
{
    free(ht->items);
    ht->size = 0;
    ht->allocated = 0;
}
