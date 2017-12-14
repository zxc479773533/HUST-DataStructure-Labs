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
  printf("|             Welcome to panyue's binary tree demo system!           |\n");
  printf("|               Here are some functions you can call:                |\n");
  printf("|                                                                    |\n");
  printf("|        1: init_binary_tree           2: destroy_bitree             |\n");
  printf("|        3: create_bitree              4: clear_bitree               |\n");
  printf("|        5: is_bitree_empty            6: bitree_depth               |\n");
  printf("|        7: bitree_root                8: bitree_get_value           |\n");
  printf("|        9: bitree_set_value          10: bitree_parent              |\n");  
  printf("|       11: bitree_left_child         12: bitree_right_child         |\n");
  printf("|       13: bitree_left_sibling       14: bitree_right_sibling       |\n");
  printf("|       15: bitree_insert_node        16: bitree_insert_child_tree   |\n");
  printf("|       17: bitree_delete_child_tree  18: bitree_preorder_traverse   |\n");
  printf("|       19: bitree_inorder_traverse   20: bitree_postorder_traverse  |\n");
  printf("|       20: bitree_levelorder_traverse                               |\n");
  printf("|        0: quit                                                     |\n");
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

void load_data(Binary_tree_main *Main_L) {
/* 
 * Function Name:  load_data
 * Module: Main control
 * Parameter: Binary_tree_main *Main_L
 * Return: None
 * Use: load link list from database
 */


}

void save_data(Binary_tree_main *Main_L) {
/* 
 * Function Name:  save_data
 * Module: Main control
 * Parameter: Binary_tree_main *Main_L
 * Return: None
 * Use: save link list from database
 */


}