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
 * @date: 2025-04-30
 * @author: Gregory Nitch
 *
 * @brief: This file contians all the declarations for the double linked list struct.
 **********************************************************************************************************************/

#pragma once

/*
========================================================================================================================
- - SYSTEM INCLUDES - -
========================================================================================================================
*/

#include <stdbool.h>
#include <stddef.h>

/*
========================================================================================================================
- - MODULE INCLUDES - -
========================================================================================================================
*/

#include "containers_common.h"

/*
========================================================================================================================
- - TYPEDEFS - -
========================================================================================================================
*/

typedef struct dlist_node_59 dlist_node_59;
typedef struct dlist_59 dlist_59;

/*
========================================================================================================================
- - STRUCTS - -
========================================================================================================================
*/

/***********************************************************************************************************************
 * @dlist_node_59
 * @brief: Reprents a doubly linked list node within the doubly linked list.
 *
 * @next: pointer to the next node.
 * @last: pointer to the last node.
 * @node_obj: pointer the object at the node, this type is stored in the dlist_59 struct and may be any type.
 *
 * @see dlist_59
 **********************************************************************************************************************/
struct dlist_node_59
{
    dlist_node_59* next;
    dlist_node_59* last;
    void* node_obj;
};

/***********************************************************************************************************************
 * @dlist_59
 * @brief: Represents a linked list with a head.
 *
 * @head: start of the linked list.
 * @tail: end of the linked list inplemented as a pointer to a pointer. Begins as address of @head.
 * @type: type of the linked list's nodes, this can be any type so besure you document what you're pointing at.
 * @type_depth: if pointing at arrays with consistent size, place the size of the arrays here, otherwise leave as 0.
 **********************************************************************************************************************/
struct dlist_59
{
    dlist_node_59* head;
    dlist_node_59** tail;
    TYPE_59_e type;
    size_t type_depth;
};

/*
========================================================================================================================
- - MODULE FUNCTIONS - -
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
ERR_59_e init_dlist_59(dlist_59** dlist, TYPE_59_e const type, size_t const type_depth);

/***********************************************************************************************************************
 * @brief: Deinits the passed doubly linked list and all of the nodes, this also deallocates the used memory.
 *
 * @param[in] dlist: doubly linked list to deinit.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e deinit_dlist_59(dlist_59** dlist);

/***********************************************************************************************************************
 * @brief: Adds a new node to the end of the doubly linked list, this node should already be memory allocated.
 *
 * @param[in] dlist: Linked list to add the node to.
 * @param[in] new_node: New node to add to the linked list.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e push_back_dlist_59(dlist_59* const dlist, dlist_node_59* const new_node);

/***********************************************************************************************************************
 * @brief: Removes the node at the end of the doubly linked list, and provides it via the @back_node parameter.
 *
 * @param[in] dlist: Doubly inked list to pop the tail from.
 * @param[out] back_node: pointer to hold the reference of the tail node, @warning this node will still need to be
 * deallocated with a call to destory_dlist_node_59().
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e pop_back_dlist_59(dlist_59* const dlist, dlist_node_59** back_node);

/***********************************************************************************************************************
 * @brief: Pushes the @new_front to the front of the doubly linked list.
 *
 * @param[in] dlist: doubly linked list to add the node to the front of.
 * @param[in] new_front: node to place at the front of the linked list.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e push_front_dlist_59(dlist_59* const dlist, dlist_node_59* const new_front);

/***********************************************************************************************************************
 * @brief: Pops the head node from the doubly linked list.
 *
 * @param[in] dlist: List to pop the head from.
 * @param[out] front_node: Head of the list returned from function call, @warning this node will need to be deallocated
 * with a call to deinit_node_dlist_59(). @note this may be NULL and will set an ERR_CONTAINER_EMPTY code.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e pop_front_dlist_59(dlist_59* const dlist, dlist_node_59** front_node);

/***********************************************************************************************************************
 * @brief: Removes the passed node from the doubly linked list. @warning DOES NOT DEALLOCATE the node, use
 * deinit_dlist_node_59() after the use of the node is complete.
 *
 * @param[in] dlist: Doubly linked list to remove the node from.
 * @param[out] remove_node: Node to remove, error is returned if not found.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e remove_given_node_from_dlist_59(dlist_59* const dlist, dlist_node_59* remove_node);

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
ERR_59_e insert_node_into_dlist_59(dlist_59* const dlist, dlist_node_59* const new_node, size_t const idx);

/***********************************************************************************************************************
 * @brief Finds a node in a doubly linked list and returns its value or null if the node was not in the list.
 *
 * @param[in] dlist Double linked list to find the node in.
 * @param[in] node Node to find in the list.
 * @param[out] val value of the found node, null if node is not in list.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e find_node_in_dlist_59(dlist_59 const* const dlist, dlist_node_59 const* const node, void** val);

/***********************************************************************************************************************
 * @brief Gets the node from the list at the given index, or null if its out of range.
 *
 * @param[in] dlist Doubly linked list to get the node from.
 * @param[in] idx Index in the doubly linked list to get the node at.
 * @param[out] node Out parameter which contains the node at the given index, or null if out of range.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e get_at_idx_dlist_59(dlist_59 const* const dlist, size_t const idx, dlist_node_59** node);

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
ERR_59_e init_dlist_node_59(dlist_node_59** node, dlist_node_59* const next, dlist_node_59* const last, void* node_obj);

/***********************************************************************************************************************
 * @brief: Deinits a doubly linked list node (deallocates memory for both the node and the void pointer object)
 *
 * @param[in] node: Node to deinit.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e deinit_dlist_node_59(dlist_node_59** node);
