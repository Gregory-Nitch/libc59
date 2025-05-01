/***********************************************************************************************************************
 * LICENSE : NONE, as in zilch, zipo, nada, null, nill, 0, zero. If you use this file and are not me you are wrong.
 *
 * @date : 2025-04-30
 * @author : Gregory Nitch
 *
 * @brief : This file contians all the declarations for the double linked list struct.
 **********************************************************************************************************************/

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

#include "container_common_59.h"

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
 * @brief : Reprents a doubly linked list node within the doubly linked list.
 *
 * @next : pointer to the next node.
 * @last : pointer to the last node.
 * @node_obj : pointer the object at the node, this type is stored in the dlist_59 struct and may be any type.
 *
 * @see dlist_59
 **********************************************************************************************************************/
struct dlist_node_59
{
    dlist_node_59 *next;
    dlist_node_59 *last;
    void *node_obj;
};

/***********************************************************************************************************************
 * @dlist_59
 * @brief : Represents a linked list with a head.
 *
 * @head : start of the linked list.
 * @tail : end of the linked list inplemented as a pointer to a pointer. Begins as address of @head.
 * @type : type of the linked list's nodes, this can be any type so besure you document what you're pointing at.
 * @type_depth : if pointing at arrays with consistent size, place the size of the arrays here, otherwise leave as 0.
 **********************************************************************************************************************/
struct dlist_59
{
    dlist_node_59 *head;
    dlist_node_59 **tail;
    TYPE_59_e type;
    size_t type_depth;
};

/*
========================================================================================================================
- - MODULE FUNCTIONS - -
========================================================================================================================
*/

ERR_59_e init_dlist_59(dlist_59 **dlist, TYPE_59_e const type, size_t const type_depth);
ERR_59_e destroy_dlist_59(dlist_59 **dlist);
ERR_59_e push_back_dlist_59(dlist_59 *const dlist, dlist_node_59 *const new_node);
ERR_59_e pop_back_dlist_59(dlist_59 *const dlist, dlist_node_59 **back_node);
ERR_59_e push_front_dlist_59(dlist_59 *const dlist, dlist_node_59 *const new_front);
ERR_59_e pop_front_dlist_59(dlist_59 *const dlist, dlist_node_59 **front_node);
ERR_59_e remove_given_node_from_dlist_59(dlist_59 *const dlist, dlist_node_59 *remove_node);
ERR_59_e insert_node_into_dlist_59(dlist_59 *const dlist, dlist_node_59 *const new_node, size_t const idx);

ERR_59_e init_dlist_node_59(dlist_node_59 **node, dlist_node_59 *next, dlist_node_59 *last, void *node_obj);
ERR_59_e destroy_dlist_node_59(dlist_node_59 **node);
