#include "binarytree.h"
#include "defs.h"
#include <stdlib.h>

EXPORT struct BinaryTree *binarytree_new(void)
{
    struct BinaryTree *bt = malloc(sizeof(struct BinaryTree));
    bt->value = NULL;
    bt->left = NULL;
    bt->right = NULL;
    bt->parent = NULL;
    return bt;
}

EXPORT void *binarytree_get_value(struct BinaryTree *bt)
{
    return bt->value;
}

EXPORT void binarytree_set_value(struct BinaryTree *bt, void *value)
{
    bt->value = value;
}

EXPORT int binarytree_has_left(struct BinaryTree *bt)
{
    return bt->left != NULL;
}

EXPORT void *binarytree_get_left(struct BinaryTree *bt)
{
    if (bt->left == NULL)
        return NULL;
    return bt->left->value;
}

EXPORT struct BinaryTree *binarytree_get_left_node(struct BinaryTree *bt)
{
    return bt->left;
}

EXPORT void binarytree_set_left(struct BinaryTree *bt, void *value)
{
    if (bt->left == NULL)
    {
        struct BinaryTree *bt_left = binarytree_new();
        binarytree_set_left_node(bt, bt_left);
    }
    bt->left->value = value;
}

EXPORT void binarytree_set_left_node(struct BinaryTree *bt, struct BinaryTree *left)
{
    bt->left = left;
    left->parent = bt;
}

EXPORT void *binarytree_pop_left(struct BinaryTree *bt)
{
    if (bt->left == NULL)
        return NULL;
    void *value = binarytree_get_left(bt);
    bt->left->parent = NULL;
    bt->left = NULL;
    return value;
}

EXPORT struct BinaryTree *binarytree_pop_left_node(struct BinaryTree *bt)
{
    if (bt->left == NULL)
        return NULL;
    struct BinaryTree *bt_left = binarytree_get_left_node(bt);
    bt->left->parent = NULL;
    bt->left = NULL;
    return bt_left;
}

EXPORT int binarytree_has_right(struct BinaryTree *bt)
{
    return bt->right != NULL;
}

EXPORT void *binarytree_get_right(struct BinaryTree *bt)
{
    if (bt->right == NULL)
        return NULL;
    return bt->right->value;
}

EXPORT struct BinaryTree *binarytree_get_right_node(struct BinaryTree *bt)
{
    return bt->right;
}

EXPORT void binarytree_set_right(struct BinaryTree *bt, void *value)
{
    if (bt->right == NULL)
    {
        struct BinaryTree *bt_right = binarytree_new();
        binarytree_set_right_node(bt, bt_right);
    }
    bt->right->value = value;
}

EXPORT void binarytree_set_right_node(struct BinaryTree *bt, struct BinaryTree *right)
{
    bt->right = right;
    right->parent = bt;
}

EXPORT void *binarytree_pop_right(struct BinaryTree *bt)
{
    if (bt->right == NULL)
        return NULL;
    void *value = binarytree_get_right(bt);
    bt->right->parent = NULL;
    bt->right = NULL;
    return value;
}

EXPORT struct BinaryTree *binarytree_pop_right_node(struct BinaryTree *bt)
{
    if (bt->right == NULL)
        return NULL;
    struct BinaryTree *bt_right = binarytree_get_right_node(bt);
    bt->right->parent = NULL;
    bt->right = NULL;
    return bt_right;
}

EXPORT int binarytree_has_parent(struct BinaryTree *bt)
{
    return bt->parent != NULL;
}

EXPORT struct BinaryTree *binarytree_get_parent(struct BinaryTree *bt)
{
    return bt->parent;
}

EXPORT void binarytree_set_parent(struct BinaryTree *bt, void *value)
{
    if (bt->parent == NULL)
        return;
    bt->parent->value = value;
}

EXPORT int binarytree_is_root(struct BinaryTree *bt)
{
    return !binarytree_has_parent(bt);
}

EXPORT void binarytree_clear(struct BinaryTree *bt)
{
    bt->value = NULL;
    bt->left = NULL;
    bt->right = NULL;
    bt->parent = NULL;
}

EXPORT void binarytree_free(struct BinaryTree *bt)
{
    free(bt);
}
