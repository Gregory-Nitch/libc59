/***********************************************************************************************************************
 * LICENSE : NONE, as in zilch, zipo, nada, null, nill, 0, zero. If you use this file and are not me you are wrong.
 *
 * @date : 2025-04-30
 * @author : Gregory Nitch
 *
 * @brief : Test cases for libc59 common that cover the basic interface functions.
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

ERR_59_e test_common_59_interface(void)
{
    ERR_59_e err = ERR_NONE;

    // is_same_mem_addr()
    puts("- - - - - - - - - - -");
    puts("Testing is_same_mem_addr()...");
    bool flag = false;
    u64 a = 1UL;
    u64 b = 2UL;

    is_same_mem_addr_59(&a, &b, &flag);
    printf("Assert: addr1 %p != %p addr2\n", &a, &b);
    assert(false == flag);

    is_same_mem_addr_59(&a, &a, &flag);
    printf("Assert: addr1 %p == %p addr1\n", &a, &a);
    assert(true == flag);

    return err;
}

/*
========================================================================================================================
- - MAIN - -
========================================================================================================================
*/

int main(int argc, char const *argv[])
{
    puts("- - -  START OF COMMON TEST  - - -");
    puts("- - - COMMON INTERFACE - - -");

    ERR_59_e err = test_common_59_interface();
    printf("ERROR CODE : %d\n", err);
    assert(ERR_NONE == err);

    puts("- - - - END OF COMMON TEST - - - -");
    return err;
}
