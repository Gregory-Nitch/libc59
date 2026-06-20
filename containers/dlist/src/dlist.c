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
 * @brief: Contains all the definitions for the doubly linked list container.
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

#include "dlist.h"

/*
========================================================================================================================
- - FUNCTION DEFINITIONS - -
========================================================================================================================
*/

ERR_59_e init_dlist_59(dlist_59** dlist, TYPE_59_e const type, size_t const type_depth)
{
    if (!dlist)
        return ERR_INV_PARAM;

    *dlist = malloc(sizeof(dlist_59));

    if (!(*dlist))
        return ERR_NO_MEM;

    (*dlist)->type = type;
    (*dlist)->type_depth = type_depth;
    (*dlist)->head = (void*)0;
    (*dlist)->tail = &(*dlist)->head;

    return ERR_NONE;
}

ERR_59_e deinit_dlist_59(dlist_59** dlist)
{
    if (!dlist || !(*dlist))
        return ERR_INV_PARAM;

    dlist_node_59* node = (*dlist)->head;
    dlist_node_59* next_node = (void*)0;
    while (node)
    {
        next_node = node->next;

        ERR_59_e err = deinit_dlist_node_59(&node);
        if (err != ERR_NONE)
            return err;

        node = next_node;
    }

    (*dlist)->head = (void*)0;
    (*dlist)->tail = (void*)0;
    (*dlist)->type = VOID_0;
    (*dlist)->type_depth = 0;
    free((*dlist));
    (*dlist) = (void*)0;

    return ERR_NONE;
}

ERR_59_e push_back_dlist_59(dlist_59* const dlist, dlist_node_59* const new_node)
{
    if (!dlist || !new_node)
        return ERR_INV_PARAM;

    dlist_node_59* current_node = dlist->head;
    while (current_node)
    {
        if (current_node->next)
            current_node = current_node->next;
        else
            break;
    }

    new_node->last = current_node;
    *(dlist->tail) = new_node;
    dlist->tail = &(*dlist->tail)->next;

    return ERR_NONE;
}

ERR_59_e pop_back_dlist_59(dlist_59* const dlist, dlist_node_59** back_node)
{
    if (!dlist || !back_node)
        return ERR_INV_PARAM;
    if (!dlist->head)
        return ERR_CONTAINER_EMPTY;

    dlist_node_59* tail = dlist->head;
    dlist_node_59* scnd_to_tail = (void*)0;
    while (tail->next)
    {
        scnd_to_tail = tail;
        tail = tail->next;
    }

    *back_node = tail;
    if (scnd_to_tail)
    {
        scnd_to_tail->next = (void*)0;
        (*back_node)->last = (void*)0;
        dlist->tail = &(scnd_to_tail->next);
    }
    else
    { // Only one node in dlist ie the head
        dlist->head = (void*)0;
        dlist->tail = &dlist->head;
    }

    return ERR_NONE;
}

ERR_59_e push_front_dlist_59(dlist_59* const dlist, dlist_node_59* const new_front)
{
    if (!dlist || !new_front)
        return ERR_INV_PARAM;

    if (!dlist->head)
    {
        *dlist->tail = new_front;
        dlist->head = new_front;
    }
    else
    {
        new_front->next = dlist->head;
        dlist->head->last = new_front;
        dlist->head = new_front;
    }

    return ERR_NONE;
}

ERR_59_e pop_front_dlist_59(dlist_59* const dlist, dlist_node_59** front_node)
{
    if (!dlist || !front_node)
        return ERR_INV_PARAM;
    if (!dlist->head)
        return ERR_CONTAINER_EMPTY;

    *front_node = dlist->head;

    if (dlist->head->next)
    {
        dlist->head->next->last = (void*)0;
        dlist->head = dlist->head->next;
    }
    else
        dlist->head = (void*)0;

    (*front_node)->next = (void*)0;

    return ERR_NONE;
}

ERR_59_e remove_given_node_from_dlist_59(dlist_59* const dlist, dlist_node_59* remove_node)
{
    if (!dlist || !remove_node)
        return ERR_INV_PARAM;

    dlist_node_59* node = dlist->head;
    if (!node)
        return ERR_CONTAINER_EMPTY;

    dlist_node_59* last_node = (void*)0;
    while (node)
    {
        if (node == remove_node)
        {
            if (last_node)
            {
                last_node->next = node->next;
                node->next->last = last_node;
            }
            else
                dlist->head = node->next;

            remove_node = node;
            remove_node->next = (void*)0;
            return ERR_NONE;
        }
        last_node = node;
        node = node->next;
    }

    return ERR_OBJ_NOT_FOUND;
}

ERR_59_e insert_node_into_dlist_59(dlist_59* const dlist, dlist_node_59* const new_node, size_t const idx)
{
    if (!dlist || !new_node)
        return ERR_INV_PARAM;

    if (!dlist->head)
    {
        dlist->head = new_node;
        return ERR_NONE;
    }

    dlist_node_59* node = dlist->head;
    dlist_node_59* last_node = (void*)0;
    for (size_t i = 0; i < idx; i++)
    {
        if (!node)
            break;

        last_node = node;
        node = node->next;
    }
    last_node->next = new_node;
    new_node->last = last_node;
    new_node->next = node;
    if (node)
        node->last = new_node;

    return ERR_NONE;
}

ERR_59_e find_node_in_dlist_59(dlist_59 const* const dlist, dlist_node_59 const* const node, void** val)
{
    if (!dlist || !node || !val)
    {
        return ERR_INV_PARAM;
    }

    *val = (void*)0;

    dlist_node_59 const* current = dlist->head;
    while (current)
    {
        if (node == current)
        {
            *val = current->node_obj;
            return ERR_NONE;
        }
        current = current->next;
    }

    return ERR_OBJ_NOT_FOUND;
}

ERR_59_e get_at_idx_dlist_59(dlist_59 const* const dlist, size_t const idx, dlist_node_59** node)
{
    if (!dlist)
    {
        return ERR_INV_PARAM;
    }

    *node = (void*)0;
    dlist_node_59* current = dlist->head;
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

ERR_59_e init_dlist_node_59(dlist_node_59** node, dlist_node_59* const next, dlist_node_59* const last, void* node_obj)
{
    if (!node)
        return ERR_INV_PARAM;

    *node = malloc(sizeof(dlist_node_59));

    if (!(*node))
        return ERR_NO_MEM;

    (*node)->next = next;
    (*node)->last = last;
    (*node)->node_obj = node_obj;

    return ERR_NONE;
}

ERR_59_e deinit_dlist_node_59(dlist_node_59** node)
{
    if (!node || !(*node))
        return ERR_INV_PARAM;

    if ((*node)->node_obj)
        free((*node)->node_obj);

    (*node)->node_obj = (void*)0;
    (*node)->next = (void*)0;
    (*node)->last = (void*)0;
    free((*node));
    (*node) = (void*)0;

    return ERR_NONE;
}
