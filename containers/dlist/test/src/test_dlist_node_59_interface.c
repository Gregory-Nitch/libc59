/***********************************************************************************************************************
 * LICENSE : NONE, as in zilch, zipo, nada, null, nill, 0, zero. If you use this file and are not me you are wrong.
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

    // destroy nodes
    puts("- - - - - - - - - - -");
    puts("destroying nodes...");
    err = destroy_dlist_node_59(&node1);
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
    puts("- - -  START OF DLIST TEST  - - -");
    puts("- - - DLIST NODE INTERFACE - - -");

    ERR_59_e err = test_dlist_node_59_interface();
    printf("ERROR CODE : %d\n", err);
    assert(ERR_NONE == err);

    puts("- - - - END OF DLIST TEST - - - -");
    return err;
}
