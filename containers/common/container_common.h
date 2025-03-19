/***********************************************************************************************************************
 * LICENSE : NONE, as in zilch, zipo, nada, null, nill, 0, zero. If you use this file and are not me you are wrong.
 * Also, to be fair, you probably wouldn't want to be using this anyway.
 *
 * @date : 2025-03-18
 * @author : Gregory Nitch
 *
 * @brief : This file contains all the common pieces required by the various containers, such as error codes.
 **********************************************************************************************************************/

/*
========================================================================================================================
- - SYSTEM INCLUDES - -
========================================================================================================================
*/

#include <sys/types.h>

/*
========================================================================================================================
- - MODULE INCLUDES - -
========================================================================================================================
*/

#include "libc59_common.h"

/*
========================================================================================================================
- - ENUMS - -
========================================================================================================================
*/

/***********************************************************************************************************************
 * @container_err_59
 * @brief : Represents the various possible fail states of the containers.
 *
 * @none : no error state -> all ok.
 * @nomem : no memory was available on allocation (during malloc).
 * @inv_param : an invalid parameter was given to a container function.
 * @intrnl : an internal error occured.
 **********************************************************************************************************************/
typedef enum container_err_59
{
    none,
    nomem,
    inv_param,
    intrnl
} container_err_59;

/***********************************************************************************************************************
 * @continer_data_type_59
 * @brief : Represents all the various possible data types for a container to store for a key, value, at a node, etc.
 * All members that are pointers to objects may be arrays, this is on the user to implement properly.
 **********************************************************************************************************************/
typedef enum container_data_type_59
{
    u8_e,
    u16_e,
    u32_e,
    u64_e,
    i8_e,
    i16_e,
    i32_e,
    i64_e,
    size_e,
    chr_e,
    str_e,
    u8_ptr_e,
    u16_ptr_e,
    u32_ptr_e,
    u64_ptr_e,
    i8_ptr_e,
    i16_ptr_e,
    i32_ptr_e,
    i64_ptr_e,
    size_ptr_e,
    chr_ptr_e,
    struct_ptr_e
} container_data_type_59;

/*
========================================================================================================================
- - MODULE FUNCTIONS - -
========================================================================================================================
*/

i64 u8_comparator(u8 a, u8 b);
i64 u16_comparator(u16 a, u16 b);
i64 u32_comparator(u32 a, u32 b);
i64 u64_comparator(u64 a, u64 b);
i64 i8_comparator(i8 a, i8 b);
i64 i16_comparator(i16 a, i16 b);
i64 i32_comparator(i32 a, i32 b);
i64 i64_comparator(i64 a, i64 b);
i64 size_comparator(size_t a, size_t b);
i64 chr_comparator(char a, char b);
i64 str_comparator(str a, str b);
i64 ptr_comparator(void *a, void *b);
