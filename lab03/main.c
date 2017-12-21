#include "main.h"

void print_menu(void) {
/* 
 * Function Name: print_menu
 * Module: Main control
 * Parameter: None
 * Return: None
 * Use: print the menu
 */

  printf("+---------------------------------------------------------------------+\n");
  printf("|             Welcome to panyue's binary tree demo system!            |\n");
  printf("|               Here are some functions you can call:                 |\n");
  printf("|                                                                     |\n");
  printf("|        1: init_binary_tree            2: destroy_bitree             |\n");
  printf("|        3: create_bitree               4: clear_bitree               |\n");
  printf("|        5: is_bitree_empty             6: bitree_depth               |\n");
  printf("|        7: bitree_root                 8: bitree_get_value           |\n");
  printf("|        9: bitree_set_value           10: bitree_parent              |\n");  
  printf("|       11: bitree_left_child          12: bitree_right_child         |\n");
  printf("|       13: bitree_left_sibling        14: bitree_right_sibling       |\n");
  printf("|       15: bitree_insert_node         16: bitree_insert_child_tree   |\n");
  printf("|       17: bitree_delete_child_tree   18: bitree_preorder_traverse   |\n");
  printf("|       19: bitree_inorder_traverse    20: bitree_postorder_traverse  |\n");
  printf("|       21: bitree_levelorder_traverse 22: ls_bitree                  |\n");
  printf("|        0: quit                                                      |\n");
  printf("|                                                                     |\n");
  printf("|Enter the number of the function and see the usage and call it!      |\n");
  printf("|Enter 0 to quit the demo system.                                     |\n");
  printf("|                                                                     |\n");
  printf("|Copyrite (C) 2017 Yue Pan                                            |\n");
  printf("|Github: zxc479773533                                                 |\n");
  printf("+---------------------------------------------------------------------+\n");
  printf("\n");
  printf("Your choose: ");
}

// assist function to load bintry node
void load_binary_tree(binary_tree_node *node, binary_tree_node *new_node) {
  if (node == NULL)
    return ;
  if (new_node->id == node->id * 2)
    node->left_child = new_node;
  else if (new_node->id == node->id * 2 + 1)
    node->right_child = new_node;
  else {
    load_binary_tree(node->left_child, new_node);
    load_binary_tree(node->right_child, new_node);
  }
}

void load_data(Binary_tree_main *Main_T) {
/* 
 * Function Name:  load_data
 * Module: Main control
 * Parameter: Binary_tree_main *Main_T
 * Return: None
 * Use: load link list from database
 */

  // open data file
  FILE *fp = fopen("binarytreedb", "rb");
  if (fp == NULL)
    return ;

  int size = 0xff;
  int count = 0;
  int index;
  binary_tree my_bitree, *T = &my_bitree;
  T->next = NULL;
  while (1) {
    binary_tree *tmp_T = (binary_tree*)malloc(sizeof(binary_tree));
    size = fread(tmp_T, sizeof(binary_tree), 1, fp);
    if (size == 0)
      break;
    if (tmp_T->size != 0) {
      binary_tree_node my_root, *root = &my_root;
      fread(root, sizeof(binary_tree_node), 1, fp);
      for (index = 1; index < tmp_T->size; index++) {
        binary_tree_node *tmp_node = (binary_tree_node*)malloc(sizeof(binary_tree_node));
        fread(tmp_node, sizeof(binary_tree_node), 1, fp);
        load_binary_tree(root, tmp_node);
      }
    tmp_T->root = root;      
    }
    count++;
    T->next = tmp_T;
    T = T->next;
  }

  Main_T->head = my_bitree.next;
  Main_T->num = count;

  // close data file
  fclose(fp);
}

// assist function to save binary tree
void save_binary_tree(binary_tree_node *node, FILE *fp) {
  if (node == NULL)
    return ;
  fwrite(node, sizeof(binary_tree_node), 1, fp);
  save_binary_tree(node->left_child, fp);
  save_binary_tree(node->right_child, fp);
}


void save_data(Binary_tree_main *Main_T) {
/* 
 * Function Name:  save_data
 * Module: Main control
 * Parameter: Binary_tree_main *Main_T
 * Return: None
 * Use: save link list from database
 */

  // open data files
  FILE *fp = fopen("binarytreedb", "wb");
  if (fp == NULL)
    return ;
  binary_tree *T = Main_T->head;
  while (T != NULL) {
    fwrite(T, sizeof(binary_tree), 1, fp);
    save_binary_tree(T->root, fp);
    T = T->next;
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
    Binary_tree_main Main_T;
    Main_T.head = NULL;
    Main_T.num = 0;
    load_data(&Main_T);

    // some variable to save the parameters
    int id, node_num, key, ordered_key, tag;
    char value[256];
    binary_tree *T = NULL;

    switch(function_choose) {

      case 1:
        printf("/*\n");
        printf(" * Function Name: init_binary_tree\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree *T\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: initial the binary tree\n");
        printf(" */\n");
        printf("\n");
        printf("Then, enter the bintry tree id: ");

        scanf("%d", &id);
        T = Main_T.head;
        while (T != NULL) {
          if (T->id == id)
            break;
          T = T->next;
        }
        if (T != NULL) {
          printf("Initial error, this bintry tree is already exists!\n");
        }
        else {
          binary_tree new_T;
          init_binary_tree(&new_T);
          printf("Initial binary tree %d succeed!\n", id);
          new_T.id = id;
          new_T.next = Main_T.head;
          Main_T.head = &new_T;
        }

        printf("\n");
        break;
      
      case 2:
        printf("/*\n");
        printf(" * Function Name: destroy_bitree\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree *T\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: destroy the binary tree\n");
        printf(" */\n");
        printf("\n");
        printf("Then, enter the binary tree id: ");

        scanf("%d", &id);
        T = Main_T.head;
        if (T->id == id) {
          Main_T.head = Main_T.head->next;
          destroy_bitree(T);
          printf("Binary tree %d has been delected!\n", id);
          printf("\n");
          break;
        }
        else {
          while (T->next != NULL) {
            if (T->next->id == id)
              break;
            T = T->next;
          }
        }
        if (T->next == NULL) {
          printf("Destroy error, this binary trss is not exists!\n");
        }
        else {
          binary_tree *to_be_del = T->next;
          T->next = T->next->next;
          destroy_bitree(to_be_del);
          printf("Binary tree %d has been deleted!\n", id);
        }

        printf("\n");
        break;

      case 3:
        printf("/*\n");
        printf(" * Function Name: create_bitree\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree *T, int node_num\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: create the binary tree with some nodes\n");
        printf(" */\n");
        printf("\n");
        printf("                                     Format: id node_num\n");
        printf("Then, enter the binary tree id and node_num: ");

        scanf("%d %d", &id, &node_num);
        T = Main_T.head;
        while (T != NULL) {
          if (T->id == id)
            break;
          T = T->next;
        }
        if (T != NULL) {
          printf("Create error, this binary tree is already exists!\n");
        }
        else {
          binary_tree new_T;
          create_bitree(&new_T, node_num);
          printf("Create binary tree %d succeed!\n", id);
          new_T.id = id;
          new_T.next = Main_T.head;
          Main_T.head = &new_T;
        }

        printf("\n");
        break;

      case 4:
        printf("/*\n");
        printf(" * Function Name: clear_bitree\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree *T\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: clear the binary tree\n");
        printf(" */\n");
        printf("\n");
        printf("Then, enter the binary tree id: ");

        scanf("%d", &id);
        T = Main_T.head;
        while (T != NULL) {
          if (T->id == id)
            break;
          T = T->next;
        }
        if (T == NULL) {
          printf("Clear error, this binary tree is not exists!\n");
        }
        else {
          if (clear_bitree(T) == OK) {
            printf("Binary tree %d has been cleared!\n", id);
          }
          else {
            printf("Clear error, this binary tree is already empty!\n");
          }
        }

        printf("\n");
        break;

      case 5:
        printf("/*\n");
        printf(" * Function Name: is_bitree_empty\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree T\n");
        printf(" * Return: int(true or false)\n");
        printf(" * Use: judge if the binary tree is empty\n");
        printf(" */\n");
        printf("\n");
        printf("Then, enter the binary tree id: ");

        scanf("%d", &id);
        T = Main_T.head;
        while (T != NULL) {
          if (T->id == id)
            break;
          T = T->next;
        }
        if (T == NULL) {
          printf("Error, this binary tree is not exists!\n");
        }
        else {
          if (is_bitree_empty(*T) == TRUE) {
            printf("Binary tree %d is empty!\n", id);
          }
          else {
            printf("Binary tree %d is not empty!\n", id);
          }
        }

        printf("\n");
        break;

      case 6:
        printf("/*\n");
        printf(" * Function Name: bitree_depth\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree T\n");
        printf(" * Return: int(the depth)\n");
        printf(" * Use: get the depth of binary tree\n");
        printf(" */\n");
        printf("\n");
        printf("Then, enter the binary tree id: ");

        scanf("%d", &id);
        T = Main_T.head;
        while (T != NULL) {
          if (T->id == id)
            break;
          T = T->next;
        }
        if (T == NULL) {
          printf("Error, this binary tree is not exists!\n");
        }
        else {
          printf("The length of binary tree %d is %d.\n", id, bitree_depth(*T));
        }

        printf("\n");
        break;

      case 7:
        printf("/*\n");
        printf(" * Function Name: bitree_root\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree T\n");
        printf(" * Return: binary_tree_node*\n");
        printf(" * Use: get the root of binary tree\n");
        printf(" */\n");
        printf("\n");
        printf("Then, enter the binary tree id: ");

        scanf("%d", &id);
        T = Main_T.head;
        while (T != NULL) {
          if (T->id == id)
            break;
          T = T->next;
        }
        if (T == NULL) {
          printf("Error, this binary tree is not exists!\n");
        }
        else {
          binary_tree_node *the_root = bitree_root(*T);
          if (the_root == NULL) {
            printf("Error, this binary tree is empty!\n");
          }
          else {
            printf("Root of binary tree %d:\n", id);
            printf("Key: %d\n", the_root->key);
            printf("Value: %s\n", the_root->value);
          }
        }

        printf("\n");
        break;

      case 8:
        printf("/*\n");
        printf(" * Function Name: bitree_get_value\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree T, int key, char *value\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: get the value of a node\n");
        printf(" */\n");
        printf("\n");
        printf("                                     Format: id key\n");
        printf("Then, enter the binary tree id and node key: ");

        scanf("%d %d", &id, &key);
        T = Main_T.head;
        while (T != NULL) {
          if (T->id == id)
            break;
          T = T->next;
        }
        if (T == NULL) {
          printf("Error, this binary tree is not exists!\n");
        }
        else {
          char the_value[256];
          if (bitree_get_value(*T, key, the_value) == OK) {
            printf("Binary tree %d, key %d\n", id, key);
            printf("The value is: %s\n", the_value);
          }
          else {
            printf("Error, the node %d is not found!\n", key);
          }
        }

        printf("\n");
        break;

      case 9:
        printf("/*\n");
        printf(" * Function Name: bitree_set_value\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree *T, int key, char *value\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: set the value of a node\n");
        printf(" */\n");
        printf("\n");
        printf("                                                    Format: id key value\n");
        printf("Then, enter the binary tree id, the node key and the value: ");

        memset(value, 0, 256);
        scanf("%d %d %s", &id, &key, value);
        T = Main_T.head;
        while (T != NULL) {
          if (T->id == id)
            break;
          T = T->next;
        }
        if (T == NULL) {
          printf("Error, this binary tree is not exists!\n");
        }
        else {
          if (bitree_set_value(T, key, value) == OK) {
            printf("Set the node %d's value succeed!\n", key);
          }
          else {
            printf("Error, the node %d is not found!\n", key);
          }
        }

        printf("\n");
        break;

      case 10:
        printf("/*\n");
        printf(" * Function Name: bitree_parent\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree T, int key\n");
        printf(" * Return: binary_tree_node*\n");
        printf(" * Use: get parent of a node\n");
        printf(" */\n");
        printf("\n");
        printf("                                     Format: id key\n");
        printf("Then, enter the binary tree id and node key: ");

        scanf("%d %d", &id, &key);
        T = Main_T.head;
        while (T != NULL) {
          if (T->id == id)
            break;
          T = T->next;
        }
        if (T == NULL) {
          printf("Error, this binary tree is not exists!\n");
        }
        else {
          binary_tree_node *the_parent = bitree_parent(*T, key);
          if (the_parent == NULL) {
            printf("Error, the parent not found!\n");
          }
          else {
            printf("The parent of node %d\n", key);
            printf("Key: %d\n", the_parent->key);
            printf("Value: %s\n", the_parent->value);
          }
        }

        printf("\n");
        break;

      case 11:
        printf("/*\n");
        printf(" * Function Name: bitree_left_child\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree T, int key\n");
        printf(" * Return: binary_tree_node*\n");
        printf(" * Use: get left child of a node\n");
        printf(" */\n");
        printf("\n");
        printf("                                     Format: id key\n");
        printf("Then, enter the binary tree id and node key: ");

        scanf("%d %d", &id, &key);
        T = Main_T.head;
        while (T != NULL) {
          if (T->id == id)
            break;
          T = T->next;
        }
        if (T == NULL) {
          printf("Error, this binary tree is not exists!\n");
        }
        else {
          binary_tree_node *the_left_child = bitree_left_child(*T, key);
          if (the_left_child == NULL) {
            printf("Error, the left child not found!\n");
          }
          else {
            printf("The left child of node %d\n", key);
            printf("Key: %d\n", the_left_child->key);
            printf("Value: %s\n", the_left_child->value);
          }
        }

        printf("\n");
        break;

      case 12:
        printf("/*\n");
        printf(" * Function Name: bitree_right_child\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree T, int key\n");
        printf(" * Return: binary_tree_node*\n");
        printf(" * Use: get right child of a node\n");
        printf(" */\n");
        printf("\n");
        printf("                                     Format: id key\n");
        printf("Then, enter the binary tree id and node key: ");

        scanf("%d %d", &id, &key);
        T = Main_T.head;
        while (T != NULL) {
          if (T->id == id)
            break;
          T = T->next;
        }
        if (T == NULL) {
          printf("Error, this binary tree is not exists!\n");
        }
        else {
          binary_tree_node *the_right_child = bitree_right_child(*T, key);
          if (the_right_child == NULL) {
            printf("Error, the right child not found!\n");
          }
          else {
            printf("The right child of node %d\n", key);
            printf("Key: %d\n", the_right_child->key);
            printf("Value: %s\n", the_right_child->value);
          }
        }

        printf("\n");
        break;

      case 13:
        printf("/*\n");
        printf(" * Function Name: bitree_left_sibling\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree T, int key\n");
        printf(" * Return: binary_tree_node*\n");
        printf(" * Use: get left sibling of a node\n");
        printf(" */\n");
        printf("\n");
        printf("                                     Format: id key\n");
        printf("Then, enter the binary tree id and node key: ");

        scanf("%d %d", &id, &key);
        T = Main_T.head;
        while (T != NULL) {
          if (T->id == id)
            break;
          T = T->next;
        }
        if (T == NULL) {
          printf("Error, this binary tree is not exists!\n");
        }
        else {
          binary_tree_node *the_left_sibling = bitree_left_sibling(*T, key);
          if (the_left_sibling == NULL) {
            printf("Error, the left sibling not found!\n");
          }
          else {
            printf("The left sibling of node %d\n", key);
            printf("Key: %d\n", the_left_sibling->key);
            printf("Value: %s\n", the_left_sibling->value);
          }
        }

        printf("\n");
        break;

      case 14:
        printf("/*\n");
        printf(" * Function Name: bitree_right_sibling\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree T, int key\n");
        printf(" * Return: binary_tree_node*\n");
        printf(" * Use: get right sibling of a node\n");
        printf(" */\n");
        printf("\n");
        printf("                                     Format: id key\n");
        printf("Then, enter the binary tree id and node key: ");

        scanf("%d %d", &id, &key);
        T = Main_T.head;
        while (T != NULL) {
          if (T->id == id)
            break;
          T = T->next;
        }
        if (T == NULL) {
          printf("Error, this binary tree is not exists!\n");
        }
        else {
          binary_tree_node *the_right_sibling = bitree_right_sibling(*T, key);
          if (the_right_sibling == NULL) {
            printf("Error, the right sibling not found!\n");
          }
          else {
            printf("The right sibling of node %d\n", key);
            printf("Key: %d\n", the_right_sibling->key);
            printf("Value: %s\n", the_right_sibling->value);
          }
        }

        printf("\n");
        break;

      case 15:
        printf("/*\n");
        printf(" * Function Name: bitree_insert_node\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree *T, int ordered_key, int tag, int key, char *value\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: get right sibling of a node\n");
        printf(" */\n");
        printf("\n");
        printf("                                                         Format: id ordered_key tag key value\n");
        printf("Then, enter the binary tree id, ordered key, tag, key and value: ");

        memset(value, 0, 256);
        scanf("%d %d %d %d %s", &id, &ordered_key, &tag, &key, value);
        T = Main_T.head;
        while (T != NULL) {
          if (T->id == id)
            break;
          T = T->next;
        }
        if (T == NULL) {
          printf("Error, this binary tree is not exists!\n");
        }
        else {
          if (bitree_insert_node(T, ordered_key, tag, key, value) == OK) {
            printf("Insert node %d succeed!\n", key);
          }
          else {
            printf("Insert error, please cheak your input!\n");
          }
        }

        printf("\n");
        break;

      case 16:
        printf("/*\n");
        printf(" * Function Name: bitree_insert_child_tree\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree *T, int ordered_key, int tag, binary_tree *C\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: insert a child tree in a binary tree\n");
        printf(" */\n");
        printf("\n");
        printf("                                                         Format: id ordered_key tag child_id\n");
        printf("Then, enter the binary tree id, ordered key, tag, child tree id: ");

        int child_id;
        scanf("%d %d %d %d", &id, &ordered_key, &tag, &child_id);
        T = Main_T.head;
        while (T != NULL) {
          if (T->id == id)
            break;
          T = T->next;
        }
        if (T == NULL) {
          printf("Error, this binary tree is not exists!\n");
          printf("\n");
          break;
        }
        binary_tree *C = Main_T.head;
        C = Main_T.head;
        while (C->next != NULL) {
          if (C->next->id == child_id)
            break;
          C = C->next;
        }
        if (C->next == NULL) {
          printf("Error, the child tree to be inserted is not exists!\n");
          printf("\n");
          break;
        }
        if (bitree_insert_child_tree(T, ordered_key, tag, C->next) == OK) {
          printf("Insert child tree %d succeed!\n", child_id);
          binary_tree *tmp = C->next;
          C->next = C->next->next;
          free(tmp);
        }
        else {
          printf("Insert error, please check your input!\n");
        }
        printf("\n");
        break;
      
      case 17:
        printf("/*\n");
        printf(" * Function Name: bitree_delete_child_tree\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree *T, int ordered_key, int tag\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: delete a child tree in a binary tree\n");
        printf(" */\n");
        printf("\n");
        printf("                                             Format: id ordered_key tag\n");
        printf("Then, enter the binary tree id, ordered key and tag: ");

        scanf("%d %d %d", &id, &ordered_key, &tag);
        T = Main_T.head;
        while (T != NULL) {
          if (T->id == id)
            break;
          T = T->next;
        }
        if (T == NULL) {
          printf("Error, this binary tree is not exists!\n");
        }
        else {
          if (bitree_delete_child_tree(T, ordered_key, tag) == OK) {
            printf("Delete child tree succeed!\n");
          }
          else {
            printf("Delete error, please check your input!\n");
          }
        }

        printf("\n");
        break;

      case 18:
        printf("/*\n");
        printf(" * Function Name: bitree_preorder_traverse\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree T\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: preorder traverse and print the values\n");
        printf(" */\n");
        printf("\n");
        printf("Then, enter the binary tree id: ");

        scanf("%d", &id);
        T = Main_T.head;
        while (T != NULL) {
          if (T->id == id)
            break;
          T = T->next;
        }
        if (T == NULL) {
          printf("Error, this binary tree is not exists!\n");
        }
        else {
          if (bitree_preorder_traverse(*T) == ERROR) {
            printf("Error, this binary tree is empty!\n");
          }
        }

        printf("\n");
        break;

      case 19:
        printf("/*\n");
        printf(" * Function Name: bitree_inorder_traverse\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree T\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: inorder traverse and print the values\n");
        printf(" */\n");
        printf("\n");
        printf("Then, enter the binary tree id: ");

        scanf("%d", &id);
        T = Main_T.head;
        while (T != NULL) {
          if (T->id == id)
            break;
          T = T->next;
        }
        if (T == NULL) {
          printf("Error, this binary tree is not exists!\n");
        }
        else {
          if (bitree_inorder_traverse(*T) == ERROR) {
            printf("Error, this binary tree is empty!\n");
          }
        }

        printf("\n");
        break;

      case 20:
        printf("/*\n");
        printf(" * Function Name: bitree_postorder_traverse\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree T\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: postorder traverse and print the values\n");
        printf(" */\n");
        printf("\n");
        printf("Then, enter the binary tree id: ");

        scanf("%d", &id);
        T = Main_T.head;
        while (T != NULL) {
          if (T->id == id)
            break;
          T = T->next;
        }
        if (T == NULL) {
          printf("Error, this binary tree is not exists!\n");
        }
        else {
          if (bitree_postorder_traverse(*T) == ERROR) {
            printf("Error, this binary tree is empty!\n");
          }
        }

        printf("\n");
        break;

      case 21:
        printf("/*\n");
        printf(" * Function Name: bitree_levelorder_traverse\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree T\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: levelorder traverse and print the values\n");
        printf(" */\n");
        printf("\n");
        printf("Then, enter the binary tree id: ");

        scanf("%d", &id);
        T = Main_T.head;
        while (T != NULL) {
          if (T->id == id)
            break;
          T = T->next;
        }
        if (T == NULL) {
          printf("Error, this binary tree is not exists!\n");
        }
        else {
          if (bitree_levelorder_traverse(*T) == ERROR) {
            printf("Error, this binary tree is empty!\n");
          }
        }

        printf("\n");
        break;

      case 22:
        T = Main_T.head;
        while (T != NULL) {
          printf("ID: %d\n", T->id);
          T = T->next;
        }

        printf("\n");
        break;

      case 0:
        printf("Thanks for using my demo system!\n");
        break;
      
      default:
        printf("You entered the wrong num, please re-enter the num.\n");
        break;
    }

    save_data(&Main_T);
  }

  return 0;
}