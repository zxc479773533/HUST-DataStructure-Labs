#include "main.h"

void print_menu(void) {
/* 
 * Function Name: print_menu
 * Module: Main control
 * Parameter: None
 * Return: None
 * Use: print the menu
 */

  printf("+--------------------------------------------------------------------+\n");
  printf("|             Welcome to panyue's link list demo system!             |\n");
  printf("|               Here are some functions you can call:                |\n");
  printf("|                                                                    |\n");
  printf("|               1: init_list           2: destroy_list               |\n");
  printf("|               3: clear_list          4: is_list_empty              |\n");
  printf("|               5: list_length         6: get_list_item              |\n");
  printf("|               7: locate_list_item    8: piror_list_item            |\n");
  printf("|               9: next_list_item     10: list_insert                |\n");  
  printf("|              11: list_delete        12: print_list                 |\n");
  printf("|              13: ls_list             0: quit                       |\n");
  printf("|                                                                    |\n");
  printf("|Enter the number of the function and see the usage and call it!     |\n");
  printf("|Enter 0 to quit the demo system.                                    |\n");
  printf("|                                                                    |\n");
  printf("|Copyrite (C) 2017 Yue Pan                                           |\n");
  printf("|Github: zxc479773533                                                |\n");
  printf("+--------------------------------------------------------------------+\n");
  printf("\n");
  printf("Your choose: ");
}

void load_data(Link_list_main *Main_L) {
/* 
 * Function Name:  load_data
 * Module: Main control
 * Parameter: Link_list_main *Main_L
 * Return: None
 * Use: load link list from database
 */

  // open file
  FILE *fp = fopen("linklistdb", "rb");
  if (fp == NULL)
    return;

  int size = 0xff;
  int count = 0;
  int index;
  link_list my_list, *L = &my_list;
  L->next = NULL;
  while (1) {
    link_list *tmp_L = (link_list*)malloc(sizeof(link_list));
    size = fread(tmp_L, sizeof(link_list), 1, fp);
    if (size == 0)
      break;
    link_node my_node, *node = &my_node;
    node->next = NULL;
    for (index = 0; index < tmp_L->length; index++) {
      link_node *tmp_node = (link_node*)malloc(sizeof(link_list));
      fread(tmp_node, sizeof(link_node), 1, fp);
      node->next = tmp_node;
      node = node->next;
    }
    count++;
    tmp_L->head = my_node.next;
    L->next = tmp_L;
    L = L->next;
  }

  Main_L->head = my_list.next;
  Main_L->num = count;

  // close file
  fclose(fp);
}

void save_data(Link_list_main *Main_L) {
/* 
 * Function Name:  save_data
 * Module: Main control
 * Parameter: Link_list_main *Main_L
 * Return: None
 * Use: save link list from database
 */

  // open data files
  FILE *fp = fopen("linklistdb", "wb");
  if (fp == NULL)
    return;

  link_list *L = Main_L->head;
  while (L != NULL) {
    fwrite(L, sizeof(link_list), 1, fp);
    link_node *a_node = L->head;
    int index;
    for (index = 0; index < L->length; index++) {
      fwrite(a_node, sizeof(link_node), 1, fp);
      a_node = a_node->next;
    }
    L = L->next;
  }


  // close file
  fclose(fp);
}

int main(void) {

  // a variable to save the function choose
  int function_choose = 0xff;

  while (function_choose != 0) {

    // print the menu
    print_menu();
    scanf("%d", &function_choose);

    // load the data
    Link_list_main Main_L;
    Main_L.head = NULL;
    Main_L.num = 0;
    load_data(&Main_L);

    // some variable to save the parameters
    int id = 0, order = 0, elem = 0, index = 0;
    link_list *L = NULL;

    switch (function_choose) {

      case 1:
        printf("/*\n");
        printf(" * Function Name: init_list\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: link_list *L\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: initial the link list\n");
        printf(" */\n");
        printf("\n");
        printf("Then, enter the list id: ");

        scanf("%d", &id);
        L = Main_L.head;
        while (L != NULL) {
          if (L->id == id)
          break;
          L = L->next;
        }
        if (L != NULL) {
          printf("Inital error, this link list is already exists!\n");
        }
        else {
          link_list new_L;
          init_list(&new_L);
          printf("Inital list %d succeed!\n", id);
          new_L.id = id;
          new_L.next = Main_L.head;
          Main_L.head = &new_L;
        }

      printf("\n");
      break;

      case 2:
        printf("/*\n");
        printf(" * Function Name: destroy_list\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: link_list *L\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: destroy the link list\n");
        printf(" */\n");
        printf("\n");
        printf("Then, enter the list id: ");

        scanf("%d", &id);
        L = Main_L.head;
        if (L->id == id) {
          Main_L.head = Main_L.head->next;
          destroy_list(L);
          printf("Link list %d has been deleted!\n", id);
          printf("\n");
          break;
        }
        else {
          while (L->next != NULL) {
            if (L->next->id == id)
              break;
            L = L->next;            
          }
        }
        if (L->next == NULL) {
          printf("Distroy error, this link list is not exits!\n");
        }
        else {
          link_list *to_be_del = L->next;
          L->next = L->next->next;
          destroy_list(to_be_del);
          printf("Link list %d has been deleted!\n", id);
        }
        
        printf("\n");
        break;

      case 3:
        printf("/*\n");
        printf(" * Function Name: clear_list\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: link_list *L\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: let the link list empty\n");
        printf(" */\n");
        printf("\n");
        printf("Then, enter the list id: ");

        scanf("%d", &id);
        L = Main_L.head;
        while (L != NULL) {
          if (L->id == id)
            break;
          L = L->next;          
        }
        if (L == NULL) {
          printf("Clear error, this link list is not exists!\n");
        }
        else {
          if (clear_list(L) == OK) {
            printf("Link list %d has been cleared!\n", id);
          }
          else {
            printf("Clear error, this link is already empty!\n");
          }
        }

        printf("\n");
        break;

      case 4:
        printf("/*\n");
        printf(" * Function Name: is_list_empty\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: link_list L\n");
        printf(" * Return: int(true or false)\n");
        printf(" * Use: judge if the link list is empty\n");
        printf(" */\n");
        printf("\n");
        printf("Then, enter the list id: ");

        scanf("%d", &id);
        L = Main_L.head;
        while (L != NULL) {
          if (L->id == id)
            break;
          L = L->next;
        }
        if (L == NULL) {
          printf("Error, this link list is not exists!\n");
        }
        else {
          if (is_list_empty(*L) == TRUE) {
            printf("Link list %d is empty!\n", id);
          }
          else {
            printf("Link list %d is not empty!\n", id);
          }
        }

        printf("\n");
        break;

      case 5:
        printf("/*\n");
        printf(" * Function Name: list_length\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: link_list L\n");
        printf(" * Return: int(the length)\n");
        printf(" * Use: get the length of link list\n");
        printf(" */\n");
        printf("\n");
        printf("Then, enter the list id: ");

        scanf("%d", &id);
        L = Main_L.head;
        while (L != NULL) {
          if (L->id == id)
            break;
          L = L->next;
        }
        if (L == NULL) {
          printf("Error, this link list is not exists!\n");
        }
        else {
          printf("The length of link list %d is %d.\n", id, list_length(*L));
        }

        printf("\n");
        break;

      case 6:
        printf("/*\n");
        printf(" * Function Name: get_list_item\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: link_list L, int order, int *elem\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: get the ordered element of link list\n");
        printf(" */\n");
        printf("\n");
        printf("                           Format: id index\n");
        printf("Then, enter the list id and index: ");

        scanf("%d %d", &id, &order);
        L = Main_L.head;
        while (L != NULL) {
          if (L->id == id)
            break;
          L = L->next;
        }
        if (L == NULL) {
          printf("Error, this link list is not exists!\n");
        }
        else {
          if (get_list_item(*L, order, &elem) == OK) {
            printf("The element is %d.\n",elem);
          }
          else {
            printf("Get element error! Please check your input.\n");
          }
        }

        printf("\n");
        break;

      case 7:
        printf("/*\n");
        printf(" * Function Name: locate_list_item\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: link_list L, int ordered_elem\n");
        printf(" * Return: int(index)\n");
        printf(" * Use: get the index of ordered item\n");
        printf(" */\n");
        printf("\n");
        printf("                             Format: id element\n");
        printf("Then, enter the list id and element: ");

        scanf("%d %d", &id, &elem);
        L = Main_L.head;
        while (L != NULL) {
          if (L->id == id)
            break;
          L = L->next;
        }
        if (L == NULL) {
          printf("Error, this link list is not exists!\n");
        }
        else {
          index = locate_list_item(*L, elem);
          printf("The index of the %d, is %d.\n", elem, index);
        }

        printf("\n");
        break;

      case 8:
        printf("/*\n");
        printf(" * Function Name: piror_list_item\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: link_list L, int elem, int *elem_pre\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: get the ordered element's piror\n");
        printf(" */\n");
        printf("\n");
        printf("                             Format: id element\n");
        printf("Then, enter the list id and element: ");

        scanf("%d %d", &id, &elem);
        L = Main_L.head;
        while (L != NULL) {
          if (L->id == id)
            break;
          L = L->next;
        }
        if (L == NULL) {
          printf("Error, this link list is not exists!\n");
        }
        else {
          int elem_pre;
          if (piror_list_item(*L, elem, &elem_pre) == OK) {
            printf("The piror element of %d is %d.\n", elem, elem_pre);
          }
          else {
            printf("Error, the piror of %d is not exists!\n", elem);
          }
        }

        printf("\n");
        break;

      case 9:
        printf("/*\n");
        printf(" * Function Name: next_list_item\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: link_list L, int elem, int *elem_next\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: get the ordered element's next\n");
        printf(" */\n");
        printf("\n");
        printf("                             Format: id element\n");
        printf("Then, enter the list id and element: ");

        scanf("%d %d", &id, &elem);
        L = Main_L.head;
        while (L != NULL) {
          if (L->id == id)
            break;
          L = L->next;
        }
        if (L == NULL) {
          printf("Error, this link list is not exists!\n");
        }
        else {
          int elem_next;
          if (next_list_item(*L, elem, &elem_next) == OK) {
            printf("The next element of %d is %d.\n", elem, elem_next);
          }
          else {
            printf("Error, the next of %d is not exists!\n", elem);
          }
        }

        printf("\n");
        break;

      case 10:
        printf("/*\n");
        printf(" * Function Name: list_insert\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: link_list *L, int order, int elem\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: insert a element in the link list\n");
        printf(" */\n");
        printf("\n");
        printf("                                    Format: id index element\n");
        printf("Then, enter the list id, index and element: ");

        scanf("%d %d %d", &id, &order, &elem);
        L = Main_L.head;
        while (L != NULL) {
          if (L->id == id)
            break;
          L = L->next;
        }
        if (L == NULL) {
          printf("Error, this link list is not exists!\n");
        }
        else {
          if (list_insert(L, order, elem) == OK) {
            printf("Insert %d succeed!\n", elem);
          }
          else {
            printf("Insert failed, please check your input!\n");
          }
        }

        printf("\n");
        break;

      case 11:
        printf("/*\n");
        printf(" * Function Name: list_delete\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: link_list *L, int order, int *elem\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: delete a element in the link list\n");
        printf(" */\n");
        printf("\n");
        printf("                           Format: id index\n");
        printf("Then, enter the list id and index: ");

        scanf("%d %d", &id, &order);
        L = Main_L.head;
        while (L != NULL) {
          if (L->id == id)
            break;
          L = L->next;
        }
        if (L == NULL) {
          printf("Error, this link list is not exists!\n");
        }
        else {
          if (list_delete(L, order, &elem) == OK) {
            printf("Delete %d succeed!\n", elem);
          }
          else {
            printf("Delete failed, please check your input!\n");
          }
        }

        printf("\n");
        break;

      case 12:
        printf("/*\n");
        printf(" * Function Name: print_list\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: link_list L, char *payload\n");
        printf(" * Return: None\n");
        printf(" * Use: print the elements of the linklist to the payload\n");
        printf(" */\n");
        printf("\n");
        printf("Then, enter the list id: ");

        scanf("%d", &id);
        L = Main_L.head;
        while (L != NULL) {
          if (L->id == id)
            break;
          L = L->next;
        }
        if (L == NULL) {
          printf("Error, this link list is not exists!\n");
        }
        else {
          printf("The elements in link list %d are:\n", id);
          print_list(*L);
        }

        printf("\n");
        break;

      case 13:
        L = Main_L.head;
        while(L != NULL) {
          printf("ID: %d\n", L->id);
          L = L->next;
        }

        printf("\n");
        break;

      case 0:
        printf("Thanks for using my demo system!\n");
        break;

      default:
        printf("You entered the wrong num, please re-enter the num.\n");
        printf("\n");        
        break;
      
    }

    save_data(&Main_L);
  }

  return 0;
}