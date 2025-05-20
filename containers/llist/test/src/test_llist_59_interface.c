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
 * @date : 2025-03-24
 * @author : Gregory Nitch
 *
 * @brief : Test cases for linked lists that cover the basic interface interactions.
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

#include "llist_59.h"

/*
========================================================================================================================
- - UNIT TESTS - -
========================================================================================================================
*/

ERR_59_e test_llist_59_interface(void)
{
    ERR_59_e err = ERR_NONE;

    // Init list and nodes
    puts("- - - - - - - - - - - - - - - - -");
    puts("Initializing list...");
    llist_59 *list;
    err = init_llist_59(&list, U64, 0);
    if (ERR_NONE != err)
        return err;

    puts("Initializing nodes with push_back()...");
    for (size_t i = 1; i < 6; i++)
    {
        llist_node_59 *node;
        err = init_llist_node_59(&node, (void *)0, malloc(sizeof(u64)));
        if (ERR_NONE != err)
            return err;

        *((u64 *)node->node_obj) = (u64)i;
        err = push_back_llist_59(list, node);
        if (ERR_NONE != err)
            return err;
    }

    // Verify list contents
    puts("- - - - - - - - - - - - - - - - -");
    puts("Checking initialization...");
    llist_node_59 *node = list->head;
    for (size_t i = 1; i < 6; i++)
    {
        printf("Assert: i = %lu == %lu = obj\n", i, *((u64 *)node->node_obj));
        assert(*((u64 *)node->node_obj) == i);
        node = node->next;
    }

    // Test llist interface
    // pop_back()
    puts("- - - - - - - - - - - - - - - - -");
    puts("Checking pop_back()...");

    err = pop_back_llist_59(list, &node);
    if (ERR_NONE != err)
        return err;
    printf("Assert: expected = %lu == %lu = obj\n", 5UL, *((u64 *)node->node_obj));
    assert(*((u64 *)node->node_obj) == 5LU);

    err = deinit_llist_node_59(&node);
    if (ERR_NONE != err)
        return err;
    puts("Back node deinited...");

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

    err = init_llist_node_59(&node, (void *)0, malloc(sizeof(u64)));
    if (ERR_NONE != err)
        return err;
    *((u64 *)node->node_obj) = 6UL;
    puts("New node with 6UL created...");

    err = push_back_llist_59(list, node);
    if (ERR_NONE != err)
        return err;

    node = list->head;
    while (node->next)
        node = node->next;
    puts("Walked list...");

    printf("Assert: expected = %lu == %lu = obj\n", 6UL, *((u64 *)node->node_obj));
    assert(*((u64 *)node->node_obj) == 6UL);

    // push_front()
    puts("- - - - - - - - - - - - - - - - -");
    puts("Checking push_front()...");

    err = init_llist_node_59(&node, (void *)0, malloc(sizeof(u64)));
    if (ERR_NONE != err)
        return err;
    *((u64 *)node->node_obj) = 0UL;
    puts("New node with 0UL created...");

    err = push_front_llist_59(list, node);
    if (ERR_NONE != err)
        return err;

    node = list->head;
    printf("Assert: expected = %lu == %lu = obj\n", 0UL, *((u64 *)node->node_obj));
    assert(*((u64 *)node->node_obj) == 0UL);

    // pop_front()
    puts("- - - - - - - - - - - - - - - - -");
    puts("Checking pop_front()...");

    err = pop_front_llist_59(list, &node);
    if (ERR_NONE != err)
        return err;

    printf("Assert: expected = %lu == %lu = obj\n", 0UL, *((u64 *)node->node_obj));
    assert(*((u64 *)node->node_obj) == 0UL);

    err = deinit_llist_node_59(&node);
    if (ERR_NONE != err)
        return err;
    puts("Popped front node deinited...");

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

    err = remove_given_node_from_llist_59(list, node);
    if (ERR_NONE != err)
        return err;

    err = deinit_llist_node_59(&node);
    if (ERR_NONE != err)
        return err;
    puts("Removed node deinited...");

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

    err = init_llist_node_59(&node, (void *)0, malloc(sizeof(u64)));
    if (ERR_NONE != err)
        return err;
    val = 8UL;
    *((u64 *)node->node_obj) = val;
    printf("Created node: %lu\n", *((u64 *)node->node_obj));

    size_t idx = 2;
    err = insert_node_into_llist_59(list, node, idx);
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

    // deinit_list()
    puts("- - - - - - - - - - - - - - - - -");
    puts("Checking deinit_list()...");

    err = deinit_llist_59(&list);
    if (ERR_NONE != err)
        return err;
    puts("List deinited...");

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
    puts("- - -  START OF LLIST TEST  - - -");
    puts("- - - INTERFACE TESTS - - -");

    ERR_59_e err = test_llist_59_interface();
    printf("ERROR CODE : %d\n", err);
    assert(ERR_NONE == err);

    puts("- - - - END OF LLIST TEST - - - -");
    return err;
}
