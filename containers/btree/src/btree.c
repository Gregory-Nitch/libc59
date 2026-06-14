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
    ERR_59_e err = compare_node_obj_59(type, &diff, root->node_obj, new_node->node_obj);
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
            return err = _insert_node_from(root->left, new_node, type, type_depth);
    }
    else
    { // (0 >= diff)
        if (!root->right)
        {
            root->right = new_node;
            return ERR_NONE;
        }
        else
            return err = _insert_node_from(root->right, new_node, type, type_depth);
    }

    return err;
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

    free((*btree));
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
        return ERR_NONE;
    }

    ERR_59_e err = _insert_node_from(btree->root, new_node, btree->type, btree->type_depth);

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
        ERR_59_e err = compare_node_obj_59(btree->type, &diff, current->node_obj, val);
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

ERR_59_e remove_given_node_from_btree_59(btree_59 const* const btree, btree_node_59* const remove_node)
{
    //! TODO: this
}

ERR_59_e btree_preorder_traverse_59(btree_59 const* const btree, vec_59** vec)
{
    //! TODO: this
}

ERR_59_e btree_inorder_traverse_59(btree_59 const* const btree, vec_59** vec)
{
    //! TODO: this
}

ERR_59_e btree_postorder_traverse_59(btree_59 const* const btree, vec_59** vec)
{
    //! TODO: this
}

ERR_59_e btree_levelorder_traverse_59(btree_59 const* const btree, vec_59** vec)
{
    //! TODO: this
}

ERR_59_e rebalance_btree_59(btree_59* const btree)
{
    //! TODO: this
}

ERR_59_e get_btree_height_59(btree_59 const* const btree, size_t* out)
{
    //! TODO: this
}

ERR_59_e init_btree_node_59(btree_node_59** node,
                            btree_node_59 const* const left,
                            btree_node_59 const* const right,
                            void const* const node_obj)
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
    free((*node));
    (*node) = (void*)0;

    return ERR_NONE;
}
