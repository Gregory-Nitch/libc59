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
 * @date: 2025-05-08
 * @author: Gregory Nitch
 *
 * @brief: This file contians all the declarations for the vector struct.
 **********************************************************************************************************************/

#pragma once

/*
========================================================================================================================
- - SYSTEM INCLUDES - -
========================================================================================================================
*/

#include <stdbool.h>
#include <stddef.h>

/*
========================================================================================================================
- - MODULE INCLUDES - -
========================================================================================================================
*/

#include "containers_common.h"

/*
========================================================================================================================
- - MACROS - -
========================================================================================================================
*/

/***********************************************************************************************************************
 * @brief: Defines all vectors default starting capacity.
 **********************************************************************************************************************/
#define VEC_DEFAULT_START_CAPACITY 4

/***********************************************************************************************************************
 * @brief: Defines the maximum vector size based on 1 in the MSB binary position.
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
 * @brief: Represents a vector.
 *
 * @data: void pointer array to serve as the vector container
 * @size: size of the data in the container
 * @capacity: size of the container, ie the actual amount of memory it is taking up.
 * @type: type of the objects contained in the vector, this can be any type so be sure you document what you're
 *         pointing at.
 * @capacity_lock: if the capacity of the vector is locked then it will not be resized on push pull and insert. You are
 *                  expected to ensure the vector is of appropriate size.
 **********************************************************************************************************************/
struct vec_59
{
    void** data;
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

/***********************************************************************************************************************
 * @brief: Initializes a new vec_59 object. This vector must later be freed, along with the memory allocated to its
 * @data member. @note Vectors created with the @capacity_lock flag must manually be resized. Vectors start with a size
 * of 0 and have their allocated void pointers zeroed.
 *
 * @param[out] vec: Pointer to a vector pointer to initialize a vector in, the new initialized vector is located in
 * this out parameter. @warning This vector must later be freed with deinit_vec_59.
 * @param[in] capacity: Capacity of the new vector. @note This is only used if the @capacity_lock flag is set,
 * otherwise the vector will be initialized to @VEC_DEFAULT_START_CAPACITY which is normally 4.
 * @param[in] type: Type of values to be held by the vector, this is used to determine how to dereference the void
 * pointers used by the vector.
 * @param[in] capacity_lock: Flag used to lock the capacity of the vector, meaning that it will not be resized by
 * library functions. @note This means the user is responsible for size and capacity management.
 *
 * @retval ERR_59_e: Error return value from the function, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e init_vec_59(vec_59** vec, size_t const capacity, TYPE_59_e const type, bool const capacity_lock);

/***********************************************************************************************************************
 * @brief: Deallocates the passed vector including the objects held within the vector.
 *
 * @param[in] vec: Vector to deallocate.
 *
 * @retval ERR_59_e: Error state of the function after the call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e deinit_vec_59(vec_59** vec);

/***********************************************************************************************************************
 * @brief: Pushes the new object to the end of the vector. @note If the @capacity_lock member is set to true then the
 * vector will not automatically resize when size is == capacity. In this situation ERR_CONTAINER_AT_CAPACITY will be
 * returned.
 *
 * @param[in] vec: Vector to push the new object onto.
 * @param[in] new_back: New object to push onto the back of the vector.
 *
 * @retval ERR_59_e: Error state of the function after the call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e push_back_vec_59(vec_59* const vec, void* const new_back);

/***********************************************************************************************************************
 * @brief: Pops the back object out of the vector.
 *
 * @param[in] vec: Vector to remove the back from.
 * @param[out] back_obj: Pointer to store the back object in. @note To properly pass this value cast it to a void
 * pointer to pointer ie (void *)&back_obj.
 *
 * @retval ERR_59_e: Error state of the function after the call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e pop_back_vec_59(vec_59* const vec, void** back_obj);

/***********************************************************************************************************************
 * @brief: Pushes a new object onto the front of the vector.
 *
 * @param[in] vec: Vector to push the new object onto.
 * @param[in] new_front: Object to push onto the front of the vector.
 *
 * @retval ERR_59_e: Error state of the function after the call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e push_front_vec_59(vec_59* const vec, void* const new_front);

/***********************************************************************************************************************
 * @brief: Pops the front object off of the passed vector.
 *
 * @param[in] vec: Vector to remove the front object off of.
 * @param[out] front_obj: Pointer to the front object of the vector.
 *
 * @retval ERR_59_e: Error state of the function after the call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e pop_front_vec_59(vec_59* const vec, void** front_obj);

/***********************************************************************************************************************
 * @brief: Removes the passed object from the vector based on @is_same_mem_addr_59(). @warning This does not deallocate
 * the passed object and only removes it from the vector.
 *
 * @param[in] vec: Vector to check if the object exsists in and remove from.
 * @param[in] remove_obj: Object to remove from the vector. @warning This object still needs to be deallocated after
 * its use has been finished, this function does not deallocate the object's memory.
 *
 * @retval ERR_59_e: Error state of the function after the call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e remove_given_obj_from_vec_59(vec_59* const vec, void* remove_obj);

/***********************************************************************************************************************
 * @brief: Inserts the passed object into the vector at the given index. @note If the index is passed the end of the
 * vector then the object is simply placed at the back of the vector.
 *
 * @param[in] vec: Vector to add the object to.
 * @param[in] new_object: Object to add to the vector.
 * @param[in] idx: Index to place the object at in the vector, all objects placed after this idx will be shifted left.
 *
 * @retval ERR_59_e: Error state of the function after the call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e insert_obj_into_vec_59(vec_59* const vec, void* const new_obj, size_t const idx);
