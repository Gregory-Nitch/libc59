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
    (void)argc;
    (void)argv;

    puts("- - -  START OF COMMON CONTAINER TEST  - - -");
    puts("- - - COMMON CONTAINER EDGE CASES - - -");

    ERR_59_e err = test_common_59_edge_cases();
    printf("ERROR CODE : %d\n", err);
    assert(ERR_NONE == err);

    puts("- - - - END OF COMMON CONTAINER TEST - - - -");
    return err;
}
