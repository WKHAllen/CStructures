#include "list.h"
#include "defs.h"
#include <stdlib.h>

EXPORT List *list_new(void)
{
    List *l = malloc(sizeof(List));
    l->items = malloc(LIST_MIN_SIZE * sizeof(void *));
    l->size = 0;
    l->allocated = 1;
    return l;
}

EXPORT idx list_size(List *l)
{
    return l->size;
}

EXPORT int list_is_empty(List *l)
{
    return l->size == 0;
}

EXPORT void list_resize(List *l, idx new_size)
{
    l->items = realloc(l->items, new_size * sizeof(void *));
    l->allocated = new_size;
}

EXPORT void list_resize_up(List *l)
{
    idx new_size = l->allocated * 2;
    list_resize(l, new_size);
}

EXPORT void list_resize_down(List *l)
{
    idx new_size = l->allocated / 2;
    if (new_size < LIST_MIN_SIZE)
        new_size = LIST_MIN_SIZE;
    list_resize(l, new_size);
}

EXPORT void *list_get(List *l, idx index)
{
    if (index < 0)
        index += l->size;
    if (index < 0 || index >= l->size)
        return NULL;
    return l->items[index];
}

EXPORT void list_set(List *l, idx index, void *value)
{
    if (index < 0)
        index += l->size;
    if (index < 0 || index >= l->size)
        return;
    l->items[index] = value;
}

EXPORT void list_append(List *l, void *value)
{
    if (l->size >= l->allocated)
        list_resize_up(l);
    l->items[l->size] = value;
    l->size++;
}

EXPORT void list_extend(List *l1, List *l2)
{
    for (idx i = 0; i < l2->size; i++)
        list_append(l1, l2->items[i]);
}

EXPORT void list_insert(List *l, idx index, void *value)
{
    if (index < 0)
        index += l->size;
    if (index < 0 || index > l->size)
        return;
    if (l->size >= l->allocated)
        list_resize_up(l);
    for (idx i = l->size - 1; i >= index; i--)
        l->items[i + 1] = l->items[i];
    l->items[index] = value;
    l->size++;
}

EXPORT void *list_pop(List *l, idx index)
{
    if (index < 0)
        index += l->size;
    if (index < 0 || index >= l->size)
        return NULL;
    void *value = l->items[index];
    for (idx i = index + 1; i < l->size; i++)
        l->items[i - 1] = l->items[i];
    if (l->size <= l->allocated / 2 && l->allocated > LIST_MIN_SIZE)
        list_resize_down(l);
    l->size--;
    return value;
}

EXPORT void list_delete(List *l, idx index)
{
    list_pop(l, index);
}

EXPORT List *list_slice(List *l, idx index1, idx index2)
{
    List *lslice = list_new();
    if (index1 < 0)
        index1 += l->size;
    if (index2 < 0)
        index2 += l->size;
    if (index1 < 0 || index1 > l->size || index2 < 0 || index2 > l->size)
        return lslice;
    while (index1++ < index2) {
        list_append(lslice, l->items[index1 - 1]);
    }
    return lslice;
}

EXPORT idx list_index(List *l, void *value)
{
    for (idx i = 0; i < l->size; i++)
        if (l->items[i] == value)
            return i;
    return -1;
}

EXPORT int list_count(List *l, void *value)
{
    int total = 0;
    for (idx i = 0; i < l->size; i++)
        if (l->items[i] == value)
            total++;
    return total;
}

EXPORT void list_remove(List *l, void *value)
{
    idx index = list_index(l, value);
    if (index != -1)
        list_delete(l, index);
}

EXPORT void list_remove_all(List *l, void *value)
{
    for (idx i = 0; i < l->size; i++)
        if (l->items[i] == value)
            list_delete(l, i--);
}

EXPORT void list_replace(List *l, void *value1, void *value2)
{
    idx index = list_index(l, value1);
    if (index != -1)
        l->items[index] = value2;
}

EXPORT void list_replace_all(List *l, void *value1, void *value2)
{
    for (idx i = 0; i < l->size; i++)
        if (l->items[i] == value1)
            l->items[i] = value2;
}

EXPORT int list_equal(List *l1, List *l2)
{
    if (l1->size != l2->size)
        return 0;
    for (idx i = 0; i < l1->size; i++)
        if (l1->items[i] != l2->items[i])
            return 0;
    return 1;
}

EXPORT void list_clear(List *l)
{
    l->items = realloc(l->items, sizeof(void *));
    l->size = 0;
    l->allocated = 1;
}

EXPORT List *list_copy(List *l)
{
    List *new_list = list_new();
    for (idx i = 0; i < l->size; i++)
        list_append(new_list, l->items[i]);
    return new_list;
}

EXPORT void list_reverse(List *l)
{
    void *tmp;
    for (idx i = 0; i < l->size / 2; i++)
    {
        tmp = l->items[i];
        l->items[i] = l->items[l->size - i - 1];
        l->items[l->size - i - 1] = tmp;
    }
}

EXPORT void list_foreach(List *l, void (*fptr)(void *, void *), void *args)
{
    for (idx i = 0; i < l->size; i++)
        (*fptr)(l->items[i], args);
}

EXPORT void list_free(List *l)
{
    free(l->items);
    free(l);
}
