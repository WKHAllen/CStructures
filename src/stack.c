#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack stack_new(void)
{
    Stack s;
    s.size = 0;
    s.head = NULL;
    return s;
}

size_t stack_size(Stack *s)
{
    return s->size;
}

int stack_is_empty(Stack *s)
{
    return s->size == 0;
}

void stack_push(Stack *s, void *value)
{
    struct StackNode *new_node = (struct StackNode *)malloc(sizeof(struct StackNode));
    if (new_node == NULL)
    {
        printf("Failed to allocate memory to new node\n");
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = s->head;
    s->head = new_node;
    s->size++;
}

void *stack_peek(Stack *s)
{
    if (s->head != NULL)
        return s->head->value;
    return NULL;
}

void *stack_pop(Stack *s)
{
    if (s->head != NULL)
    {
        void *value = s->head->value;
        struct StackNode *head_next = s->head->next;
        free(s->head);
        s->head = head_next;
        s->size--;
        return value;
    }
    return NULL;
}

void stack_free(Stack *s)
{
    while (s->head != NULL)
    {
        struct StackNode *head_next = s->head->next;
        free(s->head);
        s->head = head_next;
    }
    s->size = 0;
}
