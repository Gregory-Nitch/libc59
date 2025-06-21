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
 * @date : 2025-03-22
 * @author : Gregory Nitch
 *
 * @brief : Contains all the common definitions for libc59.
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

#include "c59_common.h"

/***********************************************************************************************************************
 * @brief : Compares two memory addresses and returns true if they are the same address, and false if they are not.
 *
 * @param[in] obj_A : Obj to compare.
 * @param[in] obj_B : Other obj to compare.
 * @param[out] is_same : bool value returned from comparison.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e is_same_mem_addr_59(void const *const obj_A, void const *const obj_B, bool *const is_same)
{
    if (!is_same)
        return ERR_INV_PARAM;

    if (!obj_A || !obj_B)
        *is_same = false;
    else
        *is_same = obj_A == obj_B;

    return ERR_NONE;
}
