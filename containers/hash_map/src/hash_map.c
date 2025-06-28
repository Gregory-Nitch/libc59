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
#include <math.h>
#include <float.h>

/*
========================================================================================================================
- - MODULE INCLUDES - -
========================================================================================================================
*/

#include "hash_map.h"

/*
========================================================================================================================
- - INTERNAL FUNCTIONS - -
========================================================================================================================
*/

/***********************************************************************************************************************
 * @brief : Deinits a linked list node held by the hash map table, this includes the void pointer to the node obj and
 * the key value pairs.
 *
 * @param[in] node : Node to deinit.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
static ERR_59_e _deinit_table_node_hash_map_59(llist_node_59 **node)
{
    if (!node || !(*node))
        return ERR_INV_PARAM;

    if ((*node)->node_obj)
    {
        key_val_pair_59 *pair = (key_val_pair_59 *)((*node)->node_obj);
        if (pair->key)
        {
            free(pair->key);
            pair->key = (void *)0;
        }
        if (pair->val)
        {
            free(pair->val);
            pair->val = (void *)0;
        }
        free((*node)->node_obj);
    }

    (*node)->node_obj = (void *)0;
    (*node)->next = (void *)0;
    free((*node));
    (*node) = (void *)0;

    return ERR_NONE;
}

/***********************************************************************************************************************
 * @brief : This function deallocates the memory for hash map table lists used by the hash_map. This is needed because
 * the node objects point to two other pointers which have been allocated an need to be freed.
 *
 * @param[out] llist : Pointer to a linked list that needs to be freed.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
static ERR_59_e _deinit_table_list_hash_map_59(llist_59 **llist)
{
    if (!llist || !(*llist))
        return ERR_INV_PARAM;

    llist_node_59 *node = (*llist)->head;
    llist_node_59 *next_node = (void *)0;
    while (node)
    {
        next_node = node->next;

        ERR_59_e err = _deinit_table_node_hash_map_59(&node);
        if (err != ERR_NONE)
            return err;

        node = next_node;
    }

    (*llist)->head = (void *)0;
    (*llist)->tail = (void *)0;
    (*llist)->type = VOID_0;
    (*llist)->type_depth = 0;
    free((*llist));
    (*llist) = (void *)0;

    return ERR_NONE;
}

/***********************************************************************************************************************
 * @brief : Finds the matching linked list node in the passed linked list
 *
 * @param[in] llist : Linked list t search for the node in.
 * @param[in] key : Key to match the node against, this matches the memory address not the value.
 * @param[out] node : Pointer to linked list node to return the matched node in.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
static ERR_59_e _find_node_in_table_list_hash_map_59(hash_map_59 *const map,
                                                     llist_59 const *const llist,
                                                     void const *const key,
                                                     llist_node_59 **node)
{
    if (!llist || !key || !node)
        return ERR_INV_PARAM;

    llist_node_59 *search_node = llist->head;
    i64 dif = 0;
    ERR_59_e err = ERR_NONE;
    while (search_node)
    {
        err = compare_node_obj_59(map->key_type, key, ((key_val_pair_59 *)search_node->node_obj)->key, &dif);
        if (ERR_NONE != err)
            return err;

        if (0 == dif)
        {
            *node = search_node;
            break;
        }
        search_node = search_node->next;
        map->_collision_detected = true; // More than one node in the llist = collision.
    }

    if (!(*node))
        return ERR_OBJ_NOT_FOUND;

    return ERR_NONE;
}

/***********************************************************************************************************************
 * @brief : Hashes the passed @key based on the passed @map @table_size member.
 *
 * @param[in] map : Map to hash the key for.
 * @param[in] key : Key to hash for the map.
 * @param[out] hash : Value to place the hash in.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 *
 * @warning This function assumes that passed strings are null terminated.
 **********************************************************************************************************************/
static ERR_59_e _hash_key_internal_hash_map_59(hash_map_59 const *const map, void *key, size_t *hash)
{
    if (!map || !key || !hash)
        return ERR_INV_PARAM;

    switch (map->key_type)
    {
    case U8_PTR:
        *hash = (*(u8 *)key) % map->table_size;
        break;

    case U16_PTR:
        *hash = (*(u16 *)key) % map->table_size;
        break;

    case U32_PTR:
        *hash = (*(u32 *)key) % map->table_size;
        break;

    case U64_PTR:
        *hash = (*(u64 *)key) % map->table_size;
        break;

    case I8_PTR:
        *hash = ((size_t)*(i8 *)key) % map->table_size;
        break;

    case I16_PTR:
        *hash = ((size_t)*(i16 *)key) % map->table_size;
        break;

    case I32_PTR:
        *hash = ((size_t)*(i32 *)key) % map->table_size;
        break;

    case I64_PTR:
        *hash = ((size_t)*(i64 *)key) % map->table_size;
        break;

    case CHAR_PTR:
        *hash = ((size_t)*(unsigned char *)key) % map->table_size;
        break;

    case STR: // Assumes null termination
        ;     // Null statement -> so pedantic
        str s = (str)key;
        while (*s)
        {
            *hash = *hash + ((unsigned char)*s);
            s++;
        }
        *hash = (*hash + map->_prime) % map->table_size;
        break;

    default:
        return ERR_NOT_SUPPORTED;
    }

    return ERR_NONE;
}

/***********************************************************************************************************************
 * @brief : Checks if the passed unsigned value is a prime number.
 *
 * @param[in] prime : Number to check which must be equal to or greater than 3.
 * @param[out] is_prime : Pointer to store the bool out value.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 *
 * @note Use of smaller numbers equates to more performance.
 **********************************************************************************************************************/
static ERR_59_e _check_is_prime_internal_hash_map_59(size_t const prime, bool *is_prime)
{
    if (!is_prime || 3 > prime || DBL_MAX < prime)
        return ERR_INV_PARAM;

    size_t test = 3;
    *is_prime = true;
    while (test < sqrt((double)prime) && true == *is_prime)
    {
        if (test == prime)
            break;

        if (0 == prime % test)
            *is_prime = false;
        test++;
    }

    return ERR_NONE;
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
 *
 * @note Smaller @prime numbers produce better hashing performance.
 *
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
        if (ERR_NONE != err || !is_prime)
        {
            free(new_map);
            return err;
        }
        else
            new_map->_prime = prime;
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
            llist_59 *llist = (void *)0;
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
    new_map->_collision_detected = false;

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
        err = _deinit_table_list_hash_map_59(&(*map)->table[i]);
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

    llist_59 *table_list = map->table[hash];
    key_val_pair_59 *pair = (void *)0;
    llist_node_59 *node = (void *)0;
    _find_node_in_table_list_hash_map_59(map, table_list, key, &node);
    if (!node)
    {
        pair = malloc(sizeof(key_val_pair_59));
        if (!pair)
            return ERR_NO_MEM;

        pair->key = key;
        pair->val = val;
        err = init_llist_node_59(&node, (void *)0, (void *)pair);
        if (ERR_NONE != err)
        {
            free(pair);
            return err;
        }

        err = push_back_llist_59(table_list, node);
        if (ERR_NONE != err)
        {
            free(pair);
            free(node);
            return err;
        }

        // If new size is less than the current size we have overflowed and our hash map table size is maxed.
        size_t new_size = map->table_size << 1;
        if (new_size > map->table_size && map->_collision_detected)
        {

            err = resize_table_hash_map_59(map, new_size);
            if (ERR_NONE != err)
                return err;
            map->_collision_detected = false;
        }
        else if (map->_collision_detected)
            return ERR_CONTAINER_AT_CAPACITY;

        return ERR_NONE;
    }

    if (!((key_val_pair_59 *)node->node_obj)->val)
        return ERR_INTRNL;

    free(((key_val_pair_59 *)node->node_obj)->val); // Remember that the value is being replaced, therefore free
    ((key_val_pair_59 *)node->node_obj)->val = val;

    return ERR_NONE;
}

/***********************************************************************************************************************
 * @brief : Gets the value for the passed key from the hash map if it is present.
 *
 * @param[in] map : Hash map to get the value from.
 * @param[in] key : Key to match to the value.
 * @param[out] val : Void pointer to place the out value into.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e get_from_hash_map_59(hash_map_59 *const map, void *key, void **val)
{
    if (!map || !key || !val)
        return ERR_INV_PARAM;

    size_t hash = 0;
    ERR_59_e err = _hash_key_internal_hash_map_59(map, key, &hash);
    if (ERR_NONE != err)
        return err;

    llist_node_59 *node = (void *)0;
    err = _find_node_in_table_list_hash_map_59(map, map->table[hash], key, &node);
    if (ERR_NONE != err)
        return err;

    *val = ((key_val_pair_59 *)node->node_obj)->val;

    return ERR_NONE;
}

/***********************************************************************************************************************
 * @brief : Removes the @key_val_pair_59 that has the matching key from the hash map.
 *
 * @param[in] map : Hash map to remove the pair from.
 * @param[in] key : Key to the pair that should be removed.
 * @param[out] pair : Pointer to place the pair in.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 *
 * @warning This DOES NOT deallocate the pair, this will need to be freed after use.
 **********************************************************************************************************************/
ERR_59_e remove_from_hash_map_59(hash_map_59 *const map, void *const key, key_val_pair_59 **pair)
{
    if (!map || !key || !pair)
        return ERR_INV_PARAM;

    size_t hash = 0;
    ERR_59_e err = _hash_key_internal_hash_map_59(map, key, &hash);
    if (ERR_NONE != err)
        return err;

    llist_node_59 *node = (void *)0;
    err = _find_node_in_table_list_hash_map_59(map, map->table[hash], key, &node);
    if (ERR_NONE != err)
        return err;

    err = remove_given_node_from_llist_59(map->table[hash], node);
    if (ERR_NONE != err)
        return err;

    *pair = (key_val_pair_59 *)node->node_obj;

    free(node);

    return ERR_NONE;
}

/***********************************************************************************************************************
 * @brief : Resizes the hash table to prevent collisions or reduce it size due to sparseness.
 *
 * @param[in] map : Hash map to resize.
 * @param[in] new_size : New size to use for the hash map table.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e resize_table_hash_map_59(hash_map_59 *const map, size_t const new_size)
{
    if (!map)
        return ERR_INV_PARAM;

    llist_59 **new_table = malloc(sizeof(llist_59 *) * new_size);
    if (!new_table)
        return ERR_NO_MEM;
    ERR_59_e err = ERR_NONE;
    for (size_t i = 0; i < new_size; i++)
    {
        llist_59 *list = (void *)0;
        err = init_llist_59(&list, map->val_type, map->val_type_depth);
        if (ERR_NONE != err)
        {
            for (size_t j = 0; j < i; j++)
                free(new_table[j]);
            free(new_table);
            return err;
        }
        new_table[i] = list;
    }

    size_t hash = 0;
    size_t old_size = map->table_size;
    llist_59 **old_table = map->table;
    map->table_size = new_size;
    map->table = new_table;
    err = ERR_NONE;
    for (size_t i = 0; i < old_size; i++)
    {
        llist_node_59 *node = old_table[i]->head;
        llist_node_59 *next_node = (void *)0;
        while (node)
        {
            err = _hash_key_internal_hash_map_59(map, ((key_val_pair_59 *)node->node_obj)->key, &hash);
            if (ERR_NONE != err)
                goto migrate_abort;
            next_node = node->next;
            node->next = (void *)0;
            err = push_back_llist_59(map->table[hash], node);
            if (ERR_NONE != err)
                goto migrate_abort;

            node = next_node;
        }
    }

    for (size_t i = 0; i < old_size; i++)
    {
        old_table[i]->head = (void *)0;
        old_table[i]->tail = (void *)0;
        free(old_table[i]);
    }
    free(old_table);

    return ERR_NONE;

migrate_abort:
    for (size_t i = 0; i < new_size; i++)
    {
        map->table[i]->head = (void *)0;
        map->table[i]->tail = (void *)0;
        free(map->table[i]);
    }
    free(map->table);
    map->table = old_table;
    map->table_size = old_size;
    return err;
}
