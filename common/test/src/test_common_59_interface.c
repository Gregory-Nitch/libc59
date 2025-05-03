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
