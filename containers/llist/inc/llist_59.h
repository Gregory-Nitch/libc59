/***********************************************************************************************************************
 * LICENSE : NONE, as in zilch, zipo, nada, null, nill, 0, zero. If you use this file and are not me you are wrong.
 *
 * @date : 2025-03-18
 * @author : Gregory Nitch
 *
 * @brief : This file contians all the declarations for the linked list struct.
 **********************************************************************************************************************/

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

#include "libc59_common.h"

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
 * @brief : Reprents a linked list node within the linked list.
 *
 * @next : pointer to the next node.
 * @node_obj : pointer the object at the node, this type is stored in the llist_59 struct and may be any type.alignas
 *
 * @see llist_59
 **********************************************************************************************************************/
struct llist_node_59
{
    llist_node_59 *next;
    void *node_obj;
};

/***********************************************************************************************************************
 * @llist_59
 * @brief : Represents a linked list with a head.
 *
 * @head : start of the linked list.
 * @tail : end of the linked list inplemented as a pointer to a pointer. Begins as address of @head.
 * @type : type of the linked list's nodes, this can be any type so besure you document what you're pointing at.
 * @type_depth : if pointing at arrays with consistent size, place the size of the arrays here, otherwise leave as 0.
 **********************************************************************************************************************/
struct llist_59
{
    llist_node_59 *head;
    llist_node_59 **tail;
    TYPE_59_e type;
    size_t type_depth;
};

/*
========================================================================================================================
- - MODULE FUNCTIONS - -
========================================================================================================================
*/

ERR_59_e init_llist_59(llist_59 **llist, TYPE_59_e type, size_t type_depth);
ERR_59_e destroy_llist_59(llist_59 **llist);
ERR_59_e push_back_llist_59(llist_59 *llist, llist_node_59 *new_node);
ERR_59_e pop_back_llist_59(llist_59 *llist, llist_node_59 **back_node);
ERR_59_e push_front_llist_59(llist_59 *llist, llist_node_59 *new_front);
ERR_59_e pop_front_llist_59(llist_59 *llist, llist_node_59 *front_node);
ERR_59_e remove_given_node_from_llist_59(llist_59 *llist, llist_node_59 *remove_node);
ERR_59_e insert_node_into_llist_59(llist_59 *llist, llist_node_59 *new_node, size_t idx);

ERR_59_e init_llist_node_59(llist_node_59 **node, llist_node_59 *next, void *node_obj);
ERR_59_e destroy_llist_node_59(llist_node_59 **node);
ERR_59_e compare_llist_nodes_59(llist_59 *llist, llist_node_59 *node_A, llist_node_59 *node_B, i64 *diff_out);
ERR_59_e is_same_llist_node_59(llist_node_59 *node_A, llist_node_59 *node_B, bool *is_same);
