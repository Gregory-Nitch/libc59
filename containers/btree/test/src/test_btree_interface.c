/***********************************************************************************************************************
 * MIT License
 *
 * Copyright (c) 2026 Gregory Nitch
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @date: 2026-06-21
 * @author: Gregory Nitch
 *
 * @brief: Test cases for btree_59 types that cover the interface of the btree.
 **********************************************************************************************************************/

/*
========================================================================================================================
- - SYSTEM INCLUDES - -
========================================================================================================================
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
========================================================================================================================
- - MODULE INCLUDES - -
========================================================================================================================
*/

#include "btree.h"

/*
========================================================================================================================
- - INTERNAL TEST HELPERS - -
========================================================================================================================
*/

static ERR_59_e _make_i32_btree_node(btree_node_59** node, i32 const value)
{
    if (!node)
        return ERR_INV_PARAM;

    i32* node_obj = malloc(sizeof(i32));
    if (!node_obj)
        return ERR_NO_MEM;

    *node_obj = value;
    ERR_59_e err = init_btree_node_59(node, (void*)0, (void*)0, node_obj);
    if (ERR_NONE != err)
    {
        free(node_obj);
        return err;
    }

    return ERR_NONE;
}

static ERR_59_e _insert_i32_btree_node(btree_59* const btree, btree_node_59** node, i32 const value)
{
    ERR_59_e err = _make_i32_btree_node(node, value);
    if (ERR_NONE != err)
        return err;

    err = insert_node_into_btree_59(btree, *node);
    if (ERR_NONE != err)
    {
        deinit_btree_node_59(node);
        return err;
    }

    return ERR_NONE;
}

static i32 _get_i32_btree_node_value(btree_node_59 const* const node)
{
    assert((void*)0 != node);
    assert((void*)0 != node->node_obj);
    return *((i32*)node->node_obj);
}

static ERR_59_e _test_btree_init_insert_find_and_height(void)
{
    ERR_59_e err = ERR_NONE;
    btree_59* btree = (void*)0;
    btree_node_59* node5 = (void*)0;
    btree_node_59* node3 = (void*)0;
    btree_node_59* node7 = (void*)0;
    btree_node_59* node6 = (void*)0;
    btree_node_59* node8 = (void*)0;
    btree_node_59* found = (void*)0;
    size_t height = 0;

    err = init_btree_59(&btree, I32_PTR, 0);
    if (ERR_NONE != err)
        return err;

    assert((void*)0 != btree);
    assert((void*)0 == btree->root);
    assert(I32_PTR == btree->type);
    assert(0 == btree->type_depth);
    assert(0 == btree->size);

    err = get_height_btree_59(btree, &height);
    if (ERR_NONE != err)
        return err;
    assert(0 == height);

    err = _insert_i32_btree_node(btree, &node5, 5);
    if (ERR_NONE != err)
        return err;

    err = _insert_i32_btree_node(btree, &node3, 3);
    if (ERR_NONE != err)
        return err;

    err = _insert_i32_btree_node(btree, &node7, 7);
    if (ERR_NONE != err)
        return err;

    err = _insert_i32_btree_node(btree, &node6, 6);
    if (ERR_NONE != err)
        return err;

    err = _insert_i32_btree_node(btree, &node8, 8);
    if (ERR_NONE != err)
        return err;

    assert(5 == btree->size);
    assert(node5 == btree->root);
    assert(node3 == btree->root->left);
    assert(node7 == btree->root->right);
    assert(node6 == node7->left);
    assert(node8 == node7->right);

    err = find_node_in_btree_59(btree, node5->node_obj, &found);
    if (ERR_NONE != err)
        return err;
    assert(node5 == found);

    err = find_node_in_btree_59(btree, node6->node_obj, &found);
    if (ERR_NONE != err)
        return err;
    assert(node6 == found);

    err = get_height_btree_59(btree, &height);
    if (ERR_NONE != err)
        return err;
    assert(3 == height);

    err = deinit_btree_59(&btree);
    if (ERR_NONE != err)
        return err;

    assert((void*)0 == btree);
    return ERR_NONE;
}

static ERR_59_e _test_btree_remove_cases(void)
{
    ERR_59_e err = ERR_NONE;
    btree_59* replacement_btree = (void*)0;
    btree_59* direct_successor_btree = (void*)0;
    btree_59* left_only_btree = (void*)0;
    btree_59* right_only_btree = (void*)0;
    btree_node_59* node5 = (void*)0;
    btree_node_59* node3 = (void*)0;
    btree_node_59* node7 = (void*)0;
    btree_node_59* node6 = (void*)0;
    btree_node_59* node8 = (void*)0;
    btree_node_59* direct_root = (void*)0;
    btree_node_59* direct_left = (void*)0;
    btree_node_59* direct_right = (void*)0;
    btree_node_59* left_root = (void*)0;
    btree_node_59* left_child = (void*)0;
    btree_node_59* right_root = (void*)0;
    btree_node_59* right_child = (void*)0;

    err = init_btree_59(&replacement_btree, I32_PTR, 0);
    if (ERR_NONE != err)
        return err;

    err = _insert_i32_btree_node(replacement_btree, &node5, 5);
    if (ERR_NONE != err)
        return err;
    err = _insert_i32_btree_node(replacement_btree, &node3, 3);
    if (ERR_NONE != err)
        return err;
    err = _insert_i32_btree_node(replacement_btree, &node7, 7);
    if (ERR_NONE != err)
        return err;
    err = _insert_i32_btree_node(replacement_btree, &node6, 6);
    if (ERR_NONE != err)
        return err;
    err = _insert_i32_btree_node(replacement_btree, &node8, 8);
    if (ERR_NONE != err)
        return err;

    err = remove_given_node_from_btree_59(replacement_btree, node5);
    if (ERR_NONE != err)
        return err;
    assert(4 == replacement_btree->size);
    assert(node6 == replacement_btree->root);
    assert(node3 == replacement_btree->root->left);
    assert(node7 == replacement_btree->root->right);
    assert(node8 == node7->right);
    assert((void*)0 == node7->left);
    assert((void*)0 == node5->left);
    assert((void*)0 == node5->right);

    err = deinit_btree_node_59(&node5);
    if (ERR_NONE != err)
        return err;
    assert((void*)0 == node5);

    err = remove_given_node_from_btree_59(replacement_btree, node8);
    if (ERR_NONE != err)
        return err;
    assert(3 == replacement_btree->size);
    assert((void*)0 == node8->left);
    assert((void*)0 == node8->right);
    assert((void*)0 == node7->right);

    err = deinit_btree_node_59(&node8);
    if (ERR_NONE != err)
        return err;
    assert((void*)0 == node8);

    err = deinit_btree_59(&replacement_btree);
    if (ERR_NONE != err)
        return err;

    err = init_btree_59(&direct_successor_btree, I32_PTR, 0);
    if (ERR_NONE != err)
        return err;

    err = _insert_i32_btree_node(direct_successor_btree, &direct_root, 5);
    if (ERR_NONE != err)
        return err;
    err = _insert_i32_btree_node(direct_successor_btree, &direct_left, 3);
    if (ERR_NONE != err)
        return err;
    err = _insert_i32_btree_node(direct_successor_btree, &direct_right, 7);
    if (ERR_NONE != err)
        return err;

    err = remove_given_node_from_btree_59(direct_successor_btree, direct_root);
    if (ERR_NONE != err)
        return err;
    assert(2 == direct_successor_btree->size);
    assert(direct_right == direct_successor_btree->root);
    assert(direct_left == direct_successor_btree->root->left);
    assert((void*)0 == direct_root->left);
    assert((void*)0 == direct_root->right);

    err = deinit_btree_node_59(&direct_root);
    if (ERR_NONE != err)
        return err;

    err = deinit_btree_59(&direct_successor_btree);
    if (ERR_NONE != err)
        return err;

    err = init_btree_59(&left_only_btree, I32_PTR, 0);
    if (ERR_NONE != err)
        return err;

    err = _insert_i32_btree_node(left_only_btree, &left_root, 5);
    if (ERR_NONE != err)
        return err;
    err = _insert_i32_btree_node(left_only_btree, &left_child, 3);
    if (ERR_NONE != err)
        return err;

    err = remove_given_node_from_btree_59(left_only_btree, left_root);
    if (ERR_NONE != err)
        return err;
    assert(1 == left_only_btree->size);
    assert(left_child == left_only_btree->root);
    assert((void*)0 == left_root->left);
    assert((void*)0 == left_root->right);

    err = deinit_btree_node_59(&left_root);
    if (ERR_NONE != err)
        return err;

    err = deinit_btree_59(&left_only_btree);
    if (ERR_NONE != err)
        return err;

    err = init_btree_59(&right_only_btree, I32_PTR, 0);
    if (ERR_NONE != err)
        return err;

    err = _insert_i32_btree_node(right_only_btree, &right_root, 5);
    if (ERR_NONE != err)
        return err;
    err = _insert_i32_btree_node(right_only_btree, &right_child, 7);
    if (ERR_NONE != err)
        return err;

    err = remove_given_node_from_btree_59(right_only_btree, right_root);
    if (ERR_NONE != err)
        return err;
    assert(1 == right_only_btree->size);
    assert(right_child == right_only_btree->root);
    assert((void*)0 == right_root->left);
    assert((void*)0 == right_root->right);

    err = deinit_btree_node_59(&right_root);
    if (ERR_NONE != err)
        return err;

    err = deinit_btree_59(&right_only_btree);
    if (ERR_NONE != err)
        return err;

    return ERR_NONE;
}

static ERR_59_e _test_btree_duplicate_values(void)
{
    ERR_59_e err = ERR_NONE;
    btree_59* btree = (void*)0;
    btree_node_59* root = (void*)0;
    btree_node_59* duplicate_a = (void*)0;
    btree_node_59* duplicate_b = (void*)0;
    btree_node_59* found = (void*)0;

    err = init_btree_59(&btree, I32_PTR, 0);
    if (ERR_NONE != err)
        return err;

    err = _insert_i32_btree_node(btree, &root, 5);
    if (ERR_NONE != err)
        return err;
    err = _insert_i32_btree_node(btree, &duplicate_a, 5);
    if (ERR_NONE != err)
        return err;
    err = _insert_i32_btree_node(btree, &duplicate_b, 5);
    if (ERR_NONE != err)
        return err;

    assert(root == btree->root);
    assert(duplicate_a == root->right);
    assert(duplicate_b == duplicate_a->right);
    assert(3 == btree->size);

    err = find_node_in_btree_59(btree, duplicate_b->node_obj, &found);
    if (ERR_NONE != err)
        return err;
    assert(root == found);

    err = remove_given_node_from_btree_59(btree, duplicate_a);
    if (ERR_NONE != err)
        return err;
    assert(2 == btree->size);
    assert(duplicate_b == root->right);
    assert((void*)0 == duplicate_a->left);
    assert((void*)0 == duplicate_a->right);

    err = deinit_btree_node_59(&duplicate_a);
    if (ERR_NONE != err)
        return err;

    err = deinit_btree_59(&btree);
    if (ERR_NONE != err)
        return err;

    return ERR_NONE;
}

static ERR_59_e _test_btree_rebalance(void)
{
    ERR_59_e err = ERR_NONE;
    btree_59* btree = (void*)0;
    btree_node_59* node1 = (void*)0;
    btree_node_59* node2 = (void*)0;
    btree_node_59* node3 = (void*)0;
    btree_node_59* node4 = (void*)0;
    btree_node_59* node5 = (void*)0;
    btree_node_59* found = (void*)0;
    size_t height_before = 0;
    size_t height_after = 0;

    err = init_btree_59(&btree, I32_PTR, 0);
    if (ERR_NONE != err)
        return err;

    err = _insert_i32_btree_node(btree, &node1, 1);
    if (ERR_NONE != err)
        return err;
    err = _insert_i32_btree_node(btree, &node2, 2);
    if (ERR_NONE != err)
        return err;
    err = _insert_i32_btree_node(btree, &node3, 3);
    if (ERR_NONE != err)
        return err;
    err = _insert_i32_btree_node(btree, &node4, 4);
    if (ERR_NONE != err)
        return err;
    err = _insert_i32_btree_node(btree, &node5, 5);
    if (ERR_NONE != err)
        return err;

    err = get_height_btree_59(btree, &height_before);
    if (ERR_NONE != err)
        return err;
    assert(5 == height_before);

    err = rebalance_btree_59(btree);
    if (ERR_NONE != err)
        return err;

    err = get_height_btree_59(btree, &height_after);
    if (ERR_NONE != err)
        return err;
    assert(3 == height_after);
    assert(3 == _get_i32_btree_node_value(btree->root));

    err = find_node_in_btree_59(btree, node1->node_obj, &found);
    if (ERR_NONE != err)
        return err;
    assert(node1 == found);

    err = find_node_in_btree_59(btree, node5->node_obj, &found);
    if (ERR_NONE != err)
        return err;
    assert(node5 == found);

    err = deinit_btree_59(&btree);
    if (ERR_NONE != err)
        return err;

    assert((void*)0 == btree);
    return ERR_NONE;
}

/*
========================================================================================================================
- - UNIT TESTS - -
========================================================================================================================
*/

ERR_59_e test_btree_59_interface(void)
{
    ERR_59_e err = _test_btree_init_insert_find_and_height();
    if (ERR_NONE != err)
        return err;

    err = _test_btree_remove_cases();
    if (ERR_NONE != err)
        return err;

    err = _test_btree_duplicate_values();
    if (ERR_NONE != err)
        return err;

    return _test_btree_rebalance();
}

/*
========================================================================================================================
- - MAIN - -
========================================================================================================================
*/

int main(int argc, char const* argv[])
{
    (void)argc;
    (void)argv;

    puts("- - -  START OF BTREE TEST  - - -");
    puts("- - - BTREE INTERFACE - - -");

    ERR_59_e err = test_btree_59_interface();
    printf("ERROR CODE: %d\n", err);
    assert(ERR_NONE == err);

    puts("- - - - END OF BTREE TEST - - - -");
    return err;
}
