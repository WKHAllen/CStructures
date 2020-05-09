#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdlib.h>

struct QueueNode
{
    void *value;
    struct QueueNode *next;
};

typedef struct _Queue
{
    struct QueueNode *head;
    struct QueueNode *tail;
    size_t size;
} Queue;

Queue *queue_new(void);

size_t queue_size(Queue *q);

int queue_is_empty(Queue *q);

void queue_push(Queue *q, void *value);

void *queue_peek(Queue *q);

void *queue_pop(Queue *q);

void queue_free(Queue *q);

#endif /* _QUEUE_H_ */
