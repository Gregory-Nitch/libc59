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
 * @brief : Test cases for doubly linked lists that cover the basic interface interactions.
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

ERR_59_e test_dlist_59_interface(void)
{
    ERR_59_e err = ERR_NONE;

    // Init list and nodes
    puts("- - - - - - - - - - - - - - - - -");
    puts("Initializing list...");
    dlist_59 *list;
    err = init_dlist_59(&list, U64, 0);
    if (ERR_NONE != err)
        return err;

    puts("Initializing nodes with push_back()...");
    for (size_t i = 1; i < 6; i++)
    {
        dlist_node_59 *node;
        err = init_dlist_node_59(&node, (void *)0, (void *)0, malloc(sizeof(u64)));
        if (ERR_NONE != err)
            return err;

        *((u64 *)node->node_obj) = (u64)i;
        err = push_back_dlist_59(list, node);
        if (ERR_NONE != err)
            return err;
    }

    // Verify list contents
    puts("- - - - - - - - - - - - - - - - -");
    puts("Checking initialization...");
    dlist_node_59 *node = list->head;
    dlist_node_59 *last_node = (void *)0;
    for (size_t i = 1; i < 6; i++)
    {
        printf("Assert: i = %lu == %lu = obj\n", i, *((u64 *)node->node_obj));
        assert(*((u64 *)node->node_obj) == i);
        last_node = node->last;
        if (last_node)
        {
            printf("Assert: i - 1 = %lu == %lu = obj\n", i - 1, *((u64 *)last_node->node_obj));
            assert(i - 1 == *((u64 *)last_node->node_obj));
        }
        node = node->next;
    }

    // Test dlist interface
    // pop_back()
    puts("- - - - - - - - - - - - - - - - -");
    puts("Checking pop_back()...");

    err = pop_back_dlist_59(list, &node);
    if (ERR_NONE != err)
        return err;
    printf("Assert: expected = %lu == %lu = obj\n", 5UL, *((u64 *)node->node_obj));
    assert(*((u64 *)node->node_obj) == 5LU);

    err = destroy_dlist_node_59(&node);
    if (ERR_NONE != err)
        return err;
    puts("Back node destroyed...");

    node = list->head;
    for (size_t i = 1; i < 5; i++)
    {
        assert(*((u64 *)node->node_obj) == i);
        printf("Assert: i = %lu == %lu = obj\n", i, *((u64 *)node->node_obj));
        node = node->next;
    }
    printf("Assert: (void*)0 = %p == %p = node(expect null)\n", (void *)0, node);
    assert((void *)0 == node);

    // push_back()
    puts("- - - - - - - - - - - - - - - - -");
    puts("Checking push_back()...");

    err = init_dlist_node_59(&node, (void *)0, (void *)0, malloc(sizeof(u64)));
    if (ERR_NONE != err)
        return err;
    *((u64 *)node->node_obj) = 6UL;
    puts("New node with 6UL created...");

    err = push_back_dlist_59(list, node);
    if (ERR_NONE != err)
        return err;

    node = list->head;
    while (node->next)
        node = node->next;
    puts("Walked list...");

    printf("Assert: expected = %lu == %lu = obj\n", 6UL, *((u64 *)node->node_obj));
    assert(*((u64 *)node->node_obj) == 6UL);

    printf("Assert: expected = %lu == %lu = last node obj\n", 4UL, *((u64 *)node->last->node_obj));
    assert(*((u64 *)node->last->node_obj) == 4UL);

    // push_front()
    puts("- - - - - - - - - - - - - - - - -");
    puts("Checking push_front()...");

    err = init_dlist_node_59(&node, (void *)0, (void *)0, malloc(sizeof(u64)));
    if (ERR_NONE != err)
        return err;
    *((u64 *)node->node_obj) = 0UL;
    puts("New node with 0UL created...");

    err = push_front_dlist_59(list, node);
    if (ERR_NONE != err)
        return err;

    node = list->head;
    printf("Assert: expected = %lu == %lu = obj\n", 0UL, *((u64 *)node->node_obj));
    assert(*((u64 *)node->node_obj) == 0UL);

    printf("Assert: expected = %lu == %lu = obj(last from next)\n", 0UL, *((u64 *)node->next->last->node_obj));
    assert(*((u64 *)node->next->last->node_obj) == 0UL);

    // pop_front()
    puts("- - - - - - - - - - - - - - - - -");
    puts("Checking pop_front()...");

    err = pop_front_dlist_59(list, &node);
    if (ERR_NONE != err)
        return err;

    printf("Assert: expected = %lu == %lu = obj\n", 0UL, *((u64 *)node->node_obj));
    assert(*((u64 *)node->node_obj) == 0UL);

    err = destroy_dlist_node_59(&node);
    if (ERR_NONE != err)
        return err;
    puts("Popped front node destroyed...");

    node = list->head;
    printf("Assert: expected = %lu == %lu = obj\n", 1UL, *((u64 *)node->node_obj));
    assert(*((u64 *)node->node_obj) == 1UL);

    // remove_node()
    puts("- - - - - - - - - - - - - - - - -");
    puts("Checking remove_node_from_list()...");

    for (size_t i = 0; i < 2UL; i++)
        node = node->next;
    printf("Got node: %lu\n", *((u64 *)node->node_obj));
    u64 val = *((u64 *)node->node_obj);

    err = remove_given_node_from_dlist_59(list, node);
    if (ERR_NONE != err)
        return err;

    err = destroy_dlist_node_59(&node);
    if (ERR_NONE != err)
        return err;
    puts("Removed node destroyed...");

    node = list->head;
    while (node)
    {
        printf("Assert: expected = %lu != %lu = obj\n", val, *((u64 *)node->node_obj));
        assert(*((u64 *)node->node_obj) != val);
        node = node->next;
    }

    // insert_node()
    puts("- - - - - - - - - - - - - - - - -");
    puts("Checking insert_node_into_list()...");

    err = init_dlist_node_59(&node, (void *)0, (void *)0, malloc(sizeof(u64)));
    if (ERR_NONE != err)
        return err;
    val = 8UL;
    *((u64 *)node->node_obj) = val;
    printf("Created node: %lu\n", *((u64 *)node->node_obj));

    size_t idx = 2;
    err = insert_node_into_dlist_59(list, node, idx);
    if (ERR_NONE != err)
        return err;

    node = list->head;
    for (size_t i = 0; i < idx; i++)
    {
        node = node->next;
    }
    printf("Walked to idx: %lu\n", idx);

    printf("Assert: expected = %lu == %lu = obj\n", val, *((u64 *)node->node_obj));
    assert(*((u64 *)node->node_obj) == val);

    printf("Assert: expected = %lu == %lu = last obj\n", 2UL, *((u64 *)node->last->node_obj));
    assert(*((u64 *)node->last->node_obj) == 2UL);

    printf("Assert: expected = %lu == %lu = next obj\n", 4UL, *((u64 *)node->next->node_obj));
    assert(*((u64 *)node->next->node_obj) == 4UL);

    // destroy_list()
    puts("- - - - - - - - - - - - - - - - -");
    puts("Checking destroy_list()...");

    err = destroy_dlist_59(&list);
    if (ERR_NONE != err)
        return err;
    puts("List destroyed...");

    printf("Assert: expected(void*)0 = %p == %p = obj\n", (void *)0, list);
    assert(list == (void *)0);

    return err;
}

/*
========================================================================================================================
- - MAIN - -
========================================================================================================================
*/

int main(int argc, char const *argv[])
{
    puts("- - -  START OF DLIST TEST  - - -");
    puts("- - - INTERFACE TESTS - - -");

    ERR_59_e err = test_dlist_59_interface();
    printf("ERROR CODE : %d\n", err);
    assert(ERR_NONE == err);

    puts("- - - - END OF DLIST TEST - - - -");
    return err;
}
