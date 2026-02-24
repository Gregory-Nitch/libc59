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
 * @date: 2025-04-30
 * @author: Gregory Nitch
 *
 * @brief: Test cases for llist_node_59 types that cover the basic interface functions.
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

#include "containers_common.h"

/*
========================================================================================================================
- - UNIT TESTS - -
========================================================================================================================
*/

void test_unsigned_node_obj_59_comparisons(TYPE_59_e const type,
                                           u64 const max,
                                           void const *const obj_A,
                                           void const *const obj_B)
{
    puts("- - - - - - - - - - -");
    i64 dif = 0;
    for (u64 i = 0; i < max; i = (i << 1) + 1)
    {
        *((u64 *)obj_A) = i;
        for (u64 j = 0; j < max; j = (j << 1) + 1)
        {
            *((u64 *)obj_B) = j;
            compare_node_obj_59(type, obj_A, obj_B, &dif);
            printf("Assert: obj1: %lu - obj2: %lu == %ld: dif \n", i, j, dif);
            assert(((i64)i - (i64)j) == dif); // We only send at most INT32_MAX to this function so this i64 cast should be acceptable.
        }
        for (u64 j = max; j > 0; j >>= 1)
        {
            *((u64 *)obj_B) = j;
            compare_node_obj_59(type, obj_A, obj_B, &dif);
            printf("Assert: obj1: %lu - obj2: %lu == %ld: dif \n", i, j, dif);
            assert(((i64)i - (i64)j) == dif); // We only send at most INT32_MAX to this function so this i64 cast should be acceptable.
        }
    }
    puts("- - - - - - - - - - -");
}

void test_signed_node_obj_59_comparisons(TYPE_59_e const type,
                                         size_t const size,
                                         void const *const obj_A,
                                         void const *const obj_B)
{
    puts("- - - - - - - - - - -");
    i64 mask = 1;
    i64 dif = 0;
    size_t i_cnt = 0;
    size_t j_cnt = 0;
    bool i_sign_flag = true;
    bool j_sign_flag = true;
    i64 i = -1;
    i64 j = -1;
    while (i_sign_flag || i_cnt < (size * 8) - 1) // val bits + 1 for sign
    {
        *((i64 *)obj_A) = i;

        while (j_sign_flag || j_cnt < (size * 8) - 1)
        {
            *((i64 *)obj_B) = j;
            compare_node_obj_59(type, obj_A, obj_B, &dif);
            printf("Assert: obj1: %ld - obj2: %ld == %ld: dif \n", i, j, dif);
            assert((i - j) == dif);

            if (j_sign_flag)
                j &= ~(mask << j_cnt);
            else
                j = mask << j_cnt;
            j_cnt++;

            if (j_sign_flag && (size * 8) - 1 == j_cnt)
            {
                j = 0;
                j_cnt = 0;
                j_sign_flag = false;
            }
        }
        j = -1;
        j_cnt = 0;
        j_sign_flag = true;

        if (i_sign_flag)
            i &= ~(mask << i_cnt);
        else
            i = mask << i_cnt;
        i_cnt++;

        if (i_sign_flag && (size * 8) - 1 == i_cnt)
        {
            i = 0;
            i_cnt = 0;
            i_sign_flag = false;
        }
    }
    puts("- - - - - - - - - - -");
}

ERR_59_e test_container_common_59_interface(void)
{
    ERR_59_e err = ERR_NONE;

    // Compare_node_obj()
    puts("- - - - - - - - - - -");
    puts("Testing compare_node_obj()...");
    i64 dif = 0;
    u64 a = 1UL;
    u64 b = 2UL;
    u64 c = 3UL;

    compare_node_obj_59(U64_PTR, &a, &b, &dif);
    printf("Assert: node1 obj < node2 obj: dif == %ld\n", dif);
    assert(-1 == dif);

    compare_node_obj_59(U64_PTR, &b, &b, &dif);
    printf("Assert: node2 obj == node2 obj: dif == %ld\n", dif);
    assert(0 == dif);

    compare_node_obj_59(U64_PTR, &c, &b, &dif);
    printf("Assert: node3 obj > node2 obj: dif == %ld\n", dif);
    assert(1 == dif);

    // Unsigned comparison Iterations
    test_unsigned_node_obj_59_comparisons(U8_PTR, UINT8_MAX, &a, &b);
    test_unsigned_node_obj_59_comparisons(U16_PTR, UINT16_MAX, &a, &b);
    test_unsigned_node_obj_59_comparisons(U32_PTR, UINT32_MAX, &a, &b);
    test_unsigned_node_obj_59_comparisons(U64_PTR, UINT32_MAX, &a, &b); // We only send at most INT32_MAX here to prevent overflow.

    // Signed comparison iterations
    i64 x = 0;
    i64 y = 0;
    test_signed_node_obj_59_comparisons(I8_PTR, sizeof(i8), &x, &y);
    test_signed_node_obj_59_comparisons(CHAR_PTR, sizeof(char), &x, &y);
    test_signed_node_obj_59_comparisons(I16_PTR, sizeof(i16), &x, &y);
    test_signed_node_obj_59_comparisons(I32_PTR, sizeof(i32), &x, &y);
    test_signed_node_obj_59_comparisons(I64_PTR, sizeof(i32), &x, &y);

    // String comparisons
    char str_A[] = "abc";
    char str_B[] = "cba";

    compare_node_obj_59(STR, str_A, str_B, &dif);
    printf("Assert: str_A = %s - str_B = %s < 0\n", str_A, str_B);
    assert(0 > dif);

    compare_node_obj_59(STR, str_B, str_A, &dif);
    printf("Assert: str_B = %s - str_A = %s > 0\n", str_B, str_A);
    assert(0 < dif);

    compare_node_obj_59(STR, str_A, str_A, &dif);
    printf("Assert: str_A = %s - str_A = %s == 0\n", str_A, str_A);
    assert(0 == dif);

    return err;
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
    puts("- - - CONTAINER COMMON INTERFACE - - -");

    ERR_59_e err = test_container_common_59_interface();
    printf("ERROR CODE: %d\n", err);
    assert(ERR_NONE == err);

    puts("- - - - END OF CONTAINER COMMON TEST - - - -");
    return err;
}
