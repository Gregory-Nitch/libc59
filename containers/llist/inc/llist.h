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
 * @brief: This file contians all the declarations for the linked list struct.
 **********************************************************************************************************************/

#pragma once

/*
========================================================================================================================
- - SYSTEM INCLUDES - -
========================================================================================================================
*/

#include <stdbool.h>

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

typedef struct llist_node_59 llist_node_59;
typedef struct llist_59 llist_59;

/*
========================================================================================================================
- - STRUCTS - -
========================================================================================================================
*/

/***********************************************************************************************************************
 * @llist_node_59
 * @brief: Reprents a linked list node within the linked list.
 *
 * @next: pointer to the next node.
 * @node_obj: pointer the object at the node, this type is stored in the llist_59 struct and may be any type.
 *
 * @see llist_59
 **********************************************************************************************************************/
struct llist_node_59
{
    llist_node_59* next;
    void* node_obj;
};

/***********************************************************************************************************************
 * @llist_59
 * @brief: Represents a linked list with a head.
 *
 * @head: start of the linked list.
 * @tail: end of the linked list inplemented as a pointer to a pointer. Begins as address of @head.
 * @type: type of the linked list's nodes, this can be any type so besure you document what you're pointing at.
 * @type_depth: if pointing at arrays with consistent size, place the size of the arrays here, otherwise leave as 0.
 **********************************************************************************************************************/
struct llist_59
{
    llist_node_59* head;
    llist_node_59** tail;
    TYPE_59_e type;
    size_t type_depth;
};

/*
========================================================================================================================
- - MODULE FUNCTIONS - -
========================================================================================================================
*/

/***********************************************************************************************************************
 * @brief: Initializes a linked list, this also allocates memory to the @llist pointer.
 *
 * @param[out] llist: linked list pointer to initialize, this will need to be freed later. @note @head and
 * @tail will be NULL. @warning This must be freed when its lifetime has ended.
 * @param[in] type: type of the linked list to initalize.
 * @param[in] type_depth: size of the node elements, all must be the same size, if not set as 0. If there are nodes of
 * different sizes the implementation will need to define comparisons and indexing into those elements.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e init_llist_59(llist_59** llist, TYPE_59_e const type, size_t const type_depth);

/***********************************************************************************************************************
 * @brief: Deinits the passed linked list and all of the nodes, this also deallocates the used memory.
 *
 * @param[in] llist: linked list to deinit.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e deinit_llist_59(llist_59** llist);

/***********************************************************************************************************************
 * @brief: Adds a new node to the end of the linked list, this node should already be memory allocated.
 *
 * @param[in] llist: Linked list to add the node to.
 * @param[in] new_node: New node to add to the linked list.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e push_back_llist_59(llist_59* const llist, llist_node_59* const new_node);

/***********************************************************************************************************************
 * @brief: Removes the node at the end of the linked list, and provides it via the @back_node parameter.
 *
 * @param[in] llist: Linked list to pop the tail from.
 * @param[out] back_node: pointer to hold the reference of the tail node, @warning this node will still need to be
 * deallocated with a call to destory_llist_node_59().
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e pop_back_llist_59(llist_59* const llist, llist_node_59** back_node);

/***********************************************************************************************************************
 * @brief: Pushes the @new_front to the front of the linked list.
 *
 * @param[in] llist: Linked list to add the node to the front of.
 * @param[in] new_front: node to place at the front of the linked list.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e push_front_llist_59(llist_59* const llist, llist_node_59* const new_front);

/***********************************************************************************************************************
 * @brief: Pops the head node from the linked list.
 *
 * @param[in] llist: List to pop the head from.
 * @param[out] front_node: Head of the list returned from function call, @warning this node will need to be deallocated
 * with a call to deinit_node_llist_59(). @note this may be NULL and will set an ERR_CONTAINER_EMPTY code.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e pop_front_llist_59(llist_59* const llist, llist_node_59** front_node);

/***********************************************************************************************************************
 * @brief: Removes the passed node from the linked list.
 *
 * @param[in] llist: Linked list to remove the node from.
 * @param[out] remove_node: Node to remove, error is returned if not found.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 *
 * @warning DOES NOT DEALLOCATE the node, use deinit_llist_node_59() after the use of the node is complete.
 **********************************************************************************************************************/
ERR_59_e remove_given_node_from_llist_59(llist_59* const llist, llist_node_59* remove_node);

/***********************************************************************************************************************
 * @brief: Inserts a node into the linked list at the passed index, if the index is passed the end of the list it
 * appends the node to the end of the list.
 *
 * @param[in] llist: Linked list to add the new node too.
 * @param[in] new_node: New node to add to the linked list.
 * @param[in] idx: Index in the linked list to add the node at.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e insert_node_into_llist_59(llist_59* const llist, llist_node_59* const new_node, size_t const idx);

/***********************************************************************************************************************
 * @brief Finds the given node in the linked list and returns its value, value will be null if not found. @note This
 * matches by memory address of the given node, not value.
 *
 * @param[in] llist The linked list to search.
 * @param[in] node the node to search for.
 * @param[out] val The pointer to place the found value in.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e find_node_in_llist_59(llist_59 const* const llist, llist_node_59 const* const node, void** val);

/***********************************************************************************************************************
 * @brief Gets the node in the linked list at the given index, if the index is out of range the node out parameter will
 * be null.
 *
 * @param[in] llist The linked list to retrive the node from.
 * @param[in] idx Index in the linked list to retreive.
 * @param[out] node Pointer to a pointer which shall return the node in the llist if idx is in range.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e get_at_idx_llist_59(llist_59 const* const llist, size_t const idx, llist_node_59** node);

/***********************************************************************************************************************
 * @brief: Initializes a node for a @llist_59, @next and @node_obj can be NULL.
 *
 * @param[in] node: Pointer to initialize new node in. @warning This node must be freed to end its lifetime.
 * @param[in] next: Next node in the llinked list to point at, may be NULL.
 * @param[in] node_obj: Object that the new node shall point to, may be NULL.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e init_llist_node_59(llist_node_59** node, llist_node_59* const next, void* node_obj);

/***********************************************************************************************************************
 * @brief: Deinits a linked list node (deallocates memory for both the node and the void pointer object)
 *
 * @param[in] node: Node to deinit.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e deinit_llist_node_59(llist_node_59** node);
