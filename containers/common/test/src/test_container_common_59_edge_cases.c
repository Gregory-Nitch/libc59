/***********************************************************************************************************************
 * LICENSE : NONE, as in zilch, zipo, nada, null, nill, 0, zero. If you use this file and are not me you are wrong.
 *
 * @date : 2025-04-29
 * @author : Gregory Nitch
 *
 * @brief : Test cases for conatiner common functions that cover edge cases the interface might encounter.
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

#include "container_common_59.h"

/*
========================================================================================================================
- - UNIT TESTS - -
========================================================================================================================
*/

ERR_59_e test_common_59_edge_cases(void)
{
    ERR_59_e err = ERR_NONE;

    // compare_node_obj()
    puts("- - - - - - - - - - -");
    puts("Testing compare_node_obj()...");
    TYPE_59_e type = U64;
    u64 a = 1UL;
    u64 b = 2UL;
    i64 dif = 0;

    err = compare_node_obj_59(type, (void *)0, &b, &dif);
    printf("Assert : err = %d == %d = ERR_INV_PARAM\n", err, ERR_INV_PARAM);
    assert(ERR_INV_PARAM == err);

    err = compare_node_obj_59(type, &a, (void *)0, &dif);
    printf("Assert : err = %d == %d = ERR_INV_PARAM\n", err, ERR_INV_PARAM);
    assert(ERR_INV_PARAM == err);

    err = compare_node_obj_59(type, &a, &b, (void *)0);
    printf("Assert : err = %d == %d = ERR_INV_PARAM\n", err, ERR_INV_PARAM);
    assert(ERR_INV_PARAM == err);

    return ERR_NONE;
}

/*
========================================================================================================================
- - MAIN - -
========================================================================================================================
*/

int main(int argc, char const *argv[])
{
    puts("- - -  START OF COMMON CONTAINER TEST  - - -");
    puts("- - - COMMON CONTAINER EDGE CASES - - -");

    ERR_59_e err = test_common_59_edge_cases();
    printf("ERROR CODE : %d\n", err);
    assert(ERR_NONE == err);

    puts("- - - - END OF COMMON CONTAINER TEST - - - -");
    return err;
}
