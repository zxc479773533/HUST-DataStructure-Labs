/*
 * AUTHOR: Yue Pan
 * GITHUB: zxc479773533
 * E-MAIL: zxc479773533@gmail.com
 */

#ifndef PY_LINKLIST_H
#define PY_LINKLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define OK 0
#define ERROR 1

// the struct of link node
typedef struct link_node {
	int data;
	struct link_node *next;
} link_node;

// the main struct of link list
typedef struct link_list {
	int id;
	int length;
	struct link_node *head;
	struct link_list *next;
} link_list;

// the struct for managing the link list
typedef struct Link_list_main {
	int num;
	link_list *head;
} Link_list_main;

int init_list(link_list *L);
/* 
 * Function Name: init_list
 * Module: Data structures
 * Parameter: link_list *L
 * Return: int(status)
 * Use: initial the link list
 */


int destroy_list(link_list *L);
/* 
 * Function Name: destroy_list
 * Module: Data structures
 * Parameter: link_list *L
 * Return: int(status)
 * Use: destroy the link list
 */


int clear_list(link_list *L);
/* 
 * Function Name: clear_list
 * Module: Data structures
 * Parameter: link_list *L
 * Return: int(status)
 * Use: let the link list empty
 */


int is_list_empty(link_list L);
/* 
 * Function Name: is_list_empty
 * Module: Data structures
 * Parameter: link_list L
 * Return: int(true or false)
 * Use: judge if the link list is empty
 */


int list_length(link_list L);
/* 
 * Function Name: list_length
 * Module: Data structures
 * Parameter: link_list L
 * Return: int(the length)
 * Use: get the length of link list
 */


int get_list_item(link_list L, int order, int *elem);
/* 
 * Function Name: get_list_item
 * Module: Data structures
 * Parameter: link_list L, int order, int *elem
 * Return: int(status)
 * Use: get the ordered element of link list
 */


int locate_list_item(link_list L, int ordered_elem);
/* 
 * Function Name: locate_list_item
 * Module: Data structures
 * Parameter: link_list L, int ordered_elem
 * Return: int(index)
 * Use: get the index of ordered item
 */


int piror_list_item(link_list L, int elem, int *elem_pir);
/* 
 * Function Name: piror_list_item
 * Module: Data structures
 * Parameter: link_list L, int elem, int *elem_pir
 * Return: int(status)
 * Use: get the ordered element's piror
 */


int next_list_item(link_list L, int elem, int *elem_next);
/* 
 * Function Name: next_list_item
 * Module: Data structures
 * Parameter: link_list L, int elem, int *elem_next
 * Return: int(status)
 * Use: get the ordered element's next
 */


int list_insert(link_list *L, int order, int elem);
/* 
 * Function Name: list_insert
 * Module: Data structures
 * Parameter: link_list *L, int order, int elem
 * Return: int(status)
 * Use: insert a element in the link list
 */


int list_delete(link_list	*L, int order, int *elem);
/* 
 * Function Name: list_delete
 * Module: Data structures
 * Parameter: link_list *L, int order, int *elem
 * Return: int(status)
 * Use: delete a element in the link list
 */


void print_list(link_list L);
/* 
 * Function Name: print_list
 * Module: Data structures
 * Parameter: link_list L
 * Return: None
 * Use: print the elements of the linklist to the payload
 */


#endif // !PY_LINKLIST_H