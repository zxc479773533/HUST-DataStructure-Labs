/*
 * AUTHOR: Yue Pan
 * GITHUB: zxc479773533
 * E-MAIL: zxc479773533@gmail.com
 */

#include "my_linklist.h"

int init_list(link_list *L) {
/* 
 * Function Name: init_list
 * Module: Data structures
 * Parameter: link_list *L
 * Return: int(status)
 * Use: initial the link list
 */

  L->length = 0;
  L->head = NULL;
  return OK;
}

int destroy_list(link_list *L) {
/* 
 * Function Name: destroy_list
 * Module: Data structures
 * Parameter: link_list *L
 * Return: int(status)
 * Use: destroy the link list
 */

  link_node *a_node = L->head;
  // traverse and free nodes
  while (a_node != NULL) {
      link_node *tmp = a_node;
      a_node = a_node->next;
      free(tmp);
  }
  free(L);
  return OK;
}

int clear_list(link_list *L) {
/* 
 * Function Name: clear_list
 * Module: Data structures
 * Parameter: link_list *L
 * Return: int(status)
 * Use: let the link list empty
 */

  link_node *a_node = L->head;
  if (a_node == NULL)
    return ERROR;
  // traverse and free node
  while (a_node != NULL) {
    link_node *tmp = a_node;
    a_node = a_node->next;
    free(tmp);
  }
  L->length = 0;
  L->head = NULL;
  return OK;
}

int is_list_empty(link_list L) {
/* 
 * Function Name: is_list_empty
 * Module: Data structures
 * Parameter: link_list L
 * Return: int(true or false)
 * Use: judge if the link list is empty
 */

  if (L.length == 0)
    return TRUE;
  else
    return FALSE;
}

int list_length(link_list L) {
/* 
 * Function Name: list_length
 * Module: Data structures
 * Parameter: link_list L
 * Return: int(the length)
 * Use: get the length of link list
 */

  return L.length;
}

int get_list_item(link_list L, int order, int *elem) {
/* 
 * Function Name: get_list_item
 * Module: Data structures
 * Parameter: link_list L, int order, int *elem
 * Return: int(status)
 * Use: get the ordered element of link list
 */

  int index = 0;
  link_node *a_node = L.head;
  // traverse and find the ordered node
  while (a_node != NULL) {
    index++;
    if (index == order) {
      *elem = a_node->data;
      break;
    }
    a_node = a_node->next;
  }
  if (a_node == NULL)
    return ERROR;
  else
    return OK;  
}

int locate_list_item(link_list L, int ordered_elem) {
/* 
 * Function Name: locate_list_item
 * Module: Data structures
 * Parameter: link_list L, int ordered_elem
 * Return: int(index)
 * Use: locate the ordered item
 */

  int index = 0;
  link_node *a_node = L.head;
  // traverse and find the ordered node
  while (a_node != NULL) {
    index++;
    if (a_node->data == ordered_elem)
      break;
    a_node = a_node->next;
  }
  if (a_node != NULL)
    return index;
  else
    return 0;
}

int piror_list_item(link_list L, int elem, int *elem_pir) {
/* 
 * Function Name: piror_list_item
 * Module: Data structures
 * Parameter: link_list L, int elem, int *elem_pir
 * Return: int(status)
 * Use: get the ordered element's piror
 */

  link_node *piror_node = L.head;
  link_node *a_node = piror_node->next;
  // traverse and find the order node
  while (a_node != NULL) {
    if (a_node->data == elem) {
      *elem_pir = piror_node->data;
      break;
    }
    piror_node = piror_node->next;
    a_node = piror_node->next;
  }
  if (a_node != NULL)
    return OK;
  else
    return ERROR;
}

int next_list_item(link_list L, int elem, int *elem_next) {
/* 
 * Function Name: next_list_item
 * Module: Data structures
 * Parameter: link_list L, int elem, int *elem_next
 * Return: int(status)
 * Use: get the ordered element's next
 */

  link_node *a_node = L.head;
  link_node *next_node = a_node->next;
  // traverse and find the order node
  while (next_node != NULL) {
    if (a_node->data == elem) {
      *elem_next = next_node->data;
      break;
    }
    a_node = a_node->next;
    next_node = a_node->next;
  }
  if (next_node != NULL)
    return OK;
  else
    return ERROR;
}

int list_insert(link_list *L, int order, int elem) {
/* 
 * Function Name: list_insert
 * Module: Data structures
 * Parameter: link_list *L, int order, int elem
 * Return: int(status)
 * Use: insert a element in the link list
 */

  int index = 0;
  link_node *a_node = L->head;
  // the first node should be discussed separately
  if (order == 1) {
    link_node *new_node = (link_node*)malloc(sizeof(link_node));
    new_node->data = elem;
    new_node->next = L->head;
    L->head = new_node;
    L->length++;
    return OK;
  }
  // start find the ordered node from the 2nd node
  while (a_node != NULL) {
    index++;
    if (index == order - 1) {
      link_node *new_node = (link_node*)malloc(sizeof(link_node));
      new_node->data = elem;
      new_node->next = a_node->next;
      a_node->next = new_node;
      L->length++;
      break;
    }
    a_node = a_node->next;
  }
  if (a_node != NULL)
    return OK;
  else
    return ERROR;
}

int list_delete(link_list	*L, int order, int *elem) {
/* 
 * Function Name: list_delete
 * Module: Data structures
 * Parameter: link_list *L, int order, int *elem
 * Return: int(status)
 * Use: delete a element in the link list
 */

  // condition check
  if (L->length == 0 || L->head == NULL)
    return ERROR;
  int index = 0;
  link_node *a_node = L->head;
  // the first node should be discussed separately
  if (order == 1) {
    L->head = a_node->next;
    free(a_node);
    L->length--;
    return OK;
  }
  // start find the ordered node from the 2nd node
  while (a_node != NULL) {
    index++;
    if (index == order - 1) {
      link_node *tmp = a_node->next;
      *(elem) = tmp->data;
      a_node->next = a_node->next->next;
      free(tmp);
      L->length--;
      break;
    }
    a_node = a_node->next;
  }
  if (a_node != NULL)
    return OK;
  else
    return ERROR;
}

void print_list(link_list L) {
/* 
 * Function Name: print_list
 * Module: Data structures
 * Parameter: link_list L
 * Return: int(status)
 * Use: print the elements of the linklist to the payload
 */

  int index = 0;
  link_node *a_node = L.head;
  while (a_node != NULL) {
    index++;
    printf("Index: %d, Data: %d\n", index, a_node->data);
    a_node = a_node->next;
  }
}