/***********************************************************************************************************************
 * LICENSE : NONE, as in zilch, zipo, nada, null, nill, 0, zero. If you use this file and are not me you are wrong.
 *
 * @date : 2025-03-19
 * @author : Gregory Nitch
 *
 * @brief : This header contains all the interfaces common across the entire libraries set of modules.
 **********************************************************************************************************************/

/*
========================================================================================================================
- - SYSTEM INCLUDES - -
========================================================================================================================
*/

#include <stdint.h>

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
 * @brief : Represents all the various possible data types in use for things such as containers to store for a key,
 * value, at a node, etc. All members that are pointers to objects may be arrays, this is on the user to implement
 * properly.
 **********************************************************************************************************************/
typedef enum TYPE_59_e
{
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
 * @brief : Represents the various possible fail states of the containers.
 *
 * @NONE : no error state -> all ok.
 * @NO_MEM : no memory was available on allocation (during malloc).
 * @INV_PARAM : an invalid parameter was given to a container function.
 * @OBJ_NOT_FOUND : object was not found in container.
 * @INTRNL : an internal error occured.
 * @NOT_SUPPORTED : user attempted an unsupported operation.
 **********************************************************************************************************************/
typedef enum ERR_59_e
{
    ERR_NONE,
    ERR_NO_MEM,
    ERR_INV_PARAM,
    ERR_OBJ_NOT_FOUND,
    ERR_INTRNL,
    ERR_NOT_SUPPORTED
} ERR_59_e;
