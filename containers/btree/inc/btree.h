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
 * @date: 2026-02-24
 * @author: Gregory Nitch
 *
 * @brief: Contains all the declarations for the binary search tree container.
 **********************************************************************************************************************/

#pragma once

/*
========================================================================================================================
- - SYSTEM INCLDUES - -
========================================================================================================================
*/

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

typedef struct btree_node_59 btree_node_59;
typedef struct btree_59 btree_59;

/*
========================================================================================================================
- - STRUCTS - -
========================================================================================================================
*/

/***********************************************************************************************************************
 * @btree_node_59
 * @brief Represents a node in a tree.
 *
 * @left: pointer to the left child.
 * @right: pointer to the right child.
 * @node_obj: pointer to the node object, this pointers type is stored in the btree_59 object and may be any type.
 *
 * @see btree_59
 **********************************************************************************************************************/
struct btree_node_59
{
    btree_node_59* left;
    btree_node_59* right;
    void* node_obj;
};

/***********************************************************************************************************************
 * @btree_59
 * @brief Represents a binary search tree.
 *
 * @root: the root of the tree.
 * @type: the type of the node objects in the tree.
 * @type_depth: if pointing at arrays with consistant size, place the size of the arrayss here, otherwise leave as 0.
 **********************************************************************************************************************/
struct btree_59
{
    btree_node_59* root;
    TYPE_59_e type;
    size_t type_depth;
    size_t size;
};

/*
========================================================================================================================
- - MODULE FUNCTIONS - -
========================================================================================================================
*/

/***********************************************************************************************************************
 * @brief: Initializes a binary search tree, this allocates memory into the @btree pointer
 *
 * @param[out] btree: pointer to a pointer to hold the allocated binary search tree made during initialization.
 * @param[in] type: type of node objects held in the tree.
 * @param[in] type_depth: size of the node elements if it is an array type, if not set as 0. If there nodes of different
 * sizes the implementaion will need to define comparisons and indexing into those elements.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e init_btree_59(btree_59** btree, TYPE_59_e const type, size_t const type_depth);

/***********************************************************************************************************************
 * @brief: Frees an entire binary search tree.
 *
 * @param[in] btree: point to pointer of a binary search tree to free.
 * @note: the contained pointer will be null after calling this function.
 *
 * @retval: ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e deinit_btree_59(btree_59** btree);

/***********************************************************************************************************************
 * @brief Inserts a node into the binary search tree.
 *
 * @param[in] btree: pointer to the binary search tree.
 * @param[in] new_node: pointer to the node to insert.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e insert_node_into_btree_59(btree_59* const btree, btree_node_59* const new_node);

/***********************************************************************************************************************
 * @brief Finds a node in the binary search tree.
 *
 * @param[in] btree: pointer to the binary search tree.
 * @param[in] val: pointer to the value to search for.
 * @param[out] out: pointer to a pointer to hold the found node.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e find_node_in_btree_59(btree_59 const* const btree, void const* const val, btree_node_59** out);

/***********************************************************************************************************************
 * @brief: Removes the given node from the binary search tree.
 *
 * @param[in] btree: pointer to the binary search tree.
 * @param[in] remove_node: pointer to the node to remove from the tree.
 *
 * @note: This function detaches the node from the tree, but does not free the removed node. The caller is responsible
 * for deallocating the node if needed.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e remove_given_node_from_btree_59(btree_59* const btree, btree_node_59* const remove_node);

/***********************************************************************************************************************
 * @brief TODO
 *
 * @param[TODO] TODO TODO.
 * @param[TODO] TODO TODO.
 *
 * @retval TODO TODO.
 **********************************************************************************************************************/
ERR_59_e rebalance_btree_59(btree_59* const btree);

/***********************************************************************************************************************
 * @brief TODO
 *
 * @param[TODO] TODO TODO.
 * @param[TODO] TODO TODO.
 *
 * @retval TODO TODO.
 **********************************************************************************************************************/
ERR_59_e get_height_btree_59(btree_59 const* const btree, size_t* out);

/***********************************************************************************************************************
 * @brief: Allocates a new node for a binary search tree.
 *
 * @param[inout] node: pointer to a pointer that shall hold the created node.
 * @param[in] left: the left child of the new node.
 * @param[in] right: the right child of the new node.
 * @param[in] node_obj: the node object to store at the new node.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e
init_btree_node_59(btree_node_59** node, btree_node_59* const left, btree_node_59* const right, void* const node_obj);

/***********************************************************************************************************************
 * @brief: Frees the passed binary search tree node.
 *
 * @param[in] node: pointer to a node pointer to free.
 * @note: this also deallocates the node object pointer's memory.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e deinit_btree_node_59(btree_node_59** node);
