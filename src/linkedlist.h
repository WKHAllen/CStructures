#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <stdlib.h>

struct LinkedListNode
{
    void *value;
    struct LinkedListNode *next;
};

typedef struct _LinkedList
{
    struct LinkedListNode *head;
    struct LinkedListNode *tail;
    size_t size;
} LinkedList;

LinkedList *linkedlist_new(void);

size_t linkedlist_size(LinkedList *ll);

int linkedlist_is_empty(LinkedList *ll);

void *linkedlist_get(LinkedList *ll, int index);

void linkedlist_set(LinkedList *ll, int index, void *value);

void linkedlist_insert(LinkedList *ll, int index, void *value);

void linkedlist_append(LinkedList *ll, void *value);

void *linkedlist_pop(LinkedList *ll, int index);

void linkedlist_remove(LinkedList *ll, int index);

void linkedlist_clear(LinkedList *ll);

void linkedlist_foreach(LinkedList *ll, void (*fptr)(void *, void *), void *args);

void linkedlist_free(LinkedList *ll);

#endif /* _LINKEDLIST_H_ */
