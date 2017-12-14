/*
 * AUTHOR: Yue Pan
 * GITHUB: zxc479773533
 * E-MAIL: zxc479773533@gmail.com
 */

#ifndef PY_BINARYTREE_MAIN_H_
#define PY_BINARYTREE_MAIN_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "my_binarytree.c"

void print_menu(void);
/* 
 * Function Name: print_menu
 * Module: Main control
 * Parameter: None
 * Return: None
 * Use: print the menu
 */


void load_data(Binary_tree_main *Main_L);
/* 
 * Function Name:  load_data
 * Module: Main control
 * Parameter: Binary_tree_main *Main_L
 * Return: None
 * Use: load link list from database
 */


void save_data(Binary_tree_main *Main_L);
/* 
 * Function Name:  save_data
 * Module: Main control
 * Parameter: Binary_tree_main *Main_L
 * Return: None
 * Use: save link list from database
 */


#endif // !PY_LINKLIST_MAIN_H_