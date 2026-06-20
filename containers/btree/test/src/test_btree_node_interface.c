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
 * @brief: Test cases for btree_59 node interface.
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

/*
========================================================================================================================
- - UNIT TESTS - -
========================================================================================================================
*/

ERR_59_e test_btree_59_node_interface(void)
{
    ERR_59_e err = ERR_NONE;
    btree_node_59* left = (void*)0;
    btree_node_59* right = (void*)0;
    btree_node_59* parent = (void*)0;
    btree_node_59* null_payload_node = (void*)0;

    err = _make_i32_btree_node(&left, 11);
    if (ERR_NONE != err)
        return err;

    err = _make_i32_btree_node(&right, 17);
    if (ERR_NONE != err)
        return err;

    i32* parent_obj = malloc(sizeof(i32));
    if (!parent_obj)
        return ERR_NO_MEM;

    *parent_obj = 13;
    err = init_btree_node_59(&parent, left, right, parent_obj);
    if (ERR_NONE != err)
    {
        free(parent_obj);
        return err;
    }

    assert(left == parent->left);
    assert(right == parent->right);
    assert(13 == *((i32*)parent->node_obj));

    err = deinit_btree_node_59(&parent);
    if (ERR_NONE != err)
        return err;
    assert((void*)0 == parent);

    assert(11 == *((i32*)left->node_obj));
    assert(17 == *((i32*)right->node_obj));

    err = deinit_btree_node_59(&left);
    if (ERR_NONE != err)
        return err;
    err = deinit_btree_node_59(&right);
    if (ERR_NONE != err)
        return err;

    err = init_btree_node_59(&null_payload_node, (void*)0, (void*)0, (void*)0);
    if (ERR_NONE != err)
        return err;

    assert((void*)0 == null_payload_node->left);
    assert((void*)0 == null_payload_node->right);
    assert((void*)0 == null_payload_node->node_obj);

    err = deinit_btree_node_59(&null_payload_node);
    if (ERR_NONE != err)
        return err;
    assert((void*)0 == null_payload_node);

    return ERR_NONE;
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
    puts("- - - BTREE NODE INTERFACE - - -");

    ERR_59_e err = test_btree_59_node_interface();
    printf("ERROR CODE: %d\n", err);
    assert(ERR_NONE == err);

    puts("- - - - END OF BTREE TEST - - - -");
    return err;
}
