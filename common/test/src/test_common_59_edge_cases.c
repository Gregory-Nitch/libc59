/***********************************************************************************************************************
 * LICENSE : NONE, as in zilch, zipo, nada, null, nill, 0, zero. If you use this file and are not me you are wrong.
 *
 * @date : 2025-04-30
 * @author : Gregory Nitch
 *
 * @brief : Test cases for common functions that cover edge cases the interface might encounter.
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

#include "libc59_common.h"

/*
========================================================================================================================
- - UNIT TESTS - -
========================================================================================================================
*/

ERR_59_e test_common_59_edge_cases(void)
{
    ERR_59_e err = ERR_NONE;

    // Allocate objects
    puts("- - - - - - - - - - -");
    puts("Initializing memory...");
    u64 *obj_A = malloc(sizeof(u64));
    u64 *obj_B = malloc(sizeof(u64));

    // Test is same mem addr
    puts("- - - - - - - - - - -");
    puts("Checking is_same_mem_addr()");

    err = is_same_mem_addr_59(obj_A, obj_B, (void *)0);
    printf("Assert: err = %d == %d = ERR_INV_PARAM\n", err, ERR_INV_PARAM);
    assert(ERR_INV_PARAM == err);

    // Test cleanup
    puts("- - - - - - - - - - -");
    puts("Cleaning up test assets...");

    free(obj_A);
    free(obj_B);

    return ERR_NONE;
}

/*
========================================================================================================================
- - MAIN - -
========================================================================================================================
*/

int main(int argc, char const *argv[])
{
    puts("- - -  START OF CONTAINER COMMON TEST  - - -");
    puts("- - - CONTAINER COMMON EDGE CASES - - -");

    ERR_59_e err = test_common_59_edge_cases();
    printf("ERROR CODE : %d\n", err);
    assert(ERR_NONE == err);

    puts("- - - - END OF CONTAINER COMMON TEST - - - -");
    return err;
}
