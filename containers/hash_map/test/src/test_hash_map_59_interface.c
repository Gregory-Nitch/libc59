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
 * @brief : Test cases for hash maps that cover the basic interface interactions.
 **********************************************************************************************************************/

/*
========================================================================================================================
- - SYSTEM INCLUDES - -
========================================================================================================================
*/

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
========================================================================================================================
- - MODULE INCLUDES - -
========================================================================================================================
*/

#include "hash_map_59.h"

/*
========================================================================================================================
- - UNIT TESTS - -
========================================================================================================================
*/

ERR_59_e test_hash_map_59_interface(void)
{
    ERR_59_e err = ERR_NONE;

    // Init hash_map
    puts("- - - - - - - - - - - - - - - - -");
    puts("Initializing hash_map...");
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
    puts("upsert_hash_map()...");

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

    // Get from hashmap
    puts("- - - - - - - - - - - - - - - - -");
    puts("get_from_hash_map()...");
    void *val = (void *)0;

    err = get_from_hash_map_59(u64_map, u1, &val);
    printf("Assert: ERR_NONE == %d = get_from_hash_map()\n", err);
    assert(ERR_NONE == err);
    printf("Assert: val = abc == %s = \n", (str)val);
    assert(0 == strcmp("abc\0", (str)val));

    err = get_from_hash_map_59(u64_map, u2, &val);
    printf("Assert: ERR_NONE == %d = get_from_hash_map()\n", err);
    assert(ERR_NONE == err);
    printf("Assert: val = def == %s = \n", (str)val);
    assert(0 == strcmp("def\0", (str)val));

    err = get_from_hash_map_59(u64_map, u3, &val);
    printf("Assert: ERR_NONE == %d = get_from_hash_map()\n", err);
    assert(ERR_NONE == err);
    printf("Assert: val = ghi == %s = \n", (str)val);
    assert(0 == strcmp("ghi\0", (str)val));

    err = get_from_hash_map_59(str_map, str4, &val);
    printf("Assert: ERR_NONE == %d = get_from_hash_map()\n", err);
    assert(ERR_NONE == err);
    printf("Assert: val = 4 == %lu = \n", *(u64 *)val);
    assert(4 == *(u64 *)val);

    err = get_from_hash_map_59(str_map, str5, &val);
    printf("Assert: ERR_NONE == %d = get_from_hash_map()\n", err);
    assert(ERR_NONE == err);
    printf("Assert: val = 5 == %lu = \n", *(u64 *)val);
    assert(5 == *(u64 *)val);

    err = get_from_hash_map_59(str_map, str6, &val);
    printf("Assert: ERR_NONE == %d = get_from_hash_map()\n", err);
    assert(ERR_NONE == err);
    printf("Assert: val = 6 == %lu = \n", *(u64 *)val);
    assert(6 == *(u64 *)val);

    //  Remove from hashmap
    puts("- - - - - - - - - - - - - - - - -");
    puts("remove_from_hash_map()...");
    key_val_pair_59 *pair = (void *)0;

    for (size_t i = 1; i < 4; i++)
    {
        err = remove_from_hash_map_59(u64_map, &i, &pair);
        printf("Assert: ERR_NONE == %d = remove_from_hash_map()\n", err);
        assert(ERR_NONE == err);
        printf("Assert: pair->key = %lu == %lu = i\n", i, *(u64 *)(pair->key));
        assert(i == *(u64 *)(pair->key));
        free(pair->key);
        free(pair->val);
        free(pair);
        pair = (void *)0;
    }

    str strs[] = {str4, str5, str6};
    for (size_t i = 0; i < 3; i++)
    {
        err = remove_from_hash_map_59(str_map, strs[i], &pair);
        printf("Assert: ERR_NONE == %d = remove_from_hash_map()\n", err);
        assert(ERR_NONE == err);
        printf("Assert: pair->val = %lu == %lu = i + 4\n", i + 4, *(u64 *)(pair->val));
        assert(i + 4 == *(u64 *)(pair->val));
        free(pair->key);
        free(pair->val);
        free(pair);
        pair = (void *)0;
    }

    // Resize hash map table
    puts("- - - - - - - - - - - - - - - - -");
    puts("resize_hash_map_table()...");

    val = (void *)0;
    for (size_t i = 0; i < 100; i++)
    {
        u64 *num = malloc(sizeof(u64));
        if (!num)
            return ERR_NO_MEM;
        *num = i;
        str a_str = malloc(sizeof(char) * 4);
        if (!a_str)
            return ERR_NO_MEM;
        for (size_t j = 0; j < 3; j++)
        {
            a_str[j] = 'a' + j;
        }
        a_str[3] = '\0';
        err = upsert_into_hash_map_59(u64_map, num, a_str);
        printf("Assert: ERR_NONE == %d = upsert_into_hash_map() for table resize [%lu]\n", err, i);
        assert(ERR_NONE == err);

        err = get_from_hash_map_59(u64_map, num, &val);
        printf("Assert: ERR_NONE == %d = get_from_hash_map() for table resize [%lu]\n", err, i);
        assert(ERR_NONE == err);
        printf("Assert: a_str = %s == %s = get_from_hash_map() val for table resize [%lu]\n", a_str, (str)val, i);
        assert(0 == strcmp(a_str, (str)val));
    }

    puts("resizing table to size 19...");
    err = resize_table_hash_map_59(u64_map, 19);
    printf("Assert: ERR_NONE == %d = resize_table_hash_map()\n", err);
    assert(ERR_NONE == err);

    // Test clean up
    puts("- - - - - - - - - - - - - - - - -");
    puts("Test clean up...");
    err = deinit_hash_map_59(&u64_map);
    err = deinit_hash_map_59(&str_map);

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
    puts("- - - INTERFACE TESTS - - -");

    ERR_59_e err = test_hash_map_59_interface();
    printf("ERROR CODE : %d\n", err);
    assert(ERR_NONE == err);

    puts("- - - - END OF HASH_MAP TEST - - - -");
    return err;
}
