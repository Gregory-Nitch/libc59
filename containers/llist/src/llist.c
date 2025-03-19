/***********************************************************************************************************************
 * LICENSE : NONE, as in zilch, zipo, nada, null, nill, 0, zero. If you use this file and are not me you are wrong.
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

#include <stdbool.h>
#include <stdlib.h>

/*
========================================================================================================================
- - MODULE INCLUDES - -
========================================================================================================================
*/

#include "libc59_common.h"
#include "llist.h"

/*
========================================================================================================================
- - FUNCTION DEFINITIONS - -
========================================================================================================================
*/

/***********************************************************************************************************************
 * @brief : Initializes a linked list, this also allocates memory to the @llist pointer.
 *
 * @param[out] llist : linked list pointer to initialize, this will need to be freed later. @note @head and
 * @tail will be NULL.
 * @param[in] type : type of the linked list to initalize.
 * @param[in] type_depth : size of the node elements, all must be the same size, if not set as 0. If there are nodes of
 * different sizes the implementation will need to define comparisons and indexing into those elements.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e init_llist_59(llist_59 *llist, TYPE_59_e type, size_t type_depth)
{

    llist = malloc(sizeof(llist_59));

    if (!llist)
        return ERR_NO_MEM;

    llist->type = type;
    llist->type_depth = type_depth;
    llist->head = (void *)0;
    llist->tail = (void *)0;

    return ERR_NONE;
}

/***********************************************************************************************************************
 * @brief : Destroys the passed linked list and all of the nodes, this also deallocates the used memory.
 *
 * @param[in] llist : linked list to destroy.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e destroy_llist_59(llist_59 *llist)
{
    if (!llist)
        return ERR_INV_PARAM;

    llist_node_59 *node = llist->head;
    llist_node_59 *next_node = (void *)0;
    while (node)
    {
        next_node = node->next;

        ERR_59_e err = destroy_llist_node_59(node);
        if (err != ERR_NONE)
            return err;

        node = next_node;
    }

    llist->head = (void *)0;
    llist->tail = (void *)0;
    llist->type = (void *)0;
    llist->type_depth = (void *)0;
    free(llist);
    llist = (void *)0;

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
ERR_59_e push_back_llist_59(llist_59 *llist, llist_node_59 *new_node)
{
    if (!llist || !new_node)
        return ERR_INV_PARAM;

    *llist->tail = new_node;
    llist->tail = &(*llist->tail)->next;

    return ERR_NONE;
}

ERR_59_e pop_back_llist_59(llist_59 *llist, llist_node_59 *back_node)
{
    // TODO :
}

ERR_59_e push_front_llist_59(llist_59 *llist, llist_node_59 *new_front)
{
    // TODO :
}

ERR_59_e pop_front_llist_59(llist_59 *llist, llist_node_59 *front_node)
{
    // TODO :
}

/***********************************************************************************************************************
 * @brief : Removes the passed node from the linked list. @warning DOES NOT DEALLOCATE the node, use
 * destroy_llist_node_59() after the use of the node is complete.
 *
 * @param[in] llist : Linked list to remove the node from.
 * @param[out] remove_node : Node to remove, error is returned if not found.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e remove_given_node_from_llist_59(llist_59 *llist, llist_node_59 *remove_node)
{
    // TODO: . . .
}

ERR_59_e insert_node_into_llist_59(llist_59 *llist, llist_node_59 *new_node, size_t idx)
{
    // TODO: . . .
}

ERR_59_e init_llist_node_59(llist_node_59 *node, llist_node_59 *next, void *node_obj)
{
    // TODO: . . .
}

ERR_59_e destroy_llist_node_59(llist_node_59 *node)
{
    // TODO: . . .
}

ERR_59_e compare_llist_nodes_59(llist_59 *llist, llist_node_59 *node_A, llist_node_59 *node_B, i64 *diff_out)
{
    // TODO: . . .
}

ERR_59_e is_same_llist_node_59(llist_node_59 *node_A, llist_node_59 *node_B, bool *is_same)
{
    // TODO: . . .
}
