/*
 * AUTHOR: Yue Pan
 * GITHUB: zxc479773533
 * E-MAIL: zxc479773533@gmail.com
 */

#include "my_linearlist.h"

int init_list(linear_list *L) {
/* 
 * Function Name: init_list
 * Module: Data structures
 * Parameter: linear_list *L
 * Return: int(status)
 * Use: initial the linear list
 */

  memset(L, 0, sizeof(linear_list));
  L->data = (int *)malloc(sizeof(int) * LIST_INIT_SIZE);
  if (L->data == NULL)
    return ERROR;
  L->length = 0;
  L->size = LIST_INIT_SIZE;
  return OK;
}

int destroy_list(linear_list *L) {
/* 
 * Function Name: destroy_list
 * Module: Data structures
 * Parameter: linear_list *L
 * Return: int(status)
 * Use: destroy the link list
 */

  if (L->data != NULL)
    free(L->data);
  memset(L, 0, sizeof(linear_list));
  return OK;
}

int clear_list(linear_list *L) {
/* 
 * Function Name: clear_list
 * Module: Data structures
 * Parameter: linear_list *L
 * Return: int(status)
 * Use: let the link list empty
 */

  if (L->data == NULL)
    return ERROR;
  memset(L->data, 0, sizeof(int) * L->size);
  L->length = 0;
  L->size = LIST_INIT_SIZE;

  return OK;
}

int is_list_empty(linear_list L) {
/* 
 * Function Name: is_list_empty
 * Module: Data structures
 * Parameter: linear_list L
 * Return: int(true or false)
 * Use: judge if the link list is empty
 */

  if (L.length == 0)
    return TRUE;
  else
    return FALSE;
}

int list_length(linear_list L) {
/* 
 * Function Name: list_length
 * Module: Data structures
 * Parameter: linear_list L
 * Return: int(the length)
 * Use: get the length of link list
 */

  return L.length;
}

int get_list_item(linear_list L, int order, elem_type *elem) {
/* 
 * Function Name: get_list_item
 * Module: Data structures
 * Parameter: linear_list L, int order, elem_type *elem
 * Return: int(status)
 * Use: get the ordered element of link list
 */

  int index = 0;
  if (order > L.length || order <= 0 || L.length == 0 || L.data == NULL)
    return ERROR;  
  *elem = *(L.data + order - 1);
  return OK;  
}

int locate_list_item(linear_list L, elem_type ordered_elem) {
/* 
 * Function Name: locate_list_item
 * Module: Data structures
 * Parameter: linear_list L, elem_type ordered_elem
 * Return: int(index)
 * Use: locate the ordered item
 */

  int index = 0;
  for (index = 0; index < L.length; index++) {
    if (*(L.data + index) == ordered_elem)
      break;
  }
  if (index == L.length)
    return 0;
  else
    return index + 1;
}


int piror_list_item(linear_list L, elem_type elem, elem_type *elem_pre) {
/* 
 * Function Name: piror_list_item
 * Module: Data structures
 * Parameter: linear_list L, elem_type elem, elem_type *elem_pre
 * Return: int(status)
 * Use: get the ordered element's piror
 */

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

}

int next_list_item(linear_list L, elem_type elem, elem_type *elem_next) {
/* 
 * Function Name: next_list_item
 * Module: Data structures
 * Parameter: linear_list L, elem_type elem, elem_type *elem_next
 * Return: int(status)
 * Use: get the ordered element's next
 */

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
}

int list_insert(linear_list *L, int order, elem_type elem) {
/* 
 * Function Name: list_insert
 * Module: Data structures
 * Parameter: linear_list *L, int order, elem_type elem
 * Return: int(status)
 * Use: insert a element in the link list
 */
  if (order > L->length || order <= 0 || L->length == 0 || L->data == NULL)
    return ERROR;
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
  return OK;
}

int list_delete(linear_list	*L, int order, elem_type elem) {
/* 
 * Function Name: list_delete
 * Module: Data structures
 * Parameter: linear_list *L, int order, elem_type elem
 * Return: int(status)
 * Use: delete a element in the link list
 */

  if (order > L->length || order <= 0 || order)
    return ERROR;
  int index;
  for (index = order - 1; index < L->length - 1; index++)
    *(L->data + index) = *(L->data + index + 1);
  L->length--;
  return OK;
}

void print_list(linear_list L, char *payload) {
/* 
 * Function Name: print_list
 * Module: Data structures
 * Parameter: linear_list L, char *payload
 * Return: int(status)
 * Use: print the elements of the linklist to the payload
 */

  int index;
  for (index = 0; index < L.length; index++) {
    sprintf(payload,"Index: %d, Data: %d\r\n", index + 1, *(L.data + index));
    payload += sizeof("Index: ") + 2 * sizeof(elem_type) + sizeof(", Data: ") + 2;
  }
}