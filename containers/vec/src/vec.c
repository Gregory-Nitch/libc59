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
 * @brief: Contains all the definitions for the vector container.
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

#include "vec.h"

/*
========================================================================================================================
- - ENUMS - -
========================================================================================================================
*/

/***********************************************************************************************************************
 * @enum
 * @brief: Used to determine what type of sizing operation branch to execute for the internal resizing function for
 * @vec_59 vectors.
 **********************************************************************************************************************/
typedef enum RESIZE_MODE_VEC_59_INTRL_e
{
    VEC_59_RESIZE_MODE_GROW,
    VEC_59_RESIZE_MODE_SHRINK
} RESIZE_MODE_VEC_59_INTRL_e;

/*
========================================================================================================================
- - INTERAL FUNCTIONS - -
========================================================================================================================
*/

/***********************************************************************************************************************
 * @brief: Resizes the passed vector based on the passed @new_cap parameter, then copies data to a new array of void
 * pointers. The old array is freed.
 *
 * @param[in] vec: Vector to resize.
 * @param[in] new_cap: New vector capacity size to allocate for.
 *
 * @retval ERR_59_e: Error return value from the function, ERR_NONE = all ok.
 **********************************************************************************************************************/
static ERR_59_e _vec_59_resize_internal(vec_59* const vec, size_t const new_cap)
{
    if (!vec)
        return ERR_INV_PARAM;

    void** new_data = malloc(sizeof(void*) * new_cap);
    if (!new_data)
        return ERR_NO_MEM;

    memcpy(new_data, vec->data, (sizeof(void*) * vec->size));
    for (size_t i = vec->size; i < new_cap; i++)
        new_data[i] = (void*)0; // Zero new memory

    void** old_data = vec->data;
    vec->data = new_data;
    vec->capacity = new_cap;
    free(old_data);

    return ERR_NONE;
}

/***********************************************************************************************************************
 * @brief: Checks to see if the passed vector needs to be resized based on vector size and capacity. @note Only vectors
 * with their capacity lock set to false will be resized.
 *
 * @param[in] vec: Vector to check.
 * @param[in] mode: Mode to determine if the vector should be checked for growing or shrinking.
 *
 * @retval ERR_59_e: Error return value from the function, ERR_NONE = all ok.
 **********************************************************************************************************************/
static ERR_59_e _vec_59_check_needs_resize_internal(vec_59* const vec, RESIZE_MODE_VEC_59_INTRL_e const mode)
{
    if (!vec)
        return ERR_INV_PARAM;

    ERR_59_e err = ERR_NONE;
    size_t new_cap = vec->capacity;
    switch (mode)
    {
    case VEC_59_RESIZE_MODE_GROW:

        if (vec->size == vec->capacity && !vec->capacity_lock)
        {
            new_cap <<= 1;

            if (new_cap < vec->capacity)
                return ERR_CONTAINER_AT_CAPACITY; // Overflow occured
            err = _vec_59_resize_internal(vec, new_cap);
        }
        else if (vec->size == vec->capacity && vec->capacity_lock)
            return ERR_CONTAINER_AT_CAPACITY;

        break;

    case VEC_59_RESIZE_MODE_SHRINK:

        new_cap >>= 1;

        // Only shrink if capacity lock is off and the current vector will fit in a smaller allocation
        if (vec->size <= new_cap && !vec->capacity_lock)
            err = _vec_59_resize_internal(vec, new_cap);

        break;

    default:
        err = ERR_NOT_SUPPORTED;
        break;
    }

    return err;
}

/*
========================================================================================================================
- - FUNCTION DEFINITIONS - -
========================================================================================================================
*/

ERR_59_e init_vec_59(vec_59** vec, size_t const capacity, TYPE_59_e const type, bool const capacity_lock)
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

    (*vec)->data = malloc(sizeof(void*) * (*vec)->capacity);
    if (!(*vec)->data)
    { // Clean up vec before error
        free(*vec);
        return ERR_NO_MEM;
    }

    for (size_t i = 0; i < (*vec)->capacity; i++)
        (*vec)->data[i] = (void*)0; // Zero new memory

    return ERR_NONE;
}

ERR_59_e deinit_vec_59(vec_59** vec)
{
    if (!vec || !(*vec))
        return ERR_INV_PARAM;

    for (size_t i = 0; i < (*vec)->size; i++)
        free((*vec)->data[i]);

    free((*vec)->data);
    free((*vec));

    return ERR_NONE;
}

ERR_59_e push_back_vec_59(vec_59* const vec, void* const new_back)
{
    if (!vec || !new_back)
    {
        return ERR_INV_PARAM;
    }

    ERR_59_e err = _vec_59_check_needs_resize_internal(vec, VEC_59_RESIZE_MODE_GROW);
    if (err != ERR_NONE)
        return err;

    vec->data[vec->size] = new_back;
    vec->size++;

    return ERR_NONE;
}

ERR_59_e pop_back_vec_59(vec_59* const vec, void** back_obj)
{
    if (!vec || !back_obj)
        return ERR_INV_PARAM;

    if (0 == vec->size)
        return ERR_CONTAINER_EMPTY;

    *back_obj = vec->data[vec->size - 1];
    vec->data[vec->size - 1] = (void*)0;
    vec->size--;

    ERR_59_e err = _vec_59_check_needs_resize_internal(vec, VEC_59_RESIZE_MODE_SHRINK);
    if (err != ERR_NONE)
        return err;

    return ERR_NONE;
}

ERR_59_e push_front_vec_59(vec_59* const vec, void* const new_front)
{
    if (!vec || !new_front)
        return ERR_INV_PARAM;

    ERR_59_e err = _vec_59_check_needs_resize_internal(vec, VEC_59_RESIZE_MODE_GROW);
    if (err != ERR_NONE)
        return err;

    for (size_t idx = vec->size; idx > 0; idx--)
        vec->data[idx] = vec->data[idx - 1];

    vec->data[0] = new_front;
    vec->size++;

    return ERR_NONE;
}

ERR_59_e pop_front_vec_59(vec_59* const vec, void** front_obj)
{
    if (!vec || !front_obj)
        return ERR_INV_PARAM;

    if (0 == vec->size)
        return ERR_CONTAINER_EMPTY;

    *front_obj = vec->data[0];

    for (size_t idx = 0; idx < vec->size - 1; idx++)
        vec->data[idx] = vec->data[idx + 1];

    vec->size--;

    ERR_59_e err = _vec_59_check_needs_resize_internal(vec, VEC_59_RESIZE_MODE_SHRINK);
    if (err != ERR_NONE)
        return err;

    return ERR_NONE;
}

ERR_59_e remove_given_obj_from_vec_59(vec_59* const vec, void* remove_obj)
{
    if (!vec || !remove_obj)
        return ERR_INV_PARAM;

    bool is_same = false;
    for (size_t idx = 0; idx < vec->size; idx++)
    {
        ERR_59_e err = is_same_mem_addr_59(vec->data[idx], remove_obj, &is_same);
        if (ERR_NONE != err)
            return err;

        if (is_same)
        {
            vec->data[idx] = (void*)0; // Clear matched object
            for (; idx < vec->size - 1; idx++)
                vec->data[idx] = vec->data[idx + 1];

            vec->size--;

            err = _vec_59_check_needs_resize_internal(vec, VEC_59_RESIZE_MODE_SHRINK);
            if (err != ERR_NONE)
                return err;

            return ERR_NONE;
        }
    }

    return ERR_OBJ_NOT_FOUND;
}

ERR_59_e insert_obj_into_vec_59(vec_59* const vec, void* const new_obj, size_t const idx)
{
    if (!vec || !new_obj)
        return ERR_INV_PARAM;

    ERR_59_e err = _vec_59_check_needs_resize_internal(vec, VEC_59_RESIZE_MODE_GROW);
    if (err != ERR_NONE)
        return err;

    if (idx >= vec->size)
        vec->data[vec->size] = new_obj;
    else
    {
        for (size_t i = vec->size; i > idx; i--)
            vec->data[i] = vec->data[i - 1];

        vec->data[idx] = new_obj;
    }

    vec->size++;

    return ERR_NONE;
}
