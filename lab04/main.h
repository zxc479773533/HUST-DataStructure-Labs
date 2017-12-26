/*
 * AUTHOR: Yue Pan
 * GITHUB: zxc479773533
 * E-MAIL: zxc479773533@gmail.com
 */

#ifndef PY_GRAPH_MAIN_H_
#define PY_GRAPH_MAIN_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "my_graph.h"

void print_menu(void);
/* 
 * Function Name: print_menu
 * Module: Main control
 * Parameter: None
 * Return: None
 * Use: print the menu
 */


void load_data(Graph_main *Main_G);
/* 
 * Function Name: load_data
 * Module: Main control
 * Parameter: Graph_main *Main_T
 * Return: None
 * Use: load link list from database
 */


void save_data(Graph_main *Main_G);
/* 
 * Function Name: save_data
 * Module: Main control
 * Parameter: Graph_main *Main_T
 * Return: None
 * Use: save link list from database
 */

#endif // !PY_GRAPH_MAIN_H_