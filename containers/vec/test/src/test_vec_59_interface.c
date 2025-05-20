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
 * @date : 2025-05-08
 * @author : Gregory Nitch
 *
 * @brief : Test cases for vectors that cover the basic interface interactions.
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

#include "vec_59.h"

/*
========================================================================================================================
- - UNIT TESTS - -
========================================================================================================================
*/

ERR_59_e test_vec_59_interface(void)
{
    ERR_59_e err = ERR_NONE;

    // Init vector
    puts("- - - - - - - - - - - - - - - - -");
    puts("Initializing vector...");

    vec_59 *vec = (void *)0;
    err = init_vec_59(&vec, 0, I64_PTR, false);
    if (ERR_NONE != err)
        return err;

    // Push_back
    puts("- - - - - - - - - - - - - - - - -");
    puts("Testing push_back()...");

    i64 *val;
    for (size_t i = 0; i < 4; i++)
    {
        val = malloc(sizeof(i64));
        *val = i;
        push_back_vec_59(vec, val);
        printf("Assert: i = %lu == %ld = vec->data[%lu]\n", i, *(i64 *)(vec->data[i]), i);
        assert(i == *(i64 *)(vec->data[i]));
    }

    puts("Checking size and capacity...");
    printf("Assert: 4 == %ld = vec->size\n", vec->size);
    assert(4 == vec->size);
    printf("Assert: 4 == %ld = vec->capacity\n", vec->capacity);
    assert(4 == vec->capacity);

    puts("Pushing one more to check resizing...");
    val = malloc(sizeof(i64));
    *val = 4;
    push_back_vec_59(vec, val);

    puts("Checking size and capacity...");
    printf("Assert: 5 == %ld = vec->size\n", vec->size);
    assert(5 == vec->size);
    printf("Assert: 8 == %ld = vec->capacity\n", vec->capacity);
    assert(8 == vec->capacity);

    // Pop_back
    puts("- - - - - - - - - - - - - - - - -");
    puts("Testing pop_back()...");

    err = pop_back_vec_59(vec, (void *)&val);
    if (ERR_NONE != err)
        return err;

    printf("Assert: 4 == %ld = popped val\n", *val);
    assert(4 == *val);

    puts("Checking size and capacity...");
    printf("Assert: 4 == %ld = vec->size\n", vec->size);
    assert(4 == vec->size);
    printf("Assert: 4 == %ld = vec->capacity\n", vec->capacity);
    assert(4 == vec->capacity);

    // Push_front
    puts("- - - - - - - - - - - - - - - - -");
    puts("Testing push_front()...");

    err = push_front_vec_59(vec, val);
    if (ERR_NONE != err)
        return err;

    printf("Assert: 4 == %ld = vec->data[0]\n", *(i64 *)(vec->data[0]));
    assert(4 == *(i64 *)(vec->data[0]));

    puts("Checking size and capacity...");
    printf("Assert: 5 == %ld = vec->size\n", vec->size);
    assert(5 == vec->size);
    printf("Assert: 8 == %ld = vec->capacity\n", vec->capacity);
    assert(8 == vec->capacity);

    puts("Checking values after push_front()...");
    for (size_t i = 1; i < vec->size; i++)
    {
        printf("Assert: i = %lu == %ld = vec->data[%lu]\n", i - 1, *(i64 *)(vec->data[i]), i - 1);
        assert(i - 1 == *(i64 *)(vec->data[i]));
    }

    // Pop_front
    puts("- - - - - - - - - - - - - - - - -");
    puts("Testing pop_front()...");

    err = pop_front_vec_59(vec, (void *)&val);
    if (ERR_NONE != err)
        return err;

    printf("Assert: 0 == %ld = vec->data[0]\n", *(i64 *)(vec->data[0]));
    assert(0 == *(i64 *)(vec->data[0]));

    printf("Assert: 4 == %ld = popped val\n", *val);
    assert(4 == *val);

    puts("Checking size and capacity...");
    printf("Assert: 4 == %ld = vec->size\n", vec->size);
    assert(4 == vec->size);
    printf("Assert: 4 == %ld = vec->capacity\n", vec->capacity);
    assert(4 == vec->capacity);

    err = push_back_vec_59(vec, val); // Repush val for clean up
    if (ERR_NONE != err)
        return err;

    // Remove_obj
    puts("- - - - - - - - - - - - - - - - -");
    puts("Testing remove_obj()...");

    bool found_val = false;

    err = remove_given_obj_from_vec_59(vec, val);
    if (ERR_NONE != err)
        return err;

    for (size_t i = 0; i < vec->size; i++)
    {
        if (4 == *(i64 *)(vec->data[i]))
            found_val = true;
    }

    printf("Assert: 4 not in list = %d\n", found_val);
    assert(!found_val);

    puts("Checking size and capacity...");
    printf("Assert: 4 == %ld = vec->size\n", vec->size);
    assert(4 == vec->size);
    printf("Assert: 4 == %ld = vec->capacity\n", vec->capacity);
    assert(4 == vec->capacity);

    err = push_back_vec_59(vec, val); // Repush val for clean up
    if (ERR_NONE != err)
        return err;

    found_val = false;

    val = (i64 *)vec->data[2];

    err = remove_given_obj_from_vec_59(vec, val);
    if (ERR_NONE != err)
        return err;

    for (size_t i = 0; i < vec->size; i++)
    {
        if (2 == *(i64 *)(vec->data[i]))
            found_val = true;
    }

    printf("Assert: 2 not in list = %d\n", found_val);
    assert(!found_val);

    err = insert_obj_into_vec_59(vec, val, 2); // Reinsert val for clean up and further tests
    if (ERR_NONE != err)
        return err;

    // insert_into_vec
    puts("- - - - - - - - - - - - - - - - -");
    puts("Testing insert_into_vec()...");

    val = malloc(sizeof(i64));
    *val = 59;

    puts("Putting 59 at idx 3...");
    err = insert_obj_into_vec_59(vec, (void *)val, 3);
    if (ERR_NONE != err)
        return err;

    printf("Assert: vec->data[3] = 59 == %ld\n", *(i64 *)vec->data[3]);
    assert(59 == *(i64 *)vec->data[3]);

    printf("Assert: vec->data[2] = 2 == %ld\n", *(i64 *)vec->data[2]);
    assert(2 == *(i64 *)vec->data[2]);

    printf("Assert: vec->data[4] = 3 == %ld\n", *(i64 *)vec->data[4]);
    assert(3 == *(i64 *)vec->data[4]);

    puts("Checking size and capacity...");
    printf("Assert: 6 == %ld = vec->size\n", vec->size);
    assert(6 == vec->size);
    printf("Assert: 8 == %ld = vec->capacity\n", vec->capacity);
    assert(8 == vec->capacity);

    err = remove_given_obj_from_vec_59(vec, val);
    if (ERR_NONE != err)
        return err;

    puts("Putting 59 at idx 0...");
    err = insert_obj_into_vec_59(vec, (void *)val, 0);
    if (ERR_NONE != err)
        return err;

    printf("Assert: vec->data[0] = 59 == %ld\n", *(i64 *)vec->data[0]);
    assert(59 == *(i64 *)vec->data[0]);

    err = remove_given_obj_from_vec_59(vec, val);
    if (ERR_NONE != err)
        return err;

    puts("Putting 59 at idx 5...");
    err = insert_obj_into_vec_59(vec, (void *)val, 5);
    if (ERR_NONE != err)
        return err;

    printf("Assert: vec->data[5] = 59 == %ld\n", *(i64 *)vec->data[5]);
    assert(59 == *(i64 *)vec->data[5]);

    // Test clean up
    puts("- - - - - - - - - - - - - - - - -");
    puts("Checking deinit_vec()...");

    err = deinit_vec_59(&vec);

    return err;
}

/*
========================================================================================================================
- - MAIN - -
========================================================================================================================
*/

int main(int argc, char const *argv[])
{
    puts("- - -  START OF vec TEST  - - -");
    puts("- - - INTERFACE TESTS - - -");

    ERR_59_e err = test_vec_59_interface();
    printf("ERROR CODE : %d\n", err);
    assert(ERR_NONE == err);

    puts("- - - - END OF vec TEST - - - -");
    return err;
}
