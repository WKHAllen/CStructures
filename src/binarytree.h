#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include <stdlib.h>

struct BinaryTree
{
    void *value;
    struct BinaryTree *left;
    struct BinaryTree *right;
    struct BinaryTree *parent;
};

struct BinaryTree *binarytree_new(void);

void *binarytree_get_value(struct BinaryTree *bt);

void binarytree_set_value(struct BinaryTree *bt, void *value);

int binarytree_has_left(struct BinaryTree *bt);

void *binarytree_get_left(struct BinaryTree *bt);

struct BinaryTree *binarytree_get_left_node(struct BinaryTree *bt);

void binarytree_set_left(struct BinaryTree *bt, void *value);

void binarytree_set_left_node(struct BinaryTree *bt, struct BinaryTree *left);

void *binarytree_pop_left(struct BinaryTree *bt);

struct BinaryTree *binarytree_pop_left_node(struct BinaryTree *bt);

int binarytree_has_right(struct BinaryTree *bt);

void *binarytree_get_right(struct BinaryTree *bt);

struct BinaryTree *binarytree_get_right_node(struct BinaryTree *bt);

void binarytree_set_right(struct BinaryTree *bt, void *value);

void binarytree_set_right_node(struct BinaryTree *bt, struct BinaryTree *right);

void *binarytree_pop_right(struct BinaryTree *bt);

struct BinaryTree *binarytree_pop_right_node(struct BinaryTree *bt);

int binarytree_has_parent(struct BinaryTree *bt);

struct BinaryTree *binarytree_get_parent(struct BinaryTree *bt);

void binarytree_set_parent(struct BinaryTree *bt, void *value);

int binarytree_is_root(struct BinaryTree *bt);

void binarytree_clear(struct BinaryTree *bt);

void binarytree_free(struct BinaryTree *bt);

#endif /* _BINARYTREE_H_ */
