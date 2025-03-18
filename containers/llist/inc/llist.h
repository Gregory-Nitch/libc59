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

#include <sys/types.h>

/*
========================================================================================================================
- - MODULE INCLUDES - -
========================================================================================================================
*/

#include "container_common.h"

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

typedef struct llist_node_59
{
    llist_node_59 *next;
    void *node_obj;
} llist_node_59;

/***********************************************************************************************************************
 * @llist_59
 * @brief : Represents a linked list with a head.
 *
 * @head : start of the linked list.alignas.
 * @type : type of the linked list's nodes, this can be any type so besure you document what you're pointing at.
 * @type_depth : if pointing at arrays with consistent size, place the size of the arrays here, otherwise leave as 0.
 **********************************************************************************************************************/
typedef struct llist_59
{
    llist_node_59 *head;
    container_data_type_59 type;
    size_t type_depth;
} llist_59;
