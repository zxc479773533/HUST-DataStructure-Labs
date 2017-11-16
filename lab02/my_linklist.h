/*
 * AUTHOR: Yue Pan
 * GITHUB: zxc479773533
 * E-MAIL: zxc479773533@gmail.com
 */

#ifndef LINKLIST_H
#define LINKLIST_H

// whether using chain storage structure
#define USING_CHAIN

#define TRUE 1
#define FALSE 0

#define OK 0
#define ERROR 1

// some defination for ordered storage structure
#define LIST_INIT_SIZE 100
#define LIST_INCREASEMENT 10

// the element type in the data structure
typedef int elem_type;

// the structure of link node using chain storage structure
typedef struct link_node {
	elem_type data;
	struct link_node *next;
} link_node;

// the main struct of linklist
typedef struct link_list {
#ifdef USING_CHAIN
	int length;
  link_node *head;
#else
  elem_type *data;
	int length;
	int size;
#endif
} link_list;


int init_list(link_list *L);
/* 
 * Func: initial the link list
 * Args: link list
 * Ret: the status
 */


int destroy_list(link_list *L);
/* 
 * Func: destroy the link list
 * Args: link list
 * Ret: the status
 */


int clear_list(link_list *L);
/* 
 * Func: let the link list empty
 * Args: link list
 * Ret: the status
 */


int is_list_empty(link_list L);
/* 
 * Func: judge if the link list is empty
 * Args: link list
 * Ret: true or false
 */


int list_length(link_list L);
/* 
 * Func: get the length of link list
 * Args: link list
 * Ret: the length
 */


int get_list_item(link_list L, int order, elem_type *elem);
/* 
 * Func: get the ordered element of link list
 * Args: link list, the order, the target element
 * Ret: the status
 */


int locate_list_item(link_list L, elem_type ordered_elem);
/* 
 * Func: locate the ordered item
 * Args: link list, the ordered element
 * Ret: the index of the element
 */


int piror_list_item(link_list L, elem_type elem, elem_type *elem_pre);
/* 
 * Func: get the ordered element's piror
 * Args: link list, the order, the target element
 * Ret: the status
 */



int next_list_item(link_list L, elem_type elem, elem_type *elem_next);
/* 
 * Func: get the ordered element's next
 * Args: link list, the order, the target element
 * Ret: the status
 */


int list_insert(link_list *L, int order, elem_type elem);
/* 
 * Func: insert a element in the link list
 * Args: link list, the order, the target element
 * Ret: the status
 */


int list_delete(link_list	*L, int order, elem_type elem);
/* 
 * Func: delete a element in the link list
 * Args: link list, the order, the target element
 * Ret: the status
 */

void print_list(link_list L);
/* 
 * Func: print the elements of the linklist
 * Args: link list
 * Ret: none
 */

#endif // !LINKLIST_H