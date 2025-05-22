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
 * @brief : Contains all the definitions for the hash map container.
 **********************************************************************************************************************/

/*
========================================================================================================================
- - SYSTEM INCLUDES - -
========================================================================================================================
*/

#include <stdlib.h>

/*
========================================================================================================================
- - MODULE INCLUDES - -
========================================================================================================================
*/

#include "hash_map_59.h"

/*
========================================================================================================================
- - INTERNAL FUNCTIONS - -
========================================================================================================================
*/

static ERR_59_e _hash_key_internal_hash_map_59(hash_map_59 *map, void *key, size_t *hash)
{
    //! TODO: . . .
}

static ERR_59_e _check_is_prime_internal_hash_map_59(size_t const prime, bool *is_prime)
{
    //! TODO: . . .
}

/*
========================================================================================================================
- - FUNCTION DEFINITIONS - -
========================================================================================================================
*/

/***********************************************************************************************************************
 * @brief : Initializes a hash map based on the passed parameters.
 *
 * @param[out] map : Pointer to a @hash_map_59 pointer to initialize the hash map in.
 * @param[in] key_type : Type of the keys for the hash map.
 * @param[in] val_type : Type of the vals for the hash map.
 * @param[in] val_type_depth : Depth of the values in the hash map, if values are not of the same size then set this to
 * 0.
 * @param[in] table_size : Size of the table in the hash_map, if 0 then the default size of @DEFAULT_HASH_MAP_TABLE_SIZE
 * is used.
 * @param[in] prime : Prime number to be used in hashing, if this parameter is not a prime number or 0 then an
 * ERR_INV_PARAM err will occur. When set as 0 then the default value of @DEFAULT_HASH_MAP_PRIME will be used.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.

 * @warning This will need to be freed with @deinit_hash_map_59 when its lifetime has expired. If values in the hash_map
 * are not of the same type depth DO NOT set the @val_type_depth parameter to anything other than 0.
 **********************************************************************************************************************/
ERR_59_e init_hash_map_59(hash_map_59 **map,
                          TYPE_59_e const key_type,
                          TYPE_59_e const val_type,
                          size_t const val_type_depth,
                          size_t const table_size,
                          size_t const prime)
{
    if (!map)
        return ERR_INV_PARAM;

    ERR_59_e err = ERR_NONE;

    hash_map_59 *new_map = malloc(sizeof(hash_map_59));
    if (!new_map)
        return ERR_NO_MEM;

    if (0 != prime)
    {
        bool is_prime = true;
        err = _check_is_prime_internal_hash_map_59(prime, &is_prime);
        if (ERR_NONE != err)
            return err;
        else if (is_prime)
            new_map->_prime = prime;
        else
            return ERR_INV_PARAM;
    }
    else
        new_map->_prime = DEFAULT_HASH_MAP_PRIME;

    if (0 != table_size)
        new_map->table_size = table_size;
    else
        new_map->table_size = DEFAULT_HASH_MAP_TABLE_SIZE;

    llist_59 **new_table = malloc(sizeof(llist_59 *) * new_map->table_size);
    if (!new_table)
    {
        free(new_map);
        return ERR_NO_MEM;
    }
    else
    {
        for (size_t i = 0; i < new_map->table_size; i++)
        {
            llist_59 *llist = malloc(sizeof(llist_59));
            if (!llist)
                err = ERR_NONE;
            err = init_llist_59(&llist, val_type, val_type_depth);
            if (ERR_NONE != err)
            {
                for (size_t j = 0; j < i; j++)
                    free(new_table[j]);
                free(new_table);
                free(new_map);
                return err;
            }
            else
                new_table[i] = llist;
        }
    }

    new_map->key_type = key_type;
    new_map->val_type = val_type;
    new_map->val_type_depth = val_type_depth;
    new_map->table = new_table;

    *map = new_map;

    return ERR_NONE;
}

/***********************************************************************************************************************
 * @brief : Deallocates the passed hash map and all of its contents.
 *
 * @param[out] map : Pointer to a hash_map_59 pointer that will be freed.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 *
 * @note The pointer to the map will be (void*)0 on return.
 **********************************************************************************************************************/
ERR_59_e deinit_hash_map_59(hash_map_59 **map)
{
    if (!map || !(*map))
        return ERR_INV_PARAM;

    ERR_59_e err = ERR_NONE;

    for (size_t i = 0; i < (*map)->table_size; i++)
    {
        err = deinit_llist_59(&(*map)->table[i]);
        if (ERR_NONE != err)
            return err;
    }

    free((*map)->table);
    free((*map));
    *map = (void *)0;

    return ERR_NONE;
}

/***********************************************************************************************************************
 * @brief : Inserts a new key and value as a @key_val_pair_59 into the hash map.
 *
 * @param[in] map : Hash map to insert the new pair into.
 * @param[in] key : Key of the new entry.
 * @param[in] val : Value of the new entry.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 *
 * @note If there is already an entry with the same key it is updated with the new value.
 **********************************************************************************************************************/
ERR_59_e upsert_into_hash_map_59(hash_map_59 *const map, void *key, void *val)
{
    if (!map || !key || !val)
        return ERR_INV_PARAM;

    ERR_59_e err = ERR_NONE;
    size_t hash = 0;
    err = _hash_key_internal_hash_map_59(map, key, &hash);
    if (ERR_NONE != err)
        return err;

    llist_node_59 *node = map->table[hash]->head;
    llist_59 *table_list = map->table[hash];
    while (node)
    {
        key_val_pair_59 *entry = (key_val_pair_59 *)node->node_obj;
        i64 dif = 0;
        err = compare_node_obj_59(map->key_type, entry->key, key, &dif);
        if (ERR_NONE != err)
            return err;

        if (0 == dif)
            entry->val = val;

        else if (!node->next)
        {
            key_val_pair_59 *new_entry = malloc(sizeof(key_val_pair_59));
            if (!new_entry)
                return ERR_NO_MEM;

            llist_node_59 *new_node = (void *)0;
            err = init_llist_node_59(&new_node, (void *)0, (void *)new_entry);
            if (ERR_NONE != err)
            {
                free(new_entry);
                return err;
            }
            err = push_back_llist_59(table_list, new_node);
            if (ERR_NONE != err)
            {
                free(new_entry);
                free(new_node);
                return err;
            }
        }

        else
            node = node->next;
    }

    return ERR_NONE;
}

ERR_59_e get_from_hash_map_59(hash_map_59 const *const map, void *key, void **val)
{
    //! TODO: . . .
}

ERR_59_e remove_from_hash_map_59(hash_map_59 *map, void *key)
{
    //! TODO: . . .
}

ERR_59_e resize_table_hash_map_59(hash_map_59 *map, size_t const new_size)
{
    //! TODO: . . .
}
