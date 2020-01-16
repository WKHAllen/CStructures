#include "binarytree.h"
#include <stdio.h>
#include <stdlib.h>

struct BinaryTree binarytree_new(void)
{
    struct BinaryTree bt;
    bt.value = NULL;
    bt.left = NULL;
    bt.right = NULL;
    bt.parent = NULL;
    return bt;
}

void *binarytree_get_value(struct BinaryTree *bt)
{
    return bt->value;
}

void binarytree_set_value(struct BinaryTree *bt, void *value)
{
    bt->value = value;
}

int binarytree_has_left(struct BinaryTree *bt)
{
    return bt->left != NULL;
}

void *binarytree_get_left(struct BinaryTree *bt)
{
    if (bt->left == NULL)
        return NULL;
    return bt->left->value;
}

struct BinaryTree *binarytree_get_left_node(struct BinaryTree *bt)
{
    return bt->left;
}

void binarytree_set_left(struct BinaryTree *bt, void *value)
{
    if (bt->left == NULL)
    {
        struct BinaryTree bt_left = binarytree_new();
        binarytree_set_left_node(bt, &bt_left);
    }
    bt->left->value = value;
}

void binarytree_set_left_node(struct BinaryTree *bt, struct BinaryTree *left)
{
    bt->left = left;
    left->parent = bt;
}

void *binarytree_pop_left(struct BinaryTree *bt)
{
    if (bt->left == NULL)
        return NULL;
    void *value = binarytree_get_left(bt);
    bt->left->parent = NULL;
    bt->left = NULL;
    return value;
}

struct BinaryTree *binarytree_pop_left_node(struct BinaryTree *bt)
{
    if (bt->left == NULL)
        return NULL;
    struct BinaryTree *bt_left = binarytree_get_left_node(bt);
    bt->left->parent = NULL;
    bt->left = NULL;
    return bt_left;
}

int binarytree_has_right(struct BinaryTree *bt)
{
    return bt->right != NULL;
}

void *binarytree_get_right(struct BinaryTree *bt)
{
    if (bt->right == NULL)
        return NULL;
    return bt->right->value;
}

struct BinaryTree *binarytree_get_right_node(struct BinaryTree *bt)
{
    return bt->right;
}

void binarytree_set_right(struct BinaryTree *bt, void *value)
{
    if (bt->right == NULL)
    {
        struct BinaryTree bt_right = binarytree_new();
        binarytree_set_right_node(bt, &bt_right);
    }
    bt->right->value = value;
}

void binarytree_set_right_node(struct BinaryTree *bt, struct BinaryTree *right)
{
    bt->right = right;
    right->parent = bt;
}

void *binarytree_pop_right(struct BinaryTree *bt)
{
    if (bt->right == NULL)
        return NULL;
    void *value = binarytree_get_right(bt);
    bt->right->parent = NULL;
    bt->right = NULL;
    return value;
}

struct BinaryTree *binarytree_pop_right_node(struct BinaryTree *bt)
{
    if (bt->right == NULL)
        return NULL;
    struct BinaryTree *bt_right = binarytree_get_right_node(bt);
    bt->right->parent = NULL;
    bt->right = NULL;
    return bt_right;
}

int binarytree_has_parent(struct BinaryTree *bt)
{
    return bt->parent != NULL;
}

struct BinaryTree *binarytree_get_parent(struct BinaryTree *bt)
{
    return bt->parent;
}

void binarytree_set_parent(struct BinaryTree *bt, void *value)
{
    if (bt->parent == NULL)
        return;
    bt->parent->value = value;
}

int binarytree_is_root(struct BinaryTree *bt)
{
    return !binarytree_has_parent(bt);
}

void binarytree_clear(struct BinaryTree *bt)
{
    bt->value = NULL;
    bt->left = NULL;
    bt->right = NULL;
    bt->parent = NULL;
}
