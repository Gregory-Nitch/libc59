/***********************************************************************************************************************
 * LICENSE : NONE, as in zilch, zipo, nada, null, nill, 0, zero. If you use this file and are not me you are wrong.
 *
 * @date : 2025-04-12
 * @author : Gregory Nitch
 *
 * @brief : Test cases for llist_node_59 types that cover edge cases the interface might encounter.
 **********************************************************************************************************************/

/*
========================================================================================================================
- - SYSTEM INCLUDES - -
========================================================================================================================
*/

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

ERR_59_e test_llist_node_59_edge_cases(void)
{
    ERR_59_e err = ERR_NONE;

    // Test init_llist_node
    puts("- - - - - - - - - - -");
    puts("Checking init_llist_node()");

    llist_node_59 *dummy_node = (void *)0;

    err = init_llist_node_59((void *)0, (void *)0, (void *)0);
    printf("Assert: err = %d == %d = ERR_INV_PARAM\n", err, ERR_INV_PARAM);
    assert(ERR_INV_PARAM == err);
    err = ERR_NONE;

    // Test destroy node
    puts("- - - - - - - - - - -");
    puts("Checking destroy_llist_node()");

    err = destroy_llist_node_59((void *)0);
    printf("Assert: err = %d == %d = ERR_INV_PARAM\n", err, ERR_INV_PARAM);
    assert(ERR_INV_PARAM == err);
    err = ERR_NONE;

    err = destroy_llist_node_59(&dummy_node);
    printf("Assert: err = %d == %d = ERR_INV_PARAM\n", err, ERR_INV_PARAM);
    assert(ERR_INV_PARAM == err);
    err = ERR_NONE;

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
    puts("- - - LLIST NODE EDGE CASES - - -");

    ERR_59_e err = test_llist_node_59_edge_cases();
    printf("ERROR CODE : %d\n", err);
    assert(ERR_NONE == err);

    puts("- - - - END OF LLIST TEST - - - -");
    return err;
}
