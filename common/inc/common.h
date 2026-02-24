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
 * @date: 2025-03-19
 * @author: Gregory Nitch
 *
 * @brief: This header contains all the interfaces common across the entire libraries set of modules.
 **********************************************************************************************************************/

#pragma once

/*
========================================================================================================================
- - SYSTEM INCLUDES - -
========================================================================================================================
*/

#include <stdint.h>
#include <stdbool.h>

/*
========================================================================================================================
- - TYPEDEFS - -
========================================================================================================================
*/

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef char *str;

/*
========================================================================================================================
- - ENUMS - -
========================================================================================================================
*/

/***********************************************************************************************************************
 * @TYPE_59_e
 * @brief: Represents all the various possible data types in use for things such as containers to store for a key,
 * value, at a node, etc. All members that are pointers to objects may be arrays, this is on the user to implement
 * properly.
 **********************************************************************************************************************/
typedef enum TYPE_59_e
{
    VOID_0,
    U8,
    U16,
    U32,
    U64,
    I8,
    I16,
    I32,
    I64,
    SIZE,
    CHAR,
    STR,
    ENUM,
    BOOL,
    U8_PTR,
    U16_PTR,
    U32_PTR,
    U64_PTR,
    I8_PTR,
    I16_PTR,
    I32_PTR,
    I64_PTR,
    SIZE_PTR,
    CHAR_PTR,
    STRUCT_PTR,
    ENUM_PTR,
    BOOL_PTR
} TYPE_59_e;

/***********************************************************************************************************************
 * @ERR_59_e
 * @brief: Represents the various possible fail states of libc59 libraries.
 *
 * @NONE: no error state -> all ok.
 * @NO_MEM: no memory was available on allocation (during malloc).
 * @INV_PARAM: an invalid parameter was given to a container function.
 * @OBJ_NOT_FOUND: object was not found in container.
 * @CONTAINER_EMPTY: container was empty.
 * @INTRNL: an internal error occured.
 * @NOT_SUPPORTED: user attempted an unsupported operation.
 * @CONTAINER_AT_CAPACITY: container being used has no more room for objects.
 **********************************************************************************************************************/
typedef enum ERR_59_e
{
    ERR_NONE,
    ERR_NO_MEM,
    ERR_INV_PARAM,
    ERR_OBJ_NOT_FOUND,
    ERR_CONTAINER_EMPTY,
    ERR_INTRNL,
    ERR_NOT_SUPPORTED,
    ERR_CONTAINER_AT_CAPACITY
} ERR_59_e;

/*
========================================================================================================================
- - FUNCTION DECLARATIONS - -
========================================================================================================================
*/

ERR_59_e is_same_mem_addr_59(void const *const obj_A, void const *const obj_B, bool *const is_same);
