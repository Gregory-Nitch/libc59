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
 * @brief : Test cases for vec_59 types that cover edge cases that the interface might encounter.
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

ERR_59_e test_vec_59_edge_cases(void)
{
    ERR_59_e err = ERR_NONE;

    // Setup vec for testing
    puts("- - - - - - - - - - - - - - - - -");
    puts("Initializing vector...");

    vec_59 **dummy_vec_pp = (void *)0;
    vec_59 *dummy_vec_p = (void *)0;
    vec_59 *capped_vec = (void *)0;
    vec_59 *vec = (void *)0;
    i64 *dummy_val = (void *)0;

    err = init_vec_59(&vec, 0, I64_PTR, false);
    if (ERR_NONE != err)
        return err;

    err = init_vec_59(&capped_vec, 0, I64_PTR, true);
    if (ERR_NONE != err)
        return err;

    i64 *val;
    for (size_t i = 0; i < 4; i++)
    {
        val = malloc(sizeof(i64));
        *val = i;
        push_back_vec_59(vec, val);
        printf("Assert: i = %lu == %ld = vec->data[%lu]\n", i, *(i64 *)(vec->data[i]), i);
        assert(i == *(i64 *)(vec->data[i]));
    }
    val = malloc(sizeof(i64));
    *val = 59; // Used by later tests

    // init_vec
    puts("- - - - - - - - - - - - - - - - -");
    puts("test init_vec...");

    err = init_vec_59(dummy_vec_pp, 0, I64_PTR, false);
    puts("Assert: (void **)0 vec init == ERR_INV_PARAM");
    assert(ERR_INV_PARAM == err);

    // destroy_vec
    puts("- - - - - - - - - - - - - - - - -");
    puts("test destroy_vec...");

    err = destroy_vec_59(dummy_vec_pp);
    puts("Assert: (void **)0 vec destroy == ERR_INV_PARAM");
    assert(ERR_INV_PARAM == err);

    err = destroy_vec_59(&dummy_vec_p);
    puts("Assert: (void *)0 vec destroy == ERR_INV_PARAM");
    assert(ERR_INV_PARAM == err);

    // pushback_vec
    puts("- - - - - - - - - - - - - - - - -");
    puts("test pushback_vec...");

    err = push_back_vec_59(dummy_vec_p, val);
    puts("Assert: (void *)0 vec & val push_back == ERR_INV_PARAM");
    assert(ERR_INV_PARAM == err);

    err = push_back_vec_59(vec, dummy_val);
    puts("Assert: vec & (void *)0 val push_back == ERR_INV_PARAM");
    assert(ERR_INV_PARAM == err);

    err = push_back_vec_59(capped_vec, val);
    puts("Assert: capped_vec & val push_back == ERR_CONTAINER_AT_CAPACITY");
    assert(ERR_CONTAINER_AT_CAPACITY == err);

    // popback_vec
    puts("- - - - - - - - - - - - - - - - -");
    puts("test popback_vec...");

    err = pop_back_vec_59(dummy_vec_p, (void *)&val);
    puts("Assert: (void *)0 vec & val pop_back == ERR_INV_PARAM");
    assert(ERR_INV_PARAM == err);

    err = pop_back_vec_59(vec, (void *)0);
    puts("Assert: vec & (void *)0 val pop_back == ERR_INV_PARAM");
    assert(ERR_INV_PARAM == err);

    size_t tmp_size = vec->size;
    vec->size = 0;
    err = pop_back_vec_59(vec, (void *)&val);
    puts("Assert: vec->size = 0 & val pop_back == ERR_CONTAINER_EMPTY");
    assert(ERR_CONTAINER_EMPTY == err);
    vec->size = tmp_size;

    // pushfront_vec
    puts("- - - - - - - - - - - - - - - - -");
    puts("test pushfront_vec...");

    err = push_front_vec_59(dummy_vec_p, val);
    puts("Assert: (void *)0 vec & val push_front == ERR_INV_PARAM");
    assert(ERR_INV_PARAM == err);

    err = push_front_vec_59(vec, dummy_val);
    puts("Assert: vec & (void *)0 val push_front == ERR_INV_PARAM");
    assert(ERR_INV_PARAM == err);

    err = push_front_vec_59(capped_vec, val);
    puts("Assert: capped_vec & val push_front == ERR_CONTAINER_AT_CAPACITY");
    assert(ERR_CONTAINER_AT_CAPACITY == err);

    // popfront_vec
    puts("- - - - - - - - - - - - - - - - -");
    puts("test popfront_vec...");

    err = pop_front_vec_59(dummy_vec_p, (void *)&val);
    puts("Assert: (void *)0 vec & val pop_front == ERR_INV_PARAM");
    assert(ERR_INV_PARAM == err);

    err = pop_front_vec_59(vec, (void *)0);
    puts("Assert: vec & (void *)0 val pop_front == ERR_INV_PARAM");
    assert(ERR_INV_PARAM == err);

    tmp_size = vec->size;
    vec->size = 0;
    err = pop_front_vec_59(vec, (void *)&val);
    puts("Assert: vec->size = 0 & val pop_front == ERR_CONTAINER_EMPTY");
    assert(ERR_CONTAINER_EMPTY == err);
    vec->size = tmp_size;

    // remove_from_vec
    puts("- - - - - - - - - - - - - - - - -");
    puts("test remove_from_vec...");

    err = remove_given_obj_from_vec_59(dummy_vec_p, (void *)&val);
    puts("Assert: (void *)0 vec & val remove_from_vec == ERR_INV_PARAM");
    assert(ERR_INV_PARAM == err);

    err = remove_given_obj_from_vec_59(vec, (void *)0);
    puts("Assert: vec & (void *)0 val remove_from_vec == ERR_INV_PARAM");
    assert(ERR_INV_PARAM == err);

    err = remove_given_obj_from_vec_59(vec, (void *)&dummy_val);
    puts("Assert: vec & dummy_val remove_from_vec == ERR_OBJ_NOT_FOUND");
    assert(ERR_OBJ_NOT_FOUND == err);

    // insert_into_vec
    puts("- - - - - - - - - - - - - - - - -");
    puts("test insert_into_vec...");

    err = insert_obj_into_vec_59(dummy_vec_p, val, 0);
    puts("Assert: (void *)0 vec & val insert_into_vec == ERR_INV_PARAM");
    assert(ERR_INV_PARAM == err);

    err = insert_obj_into_vec_59(vec, dummy_val, 0);
    puts("Assert: vec & (void *)0 val insert_into_vec == ERR_INV_PARAM");
    assert(ERR_INV_PARAM == err);

    err = insert_obj_into_vec_59(capped_vec, val, 0);
    puts("Assert: capped_vec & val insert_into_vec == ERR_CONTAINER_AT_CAPACITY");
    assert(ERR_CONTAINER_AT_CAPACITY == err);

    // Test clean up
    puts("- - - - - - - - - - - - - - - - -");
    puts("Test clean up...");

    err = push_back_vec_59(vec, val); // Clean up 59 pointer
    err = destroy_vec_59(&capped_vec);
    err = destroy_vec_59(&vec);

    return err;
}

/*
========================================================================================================================
- - MAIN - -
========================================================================================================================
*/

int main(int argc, char const *argv[])
{
    puts("- - -  START OF VEC TEST  - - -");
    puts("- - - VEC EDGE CASES - - -");

    ERR_59_e err = test_vec_59_edge_cases();
    printf("ERROR CODE : %d\n", err);
    assert(ERR_NONE == err);

    puts("- - - - END OF VEC TEST - - - -");
    return err;
}
