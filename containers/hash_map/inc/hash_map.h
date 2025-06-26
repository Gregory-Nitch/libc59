#pragma once
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
 * @date : 2025-05-18
 * @author : Gregory Nitch
 *
 * @brief : This file contians all the declarations for the hash map struct.
 **********************************************************************************************************************/

/*
========================================================================================================================
- - SYSTEM INCLUDES - -
========================================================================================================================
*/

#include <stddef.h>

/*
========================================================================================================================
- - MODULE INCLUDES - -
========================================================================================================================
*/

#include "containers_common.h"
#include "llist.h"

/*
========================================================================================================================
- - MACROS - -
========================================================================================================================
*/

/***********************************************************************************************************************
 * @brief : Default size of hash map tables.
 **********************************************************************************************************************/
#define DEFAULT_HASH_MAP_TABLE_SIZE 10

/***********************************************************************************************************************
 * @brief : Default prime number to use in hashing for hash maps.
 **********************************************************************************************************************/
#define DEFAULT_HASH_MAP_PRIME (11UL)

/*
========================================================================================================================
- - TYPEDEFS - -
========================================================================================================================
*/

typedef struct hash_map_59 hash_map_59;
typedef struct key_val_pair_59 key_val_pair_59;

/*
========================================================================================================================
- - STRUCTS - -
========================================================================================================================
*/

/***********************************************************************************************************************
 * @key_val_pair_59
 * @brief : Key value pair struct to represent a hash map entry.
 *
 * @key : Key to the values entry, will be unique in the hash map.
 * @val : Value to the key, is not unique in the hash map.
 **********************************************************************************************************************/
struct key_val_pair_59
{
    void *key;
    void *val;
};

/***********************************************************************************************************************
 * @hash_map_59
 * @brief : A hash map built with llist_59 and llist_node_59, this hash map does not automatically resize its table.
 *
 * @key_type : Type of the key for the hash.
 * @val_type : Type of the val held at the hashed key.
 * @table : A pointer to pointer of llist_59(arr).
 * @table_size : Size of the hash table, call resize to grow or shrink the table.
 * @_prime : Prime number used in hashing.
 *
 * @note Default table size is @DEFAULT_HASH_MAP_TABLE_SIZE. Ideally you should not alter the @_prime member, default
 * value is 11.
 **********************************************************************************************************************/
struct hash_map_59
{
    TYPE_59_e key_type;
    TYPE_59_e val_type;
    size_t val_type_depth;
    llist_59 **table;
    size_t table_size;
    size_t _prime;
};

/*
========================================================================================================================
- - MODULE FUNCTIONS - -
========================================================================================================================
*/

ERR_59_e init_hash_map_59(hash_map_59 **map,
                          TYPE_59_e const key_type,
                          TYPE_59_e const val_type,
                          size_t const val_type_depth,
                          size_t const table_size,
                          size_t const _prime);
ERR_59_e deinit_hash_map_59(hash_map_59 **map);
ERR_59_e upsert_into_hash_map_59(hash_map_59 *const map, void *key, void *val);
ERR_59_e get_from_hash_map_59(hash_map_59 const *const map, void *key, void **val);
ERR_59_e remove_from_hash_map_59(hash_map_59 *const map, void *const key, key_val_pair_59 **pair);
ERR_59_e resize_table_hash_map_59(hash_map_59 *map, size_t const new_size);
