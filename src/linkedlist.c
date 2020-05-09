#include "linkedlist.h"
#include "defs.h"
#include <stdlib.h>

EXPORT LinkedList *linkedlist_new(void)
{
    LinkedList *ll = malloc(sizeof(*ll));
    ll->size = 0;
    ll->head = NULL;
    ll->tail = NULL;
    return ll;
}

EXPORT size_t linkedlist_size(LinkedList *ll)
{
    return ll->size;
}

EXPORT int linkedlist_is_empty(LinkedList *ll)
{
    return ll->size == 0;
}

EXPORT void *linkedlist_get(LinkedList *ll, int index)
{
    if (index < 0 || index >= ll->size)
        return NULL;
    struct LinkedListNode *current = ll->head;
    while (index--)
        current = current->next;
    return current->value;
}

EXPORT void linkedlist_set(LinkedList *ll, int index, void *value)
{
    if (index < 0 || index >= ll->size)
        return;
    struct LinkedListNode *current = ll->head;
    while (index--)
        current = current->next;
    current->value = value;
}

EXPORT void linkedlist_insert(LinkedList *ll, int index, void *value)
{
    if (index < 0 || index > ll->size)
        return;
    struct LinkedListNode *new_node = (struct LinkedListNode *)malloc(sizeof(struct LinkedListNode));
    new_node->value = value;
    if (index == 0)
    {
        new_node->next = ll->head;
        ll->head = new_node;
        if (ll->tail == NULL)
            ll->tail = new_node;
    }
    else if (index == ll->size)
    {
        new_node->next = NULL;
        ll->tail->next = new_node;
        ll->tail = new_node;
    }
    else
    {
        struct LinkedListNode *current = ll->head;
        while (--index)
            current = current->next;
        new_node->next = current->next;
        current->next = new_node;
    }
    ll->size++;
}

EXPORT void linkedlist_append(LinkedList *ll, void *value)
{
    linkedlist_insert(ll, ll->size, value);
}

EXPORT void *linkedlist_pop(LinkedList *ll, int index)
{
    if (index < 0 || index >= ll->size)
        return NULL;
    if (index == 0)
    {
        void *value = ll->head->value;
        struct LinkedListNode *head_next = ll->head->next;
        free(ll->head);
        ll->head = head_next;
        if (head_next == NULL)
            ll->tail = NULL;
        ll->size--;
        return value;
    }
    else
    {
        struct LinkedListNode *current = ll->head;
        while (--index)
            current = current->next;
        void *value = current->next->value;
        struct LinkedListNode *current_next_next = current->next->next;
        free(current->next);
        current->next = current_next_next;
        if (current_next_next == NULL);
            ll->tail = current;
        ll->size--;
        return value;
    }
}

EXPORT void linkedlist_remove(LinkedList *ll, int index)
{
    linkedlist_pop(ll, index);
}

EXPORT void linkedlist_clear(LinkedList *ll)
{
    while (!linkedlist_is_empty(ll))
        linkedlist_pop(ll, 0);
}

EXPORT void linkedlist_foreach(LinkedList *ll, void (*fptr)(void *, void *), void *args)
{
    struct LinkedListNode *current = ll->head;
    while (current != NULL)
    {
        (*fptr)(current->value, args);
        current = current->next;
    }
}

EXPORT void linkedlist_free(LinkedList *ll)
{
    while (ll->head != NULL)
    {
        struct LinkedListNode *head_next = ll->head->next;
        free(ll->head);
        ll->head = head_next;
    }
    free(ll);
}
