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
#include <string.h>

#include <stdio.h> // TODO REMOVE

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
 * @tail will be NULL.
 * @param[in] type : type of the linked list to initalize.
 * @param[in] type_depth : size of the node elements, all must be the same size, if not set as 0. If there are nodes of
 * different sizes the implementation will need to define comparisons and indexing into those elements.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e init_llist_59(llist_59 **llist, TYPE_59_e type, size_t type_depth)
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
 * @brief : Destroys the passed linked list and all of the nodes, this also deallocates the used memory.
 *
 * @param[in] llist : linked list to destroy.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e destroy_llist_59(llist_59 **llist)
{
    if (!llist || !(*llist))
        return ERR_INV_PARAM;

    llist_node_59 *node = (*llist)->head;
    llist_node_59 *next_node = (void *)0;
    while (node)
    {
        next_node = node->next;

        ERR_59_e err = destroy_llist_node_59(&node);
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
ERR_59_e push_back_llist_59(llist_59 *llist, llist_node_59 *new_node)
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
ERR_59_e pop_back_llist_59(llist_59 *llist, llist_node_59 **back_node)
{
    if (!llist)
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
        llist->tail = &llist->head;
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
ERR_59_e push_front_llist_59(llist_59 *llist, llist_node_59 *new_front)
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
 * with a call to destroy_node_llist_59(). @note this may be NULL and will set an ERR_CONTAINER_EMPTY code.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e pop_front_llist_59(llist_59 *llist, llist_node_59 *front_node)
{
    if (!llist)
        return ERR_INV_PARAM;
    if (!llist->head)
        return ERR_CONTAINER_EMPTY;

    front_node = llist->head;

    if (llist->head->next)
        llist->head = llist->head->next;
    else
        llist->head = (void *)0;

    front_node->next = (void *)0;

    return ERR_NONE;
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
                last_node->next = node->next;
            else
                llist->head = node->next;

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
ERR_59_e insert_node_into_llist_59(llist_59 *llist, llist_node_59 *new_node, size_t idx)
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
 * @param[in] node : Pointer to initialize new node in.
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
 * @brief : Destroys a linked list node (deallocates memory for both the node and the void pointer object)
 *
 * @param[in] node : Node to destroy.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e destroy_llist_node_59(llist_node_59 **node)
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

/***********************************************************************************************************************
 * @brief : Compares two list nodes such that if the value of @node_A is greater than @node_B a positive value is
 * returned in @diff_out, or a negative when @node_B is greater than @node_A, or 0 when they are equal.
 *
 * @param[in] llist : Linked List that the nodes belong to, the type struct member will be used to determine the
 * comparison path.
 * @param[in] node_A : Node to compare.
 * @param[in] node_B : Other node to compare.
 * @param[out] diff_out : Difference determined based on the difference between the node_obj members of the nodes.
 *
 * @note Strings when compared will produce negative values for strings that come first alphabetically. ie, a - b = -1
 * @note Only only signed, unsigned, chars, and strings are supported by this function. ERR_NOT_SUPPORTED will be
 * returned.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e compare_llist_nodes_59(llist_59 *llist, llist_node_59 *node_A, llist_node_59 *node_B, i64 *diff_out)
{
    if (!llist || !node_A || !node_B || !diff_out)
        return ERR_INV_PARAM;

    switch (llist->type)
    { // TODO : properly test return of unsigned types
    // Unsigned
    case U8_PTR:
        *diff_out = *((u8 *)node_A->node_obj) - *((u8 *)node_B->node_obj);
        break;

    case U16_PTR:
        *diff_out = *((u16 *)node_A->node_obj) - *((u16 *)node_B->node_obj);
        break;

    case U32_PTR:
        *diff_out = *((u32 *)node_A->node_obj) - *((u32 *)node_B->node_obj);
        break;

    case U64_PTR:
        *diff_out = *((u64 *)node_A->node_obj) - *((u64 *)node_B->node_obj);
        break;

    case SIZE_PTR:
        *diff_out = *((size_t *)node_A->node_obj) = *((size_t *)node_B->node_obj);
        break;

    // Signed
    case I8_PTR:
        *diff_out = *((i8 *)node_A->node_obj) - *((i8 *)node_B->node_obj);
        break;

    case I16_PTR:
        *diff_out = *((i16 *)node_A->node_obj) - *((i16 *)node_B->node_obj);
        break;

    case I32_PTR:
        *diff_out = *((i32 *)node_A->node_obj) - *((i32 *)node_B->node_obj);
        break;

    case I64_PTR:
        *diff_out = *((i64 *)node_A->node_obj) - *((i64 *)node_B->node_obj);
        break;

    // Other
    case CHAR_PTR: // NOTE : This is not a string (only a single char)
        *diff_out = *((char *)node_A->node_obj) - *((char *)node_B->node_obj);
        break;

    case STR: // NOTE : This is an array of chars terminated by '\0', ie a string
        *diff_out = strcmp((char *)node_A->node_obj, (char *)node_B->node_obj);
        break;

    default: // We are trying to compare something that this function has not been made for. Such as a struct
        return ERR_NOT_SUPPORTED;
    }

    return ERR_NONE;
}

/***********************************************************************************************************************
 * @brief : Compares two linked list node pointers, if they point to the same address they are the same node. Returns
 * false when one or both nodes are NULL.
 *
 * @param[in] node_A : Node to compare.
 * @param[in] node_B : Other node to compare.
 * @param[out] is_same : bool value to return for boolean logic.
 *
 * @retval ERR_59_e : error value encountered during the function call, ERR_NONE = all ok.
 **********************************************************************************************************************/
ERR_59_e is_same_llist_node_59(llist_node_59 *node_A, llist_node_59 *node_B, bool *is_same)
{
    if (!is_same)
        return ERR_INV_PARAM;

    if (!node_A || !node_B)
        *is_same = false;
    else
        *is_same = node_A == node_B;

    return ERR_NONE;
}
