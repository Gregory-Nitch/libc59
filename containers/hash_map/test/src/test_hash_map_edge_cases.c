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
 * @date : 2025-05-18
 * @author : Gregory Nitch
 *
 * @brief : Test cases for hash_map_59 types that cover edge cases that the interface might encounter.
 **********************************************************************************************************************/

/*
========================================================================================================================
- - SYSTEM INCLUDES - -
========================================================================================================================
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
========================================================================================================================
- - MODULE INCLUDES - -
========================================================================================================================
*/

#include "hash_map.h"

/*
========================================================================================================================
- - UNIT TESTS - -
========================================================================================================================
*/

ERR_59_e test_hash_map_59_edge_cases(void)
{
    ERR_59_e err = ERR_NONE;

    // Init hash_map
    puts("- - - - - - - - - - - - - - - - -");
    puts("Initializing hash_maps...");

    hash_map_59 *u64_map = (void *)0;
    err = init_hash_map_59(&u64_map, U64_PTR, STR, 0, 0, 0);
    if (ERR_NONE != err)
        return err;

    hash_map_59 *str_map = (void *)0;
    err = init_hash_map_59(&str_map, STR, U64_PTR, 0, 0, 0);
    if (ERR_NONE != err)
        return err;

    // Upsert into hashmap
    puts("- - - - - - - - - - - - - - - - -");
    puts("upsert_hash_map() for test init...");

    u64 *u1 = malloc(sizeof(u64));
    *u1 = 1;
    u64 *u2 = malloc(sizeof(u64));
    *u2 = 2;
    u64 *u3 = malloc(sizeof(u64));
    *u3 = 3;
    str str1 = malloc(sizeof(char) * 4);
    str1[0] = 'a';
    str1[1] = 'b';
    str1[2] = 'c';
    str1[3] = '\0';
    str str2 = malloc(sizeof(char) * 4);
    str2[0] = 'd';
    str2[1] = 'e';
    str2[2] = 'f';
    str2[3] = '\0';
    str str3 = malloc(sizeof(char) * 4);
    str3[0] = 'g';
    str3[1] = 'h';
    str3[2] = 'i';
    str3[3] = '\0';

    u64 *u4 = malloc(sizeof(u64));
    *u4 = 4;
    u64 *u5 = malloc(sizeof(u64));
    *u5 = 5;
    u64 *u6 = malloc(sizeof(u64));
    *u6 = 6;
    str str4 = malloc(sizeof(char) * 4);
    str4[0] = 'l';
    str4[1] = 'm';
    str4[2] = 'n';
    str4[3] = '\0';
    str str5 = malloc(sizeof(char) * 4);
    str5[0] = 'r';
    str5[1] = 's';
    str5[2] = 't';
    str5[3] = '\0';
    str str6 = malloc(sizeof(char) * 4);
    str6[0] = 'x';
    str6[1] = 'y';
    str6[2] = 'z';
    str6[3] = '\0';

    err = upsert_into_hash_map_59(u64_map, u1, str1);
    printf("Assert: ERR_NONE == %d = upsert_into_hash_map()\n", err);
    assert(ERR_NONE == err);

    err = upsert_into_hash_map_59(u64_map, u2, str2);
    printf("Assert: ERR_NONE == %d = upsert_into_hash_map()\n", err);
    assert(ERR_NONE == err);

    err = upsert_into_hash_map_59(u64_map, u3, str3);
    printf("Assert: ERR_NONE == %d = upsert_into_hash_map()\n", err);
    assert(ERR_NONE == err);

    err = upsert_into_hash_map_59(str_map, str4, u4);
    printf("Assert: ERR_NONE == %d = upsert_into_hash_map()\n", err);
    assert(ERR_NONE == err);

    err = upsert_into_hash_map_59(str_map, str5, u5);
    printf("Assert: ERR_NONE == %d = upsert_into_hash_map()\n", err);
    assert(ERR_NONE == err);

    err = upsert_into_hash_map_59(str_map, str6, u6);
    printf("Assert: ERR_NONE == %d = upsert_into_hash_map()\n", err);
    assert(ERR_NONE == err);

    hash_map_59 *u64_map_dummy = (void *)0;
    u64 *u_dummy = (void *)0;

    // Test init_hash_map edge cases
    puts("- - - - - - - - - - - - - - - - -");
    puts("Test init_hash_map...");

    err = init_hash_map_59((void *)0, U8_PTR, U8_PTR, 0, 0, 0);
    printf("Assert: ERR_INV_PARAM == %d = init_hash_map() with void ptr\n", err);
    assert(ERR_INV_PARAM == err);

    err = init_hash_map_59(&u64_map_dummy, U64_PTR, U64_PTR, 0, 0, 2);
    printf("Assert: ERR_INV_PARAM == %d = init_hash_map() with bad prime\n", err);
    assert(ERR_INV_PARAM == err);

    // Test deinit_hash_map edge cases
    puts("- - - - - - - - - - - - - - - - -");
    puts("Test deinit_hash_map...");

    err = deinit_hash_map_59((void *)0);
    printf("Assert: ERR_INV_PARAM == %d = deinit_hash_map() with void ptr\n", err);
    assert(ERR_INV_PARAM == err);

    err = deinit_hash_map_59(&u64_map_dummy);
    printf("Assert: ERR_INV_PARAM == %d = deinit_hash_map() with void ptr\n", err);
    assert(ERR_INV_PARAM == err);

    // Test upsert_hash_map edge cases
    puts("- - - - - - - - - - - - - - - - -");
    puts("Test upsert_hash_map...");

    err = upsert_into_hash_map_59(u64_map_dummy, u1, str1);
    printf("Assert: ERR_INV_PARAM == %d = upsert_hash_map()\n", err);
    assert(ERR_INV_PARAM == err);

    err = upsert_into_hash_map_59(u64_map, u_dummy, str1);
    printf("Assert: ERR_INV_PARAM == %d = upsert_hash_map()\n", err);
    assert(ERR_INV_PARAM == err);

    err = upsert_into_hash_map_59(u64_map, u1, u_dummy);
    printf("Assert: ERR_INV_PARAM == %d = upsert_hash_map()\n", err);
    assert(ERR_INV_PARAM == err);

    // Test get_from_hash_map edge cases
    puts("- - - - - - - - - - - - - - - - -");
    puts("Test get_from_hash_map...");

    err = get_from_hash_map_59(u64_map_dummy, u1, (void *)&str1);
    printf("Assert: ERR_INV_PARAM == %d = get_from_hash_map()\n", err);
    assert(ERR_INV_PARAM == err);

    err = get_from_hash_map_59(u64_map, u_dummy, (void *)&str1);
    printf("Assert: ERR_INV_PARAM == %d = get_from_hash_map()\n", err);
    assert(ERR_INV_PARAM == err);

    // Test remove_hash_map edge cases
    puts("- - - - - - - - - - - - - - - - -");
    puts("Test remove_from_hash_map...");

    key_val_pair_59 *pair = (void *)0;

    err = remove_from_hash_map_59(u64_map_dummy, u1, &pair);
    printf("Assert: ERR_INV_PARAM == %d = remove_from_hash_map()\n", err);
    assert(ERR_INV_PARAM == err);

    err = remove_from_hash_map_59(u64_map, u_dummy, &pair);
    printf("Assert: ERR_INV_PARAM == %d = remove_from_hash_map()\n", err);
    assert(ERR_INV_PARAM == err);

    u64 *test_num = malloc(sizeof(u64));
    *test_num = 99;

    err = remove_from_hash_map_59(u64_map, test_num, &pair);
    printf("Assert: ERR_OBJ_NOT_FOUND == %d = remove_from_hash_map()\n", err);
    assert(ERR_OBJ_NOT_FOUND == err);

    // Test resize_hash_map edge cases
    puts("- - - - - - - - - - - - - - - - -");
    puts("Test resize_hash_map...");

    err = resize_table_hash_map_59(u64_map_dummy, 23);
    printf("Assert: ERR_INV_PARAM == %d = resize_hash_map()\n", err);
    assert(ERR_INV_PARAM == err);

    // Test clean up
    puts("- - - - - - - - - - - - - - - - -");
    puts("Test clean up...");
    err = deinit_hash_map_59(&u64_map);
    err = deinit_hash_map_59(&str_map);
    free(test_num);

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

    puts("- - -  START OF HASH MAP TEST  - - -");
    puts("- - - HASH MAP EDGE CASES - - -");

    ERR_59_e err = test_hash_map_59_edge_cases();
    printf("ERROR CODE : %d\n", err);
    assert(ERR_NONE == err);

    puts("- - - - END OF HASH MAP TEST - - - -");
    return err;
}
