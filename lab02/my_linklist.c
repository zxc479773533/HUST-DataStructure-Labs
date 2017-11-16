/*
 * AUTHOR: Yue Pan
 * GITHUB: zxc479773533
 * E-MAIL: zxc479773533@gmail.com
 */

#include "my_linklist.h"
#include <stdio.h>
#include <stdlib.h>


int init_list(link_list *L) {
/* 
 * Func: initial the link list
 * Args: link list
 * Ret: the status
 */
#ifdef USING_CHAIN
  L->length = 0;
  L->head = NULL;
#else
  L->data = (elem_type*)malloc(LIST_INIT_SIZE * sizeof(elem_type));
  if (L->data == NULL)
    return ERROR;
  L->length = 0;
  L->size = LIST_INIT_SIZE;
#endif
  return OK;
}

int destroy_list(link_list *L) {
/* 
 * Func: destroy the link list
 * Args: link list
 * Ret: the status
 */
#ifdef USING_CHAIN
  link_node *a_node = L->head;
  while (a_node != NULL) {
    link_node *temp_node = a_node;
    a_node = a_node->next;
    free(temp_node);
  }
  L->head = NULL;
  L->length = 0;
#else
  free(L->data);
  L->length = 0;
  L->size = LIST_INIT_SIZE;
#endif
  return OK;
}

int clear_list(link_list *L) {
/* 
 * Func: let the link list empty
 * Args: link list
 * Ret: the status
 */
#ifdef  USING_CHAIN
  link_node *a_node = L->head;
  while (a_node != NULL) {
    link_node *temp_node = a_node;
    a_node = a_node->next;
    free(temp_node);
  }
  L->head = NULL;
  L->length = 0;
#else
  free(L->data);
  L->length = 0;
#endif
  return OK;
}

int is_list_empty(link_list L) {
/* 
 * Func: judge if the link list is empty
 * Args: link list
 * Ret: true or false
 */
  if (L.length == 0)
    return TRUE;
  else
    return FALSE;
}

int list_length(link_list L) {
/* 
 * Func: get the length of link list
 * Args: link list
 * Ret: the length
 */
  return L.length;
}

int get_list_item(link_list L, int order, elem_type *elem) {
/* 
 * Func: get the ordered element of link list
 * Args: link list, the order, the target element
 * Ret: the status
 */
  int index = 0;
  if (order > L.length)
    return ERROR;  
#ifdef USING_CHAIN
  link_node *a_node = L.head;
  while (a_node != NULL) {
    index++;
    if (index == order) {
      *elem = (a_node->data);
      break;
    }
    a_node = a_node->next;
  }
#else
  *elem = *(L.data + order - 1);
#endif
  return OK;  
}

int locate_list_item(link_list L, elem_type ordered_elem) {
/* 
 * Func: locate the ordered item
 * Args: link list, the order, the target element
 * Ret: the index of the element
 */
  int index = 0;
#ifdef USING_CHAIN
  link_node *a_node = L.head;
  while (a_node != NULL) {
    index++;
    if (a_node->data == ordered_elem)
      break;
    a_node = a_node->next;
  }
  if (a_node == NULL)
    return 0;
  else
    return index;
#else
  for (index = 0; index < L.length; index++) {
    if (*(L.data + index) == ordered_elem)
      break;
  }
  if (index == L.length)
    return 0;
  else
    return index + 1;
#endif
}


int piror_list_item(link_list L, elem_type elem, elem_type *elem_pre) {
/* 
 * Func: get the ordered element's piror
 * Args: link list, the order, the target element
 * Ret: the status
 */
#ifdef USING_CHAIN
  link_node *a_node_pir =L.head, *a_node = a_node_pir->next;
  while (a_node != NULL) {
    if (a_node->data == elem) {
      *elem_pre = a_node_pir->data;
      break;
    }
    a_node_pir = a_node_pir->next;
    a_node = a_node_pir->next;
  }
  if (a_node == NULL)
    return ERROR;
  else
    return OK;
#else
  int index;
  for (index = 1; index < L.length; index++) {
    if (*(L.data + index) == elem) {
      *elem_pre = *(L.data + index - 1);
      break;
    }
  }
  if (index == L.length)
    return ERROR;
  else
    return OK;
#endif
}

int next_list_item(link_list L, elem_type elem, elem_type *elem_next) {
/* 
 * Func: get the ordered element's next
 * Args: link list, the order, the target element
 * Ret: the status
 */
#ifdef USING_CHAIN
  link_node *a_node = L.head;
  while (a_node->next != NULL) {
    if (a_node->next->data == elem) {
      *elem_next = a_node->next->data;
      break;
    }
    a_node = a_node->next;
  }
  if (a_node->next == NULL)
    return ERROR;
  else
    return OK;
#else
  int index;
  for (index = 0; index < L.length - 1; index++)  {
    if (*(L.data + index) == elem) {
      *elem_next = *(L.data + index + 1);
      break;
    }
  }
  if (index == L.length - 1)
    return ERROR;
  else
    return OK;
#endif
}

int list_insert(link_list *L, int order, elem_type elem) {
/* 
 * Func: insert a element in the link list
 * Args: link list, the order, the target element
 * Ret: the status
 */
#ifdef  USING_CHAIN
  link_node *a_node = L->head;
  if (order == 1) {
    link_node *new_node = (link_node*)malloc(sizeof(link_node));
    new_node->data = elem;
    new_node->next = a_node->next;
    L->head = new_node;
    return OK;
  }
  int index = 0;
  while (a_node != NULL) {
    index++;
    if (index == order - 1) {
      link_node *new_node = (link_node*)malloc(sizeof(link_node));
      new_node->data = elem;
      new_node->next = a_node->next;
      a_node->next = new_node;
    }
    a_node = a_node->next;
  }
  if (a_node == NULL)
    return ERROR;
#else
  if (L->length == L->size) {
    elem_type *new_base = (elem_type*)realloc(L->data, (L->size + LIST_INCREASEMENT) * sizeof(elem_type));
    if (new_base == NULL)
      return ERROR;
    L->data = new_base;
    L->size += LIST_INCREASEMENT;
  }
  int index;
  for (index = L->size; index >= order; index--)
    *(L->data + index) = *(L->data + index - 1);
  *(L->data + order - 1) = elem;
  L->length++;
#endif
  return OK;
}

int list_delete(link_list	*L, int order, elem_type elem) {
/* 
 * Func: delete a element in the link list
 * Args: link list, the order, the target element
 * Ret: the status
 */
  if (order > L->length)
    return ERROR;
#ifdef USING_CHAIN
  link_node *a_node = L->head;
  if (order == 1) {
    link_node *temp_node = L->head;
    L->head = temp_node->next;
    free(temp_node);
  }
  int index = 0;
  while (a_node != NULL) {
    index++;
    if (index == order - 1) {
      link_node *temp_node = a_node->next;
      a_node->next = temp_node->next;
      free(temp_node);
    }
    a_node = a_node->next;
  }
#else
  int index;
  for (index = order - 1; index < L->length - 1; index++)
    *(L->data + index) = *(L->data + index + 1);
  L->length--;
#endif
  return OK;
}

void print_list(link_list L) {
/* 
 * Func: print the elements of the linklist
 * Args: link list
 * Ret: none
 */
#ifdef USING_CHAIN
  link_node *a_node = L.head;
  int index = 0;
  while (a_node != NULL) {
    index++;
    printf("Index: %d, Data: %d\n", index, a_node->data);
    a_node = a_node->next;
  }
#else
  int index;
  for (index = 0; index < L.length; index++)
    printf("Index: %d, Data: %d\n", index + 1, *(L.data + index));
#endif
}