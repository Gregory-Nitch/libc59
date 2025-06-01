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
 * @brief : Contains all the function definitions common between containers.
 **********************************************************************************************************************/

/*
========================================================================================================================
- - SYSETM INCLUDES - -
========================================================================================================================
*/

#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/*
========================================================================================================================
- - MODULE INCLUDES - -
========================================================================================================================
*/
#include "container_common_59.h"

/*
========================================================================================================================
- - FUNCTION DEFINITIONS - -
========================================================================================================================
*/

/***********************************************************************************************************************
 * @brief : Compares two node objects such that if the value of @obj_A is greater than @obj_B a positive value is
 * returned in @diff_out, or a negative when @obj_B is greater than @obj_A, or 0 when they are equal.
 *
 * @param[in] type : @TYPE_59_e used to produce comparison path.
 * @param[in] obj_A : Obj to compare.
 * @param[in] obj_B : Other obj to compare.
 * @param[out] diff_out : Difference determined based on the difference between the objs.
 *
 * @note Strings when compared will produce negative values for strings that come first alphabetically. ie, a - b = -1
 * @note Only signed, unsigned, chars, and strings are supported by this function. ERR_NOT_SUPPORTED will be
 * returned.
 * @note u64 and size_t values have a limit on @diff_out values due to memory restraints of the i64 return value. If the
 * difference is outside of the INT64_MAX and INT64_MIN range than max or min will be returned appropriately.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e compare_node_obj_59(TYPE_59_e const type,
                             void const *const obj_A,
                             void const *const obj_B,
                             i64 *const diff_out)
{
    if (!type || !obj_A || !obj_B || !diff_out)
        return ERR_INV_PARAM;

    switch (type)
    {
    // Unsigned
    case U8_PTR:
        *diff_out = (i64)(*((u8 *)obj_A)) - (i64)(*((u8 *)obj_B));
        break;

    case U16_PTR:
        *diff_out = (i64)(*((u16 *)obj_A)) - (i64)(*((u16 *)obj_B));
        break;

    case U32_PTR:
        *diff_out = (i64)(*((u32 *)obj_A)) - (i64)(*((u32 *)obj_B));
        break;

    case U64_PTR:
        u64 u64_A = *((u64 *)obj_A);
        u64 u64_B = *((u64 *)obj_B);
        u64 u64_dist = 0;

        if (u64_A >= u64_B)
        {
            u64_dist = u64_A - u64_B;
            if (u64_dist > INT64_MAX)
                *diff_out = INT64_MAX;
            else
                *diff_out = (i64)u64_dist;
        }
        else
        {
            u64_dist = u64_B - u64_A;
            if (u64_dist > ((u64)INT64_MAX) + 1) // INT64_MIN is + 1 in abs val
                *diff_out = INT64_MIN;
            else
                *diff_out = u64_A - u64_B;
        }

        break;

    case SIZE_PTR:
        size_t size_A = *((size_t *)obj_A);
        size_t size_B = *((size_t *)obj_B);
        size_t size_dist = 0;

        if (size_A >= size_B)
        {
            size_dist = size_A - size_B;
            if (size_dist > INT64_MAX)
                *diff_out = INT64_MAX;
            else
                *diff_out = (size_t)size_dist;
        }
        else
        {
            size_dist = size_B - size_A;
            if (size_dist > ((u64)INT64_MAX) + 1) // INT64_MIN is + 1 in abs val
                *diff_out = INT64_MIN;
            else
                *diff_out = size_A - size_B;
        }

        break;

    // Signed
    case I8_PTR:
        *diff_out = *((i8 *)obj_A) - *((i8 *)obj_B);
        break;

    case I16_PTR:
        *diff_out = *((i16 *)obj_A) - *((i16 *)obj_B);
        break;

    case I32_PTR:
        *diff_out = *((i32 *)obj_A) - *((i32 *)obj_B);
        break;

    case I64_PTR:
        i64 i64_A = *((i64 *)obj_A);
        i64 i64_B = *((i64 *)obj_B);
        i64 dist_to_max = 0;

        if (i64_A >= 0 && i64_B <= 0)
        {
            dist_to_max = INT64_MAX - i64_A;
            if (INT64_MIN == i64_B || llabs(i64_B) > dist_to_max)
                *diff_out = INT64_MAX;
            else
                *diff_out = i64_A - i64_B;
        }
        else if (i64_A <= 0 && i64_B >= 0)
        {
            dist_to_max = INT64_MAX - i64_B;
            if (INT64_MIN == i64_A || llabs(i64_A) > dist_to_max)
                *diff_out = INT64_MIN;
            else
                *diff_out = i64_A - i64_B;
        }
        else
            *diff_out = i64_A - i64_B;

        break;

    // Other
    case CHAR_PTR: // NOTE : This is not a string (only a single char)
        *diff_out = *((char *)obj_A) - *((char *)obj_B);
        break;

    case STR: // NOTE : This is an array of chars terminated by '\0', ie a string
        *diff_out = strcmp((char *)obj_A, (char *)obj_B);
        break;

    default: // We are trying to compare something that this function has not been made for. Such as a struct or float.
        return ERR_NOT_SUPPORTED;
    }

    return ERR_NONE;
}
