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
 * @date : 2025-04-12
 * @author : Gregory Nitch
 *
 * @brief : Test cases for llist_59 types that cover edge cases that the interface might encounter.
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

#include "llist.h"

/*
========================================================================================================================
- - UNIT TESTS - -
========================================================================================================================
*/

ERR_59_e test_llist_59_edge_cases(void)
{
    ERR_59_e err = ERR_NONE;

    // Setup list and nodes for testing
    puts("- - - - - - - - - - - - - - - - -");
    puts("Initializing list and nodes...");
    llist_59 *list = (void *)0;
    llist_node_59 *node1 = (void *)0;
    llist_node_59 *node2 = (void *)0;
    llist_node_59 *dummy_node = (void *)0;
    err = init_llist_59(&list, I64_PTR, 0);
    err = init_llist_node_59(&node1, (void *)0, malloc(sizeof(i64 *)));
    err = init_llist_node_59(&node2, (void *)0, malloc(sizeof(i64 *)));
    *((i64 *)node1->node_obj) = 33;
    *((i64 *)node2->node_obj) = 59;

    // init list
    puts("- - - - - - - - - - - - - - - - -");
    puts("Testing init_llist()...");

    err = init_llist_59((void *)0, I64_PTR, 0);
    printf("Assert: err = %d == %d ERR_INV_PARAM\n", err, ERR_INV_PARAM);
    assert(ERR_INV_PARAM == err);
    err = ERR_NONE;

    // deinit list
    puts("- - - - - - - - - - - - - - - - -");
    puts("Testing deinit_llist()...");

    err = deinit_llist_59((void *)0);
    printf("Assert: err = %d == %d ERR_INV_PARAM\n", err, ERR_INV_PARAM);
    assert(ERR_INV_PARAM == err);
    err = ERR_NONE;

    llist_59 *dummy_list = (void *)0;
    err = deinit_llist_59(&dummy_list);
    printf("Assert: err = %d == %d ERR_INV_PARAM\n", err, ERR_INV_PARAM);
    assert(ERR_INV_PARAM == err);
    err = ERR_NONE;

    // push back
    puts("- - - - - - - - - - - - - - - - -");
    puts("Testing push_back()...");

    err = push_back_llist_59((void *)0, node1);
    printf("Assert: err = %d == %d ERR_INV_PARAM\n", err, ERR_INV_PARAM);
    assert(ERR_INV_PARAM == err);
    err = ERR_NONE;

    err = push_back_llist_59(list, (void *)0);
    printf("Assert: err = %d == %d ERR_INV_PARAM\n", err, ERR_INV_PARAM);
    assert(ERR_INV_PARAM == err);
    err = ERR_NONE;

    // pop_back
    puts("- - - - - - - - - - - - - - - - -");
    puts("Testing pop_back()...");

    err = pop_back_llist_59((void *)0, &dummy_node);
    printf("Assert: err = %d == %d ERR_INV_PARAM\n", err, ERR_INV_PARAM);
    assert(ERR_INV_PARAM == err);
    err = ERR_NONE;

    err = pop_back_llist_59(list, (void *)0);
    printf("Assert: err = %d == %d ERR_INV_PARAM\n", err, ERR_INV_PARAM);
    assert(ERR_INV_PARAM == err);
    err = ERR_NONE;

    err = pop_back_llist_59(list, &dummy_node);
    printf("Assert: err = %d == %d ERR_CONTAINER_EMPTY\n", err, ERR_CONTAINER_EMPTY);
    assert(ERR_CONTAINER_EMPTY == err);
    err = ERR_NONE;

    // push_front
    puts("- - - - - - - - - - - - - - - - -");
    puts("Testing push_front()...");

    err = push_front_llist_59((void *)0, node1);
    printf("Assert: err = %d == %d ERR_INV_PARAM\n", err, ERR_INV_PARAM);
    assert(ERR_INV_PARAM == err);
    err = ERR_NONE;

    err = push_front_llist_59(list, (void *)0);
    printf("Assert: err = %d == %d ERR_INV_PARAM\n", err, ERR_INV_PARAM);
    assert(ERR_INV_PARAM == err);
    err = ERR_NONE;

    // pop_front
    puts("- - - - - - - - - - - - - - - - -");
    puts("Testing pop_front()...");

    err = pop_front_llist_59((void *)0, &node1);
    printf("Assert: err = %d == %d ERR_INV_PARAM\n", err, ERR_INV_PARAM);
    assert(ERR_INV_PARAM == err);
    err = ERR_NONE;

    err = pop_front_llist_59(list, (void *)0);
    printf("Assert: err = %d == %d ERR_INV_PARAM\n", err, ERR_INV_PARAM);
    assert(ERR_INV_PARAM == err);
    err = ERR_NONE;

    err = pop_front_llist_59(list, &dummy_node);
    printf("Assert: err = %d == %d ERR_CONTAINER_EMPTY\n", err, ERR_CONTAINER_EMPTY);
    assert(ERR_CONTAINER_EMPTY == err);
    err = ERR_NONE;

    // remove node from list
    puts("- - - - - - - - - - - - - - - - -");
    puts("Testing remove_node_from_list()...");

    err = remove_given_node_from_llist_59((void *)0, dummy_node);
    printf("Assert: err = %d == %d ERR_INV_PARAM\n", err, ERR_INV_PARAM);
    assert(ERR_INV_PARAM == err);
    err = ERR_NONE;

    err = remove_given_node_from_llist_59(list, (void *)0);
    printf("Assert: err = %d == %d ERR_INV_PARAM\n", err, ERR_INV_PARAM);
    assert(ERR_INV_PARAM == err);
    err = ERR_NONE;

    err = remove_given_node_from_llist_59(list, node1);
    printf("Assert: err = %d == %d ERR_CONTAINER_EMPTY\n", err, ERR_CONTAINER_EMPTY);
    assert(ERR_CONTAINER_EMPTY == err);
    err = ERR_NONE;

    err = push_front_llist_59(list, node1); // populate list for next test
    if (ERR_NONE != err)
        return err;
    err = remove_given_node_from_llist_59(list, node2);
    printf("Assert: err = %d == %d ERR_OBJ_NOT_FOUND\n", err, ERR_OBJ_NOT_FOUND);
    assert(ERR_OBJ_NOT_FOUND == err);
    err = ERR_NONE;

    // insert node into list
    puts("- - - - - - - - - - - - - - - - -");
    puts("Testing insert_node_into_list()...");

    err = insert_node_into_llist_59((void *)0, dummy_node, 1);
    printf("Assert: err = %d == %d ERR_INV_PARAM\n", err, ERR_INV_PARAM);
    assert(ERR_INV_PARAM == err);
    err = ERR_NONE;

    err = insert_node_into_llist_59(list, (void *)0, 1);
    printf("Assert: err = %d == %d ERR_INV_PARAM\n", err, ERR_INV_PARAM);
    assert(ERR_INV_PARAM == err);
    err = ERR_NONE;

    err = remove_given_node_from_llist_59(list, node1);
    if (ERR_NONE != err)
        return err;
    err = insert_node_into_llist_59(list, node1, 1);
    printf("Assert: err = %d == %d ERR_NONE\n", err, ERR_NONE);
    assert(ERR_NONE == err);

    err = insert_node_into_llist_59(list, node2, 3);
    printf("Assert: err = %d == %d ERR_NONE\n", err, ERR_NONE);
    assert(ERR_NONE == err);

    // check head and tail values from insert passed list end test
    printf("Assert: head = %ld == %ld\n", *(i64 *)(list->head->node_obj), 33UL);
    assert(33 == *(i64 *)(list->head->node_obj));
    printf("Assert: head = %ld == %ld\n", *(i64 *)(list->head->next->node_obj), 59UL);
    assert(59 == *(i64 *)(list->head->next->node_obj));

    // Test clean up
    puts("- - - - - - - - - - - - - - - - -");
    puts("Test clean up...");
    err = deinit_llist_59(&list);

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

    puts("- - -  START OF LLIST TEST  - - -");
    puts("- - - LLIST EDGE CASES - - -");

    ERR_59_e err = test_llist_59_edge_cases();
    printf("ERROR CODE : %d\n", err);
    assert(ERR_NONE == err);

    puts("- - - - END OF LLIST TEST - - - -");
    return err;
}
