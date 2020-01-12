#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

Queue queue_new(void)
{
    Queue q;
    q.size = 0;
    q.head = NULL;
    q.tail = NULL;
    return q;
}

size_t queue_size(Queue *q)
{
    return q->size;
}

int queue_is_empty(Queue *q)
{
    return q->size == 0;
}

void queue_push(Queue *q, void *value)
{
    struct QueueNode *new_node = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    if (new_node == NULL)
    {
        printf("Failed to allocate memory to new node\n");
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = NULL;
    if (q->tail != NULL)
        q->tail->next = new_node;
    else
        q->head = new_node;
    q->tail = new_node;
    q->size++;
}

void *queue_peek(Queue *q)
{
    if (q->head != NULL)
        return q->head->value;
    return NULL;
}

void *queue_pop(Queue *q)
{
    if (q->head != NULL)
    {
        void *value = q->head->value;
        struct QueueNode *head_next = q->head->next;
        free(q->head);
        q->head = head_next;
        if (head_next == NULL)
            q->tail = NULL;
        q->size--;
        return value;
    }
    return NULL;
}

void queue_free(Queue *q)
{
    while (q->head != NULL)
    {
        struct QueueNode *head_next = q->head->next;
        free(q->head);
        q->head = head_next;
    }
    q->tail = NULL;
    q->size = 0;
}