#ifndef _STACK_H_
#define _STACK_H_

#include "defs.h"
#include <stdlib.h>

struct StackNode
{
    void *value;
    struct StackNode *next;
};

typedef struct _Stack
{
    struct StackNode *head;
    idx size;
} Stack;

Stack *stack_new(void);

idx stack_size(Stack *s);

int stack_is_empty(Stack *s);

void stack_push(Stack *s, void *value);

void *stack_peek(Stack *s);

void *stack_pop(Stack *s);

void stack_free(Stack *s);

#endif /* _STACK_H_ */
