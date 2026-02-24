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

/***********************************************************************************************************************
 * @brief: Initializes a doubly linked list, this also allocates memory to the @dlist pointer.
 *
 * @param[out] dlist: doubly linked list pointer to initialize, this will need to be freed later. @note @head and
 * @tail will be NULL. @warning This must be freed when its lifetime has ended.
 * @param[in] type: type of the linked list to initalize.
 * @param[in] type_depth: size of the node elements, all must be the same size, if not set as 0. If there are nodes of
 * different sizes the implementation will need to define comparisons and indexing into those elements.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e init_dlist_59(dlist_59 **dlist, TYPE_59_e const type, size_t const type_depth)
{
    if (!dlist)
        return ERR_INV_PARAM;

    *dlist = malloc(sizeof(dlist_59));

    if (!(*dlist))
        return ERR_NO_MEM;

    (*dlist)->type = type;
    (*dlist)->type_depth = type_depth;
    (*dlist)->head = (void *)0;
    (*dlist)->tail = &(*dlist)->head;

    return ERR_NONE;
}

/***********************************************************************************************************************
 * @brief: Deinits the passed doubly linked list and all of the nodes, this also deallocates the used memory.
 *
 * @param[in] dlist: doubly linked list to deinit.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e deinit_dlist_59(dlist_59 **dlist)
{
    if (!dlist || !(*dlist))
        return ERR_INV_PARAM;

    dlist_node_59 *node = (*dlist)->head;
    dlist_node_59 *next_node = (void *)0;
    while (node)
    {
        next_node = node->next;

        ERR_59_e err = deinit_dlist_node_59(&node);
        if (err != ERR_NONE)
            return err;

        node = next_node;
    }

    (*dlist)->head = (void *)0;
    (*dlist)->tail = (void *)0;
    (*dlist)->type = VOID_0;
    (*dlist)->type_depth = 0;
    free((*dlist));
    (*dlist) = (void *)0;

    return ERR_NONE;
}

/***********************************************************************************************************************
 * @brief: Adds a new node to the end of the doubly linked list, this node should already be memory allocated.
 *
 * @param[in] dlist: Linked list to add the node to.
 * @param[in] new_node: New node to add to the linked list.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e push_back_dlist_59(dlist_59 *const dlist, dlist_node_59 *const new_node)
{
    if (!dlist || !new_node)
        return ERR_INV_PARAM;

    dlist_node_59 *current_node = dlist->head;
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

/***********************************************************************************************************************
 * @brief: Removes the node at the end of the doubly linked list, and provides it via the @back_node parameter.
 *
 * @param[in] dlist: Doubly inked list to pop the tail from.
 * @param[out] back_node: pointer to hold the reference of the tail node, @warning this node will still need to be
 * deallocated with a call to destory_dlist_node_59().
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e pop_back_dlist_59(dlist_59 *const dlist, dlist_node_59 **back_node)
{
    if (!dlist || !back_node)
        return ERR_INV_PARAM;
    if (!dlist->head)
        return ERR_CONTAINER_EMPTY;

    dlist_node_59 *tail = dlist->head;
    dlist_node_59 *scnd_to_tail = (void *)0;
    while (tail->next)
    {
        scnd_to_tail = tail;
        tail = tail->next;
    }

    *back_node = tail;
    if (scnd_to_tail)
    {
        scnd_to_tail->next = (void *)0;
        (*back_node)->last = (void *)0;
        dlist->tail = &(scnd_to_tail->next);
    }
    else
    { // Only one node in dlist ie the head
        dlist->head = (void *)0;
        dlist->tail = &dlist->head;
    }

    return ERR_NONE;
}

/***********************************************************************************************************************
 * @brief: Pushes the @new_front to the front of the doubly linked list.
 *
 * @param[in] dlist: doubly linked list to add the node to the front of.
 * @param[in] new_front: node to place at the front of the linked list.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e push_front_dlist_59(dlist_59 *const dlist, dlist_node_59 *const new_front)
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

/***********************************************************************************************************************
 * @brief: Pops the head node from the doubly linked list.
 *
 * @param[in] dlist: List to pop the head from.
 * @param[out] front_node: Head of the list returned from function call, @warning this node will need to be deallocated
 * with a call to deinit_node_dlist_59(). @note this may be NULL and will set an ERR_CONTAINER_EMPTY code.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e pop_front_dlist_59(dlist_59 *const dlist, dlist_node_59 **front_node)
{
    if (!dlist || !front_node)
        return ERR_INV_PARAM;
    if (!dlist->head)
        return ERR_CONTAINER_EMPTY;

    *front_node = dlist->head;

    if (dlist->head->next)
    {
        dlist->head->next->last = (void *)0;
        dlist->head = dlist->head->next;
    }
    else
        dlist->head = (void *)0;

    (*front_node)->next = (void *)0;

    return ERR_NONE;
}

/***********************************************************************************************************************
 * @brief: Removes the passed node from the doubly linked list. @warning DOES NOT DEALLOCATE the node, use
 * deinit_dlist_node_59() after the use of the node is complete.
 *
 * @param[in] dlist: Doubly linked list to remove the node from.
 * @param[out] remove_node: Node to remove, error is returned if not found.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e remove_given_node_from_dlist_59(dlist_59 *const dlist, dlist_node_59 *remove_node)
{
    if (!dlist || !remove_node)
        return ERR_INV_PARAM;

    dlist_node_59 *node = dlist->head;
    if (!node)
        return ERR_CONTAINER_EMPTY;

    dlist_node_59 *last_node = (void *)0;
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
            remove_node->next = (void *)0;
            return ERR_NONE;
        }
        last_node = node;
        node = node->next;
    }

    return ERR_OBJ_NOT_FOUND;
}

/***********************************************************************************************************************
 * @brief: Inserts a node into the doubly linked list at the passed index, if the index is passed the end of the list it
 * appends the node to the end of the list.
 *
 * @param[in] dlist: Doubly inked list to add the new node too.
 * @param[in] new_node: New node to add to the doubly linked list.
 * @param[in] idx: Index in the doubly linked list to add the node at.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e insert_node_into_dlist_59(dlist_59 *const dlist, dlist_node_59 *const new_node, size_t const idx)
{
    if (!dlist || !new_node)
        return ERR_INV_PARAM;

    if (!dlist->head)
    {
        dlist->head = new_node;
        return ERR_NONE;
    }

    dlist_node_59 *node = dlist->head;
    dlist_node_59 *last_node = (void *)0;
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

/***********************************************************************************************************************
 * @brief Finds a node in a doubly linked list and returns its value or null if the node was not in the list.
 *
 * @param[in] dlist Double linked list to find the node in.
 * @param[in] node Node to find in the list.
 * @param[out] val value of the found node, null if node is not in list.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e find_node_in_dlist_59(dlist_59 const *const dlist, dlist_node_59 const *const node, void **val)
{
    if (!dlist || !node || !val)
    {
        return ERR_INV_PARAM;
    }

    *val = (void *)0;

    ERR_59_e err = ERR_NONE;
    dlist_node_59 const *current = dlist->head;
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

/***********************************************************************************************************************
 * @brief Gets the node from the list at the given index, or null if its out of range.
 *
 * @param[in] dlist Doubly linked list to get the node from.
 * @param[in] idx Index in the doubly linked list to get the node at.
 * @param[out] node Out parameter which contains the node at the given index, or null if out of range.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e get_at_idx_dlist_59(dlist_59 const *const dlist, size_t const idx, dlist_node_59 **node)
{
    if (!dlist)
    {
        return ERR_INV_PARAM;
    }

    *node = (void *)0;
    dlist_node_59 *current = dlist->head;
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

/***********************************************************************************************************************
 * @brief: Initializes a node for a @dlist_59, @next, @last and @node_obj can be NULL.
 *
 * @param[in] node: Pointer to initialize new node in. @warning This node must be freed to end its lifetime.
 * @param[in] next: Next node in the doubly linked list to point at, may be NULL.
 * @param[in] last: Last node in the doubly linked list to point at, may be NULL.
 * @param[in] node_obj: Object that the new node shall point to, may be NULL.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e init_dlist_node_59(dlist_node_59 **node, dlist_node_59 *const next, dlist_node_59 *const last, void *node_obj)
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

/***********************************************************************************************************************
 * @brief: Deinits a doubly linked list node (deallocates memory for both the node and the void pointer object)
 *
 * @param[in] node: Node to deinit.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e deinit_dlist_node_59(dlist_node_59 **node)
{
    if (!node || !(*node))
        return ERR_INV_PARAM;

    if ((*node)->node_obj)
        free((*node)->node_obj);

    (*node)->node_obj = (void *)0;
    (*node)->next = (void *)0;
    (*node)->last = (void *)0;
    free((*node));
    (*node) = (void *)0;

    return ERR_NONE;
}
