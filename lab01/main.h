/*
 * AUTHOR: Yue Pan
 * GITHUB: zxc479773533
 * E-MAIL: zxc479773533@gmail.com
 */

#ifndef PY_LINEARLIST_MAIN_H_
#define PY_LINEARLIST_MAIN_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "my_linearlist.c"

void print_menu(void);
/* 
 * Function Name: print_menu
 * Module: Main control
 * Parameter: None
 * Return: None
 * Use: print the menu
 */


void load_data(Linear_list_main *Main_L);
/* 
 * Function Name:  load_data
 * Module: Main control
 * Parameter: Linear_list_main *Main_L
 * Return: None
 * Use: load linear list from database
 */


void save_data(Linear_list_main *Main_L);
/* 
 * Function Name:  save_data
 * Module: Main control
 * Parameter: Linear_list_main *Main_L
 * Return: None
 * Use: save linear list from database
 */


#endif // !PY_LINEARLIST_MAIN_H_