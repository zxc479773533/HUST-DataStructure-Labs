/*
 * AUTHOR: Yue Pan
 * GITHUB: zxc479773533
 * E-MAIL: zxc479773533@gmail.com
 */

#ifndef PY_LINEARLIST_H
#define PY_LINEARLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define OK 0
#define ERROR 1

#define LIST_INIT_SIZE 100
#define LIST_INCREASEMENT 10


// the main struct of linear list
typedef struct linear_list {
	int id;
	int *data;
	int length;
	int size;
	struct linear_list *next;
} linear_list;

// the struct for managing the linear list
typedef struct Linear_list_main {
	int num;
	linear_list *head;
} Linear_list_main;


int init_list(linear_list *L);
/* 
 * Function Name: init_list
 * Module: Data structures
 * Parameter: linear_list *L
 * Return: int(status)
 * Use: initial the linear list
 */


int destroy_list(linear_list *L);
/* 
 * Function Name: destroy_list
 * Module: Data structures
 * Parameter: linear_list *L
 * Return: int(status)
 * Use: destroy the link list
 */


int clear_list(linear_list *L);
/* 
 * Function Name: clear_list
 * Module: Data structures
 * Parameter: linear_list *L
 * Return: int(status)
 * Use: let the link list empty
 */


int is_list_empty(linear_list L);
/* 
 * Function Name: is_list_empty
 * Module: Data structures
 * Parameter: linear_list L
 * Return: int(true or false)
 * Use: judge if the link list is empty
 */


int list_length(linear_list L);
/* 
 * Function Name: list_length
 * Module: Data structures
 * Parameter: linear_list L
 * Return: int(the length)
 * Use: get the length of linear list
 */


int get_list_item(linear_list L, int order, int *elem);
/* 
 * Function Name: get_list_item
 * Module: Data structures
 * Parameter: linear_list L, int order, int *elem
 * Return: int(status)
 * Use: get the ordered element of link list
 */


int locate_list_item(linear_list L, int ordered_elem);
/* 
 * Function Name: locate_list_item
 * Module: Data structures
 * Parameter: linear_list L, int ordered_elem
 * Return: int(index)
 * Use: get the index of ordered item
 */


int piror_list_item(linear_list L, int elem, int *elem_pre);
/* 
 * Function Name: piror_list_item
 * Module: Data structures
 * Parameter: linear_list L, int elem, int *elem_pre
 * Return: int(status)
 * Use: get the ordered element's piror
 */


int next_list_item(linear_list L, int elem, int *elem_next);
/* 
 * Function Name: next_list_item
 * Module: Data structures
 * Parameter: linear_list L, int elem, int *elem_next
 * Return: int(status)
 * Use: get the ordered element's next
 */


int list_insert(linear_list *L, int order, int elem);
/* 
 * Function Name: list_insert
 * Module: Data structures
 * Parameter: linear_list *L, int order, int elem
 * Return: int(status)
 * Use: insert a element in the link list
 */


int list_delete(linear_list	*L, int order, int *elem);
/* 
 * Function Name: list_delete
 * Module: Data structures
 * Parameter: linear_list *L, int order, int *elem
 * Return: int(status)
 * Use: delete a element in the link list
 */


void print_list(linear_list L);
/* 
 * Function Name: print_list
 * Module: Data structures
 * Parameter: linear_list L
 * Return: None
 * Use: print the elements of the linklist to the payload
 */


#endif // !PY_LINEARLIST_H