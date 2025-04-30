/***********************************************************************************************************************
 * LICENSE : NONE, as in zilch, zipo, nada, null, nill, 0, zero. If you use this file and are not me you are wrong.
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

#include "libc59_common.h"

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
