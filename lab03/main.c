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
  printf("|       15: bitree_insert_child        16: bitree_delete_child        |\n");
  printf("|       17: bitree_preorder_traverse   18: bitree_inorder_traverse    |\n");
  printf("|       19: bitree_postorder_traverse  20: bitree_levelorder_traverse |\n");
  printf("|       21: ls_bitree                   0: quit                       |\n");
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

  binary_tree trees, *a_tree = &trees;
  a_tree->next = NULL;

  int size = 0xff;
  while (1) {
    Binary_tree_store def;
    binary_tree *tmp_tree = NULL;
    size = fread(&def, sizeof(Binary_tree_store), 1, fp);
    if (size == 0)
      break;

    tmp_tree = (binary_tree*)malloc(sizeof(binary_tree));
    init_binary_tree(tmp_tree);

    if (def.size != 0) {
      def.pre_index = (int*)malloc(sizeof(int) * def.size);
      def.pre_defination = (int*)malloc(sizeof(int) * def.size);
      def.in_index = (int*)malloc(sizeof(int) * def.size);
      def.in_defination = (int*)malloc(sizeof(int) * def.size);
      fread(def.pre_index, sizeof(int) * def.size, 1, fp);
      fread(def.pre_defination, sizeof(int) * def.size, 1, fp);
      fread(def.in_index, sizeof(int) * def.size, 1, fp);
      fread(def.in_defination, sizeof(int) * def.size, 1, fp);
      create_bitree(tmp_tree, def.pre_index, def.pre_defination, def.in_index, def.in_defination, def.size);
    }

    tmp_tree->id = def.id;
    tmp_tree->next = NULL;
    a_tree->next = tmp_tree;
    a_tree = a_tree->next;
  }

  Main_T->head = trees.next;

  // close data file
  fclose(fp);
}

// assist function to preorder, inorder traverse the tree save nodes
void traverse_and_save(binary_tree_node *node, int order, int *indexs, int *defination, int *pos) {
  if (node == NULL)
    return ;
  if (pos == NULL) {
    int new_pos = 0;
    traverse_and_save(node, order, indexs, defination, &new_pos);
    return ;
  }
  if (order == PRE_ORDER) {
    indexs[*pos] = node->index;
    defination[*pos] = node->value;
    (*pos)++;
    traverse_and_save(node->left_child, order, indexs, defination, pos);
    traverse_and_save(node->right_child, order, indexs, defination, pos);
  }
  else if (order == IN_ORDER) {
    traverse_and_save(node->left_child, order, indexs, defination, pos);
    indexs[*pos] = node->index;
    defination[*pos] = node->value;
    (*pos)++;
    traverse_and_save(node->right_child, order, indexs, defination, pos);
  }
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
  
  binary_tree *a_tree = Main_T->head;
  while (a_tree != NULL) {
    Binary_tree_store def;
    def.id = a_tree->id;
    def.size = a_tree->size;
    def.pre_index = (int*)malloc(sizeof(int) * def.size);
    def.pre_defination = (int*)malloc(sizeof(int) * def.size);
    def.in_index = (int*)malloc(sizeof(int) * def.size);
    def.in_defination = (int*)malloc(sizeof(int) * def.size);
    traverse_and_save(a_tree->root, PRE_ORDER, def.pre_index, def.pre_defination, NULL);
    traverse_and_save(a_tree->root, IN_ORDER, def.in_index, def.in_defination, NULL);
    fwrite(&def, sizeof(Binary_tree_store), 1, fp);
    fwrite(def.pre_index, sizeof(int) * def.size, 1, fp);
    fwrite(def.pre_defination, sizeof(int) * def.size, 1, fp);
    fwrite(def.in_index, sizeof(int) * def.size, 1, fp);
    fwrite(def.in_defination, sizeof(int) * def.size, 1, fp);
    a_tree = a_tree->next;
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
    load_data(&Main_T);

    // some variable to save the parameters
    int id, node_num, index, value, LorR;
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
        printf(" * Parameter: binary_tree *T, int *pre_index, int *pre_defination,\n");
        printf(" * int *in_index, int *in_defination, int difination_len\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: create the binary tree with some nodes\n");
        printf(" */\n");
        printf("\n");
        printf("                                      Format: id size\n");
        printf("Then, enter the binary tree id and tree size: ");

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
          int *pre_index = (int*)malloc(sizeof(int) * node_num);
          int *pre_defination = (int*)malloc(sizeof(int) * node_num);
          int *in_index = (int*)malloc(sizeof(int) * node_num);
          int *in_defination = (int*)malloc(sizeof(int) * node_num);
          printf("Please enter the preorder sequence: (Format: index value)\n");
          for (int i = 0; i < node_num; i++) { scanf("%d %d", &pre_index[i], &pre_defination[i]); }
          printf("Please enter the inorder sequence: (Format: index value)\n");
          for (int i = 0; i < node_num; i++) { scanf("%d %d", &in_index[i], &in_defination[i]); }
          binary_tree new_T;
          create_bitree(&new_T, pre_index, pre_defination, in_index, in_defination, node_num);
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
            printf("Index: %d\n", the_root->index);
            printf("Value: %d\n", the_root->value);
          }
        }

        printf("\n");
        break;

      case 8:
        printf("/*\n");
        printf(" * Function Name: bitree_get_value\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree T, int index, int value\n");
        printf(" * Return: int(the value)\n");
        printf(" * Use: get the value of a node\n");
        printf(" */\n");
        printf("\n");
        printf("                                       Format: id index\n");
        printf("Then, enter the binary tree id and node index: ");

        scanf("%d %d", &id, &index);
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
            printf("Binary tree %d, Index %d\n", id, index);
            printf("The value is: %d\n", bitree_get_value(*T, index));
        }

        printf("\n");
        break;

      case 9:
        printf("/*\n");
        printf(" * Function Name: bitree_set_value\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree *T, int index, int value\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: set the value of a node\n");
        printf(" */\n");
        printf("\n");
        printf("                                                      Format: id index value\n");
        printf("Then, enter the binary tree id, the node index and the value: ");

        scanf("%d %d %d", &id, &index, &value);
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
          if (bitree_set_value(T, index, value) == OK) {
            printf("Set the node %d's value succeed!\n", index);
          }
          else {
            printf("Error, the node %d is not found!\n", index);
          }
        }

        printf("\n");
        break;

      case 10:
        printf("/*\n");
        printf(" * Function Name: bitree_parent\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree T, int index\n");
        printf(" * Return: binary_tree_node*\n");
        printf(" * Use: get parent of a node\n");
        printf(" */\n");
        printf("\n");
        printf("                                       Format: id index\n");
        printf("Then, enter the binary tree id and node index: ");

        scanf("%d %d", &id, &index);
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
          binary_tree_node *the_parent = bitree_parent(*T, index);
          if (the_parent == NULL) {
            printf("Error, the parent not found!\n");
          }
          else {
            printf("The parent of node %d\n", index);
            printf("Key: %d\n", the_parent->index);
            printf("Value: %d\n", the_parent->value);
          }
        }

        printf("\n");
        break;

      case 11:
        printf("/*\n");
        printf(" * Function Name: bitree_left_child\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree T, int index\n");
        printf(" * Return: binary_tree_node*\n");
        printf(" * Use: get left child of a node\n");
        printf(" */\n");
        printf("\n");
        printf("                                       Format: id index\n");
        printf("Then, enter the binary tree id and node index: ");

        scanf("%d %d", &id, &index);
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
          binary_tree_node *the_left_child = bitree_left_child(*T, index);
          if (the_left_child == NULL) {
            printf("Error, the left child not found!\n");
          }
          else {
            printf("The left child of node %d\n", index);
            printf("Key: %d\n", the_left_child->index);
            printf("Value: %d\n", the_left_child->value);
          }
        }

        printf("\n");
        break;

      case 12:
        printf("/*\n");
        printf(" * Function Name: bitree_right_child\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree T, int index\n");
        printf(" * Return: binary_tree_node*\n");
        printf(" * Use: get right child of a node\n");
        printf(" */\n");
        printf("\n");
        printf("                                       Format: id index\n");
        printf("Then, enter the binary tree id and node index: ");

        scanf("%d %d", &id, &index);
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
          binary_tree_node *the_right_child = bitree_right_child(*T, index);
          if (the_right_child == NULL) {
            printf("Error, the right child not found!\n");
          }
          else {
            printf("The right child of node %d\n", index);
            printf("Key: %d\n", the_right_child->index);
            printf("Value: %d\n", the_right_child->value);
          }
        }

        printf("\n");
        break;

      case 13:
        printf("/*\n");
        printf(" * Function Name: bitree_left_sibling\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree T, int index\n");
        printf(" * Return: binary_tree_node*\n");
        printf(" * Use: get left sibling of a node\n");
        printf(" */\n");
        printf("\n");
        printf("                                       Format: id index\n");
        printf("Then, enter the binary tree id and node index: ");

        scanf("%d %d", &id, &index);
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
          binary_tree_node *the_left_sibling = bitree_left_sibling(*T, index);
          if (the_left_sibling == NULL) {
            printf("Error, the left sibling not found!\n");
          }
          else {
            printf("The left sibling of node %d\n", index);
            printf("Key: %d\n", the_left_sibling->index);
            printf("Value: %d\n", the_left_sibling->value);
          }
        }

        printf("\n");
        break;

      case 14:
        printf("/*\n");
        printf(" * Function Name: bitree_right_sibling\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree T, int index\n");
        printf(" * Return: binary_tree_node*\n");
        printf(" * Use: get right sibling of a node\n");
        printf(" */\n");
        printf("\n");
        printf("                                       Format: id index\n");
        printf("Then, enter the binary tree id and node index: ");

        scanf("%d %d", &id, &index);
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
          binary_tree_node *the_right_sibling = bitree_right_sibling(*T, index);
          if (the_right_sibling == NULL) {
            printf("Error, the right sibling not found!\n");
          }
          else {
            printf("The right sibling of node %d\n", index);
            printf("Key: %d\n", the_right_sibling->index);
            printf("Value: %d\n", the_right_sibling->value);
          }
        }

        printf("\n");
        break;

      case 15:
        printf("/*\n");
        printf(" * Function Name: bitree_insert_child\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree *T, int index, int LorR, binary_tree *C\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: insert a child tree in a binary tree\n");
        printf(" */\n");
        printf("\n");
        printf("                                                    Format: id index LorR child_id\n");
        printf("Then, enter the binary tree id, index, LorR, child tree id: ");

        int child_id;
        scanf("%d %d %d %d", &id, &index, &LorR, &child_id);
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
        if (C->id == child_id) {
          if (bitree_insert_child_tree(T, index, LorR, C) == OK) {
            printf("Insert child tree %d succeed!\n", child_id);
            Main_T.head = Main_T.head->next;
            free(C);
          }
          else {
            printf("Insert error, please check your input!\n");
          }
          printf("\n");
          break;
        }
        if (bitree_insert_child_tree(T, index, LorR, C->next) == OK) {
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
      
      case 16:
        printf("/*\n");
        printf(" * Function Name: bitree_delete_child\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: binary_tree *T, int index, int LorR\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: delete a child tree in a binary tree\n");
        printf(" */\n");
        printf("\n");
        printf("                                        Format: id index LorR\n");
        printf("Then, enter the binary tree id, index and LorR: ");

        scanf("%d %d %d", &id, &index, &LorR);
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
          if (bitree_delete_child_tree(T, index, LorR) == OK) {
            printf("Delete child tree succeed!\n");
          }
          else {
            printf("Delete error, please check your input!\n");
          }
        }

        printf("\n");
        break;

      case 17:
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

      case 18:
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

      case 19:
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

      case 20:
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

      case 21:
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