/***********************************************************************************************************************
 * LICENSE : NONE, as in zilch, zipo, nada, null, nill, 0, zero. If you use this file and are not me you are wrong.
 *
 * @date : 2025-03-24
 * @author : Gregory Nitch
 *
 * @brief : Main for linked list testing.
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

ERR_59_e test_list_manipulations(void)
{
    ERR_59_e err = ERR_NONE;

    // Init list and nodes
    llist_59 *list;
    err = init_llist_59(list, U64, 0);
    if (err != ERR_NONE)
        return err;

    for (size_t i = 1; i < 6; i++)
    {
        llist_node_59 *node;
        err = init_llist_node_59(node, (void *)0, malloc(sizeof(u64)));
        if (err != ERR_NONE)
            return err;

        *((u64 *)node->node_obj) = (u64)i;

        err = push_back_llist_59(list, node);
        if (err != ERR_NONE)
            return err;
    }

    // Verify list contents
    llist_node_59 *node = list->head;
    for (size_t i = 1; i < 6; i++)
    {
        assert(*((u64 *)node->node_obj) == i);
        node = node->next;
    }

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

    assert(test_list_manipulations() == ERR_NONE);

    puts("- - - - END OF LLIST TEST - - - -");
    return EXIT_SUCCESS;
}
