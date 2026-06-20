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
 * @brief: Test cases for btree_59 types that cover edge cases that the node might encounter.
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
- - UNIT TESTS - -
========================================================================================================================
*/

ERR_59_e test_btree_59_node_edge_cases(void)
{
    ERR_59_e err = init_btree_node_59((void*)0, (void*)0, (void*)0, (void*)0);
    assert(ERR_INV_PARAM == err);
    err = ERR_NONE;

    err = deinit_btree_node_59((void*)0);
    assert(ERR_INV_PARAM == err);
    err = ERR_NONE;

    return err;
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
    puts("- - - BTREE NODE EDGE CASES - - -");

    ERR_59_e err = test_btree_59_node_edge_cases();
    printf("ERROR CODE: %d\n", err);
    assert(ERR_NONE == err);

    puts("- - - - END OF BTREE TEST - - - -");
    return err;
}
