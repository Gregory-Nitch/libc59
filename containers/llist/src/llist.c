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
 * @brief: Contains all the definitions for the linked list container.
 **********************************************************************************************************************/

/*
========================================================================================================================
- - SYSTEM INCLUDES - -
========================================================================================================================
*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/*
========================================================================================================================
- - MODULE INCLUDES - -
========================================================================================================================
*/

#include "llist.h"

/*
========================================================================================================================
- - FUNCTION DEFINITIONS - -
========================================================================================================================
*/

ERR_59_e init_llist_59(llist_59** llist, TYPE_59_e const type, size_t const type_depth)
{
    if (!llist)
        return ERR_INV_PARAM;

    *llist = malloc(sizeof(llist_59));

    if (!(*llist))
        return ERR_NO_MEM;

    (*llist)->type = type;
    (*llist)->type_depth = type_depth;
    (*llist)->head = (void*)0;
    (*llist)->tail = &(*llist)->head;

    return ERR_NONE;
}

ERR_59_e deinit_llist_59(llist_59** llist)
{
    if (!llist || !(*llist))
        return ERR_INV_PARAM;

    llist_node_59* node = (*llist)->head;
    llist_node_59* next_node = (void*)0;
    while (node)
    {
        next_node = node->next;

        ERR_59_e err = deinit_llist_node_59(&node);
        if (err != ERR_NONE)
            return err;

        node = next_node;
    }

    (*llist)->head = (void*)0;
    (*llist)->tail = (void*)0;
    (*llist)->type = VOID_0;
    (*llist)->type_depth = 0;
    free((*llist));
    (*llist) = (void*)0;

    return ERR_NONE;
}

ERR_59_e push_back_llist_59(llist_59* const llist, llist_node_59* const new_node)
{
    if (!llist || !new_node)
        return ERR_INV_PARAM;

    *(llist->tail) = new_node;
    llist->tail = &(*llist->tail)->next;

    return ERR_NONE;
}

ERR_59_e pop_back_llist_59(llist_59* const llist, llist_node_59** back_node)
{
    if (!llist || !back_node)
        return ERR_INV_PARAM;
    if (!llist->head)
        return ERR_CONTAINER_EMPTY;

    llist_node_59* tail = llist->head;
    llist_node_59* scnd_to_tail = (void*)0;
    while (tail->next)
    {
        scnd_to_tail = tail;
        tail = tail->next;
    }

    *back_node = tail;
    if (scnd_to_tail)
    {
        scnd_to_tail->next = (void*)0;
        llist->tail = &(scnd_to_tail->next);
    }
    else
    { // Only one node in llist ie the head
        llist->head = (void*)0;
        llist->tail = &(llist->head);
    }

    return ERR_NONE;
}

ERR_59_e push_front_llist_59(llist_59* const llist, llist_node_59* const new_front)
{
    if (!llist || !new_front)
        return ERR_INV_PARAM;

    if (!llist->head)
    {
        *llist->tail = new_front;
        llist->head = new_front;
    }
    else
    {
        new_front->next = llist->head;
        llist->head = new_front;
    }

    return ERR_NONE;
}

ERR_59_e pop_front_llist_59(llist_59* const llist, llist_node_59** front_node)
{
    if (!llist || !front_node)
        return ERR_INV_PARAM;
    if (!llist->head)
        return ERR_CONTAINER_EMPTY;

    *front_node = llist->head;

    if (llist->head->next)
        llist->head = llist->head->next;
    else
        llist->head = (void*)0;

    (*front_node)->next = (void*)0;

    return ERR_NONE;
}

ERR_59_e remove_given_node_from_llist_59(llist_59* const llist, llist_node_59* remove_node)
{
    if (!llist || !remove_node)
        return ERR_INV_PARAM;

    llist_node_59* node = llist->head;
    if (!node)
        return ERR_CONTAINER_EMPTY;

    llist_node_59* last_node = (void*)0;
    while (node)
    {
        if (node == remove_node)
        {
            if (last_node)
            {
                last_node->next = node->next;
                if ((void*)0 == last_node->next) // Removed node was the true tail, so tail needs to be moved.
                    llist->tail = &(last_node->next);
            }
            else
            { // Head was only node in the list, tail also needs to be reset.
                llist->head = node->next;
                llist->tail = &(llist->head);
            }

            remove_node = node;
            remove_node->next = (void*)0;
            return ERR_NONE;
        }
        last_node = node;
        node = node->next;
    }

    return ERR_OBJ_NOT_FOUND;
}

ERR_59_e insert_node_into_llist_59(llist_59* const llist, llist_node_59* const new_node, size_t const idx)
{
    if (!llist || !new_node)
        return ERR_INV_PARAM;

    if (!llist->head)
    {
        llist->head = new_node;
        return ERR_NONE;
    }

    llist_node_59* node = llist->head;
    llist_node_59* last_node = (void*)0;
    for (size_t i = 0; i < idx; i++)
    {
        if (!node)
            break;

        last_node = node;
        node = node->next;
    }
    last_node->next = new_node;
    new_node->next = node;

    return ERR_NONE;
}

ERR_59_e find_node_in_llist_59(llist_59 const* const llist, llist_node_59 const* const node, void** val)
{
    if (!llist || !node || !val)
    {
        return ERR_INV_PARAM;
    }

    *val = (void*)0;

    ERR_59_e err = ERR_NONE;
    llist_node_59 const* current = llist->head;
    bool is_same = false;
    while (current)
    {
        err = is_same_mem_addr_59(node, current, &is_same);
        if (ERR_NONE != err)
        {
            return err;
        }
        else if (is_same)
        {
            *val = current->node_obj;
            return err;
        }
        current = current->next;
    }

    return ERR_OBJ_NOT_FOUND;
}

ERR_59_e get_at_idx_llist_59(llist_59 const* const llist, size_t const idx, llist_node_59** node)
{
    if (!llist)
    {
        return ERR_INV_PARAM;
    }

    *node = (void*)0;
    llist_node_59* current = llist->head;
    for (size_t i = 0; i <= idx; i++)
    {
        if (current)
        {
            current = current->next;
        }
        else
        {
            return ERR_INV_PARAM;
        }
    }

    *node = current;
    return ERR_NONE;
}

ERR_59_e init_llist_node_59(llist_node_59** node, llist_node_59* const next, void* node_obj)
{
    if (!node)
        return ERR_INV_PARAM;

    *node = malloc(sizeof(llist_node_59));

    if (!(*node))
        return ERR_NO_MEM;

    (*node)->next = next;
    (*node)->node_obj = node_obj;

    return ERR_NONE;
}

ERR_59_e deinit_llist_node_59(llist_node_59** node)
{
    if (!node || !(*node))
        return ERR_INV_PARAM;

    if ((*node)->node_obj)
        free((*node)->node_obj);

    (*node)->node_obj = (void*)0;
    (*node)->next = (void*)0;
    free((*node));
    (*node) = (void*)0;

    return ERR_NONE;
}
