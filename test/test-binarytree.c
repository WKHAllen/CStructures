#include "../bin/include/binarytree.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>

void int_powers(void *a, void *b)
{
    *(int *)b = pow(*(int *)a, *(int *)b);
}

int main(int argc, char **argv)
{
    printf("Running tests...\n");
    
    int value1 = 7;
    char *value2 = "hello";
    float value3 = 3.14;
    char value4 = 'C';

    // test initialization
    struct BinaryTree bt = binarytree_new();
    assert(bt.value == NULL);
    assert(bt.left == NULL);
    assert(bt.right == NULL);
    assert(bt.parent == NULL);

    // test set_value and get_value
    binarytree_set_value(&bt, &value1);
    assert(*(int *)binarytree_get_value(&bt) == value1);

    // test has_left, has_right, and has_parent
    assert(!binarytree_has_left(&bt));
    assert(!binarytree_has_right(&bt));
    assert(!binarytree_has_parent(&bt));

    // test set_left and get_left
    binarytree_set_left(&bt, &value2);
    assert(binarytree_has_left(&bt));
    char *result1 = *(char **)binarytree_get_left(&bt);
    assert(result1 == value2);

    // test set_right and get_right
    binarytree_set_right(&bt, &value3);
    assert(binarytree_has_right(&bt));
    float result2 = *(float *)binarytree_get_right(&bt);
    assert(result2 == value3);

    // test get_left_node and get_right_node
    assert(binarytree_get_left_node(&bt) == bt.left);
    assert(binarytree_get_right_node(&bt) == bt.right);

    // test set_left_node, set_right_node, pop_left_node, and pop_right_node
    struct BinaryTree *left = binarytree_pop_left_node(&bt);
    struct BinaryTree *right = binarytree_pop_right_node(&bt);
    binarytree_set_left_node(&bt, right);
    binarytree_set_right_node(&bt, left);

    // test pop_left and pop_right
    assert(binarytree_pop_left(&bt) == right->value);
    assert(binarytree_pop_right(&bt) == left->value);
    binarytree_set_left_node(&bt, left);
    binarytree_set_right_node(&bt, right);

    // test has_parent and get_parent
    assert(!binarytree_has_parent(&bt));
    assert(binarytree_has_parent(left));
    assert(binarytree_has_parent(right));
    assert(binarytree_get_parent(left) == &bt);
    assert(binarytree_get_parent(right) == &bt);

    // test set_parent
    binarytree_set_parent(left, &value4);
    assert(*(char *)binarytree_get_value(&bt) == value4);

    // test clear
    binarytree_clear(&bt);
    assert(bt.value == NULL);
    assert(bt.left == NULL);
    assert(bt.right == NULL);
    assert(bt.parent == NULL);

    printf("Successfully passed all tests\n");
    return 0;
}
