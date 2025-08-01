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

#include "common.h"

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
    /* Values assigned to prevent uninitialized compiler warnings, though these values are not acutally used. */
    *obj_A = 11;
    *obj_B = 59;

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
    (void)argc;
    (void)argv;

    puts("- - -  START OF CONTAINER COMMON TEST  - - -");
    puts("- - - CONTAINER COMMON EDGE CASES - - -");

    ERR_59_e err = test_common_59_edge_cases();
    printf("ERROR CODE : %d\n", err);
    assert(ERR_NONE == err);

    puts("- - - - END OF CONTAINER COMMON TEST - - - -");
    return err;
}
