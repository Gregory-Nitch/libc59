#pragma once
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
 * @brief : Reprents a linked list node within the linked list.
 *
 * @next : pointer to the next node.
 * @node_obj : pointer the object at the node, this type is stored in the llist_59 struct and may be any type.
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

ERR_59_e init_llist_59(llist_59 **llist, TYPE_59_e const type, size_t const type_depth);
ERR_59_e deinit_llist_59(llist_59 **llist);
ERR_59_e push_back_llist_59(llist_59 *const llist, llist_node_59 *const new_node);
ERR_59_e pop_back_llist_59(llist_59 *const llist, llist_node_59 **back_node);
ERR_59_e push_front_llist_59(llist_59 *const llist, llist_node_59 *const new_front);
ERR_59_e pop_front_llist_59(llist_59 *const llist, llist_node_59 **front_node);
ERR_59_e remove_given_node_from_llist_59(llist_59 *const llist, llist_node_59 *remove_node);
ERR_59_e insert_node_into_llist_59(llist_59 *const llist, llist_node_59 *const new_node, size_t const idx);
ERR_59_e find_node_in_llist_59(llist_59 const *const llist, llist_node_59 **node, void *val);
ERR_59_e get_at_idx_llist_59(llist_59 const *const llist, llist_node_59 **node, size_t const idx);

ERR_59_e init_llist_node_59(llist_node_59 **node, llist_node_59 *next, void *node_obj);
ERR_59_e deinit_llist_node_59(llist_node_59 **node);
