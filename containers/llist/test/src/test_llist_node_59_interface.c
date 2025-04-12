/***********************************************************************************************************************
 * LICENSE : NONE, as in zilch, zipo, nada, null, nill, 0, zero. If you use this file and are not me you are wrong.
 *
 * @date : 2025-04-12
 * @author : Gregory Nitch
 *
 * @brief : Test cases for llist_node_59 types that cover the basic interface functions.
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

ERR_59_e test_llist_node_59_interface(void)
{
    ERR_59_e err = ERR_NONE;
    // init nodes
    puts("- - - - - - - - - - -");
    puts("Initializing nodes...");
    llist_node_59 *node1;
    llist_node_59 *node2;
    llist_node_59 *other2;
    llist_node_59 *node3;
    llist_59 *list;

    err = init_llist_node_59(&node1, (void *)0, malloc(sizeof(u64)));
    err = init_llist_node_59(&node2, (void *)0, malloc(sizeof(u64)));
    err = init_llist_node_59(&other2, (void *)0, malloc(sizeof(u64)));
    err = init_llist_node_59(&node3, (void *)0, malloc(sizeof(u64)));
    err = init_llist_59(&list, U64_PTR, 0);
    if (ERR_NONE != err)
        return err;

    *((u64 *)node1->node_obj) = 1UL;
    *((u64 *)node2->node_obj) = 2UL;
    *((u64 *)other2->node_obj) = 2UL;
    *((u64 *)node3->node_obj) = 3UL;

    printf("Assert: node1 = val %lu at %p\n", *((u64 *)node1->node_obj), node1);
    assert(1UL == *((u64 *)node1->node_obj));
    printf("Assert: node2 = val %lu at %p\n", *((u64 *)node2->node_obj), node2);
    assert(2UL == *((u64 *)node2->node_obj));
    printf("Assert: other2 = val %lu at %p\n", *((u64 *)other2->node_obj), other2);
    assert(2UL == *((u64 *)other2->node_obj));
    printf("Assert: node3 = val %lu at %p\n", *((u64 *)node3->node_obj), node3);
    assert(3UL == *((u64 *)node3->node_obj));

    // compare_nodes()
    puts("- - - - - - - - - - -");
    puts("Testing compare_llist_nodes()...");
    i64 dif = 0;

    compare_llist_nodes_59(list, node1, node2, &dif);
    printf("Assert: node1 obj < node2 obj : dif == %ld\n", dif);
    assert(-1 == dif);

    compare_llist_nodes_59(list, node2, other2, &dif);
    printf("Assert: node2 obj == other2 obj : dif == %ld\n", dif);
    assert(0 == dif);

    compare_llist_nodes_59(list, node3, node2, &dif);
    printf("Assert: node3 obj > node2 obj : dif == %ld\n", dif);
    assert(1 == dif);

    // is_same_llist_node()
    puts("- - - - - - - - - - -");
    puts("Testing is_same_llist_node()...");
    bool flag = false;

    is_same_llist_node_59(node1, node2, &flag);
    printf("Assert: node1 %p != %p node2\n", node1, node2);
    assert(false == flag);

    is_same_llist_node_59(node1, node1, &flag);
    printf("Assert: node1 %p == %p node1\n", node1, node1);
    assert(true == flag);

    // destroy nodes
    puts("- - - - - - - - - - -");
    puts("destroying nodes...");
    err = destroy_llist_node_59(&node1);
    printf("Assert: (void*)0 = %p  == %p = node1(null)\n", (void *)0, node1);
    assert((void *)0 == node1);
    err = destroy_llist_node_59(&node2);
    printf("Assert: (void*)0 = %p  == %p = node2(null)\n", (void *)0, node2);
    assert((void *)0 == node2);
    err = destroy_llist_node_59(&other2);
    printf("Assert: (void*)0 = %p  == %p = other2(null)\n", (void *)0, other2);
    assert((void *)0 == other2);
    err = destroy_llist_node_59(&node3);
    printf("Assert: (void*)0 = %p  == %p = node3(null)\n", (void *)0, node3);
    assert((void *)0 == node3);
    err = destroy_llist_59(&list); // tested in llist no need to assert

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
    puts("- - - LLIST NODE INTERFACE - - -");

    ERR_59_e err = test_llist_node_59_interface();
    printf("ERROR CODE : %d\n", err);
    assert(ERR_NONE == err);

    puts("- - - - END OF LLIST TEST - - - -");
    return err;
}
