#ifndef _LIST_H_
#define _LIST_H_

#include <stdlib.h>

#define LIST_MIN_SIZE 1

typedef struct
{
    void **items;
    size_t size;
    size_t allocated;
} List;

List list_new(void);

size_t list_size(List *l);

int list_is_empty(List *l);

void list_resize(List *l, size_t new_size);

void list_resize_up(List *l);

void list_resize_down(List *l);

void *list_get(List *l, int index);

void list_set(List *l, int index, void *value);

void list_append(List *l, void *value);

void list_extend(List *l1, List *l2);

void list_insert(List *l, int index, void *value);

void *list_pop(List *l, int index);

void list_delete(List *l, int index);

List list_slice(List *l, int index1, int index2);

int list_index(List *l, void *value);

int list_count(List *l, void *value);

void list_remove(List *l, void *value);

void list_remove_all(List *l, void *value);

void list_replace(List *l, void *value1, void *value2);

void list_replace_all(List *l, void *value1, void *value2);

int list_equal(List *l1, List *l2);

void list_clear(List *l);

List list_copy(List *l);

void list_reverse(List *l);

void list_foreach(List *l, void (*fptr)(void *, void *), void *args);

void list_free(List *l);

#endif /* _LIST_H_ */
