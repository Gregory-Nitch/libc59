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
 * @brief: Test cases for btree_59 types that cover edge cases that the interface might encounter.
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

static ERR_59_e _make_bool_btree_node(btree_node_59** node, bool const value)
{
    if (!node)
        return ERR_INV_PARAM;

    bool* node_obj = malloc(sizeof(bool));
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

static ERR_59_e _test_btree_invalid_params(void)
{
    ERR_59_e err = ERR_NONE;
    btree_59* btree = (void*)0;
    btree_59* null_btree = (void*)0;
    btree_node_59* node = (void*)0;
    btree_node_59* out = (void*)0;
    i32 missing_value = 99;
    size_t height = 0;

    err = init_btree_59((void*)0, I32_PTR, 0);
    assert(ERR_INV_PARAM == err);

    err = init_btree_59(&btree, I32_PTR, 4);
    if (ERR_NONE != err)
        return err;

    err = _make_i32_btree_node(&node, 33);
    if (ERR_NONE != err)
        return err;

    err = deinit_btree_59((void*)0);
    assert(ERR_INV_PARAM == err);

    err = deinit_btree_59(&null_btree);
    assert(ERR_INV_PARAM == err);

    err = insert_node_into_btree_59((void*)0, node);
    assert(ERR_INV_PARAM == err);

    err = insert_node_into_btree_59(btree, (void*)0);
    assert(ERR_INV_PARAM == err);

    err = find_node_in_btree_59((void*)0, &missing_value, &out);
    assert(ERR_INV_PARAM == err);

    err = find_node_in_btree_59(btree, (void*)0, &out);
    assert(ERR_INV_PARAM == err);

    err = find_node_in_btree_59(btree, &missing_value, (void*)0);
    assert(ERR_INV_PARAM == err);

    err = remove_given_node_from_btree_59((void*)0, node);
    assert(ERR_INV_PARAM == err);

    err = remove_given_node_from_btree_59(btree, (void*)0);
    assert(ERR_INV_PARAM == err);

    err = rebalance_btree_59((void*)0);
    assert(ERR_INV_PARAM == err);

    err = rebalance_btree_59(btree);
    assert(ERR_INV_PARAM == err);

    err = get_height_btree_59((void*)0, &height);
    assert(ERR_INV_PARAM == err);

    err = get_height_btree_59(btree, (void*)0);
    assert(ERR_INV_PARAM == err);

    err = deinit_btree_node_59(&node);
    if (ERR_NONE != err)
        return err;

    err = deinit_btree_59(&btree);
    if (ERR_NONE != err)
        return err;

    return ERR_NONE;
}

static ERR_59_e _test_btree_not_found_and_unsupported_cases(void)
{
    ERR_59_e err = ERR_NONE;
    btree_59* btree = (void*)0;
    btree_59* unsupported_btree = (void*)0;
    btree_node_59* root = (void*)0;
    btree_node_59* missing_node = (void*)0;
    btree_node_59* unsupported_root = (void*)0;
    btree_node_59* unsupported_extra = (void*)0;
    btree_node_59* found = (void*)0;
    i32 missing_value = 101;

    err = init_btree_59(&btree, I32_PTR, 0);
    if (ERR_NONE != err)
        return err;

    err = _make_i32_btree_node(&root, 33);
    if (ERR_NONE != err)
        return err;

    err = _make_i32_btree_node(&missing_node, 59);
    if (ERR_NONE != err)
        return err;

    err = find_node_in_btree_59(btree, &missing_value, &found);
    assert(ERR_OBJ_NOT_FOUND == err);
    assert((void*)0 == found);

    err = remove_given_node_from_btree_59(btree, missing_node);
    assert(ERR_OBJ_NOT_FOUND == err);

    err = insert_node_into_btree_59(btree, root);
    if (ERR_NONE != err)
        return err;

    err = find_node_in_btree_59(btree, &missing_value, &found);
    assert(ERR_OBJ_NOT_FOUND == err);
    assert((void*)0 == found);

    err = remove_given_node_from_btree_59(btree, missing_node);
    assert(ERR_OBJ_NOT_FOUND == err);

    err = deinit_btree_node_59(&missing_node);
    if (ERR_NONE != err)
        return err;

    err = deinit_btree_59(&btree);
    if (ERR_NONE != err)
        return err;

    err = init_btree_59(&unsupported_btree, BOOL_PTR, 0);
    if (ERR_NONE != err)
        return err;

    err = _make_bool_btree_node(&unsupported_root, true);
    if (ERR_NONE != err)
        return err;

    err = _make_bool_btree_node(&unsupported_extra, false);
    if (ERR_NONE != err)
        return err;

    err = insert_node_into_btree_59(unsupported_btree, unsupported_root);
    if (ERR_NONE != err)
        return err;

    err = insert_node_into_btree_59(unsupported_btree, unsupported_extra);
    assert(ERR_NOT_SUPPORTED == err);

    err = find_node_in_btree_59(unsupported_btree, unsupported_root->node_obj, &found);
    assert(ERR_NOT_SUPPORTED == err);

    err = deinit_btree_node_59(&unsupported_extra);
    if (ERR_NONE != err)
        return err;

    err = deinit_btree_59(&unsupported_btree);
    if (ERR_NONE != err)
        return err;

    return ERR_NONE;
}

/*
========================================================================================================================
- - UNIT TESTS - -
========================================================================================================================
*/

ERR_59_e test_btree_59_edge_cases(void)
{
    ERR_59_e err = _test_btree_invalid_params();
    if (ERR_NONE != err)
        return err;

    return _test_btree_not_found_and_unsupported_cases();
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
    puts("- - - BTREE EDGE CASES - - -");

    ERR_59_e err = test_btree_59_edge_cases();
    printf("ERROR CODE: %d\n", err);
    assert(ERR_NONE == err);

    puts("- - - - END OF BTREE TEST - - - -");
    return err;
}
