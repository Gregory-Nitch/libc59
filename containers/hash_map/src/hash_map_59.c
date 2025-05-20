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

static ERR_59_e _hash_key_internal_hash_map_59(hash_map_59 *map, void *key)
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

ERR_59_e deinit_hash_map59(hash_map_59 **map)
{
    if (!map || !(*map))
        return ERR_INV_PARAM;

    ERR_59_e err = ERR_NONE;

    for (size_t i = 0; i < (*map)->table_size; i++)
    {
        err = deinit_llist_59((*map)->table[i]);
        if (ERR_NONE != err)
            return err;
    }

    free((*map)->table);
    free((*map));
    *map = (void *)0;

    return ERR_NONE;
}

ERR_59_e insert_into_hash_map_59(hash_map_59 *const map, void *key, void *val)
{
    //! TODO: . . .
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
