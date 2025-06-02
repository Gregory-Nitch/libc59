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
 * @date : 2025-03-18
 * @author : Gregory Nitch
 *
 * @brief : Contains all the definitions for the linked list container.
 **********************************************************************************************************************/

/*
========================================================================================================================
- - SYSTEM INCLUDES - -
========================================================================================================================
*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> //! TODO: Remove this

/*
========================================================================================================================
- - MODULE INCLUDES - -
========================================================================================================================
*/

#include "llist_59.h"

/*
========================================================================================================================
- - FUNCTION DEFINITIONS - -
========================================================================================================================
*/

/***********************************************************************************************************************
 * @brief : Initializes a linked list, this also allocates memory to the @llist pointer.
 *
 * @param[out] llist : linked list pointer to initialize, this will need to be freed later. @note @head and
 * @tail will be NULL. @warning This must be freed when its lifetime has ended.
 * @param[in] type : type of the linked list to initalize.
 * @param[in] type_depth : size of the node elements, all must be the same size, if not set as 0. If there are nodes of
 * different sizes the implementation will need to define comparisons and indexing into those elements.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e init_llist_59(llist_59 **llist, TYPE_59_e const type, size_t const type_depth)
{
    if (!llist)
        return ERR_INV_PARAM;

    *llist = malloc(sizeof(llist_59));

    if (!(*llist))
        return ERR_NO_MEM;

    (*llist)->type = type;
    (*llist)->type_depth = type_depth;
    (*llist)->head = (void *)0;
    (*llist)->tail = &(*llist)->head;

    return ERR_NONE;
}

/***********************************************************************************************************************
 * @brief : Deinits the passed linked list and all of the nodes, this also deallocates the used memory.
 *
 * @param[in] llist : linked list to deinit.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e deinit_llist_59(llist_59 **llist)
{
    if (!llist || !(*llist))
        return ERR_INV_PARAM;

    llist_node_59 *node = (*llist)->head;
    llist_node_59 *next_node = (void *)0;
    while (node)
    {
        next_node = node->next;

        ERR_59_e err = deinit_llist_node_59(&node);
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
 * @brief : Adds a new node to the end of the linked list, this node should already be memory allocated.
 *
 * @param[in] llist : Linked list to add the node to.
 * @param[in] new_node : New node to add to the linked list.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e push_back_llist_59(llist_59 *const llist, llist_node_59 *const new_node)
{
    if (!llist || !new_node)
        return ERR_INV_PARAM;

    *(llist->tail) = new_node;
    llist->tail = &(*llist->tail)->next;

    return ERR_NONE;
}

/***********************************************************************************************************************
 * @brief : Removes the node at the end of the linked list, and provides it via the @back_node parameter.
 *
 * @param[in] llist : Linked list to pop the tail from.
 * @param[out] back_node : pointer to hold the reference of the tail node, @warning this node will still need to be
 * deallocated with a call to destory_llist_node_59().
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e pop_back_llist_59(llist_59 *const llist, llist_node_59 **back_node)
{
    if (!llist || !back_node)
        return ERR_INV_PARAM;
    if (!llist->head)
        return ERR_CONTAINER_EMPTY;

    llist_node_59 *tail = llist->head;
    llist_node_59 *scnd_to_tail = (void *)0;
    while (tail->next)
    {
        scnd_to_tail = tail;
        tail = tail->next;
    }

    *back_node = tail;
    if (scnd_to_tail)
    {
        scnd_to_tail->next = (void *)0;
        llist->tail = &(scnd_to_tail->next);
    }
    else
    { // Only one node in llist ie the head
        llist->head = (void *)0;
        llist->tail = &(llist->head);
    }

    return ERR_NONE;
}

/***********************************************************************************************************************
 * @brief : Pushes the @new_front to the front of the linked list.
 *
 * @param[in] llist : Linked list to add the node to the front of.
 * @param[in] new_front : node to place at the front of the linked list.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e push_front_llist_59(llist_59 *const llist, llist_node_59 *const new_front)
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

/***********************************************************************************************************************
 * @brief : Pops the head node from the linked list.
 *
 * @param[in] llist : List to pop the head from.
 * @param[out] front_node : Head of the list returned from function call, @warning this node will need to be deallocated
 * with a call to deinit_node_llist_59(). @note this may be NULL and will set an ERR_CONTAINER_EMPTY code.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e pop_front_llist_59(llist_59 *const llist, llist_node_59 **front_node)
{
    if (!llist || !front_node)
        return ERR_INV_PARAM;
    if (!llist->head)
        return ERR_CONTAINER_EMPTY;

    *front_node = llist->head;

    if (llist->head->next)
        llist->head = llist->head->next;
    else
        llist->head = (void *)0;

    (*front_node)->next = (void *)0;

    return ERR_NONE;
}

/***********************************************************************************************************************
 * @brief : Removes the passed node from the linked list.
 *
 * @param[in] llist : Linked list to remove the node from.
 * @param[out] remove_node : Node to remove, error is returned if not found.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 *
 * @warning DOES NOT DEALLOCATE the node, use deinit_llist_node_59() after the use of the node is complete.
 **********************************************************************************************************************/
ERR_59_e remove_given_node_from_llist_59(llist_59 *const llist, llist_node_59 *remove_node)
{
    if (!llist || !remove_node)
        return ERR_INV_PARAM;

    llist_node_59 *node = llist->head;
    if (!node)
        return ERR_CONTAINER_EMPTY;

    llist_node_59 *last_node = (void *)0;
    while (node)
    {
        if (node == remove_node)
        {
            if (last_node)
            {
                last_node->next = node->next;
                if ((void *)0 == last_node->next) // Removed node was the true tail, so tail needs to be moved.
                    llist->tail = &(last_node->next);
            }
            else
            { // Head was only node in the list, tail also needs to be reset.
                llist->head = node->next;
                llist->tail = &(llist->head);
            }

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
 * @brief : Inserts a node into the linked list at the passed index, if the index is passed the end of the list it
 * appends the node to the end of the list.
 *
 * @param[in] llist : Linked list to add the new node too.
 * @param[in] new_node : New node to add to the linked list.
 * @param[in] idx : Index in the linked list to add the node at.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e insert_node_into_llist_59(llist_59 *const llist, llist_node_59 *const new_node, size_t const idx)
{
    if (!llist || !new_node)
        return ERR_INV_PARAM;

    if (!llist->head)
    {
        llist->head = new_node;
        return ERR_NONE;
    }

    llist_node_59 *node = llist->head;
    llist_node_59 *last_node = (void *)0;
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

/***********************************************************************************************************************
 * @brief : Initializes a node for a @llist_59, @next and @node_obj can be NULL.
 *
 * @param[in] node : Pointer to initialize new node in. @warning This node must be freed to end its lifetime.
 * @param[in] next : Next node in the llinked list to point at, may be NULL.
 * @param[in] node_obj : Object that the new node shall point to, may be NULL.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e init_llist_node_59(llist_node_59 **node, llist_node_59 *next, void *node_obj)
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

/***********************************************************************************************************************
 * @brief : Deinits a linked list node (deallocates memory for both the node and the void pointer object)
 *
 * @param[in] node : Node to deinit.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e deinit_llist_node_59(llist_node_59 **node)
{
    if (!node || !(*node))
        return ERR_INV_PARAM;

    if ((*node)->node_obj)
        free((*node)->node_obj);

    (*node)->node_obj = (void *)0;
    (*node)->next = (void *)0;
    free((*node));
    (*node) = (void *)0;

    return ERR_NONE;
}
