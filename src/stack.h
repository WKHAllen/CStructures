#ifndef _STACK_H_
#define _STACK_H_

#include <stdlib.h>

struct StackNode
{
    void *value;
    struct StackNode *next;
};

typedef struct
{
    struct StackNode *head;
    size_t size;
} Stack;

Stack stack_new();

size_t stack_size(Stack *s);

int stack_is_empty(Stack *s);

void stack_push(Stack *s, void *value, size_t data_size);

void *stack_peek(Stack *s);

void *stack_pop(Stack *s);

void stack_free(Stack *s);

#endif /* _STACK_H_ */
