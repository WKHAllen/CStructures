#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "defs.h"
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
    idx size;
} Queue;

Queue *queue_new(void);

idx queue_size(Queue *q);

int queue_is_empty(Queue *q);

void queue_push(Queue *q, void *value);

void *queue_peek(Queue *q);

void *queue_pop(Queue *q);

void queue_free(Queue *q);

#endif /* _QUEUE_H_ */
