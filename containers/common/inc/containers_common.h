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
 * @date: 2025-03-18
 * @author: Gregory Nitch
 *
 * @brief: This file contains all the common pieces required by the various containers, node obj comparisons.
 **********************************************************************************************************************/

#pragma once

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

#include "common.h"

/*
========================================================================================================================
- - FUNCTION DECLARATIONS - -
========================================================================================================================
*/

/***********************************************************************************************************************
 * @brief: Compares two node objects such that if the value of @obj_A is greater than @obj_B a positive value is
 * returned in @diff_out, or a negative when @obj_B is greater than @obj_A, or 0 when they are equal.
 *
 * @param[in] type: @TYPE_59_e used to produce comparison path.
 * @param[in] obj_A: Obj to compare.
 * @param[in] obj_B: Other obj to compare.
 * @param[out] diff_out: Difference determined based on the difference between the objs.
 *
 * @note Strings when compared will produce negative values for strings that come first alphabetically. ie, a - b = -1
 * where a = "abc" and b = "cba".
 * @note Only signed, unsigned, chars, and strings are supported by this function. ERR_NOT_SUPPORTED will be
 * returned.
 * @note u64 and size_t values have a limit on @diff_out values due to memory restraints of the i64 return value. If the
 * difference is outside of the INT64_MAX and INT64_MIN range than max or min will be returned appropriately.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e
compare_node_obj_59(TYPE_59_e const type, void const* const obj_A, void const* const obj_B, i64* const diff_out);
