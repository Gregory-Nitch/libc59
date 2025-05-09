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
 * @brief : Contains all the definitions for the vector container.
 **********************************************************************************************************************/

/*
========================================================================================================================
- - SYSTEM INCLUDES - -
========================================================================================================================
*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/*
========================================================================================================================
- - MODULE INCLUDES - -
========================================================================================================================
*/

#include "vec_59.h"

/*
========================================================================================================================
- - INTERAL FUNCTIONS - -
========================================================================================================================
*/

/***********************************************************************************************************************
 * @brief : Resizes the passed vector by shifting capacity value left by 1 bit, then copies data to a new array of void
 * pointers. @note This function cannot be used with vectors that have their capacity locked, such vectors need to be
 * resized manually.
 *
 * @param[in] vec : Vector to resize.
 *
 * @retval ERR_59_e : Error return value from the function, ERR_NONE = all ok.
 **********************************************************************************************************************/
static ERR_59_e _vec_59_resize_internal(vec_59 *const vec)
{
    if (!vec)
        return ERR_INV_PARAM;

    if (vec->capacity_lock)
        return ERR_NOT_SUPPORTED;

    size_t new_size = vec->size + 1;
    size_t new_cap = vec->capacity << 1;

    if (new_cap < vec->capacity)
        return ERR_CONTAINER_AT_CAPACITY; // Overflow occured

    void **new_data = malloc(sizeof(void *) * new_cap);
    if (!new_data)
        return ERR_NO_MEM;

    memcpy(new_data, vec->data, (sizeof(void *) * vec->size));
    for (size_t i = vec->size; i < new_cap; i++)
        new_data[i] = (void *)0; // Zero new memory

    void **old_data = vec->data;
    vec->data = new_data;
    vec->size = new_size;
    vec->capacity = new_cap;
    free(old_data);

    return ERR_NONE;
}

/*
========================================================================================================================
- - FUNCTION DEFINITIONS - -
========================================================================================================================
*/

/***********************************************************************************************************************
 * @brief : Initializes a new vec_59 object. This vector must later be freed, along with the memory allocated to its
 * @data member. @note Vectors created with the @capacity_lock flag must manually be resized. Vectors start with a size
 * of 0 and have their allocated void pointers zeroed.
 *
 * @param[out] vec : Pointer to a vector pointer to initialize a vector in, the new initialized vector is located in
 * this out parameter. @warning This vector must later be freed with destroy_vec_59.
 * @param[in] capacity : Capacity of the new vector. @note This is only used if the @capacity_lock flag is set,
 * otherwise the vector will be initialized to @VEC_DEFAULT_START_CAPACITY which is normally 4.
 * @param[in] type : Type of values to be held by the vector, this is used to determine how to dereference the void
 * pointers used by the vector.
 * @param[in] capacity_lock : Flag used to lock the capacity of the vector, meaning that it will not be resized by
 * library functions. @note This means the user is responsible for size and capacity management.
 *
 * @retval ERR_59_e : Error return value from the function, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e init_vec_59(vec_59 **vec,
                     size_t const capacity,
                     TYPE_59_e const type,
                     bool const capacity_lock)
{
    if (!vec)
        return ERR_INV_PARAM;

    *vec = malloc(sizeof(vec_59));
    if (!(*vec))
    {
        return ERR_NO_MEM;
    }

    (*vec)->type = type;
    (*vec)->size = 0;
    (*vec)->capacity_lock = capacity_lock;
    if ((*vec)->capacity_lock)
        (*vec)->capacity = capacity;
    else
        (*vec)->capacity = VEC_DEFAULT_START_CAPACITY;

    (*vec)->data = malloc(sizeof(void *) * (*vec)->capacity);
    if (!(*vec)->data)
    { // Clean up vec before error
        free(*vec);
        return ERR_NO_MEM;
    }

    for (size_t i = 0; i < (*vec)->capacity; i++)
        (*vec)->data[i] = (void *)0; // Zero new memory

    return ERR_NONE;
}

ERR_59_e destroy_vec_59(vec_59 **vec)
{
}

ERR_59_e push_back_vec_59(vec_59 *const vec, void *const new_back)
{
}

ERR_59_e pop_back_vec_59(vec_59 *const vec, void **back_obj)
{
}

ERR_59_e push_front_vec_59(vec_59 *const vec, void *const new_front)
{
}

ERR_59_e pop_front_vec_59(vec_59 *const vec, void **front_obj)
{
}

ERR_59_e remove_given_obj_from_vec_59(vec_59 *const vec, void *remove_obj)
{
}

ERR_59_e insert_obj_into_vec_59(vec_59 *const vec, void *const new_obj, size_t const idx)
{
}
