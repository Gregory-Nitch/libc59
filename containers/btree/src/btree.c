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
 * @date: 2025-02-25
 * @author: Gregory Nitch
 *
 * @brief: Contains all the definitions for the binary search tree container.
 **********************************************************************************************************************/

/*
========================================================================================================================
- - SYSTEM INCLUDES - -
========================================================================================================================
*/

#include <stddef.h>
#include <stdlib.h>

/*
========================================================================================================================
- - MODULE INCLUDES - -
========================================================================================================================
*/

#include "btree.h"
#include "common.h"
#include "containers_common.h"

/*
========================================================================================================================
- - INTERNAL FUNCTION DEFINITIONS - -
========================================================================================================================
*/

/***********************************************************************************************************************
 * @brief: Deletes all nodes under the given node.
 *
 * @param[in]: node node to free all the children from.
 * @warning: this is inclusive, ie the passed node will also be freed.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
static ERR_59_e _delete_from_node(btree_node_59** node)
{
    if (!node)
        return ERR_INV_PARAM;
    if (!(*node))
        return ERR_NONE;
    _delete_from_node(&(*node)->left);
    _delete_from_node(&(*node)->right);
    ERR_59_e err = deinit_btree_node_59(node);

    return err;
}

/***********************************************************************************************************************
 * @brief: Inserts a node into the binary search tree. (Used internally after checking for null root)
 *
 * @param[in]: root root or current (ie sub root) node of the tree.
 * @param[in]: new_node node to insert.
 * @param[in]: type type of the node object.
 * @param[in]: type_depth depth of the node type (if it is an array).
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
static ERR_59_e _insert_node_from(btree_node_59* const root,
                                  btree_node_59* const new_node,
                                  TYPE_59_e const type,
                                  size_t const type_depth)
{
    if (!root || !new_node)
        return ERR_INV_PARAM;

    i64 diff = 0; // negative diff = new node is bigger
    ERR_59_e err = compare_node_obj_59(type, root->node_obj, new_node->node_obj, &diff);
    if (ERR_NONE != err)
        return err;

    if (0 > diff)
    {
        if (!root->left)
        {
            root->left = new_node;
            return ERR_NONE;
        }
        else
            return _insert_node_from(root->left, new_node, type, type_depth);
    }
    else
    { // (0 <= diff)
        if (!root->right)
        {
            root->right = new_node;
            return ERR_NONE;
        }
        else
            return _insert_node_from(root->right, new_node, type, type_depth);
    }
}

/***********************************************************************************************************************
 * @brief: Recursively computes the maximum number of levels in the subtree.
 *
 * @param[in]: node Current node in the traversal. A null node marks the bottom of a branch.
 * @param[in]: depth Current traversal depth (level count from the original caller context).
 * @param[out]: out Pointer to the running maximum depth found across all visited branches.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
static ERR_59_e _count_levels_intrnl(btree_node_59 const* const node, size_t depth, size_t* out)
{
    if (!out)
        return ERR_INV_PARAM;

    if (!node) // Base case, bottom of this part of the tree
    {
        if (depth > *out)
            *out = depth;
        return ERR_NONE;
    }

    ERR_59_e err = _count_levels_intrnl(node->left, depth + 1, out);
    if (ERR_NONE != err)
        return err;

    return _count_levels_intrnl(node->right, depth + 1, out);
}

/***********************************************************************************************************************
 * @brief: Writes the subtree nodes into an array using an inorder traversal.
 *
 * @param[in]: node Current node in the traversal. A null node marks the bottom of a branch.
 * @param[out]: arr Array of node pointers to fill in sorted tree order.
 * @param[in,out]: index Running insertion index into @arr.
 *
 * @retval ERR_59_e: error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
static ERR_59_e
_inorder_traverse_to_arr_intrnl(btree_node_59* const node, btree_node_59** const arr, size_t* const index)
{
    if (!arr || !index)
        return ERR_INV_PARAM;

    if (!node)
        return ERR_NONE;

    ERR_59_e err = _inorder_traverse_to_arr_intrnl(node->left, arr, index);
    if (ERR_NONE != err)
        return err;

    arr[*index] = node;
    (*index)++;

    return _inorder_traverse_to_arr_intrnl(node->right, arr, index);
}

/***********************************************************************************************************************
 * @brief: Rebuilds a balanced subtree from a sorted array of node pointers.
 *
 * @param[in]: nodes Array of node pointers sorted in binary-search-tree order.
 * @param[in]: start First array index included in the subtree range.
 * @param[in]: end Last array index included in the subtree range.
 *
 * @retval btree_node_59*: Root node of the rebuilt subtree, or null if the range is empty.
 **********************************************************************************************************************/
static btree_node_59* _rebuild_from_arr_intrnl(btree_node_59** nodes, size_t start, size_t end)
{
    if (start > end) //! TODO: if (start > end) is better? what about overflow?
        return (void*)0;

    size_t mid = start + (end - start) / 2;
    btree_node_59* node = nodes[mid];
    node->left = (void*)0;
    node->right = (void*)0;

    if (mid > start)
        node->left = _rebuild_from_arr_intrnl(nodes, start, mid - 1);
    if (mid < end)
        node->right = _rebuild_from_arr_intrnl(nodes, mid + 1, end);

    return node;
}

/*
========================================================================================================================
- - FUNCTION DEFINITIONS - -
========================================================================================================================
*/

ERR_59_e init_btree_59(btree_59** btree, TYPE_59_e const type, size_t const type_depth)
{
    if (!btree)
        return ERR_INV_PARAM;

    *btree = malloc(sizeof(btree_59));
    if (!(*btree))
        return ERR_NO_MEM;

    (*btree)->root = (void*)0;
    (*btree)->type = type;
    (*btree)->type_depth = type_depth;
    (*btree)->size = 0;

    return ERR_NONE;
}

ERR_59_e deinit_btree_59(btree_59** btree)
{
    if (!btree || !(*btree))
        return ERR_INV_PARAM;

    ERR_59_e err = _delete_from_node(&(*btree)->root);

    free(*btree);
    *btree = (void*)0;

    return err;
}

ERR_59_e insert_node_into_btree_59(btree_59* const btree, btree_node_59* const new_node)
{
    if (!btree || !new_node)
        return ERR_INV_PARAM;

    if (!btree->root)
    {
        btree->root = new_node;
        btree->size++;
        return ERR_NONE;
    }

    ERR_59_e err = _insert_node_from(btree->root, new_node, btree->type, btree->type_depth);
    if (ERR_NONE == err)
        btree->size++;

    return err;
}

ERR_59_e find_node_in_btree_59(btree_59 const* const btree, void const* const val, btree_node_59** out)
{
    if (!btree || !val || !out)
        return ERR_INV_PARAM;

    *out = (void*)0;
    btree_node_59* current = btree->root;

    while (current)
    {
        i64 diff = 0; // negative diff = searching value is bigger
        ERR_59_e err = compare_node_obj_59(btree->type, current->node_obj, val, &diff);
        if (ERR_NONE != err)
            return err;

        if (0 == diff)
        {
            *out = current;
            return ERR_NONE;
        }
        else if (0 > diff)
            current = current->right;
        else // (0 < diff)
            current = current->left;
    }

    *out = (void*)0;
    return ERR_OBJ_NOT_FOUND;
}

ERR_59_e remove_given_node_from_btree_59(btree_59* const btree, btree_node_59* const remove_node)
{
    if (!btree || !remove_node)
        return ERR_INV_PARAM;

    btree_node_59* current = btree->root;
    btree_node_59* parent = (void*)0;
    i64 diff = 0;
    ERR_59_e err = ERR_NONE;
    bool found_node = false;
    while (current)
    {
        if (current == remove_node)
        {
            found_node = true;
            break;
        }

        err = compare_node_obj_59(btree->type, &diff, current->node_obj, remove_node->node_obj);
        if (ERR_NONE != err)
            return err;

        parent = current;
        if (0 > diff)
            current = current->left;
        else // 0 <= diff : ie., copies go right
            current = current->right;
    }

    if (!found_node)
        return ERR_OBJ_NOT_FOUND; // Null root case && not found case

    if (!current->left && !current->right)
    {
        if (parent)
        {
            if (0 > diff)
                parent->left = (void*)0;
            else // 0 <= diff : ie., copies go right
                parent->right = (void*)0;
        }
        else
        { // current = root
            btree->root = (void*)0;
        }
    }
    else if (current->left && current->right)
    {
        btree_node_59* smallest = current->right;
        btree_node_59* smallest_parent = current;
        while (smallest->left)
        {
            smallest_parent = smallest;
            smallest = smallest->left;
        }

        if (smallest_parent != current)
        {
            smallest_parent->left = smallest->right;
            smallest->right = current->right;
        }

        smallest->left = current->left;

        if (!parent)
            btree->root = smallest;
        else if (parent->left == current)
            parent->left = smallest;
        else
            parent->right = smallest;
    }
    else if (current->left)
    {
        if (!parent)
            btree->root = current->left;
        else if (parent->left == current)
            parent->left = current->left;
        else
            parent->right = current->left;
    }
    else if (current->right)
    {
        if (!parent)
            btree->root = current->right;
        else if (parent->right == current)
            parent->right = current->right;
        else
            parent->left = current->right;
    }

    remove_node->left = (void*)0;
    remove_node->right = (void*)0;
    btree->size--;
    return ERR_NONE;
}

ERR_59_e rebalance_btree_59(btree_59* const btree)
{
    if (!btree || !btree->root || !btree->size)
        return ERR_INV_PARAM;

    //! NOTE: No calloc because we assume all memory will be overwritten with the nodes to be inserted.
    btree_node_59** nodes = malloc(sizeof(btree_node_59*) * btree->size);
    if (!nodes)
        return ERR_NO_MEM;

    size_t index = 0;
    ERR_59_e err = _inorder_traverse_to_arr_intrnl(btree->root, nodes, &index);
    if (ERR_NONE != err)
    {
        free(nodes);
        return err;
    }

    btree->root = _rebuild_from_arr_intrnl(nodes, 0, btree->size - 1);

    free(nodes);
    return err;
}

ERR_59_e get_height_btree_59(btree_59 const* const btree, size_t* out)
{
    if (!btree || !out)
        return ERR_INV_PARAM;

    *out = 0;
    return _count_levels_intrnl(btree->root, 0, out);
}

ERR_59_e
init_btree_node_59(btree_node_59** node, btree_node_59* const left, btree_node_59* const right, void* const node_obj)
{
    if (!node)
        return ERR_INV_PARAM;

    (*node) = malloc(sizeof(btree_node_59));

    if (!(*node))
        return ERR_NO_MEM;

    (*node)->node_obj = node_obj;
    (*node)->left = left;
    (*node)->right = right;

    return ERR_NONE;
}

ERR_59_e deinit_btree_node_59(btree_node_59** node)
{
    if (!node || !(*node))
        return ERR_INV_PARAM;

    free((*node)->node_obj);
    (*node)->node_obj = (void*)0;
    free(*node);
    (*node) = (void*)0;

    return ERR_NONE;
}
