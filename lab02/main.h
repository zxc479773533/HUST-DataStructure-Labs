/*
 * AUTHOR: Yue Pan
 * GITHUB: zxc479773533
 * E-MAIL: zxc479773533@gmail.com
 */

#ifndef PY_LINKLIST_MAIN_H_
#define PY_LINKLIST_MAIN_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "my_linklist.c"

void print_menu(void);
/* 
 * Function Name: print_menu
 * Module: Main control
 * Parameter: None
 * Return: None
 * Use: print the menu
 */


void load_data(Link_list_main *Main_L);
/* 
 * Function Name:  load_data
 * Module: Main control
 * Parameter: Link_list_main *Main_L
 * Return: None
 * Use: load link list from database
 */


void save_data(Link_list_main *Main_L);
/* 
 * Function Name:  save_data
 * Module: Main control
 * Parameter: Link_list_main *Main_L
 * Return: None
 * Use: save link list from database
 */


#endif // !PY_LINKLIST_MAIN_H_