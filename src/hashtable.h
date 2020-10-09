#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include "defs.h"
#include <stdlib.h>

#define HASHTABLE_MIN_SIZE    16
#define HASHTABLE_UNALLOCATED  0
#define HASHTABLE_ALLOCATED    1

typedef struct _HashTableItem
{
    void *key;
    void *value;
    int is_allocated;
    idx key_size;
} HashTableItem;

typedef struct _HashTable
{
    HashTableItem *items;
    idx size;
    idx allocated;
} HashTable;

HashTable *hashtable_new(void);

int hashtable_hash(HashTable *ht, void *key, idx key_size);

idx hashtable_size(HashTable *ht);

int hashtable_is_empty(HashTable *ht);

void **hashtable_keys(HashTable *ht);

void **hashtable_values(HashTable *ht);

void hashtable_resize(HashTable *ht, idx new_size);

void hashtable_resize_up(HashTable *ht);

void hashtable_resize_down(HashTable *ht);

void *hashtable_get(HashTable *ht, void *key, idx key_size);

void hashtable_set(HashTable *ht, void *key, void *value, idx key_size);

void hashtable_extend(HashTable *ht1, HashTable *ht2);

void *hashtable_pop(HashTable *ht, void *key, idx key_size);

void hashtable_delete(HashTable *ht, void *key, idx key_size);

void *hashtable_key(HashTable *ht, void *value);

int hashtable_contains(HashTable *ht, void *key, idx key_size);

int hashtable_count(HashTable *ht, void *value);

int hashtable_equal(HashTable *ht1, HashTable *ht2);

void hashtable_clear(HashTable *ht);

HashTable *hashtable_copy(HashTable *ht);

void hashtable_foreach(HashTable *ht, void (*fptr)(void *, void *, void *), void *args);

void hashtable_free(HashTable *ht);

#endif /* _HASHTABLE_H_ */
