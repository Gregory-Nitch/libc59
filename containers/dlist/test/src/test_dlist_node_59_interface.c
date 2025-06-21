/***********************************************************************************************************************
 * MIT License
 *
 * Copyright (c) 2025 Gregory Nitch
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
 * @date : 2025-05-01
 * @author : Gregory Nitch
 *
 * @brief : Test cases for dlist_node_59 types that cover the basic interface functions.
 **********************************************************************************************************************/

/*
========================================================================================================================
- - SYSTEM INCLUDES - -
========================================================================================================================
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/*
========================================================================================================================
- - MODULE INCLUDES - -
========================================================================================================================
*/

#include "dlist_59.h"

/*
========================================================================================================================
- - UNIT TESTS - -
========================================================================================================================
*/

ERR_59_e test_dlist_node_59_interface(void)
{
    ERR_59_e err = ERR_NONE;
    // init nodes
    puts("- - - - - - - - - - -");
    puts("Initializing nodes...");
    dlist_node_59 *node1;

    err = init_dlist_node_59(&node1, (void *)0, (void *)0, malloc(sizeof(u64)));
    if (ERR_NONE != err)
        return err;

    *((u64 *)node1->node_obj) = 1UL;

    printf("Assert: node1 = val %lu at %p\n", *((u64 *)node1->node_obj), node1);
    assert(1UL == *((u64 *)node1->node_obj));

    // deinit nodes
    puts("- - - - - - - - - - -");
    puts("deiniting nodes...");
    err = deinit_dlist_node_59(&node1);
    printf("Assert: (void*)0 = %p  == %p = node1(null)\n", (void *)0, node1);
    assert((void *)0 == node1);

    return err;
}

/*
========================================================================================================================
- - MAIN - -
========================================================================================================================
*/

int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;

    puts("- - -  START OF DLIST TEST  - - -");
    puts("- - - DLIST NODE INTERFACE - - -");

    ERR_59_e err = test_dlist_node_59_interface();
    printf("ERROR CODE : %d\n", err);
    assert(ERR_NONE == err);

    puts("- - - - END OF DLIST TEST - - - -");
    return err;
}
