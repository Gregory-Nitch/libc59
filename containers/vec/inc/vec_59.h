#pragma once
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
 * @brief : This file contians all the declarations for the vector struct.
 **********************************************************************************************************************/

/*
========================================================================================================================
- - SYSTEM INCLUDES - -
========================================================================================================================
*/

#include <stdbool.h>

/*
========================================================================================================================
- - MODULE INCLUDES - -
========================================================================================================================
*/

#include "container_common_59.h"

/*
========================================================================================================================
- - MACROS - -
========================================================================================================================
*/

/***********************************************************************************************************************
 * @brief : Defines all vectors default starting capacity.
 **********************************************************************************************************************/
#define VEC_DEFAULT_START_CAPACITY 4

/***********************************************************************************************************************
 * @brief : Defines the maximum vector size based on 1 in the MSB binary position.
 **********************************************************************************************************************/
#define STANDARD_MAX_VEC_CAPACITY 0x8000000000000000

/*
========================================================================================================================
- - TYPEDEFS - -
========================================================================================================================
*/

typedef struct vec_59 vec_59;

/*
========================================================================================================================
- - STRUCTS - -
========================================================================================================================
*/

/***********************************************************************************************************************
 * @vec_59
 * @brief : Represents a vector.
 *
 * @data : void pointer array to serve as the vector container
 * @size : size of the data in the container
 * @capacity : size of the container, ie the actual amount of memory it is taking up.
 * @type : type of the objects contained in the vector, this can be any type so be sure you document what you're
 *         pointing at.
 * @capacity_lock : if the capacity of the vector is locked then it will not be resized on push pull and insert. You are
 *                  expected to ensure the vector is of appropriate size.
 **********************************************************************************************************************/
struct vec_59
{
    void **data;
    size_t size;
    size_t capacity;
    TYPE_59_e type;
    bool capacity_lock;
};

/*
========================================================================================================================
- - MODULE FUNCTIONS - -
========================================================================================================================
*/

ERR_59_e init_vec_59(vec_59 **vec, size_t const capacity, TYPE_59_e const type, bool const capacity_lock);
ERR_59_e deinit_vec_59(vec_59 **vec);
ERR_59_e push_back_vec_59(vec_59 *const vec, void *const new_back);
ERR_59_e pop_back_vec_59(vec_59 *const vec, void **back_obj);
ERR_59_e push_front_vec_59(vec_59 *const vec, void *const new_front);
ERR_59_e pop_front_vec_59(vec_59 *const vec, void **front_obj);
ERR_59_e find_val_in_vec_59(vec_59 const *const vec, void **val);
ERR_59_e get_at_idx_llist_59(vec_59 const *const vec, void **node, size_t const idx);
ERR_59_e remove_given_obj_from_vec_59(vec_59 *const vec, void *remove_obj);
ERR_59_e insert_obj_into_vec_59(vec_59 *const vec, void *const new_obj, size_t const idx);
