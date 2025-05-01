/***********************************************************************************************************************
 * LICENSE : NONE, as in zilch, zipo, nada, null, nill, 0, zero. If you use this file and are not me you are wrong.
 *
 * @date : 2025-05-01
 * @author : Gregory Nitch
 *
 * @brief : Test cases for dlist_node_59 types that cover edge cases the interface might encounter.
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

#include "dlist_59.h"

/*
========================================================================================================================
- - UNIT TESTS - -
========================================================================================================================
*/

ERR_59_e test_dlist_node_59_edge_cases(void)
{
    ERR_59_e err = ERR_NONE;

    // Test init_dlist_node
    puts("- - - - - - - - - - -");
    puts("Checking init_dlist_node()");

    dlist_node_59 *dummy_node = (void *)0;

    err = init_dlist_node_59((void *)0, (void *)0, (void *)0, (void *)0);
    printf("Assert: err = %d == %d = ERR_INV_PARAM\n", err, ERR_INV_PARAM);
    assert(ERR_INV_PARAM == err);
    err = ERR_NONE;

    // Test destroy node
    puts("- - - - - - - - - - -");
    puts("Checking destroy_dlist_node()");

    err = destroy_dlist_node_59((void *)0);
    printf("Assert: err = %d == %d = ERR_INV_PARAM\n", err, ERR_INV_PARAM);
    assert(ERR_INV_PARAM == err);
    err = ERR_NONE;

    err = destroy_dlist_node_59(&dummy_node);
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
    puts("- - -  START OF DLIST TEST  - - -");
    puts("- - - DLIST NODE EDGE CASES - - -");

    ERR_59_e err = test_dlist_node_59_edge_cases();
    printf("ERROR CODE : %d\n", err);
    assert(ERR_NONE == err);

    puts("- - - - END OF DLIST TEST - - - -");
    return err;
}
