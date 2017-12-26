/*
 * AUTHOR: Yue Pan
 * GITHUB: zxc479773533
 * E-MAIL: zxc479773533@gmail.com
 */

#ifndef PY_GRAPH_H
#define PY_GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define OK 0
#define ERROR 1

#define DIRECTED_GRAPH 0
#define UNDIRECTED_GRAPH 1
#define DIRECTED_NET 2
#define UNDIRECTED_NET 3


// the struct of arc
typedef struct arc_node {
  int vertex;
  struct arc_node *next;
  int weight;
} arc_node;

// the struct of vertex
typedef struct vertex_node {
  int index;
  int value;
  arc_node *first_arc;
} vertex_node;

// the struct of graph
typedef struct graph {
  int id;
  vertex_node *first_vertex;
  int vertex_num;
  int arc_num;
  int kind;
  graph *next;
} graph;

// the struct for managin the graph
typedef struct Graph_main {
  graph *head;
} Graph_main;

// the struct to save the graph
typedef struct Graph_store {
  int id;
  int vertex_num;
  int arc_num;
  int *v_indexs;
  int *v_values;
  int **a_matrix;
} Graph_store;


int creat_graph(graph &G, int v_num, int a_num, int *v_indexs, int *v_values, int **a_matrix);
/* 
 * Function Name: creat_graph
 * Module: Data structures
 * Parameter: graph &G, int v_num, int a_num, int *v_indexs, int *v_values, int **a_matrix
 * Return: int(status)
 * Use: create a graph
 */


int destory_graph(graph &G);
/* 
 * Function Name: destory_graph
 * Module: Data structures
 * Parameter: graph &G
 * Return: int(status)
 * Use: destory a graph
 */


int locate_vex(graph &G, int value);
/* 
 * Function Name: locate_vex
 * Module: Data structures
 * Parameter: graph &G, int value
 * Return: int(the index)
 * Use: find a vertex in graph
 */


int get_vex_value(graph &G, int index);
/* 
 * Function Name: get_vex_value
 * Module: Data structures
 * Parameter: graph &G, int index
 * Return: int(the value)
 * Use: find a value of a vertex
 */


int set_vex_value(graph &G, int index, int value);
/* 
 * Function Name: set_vex_value
 * Module: Data structures
 * Parameter: graph &G, int index, int value
 * Return: int(statue)
 * Use: set a vertex's value
 */


arc_node* first_adj_vex(graph &G, int index);
/* 
 * Function Name: first_adj_vex
 * Module: Data structures
 * Parameter: graph &G, int index
 * Return: arc_node*(the first vertex)
 * Use: get the fitst adjacency vertex
 */


arc_node* next_adj_vex(graph &G, int index, int now_index);
/* 
 * Function Name: next_adj_vex
 * Module: Data structures
 * Parameter: graph &G, int index, int now_index
 * Return: arc_node*(the next vertex)
 * Use: get the next adjacency vertex
 */


int insert_vex(graph &G, int index, int value);
/* 
 * Function Name: insert_vex
 * Module: Data structures
 * Parameter: graph &G, int index, int value
 * Return: int(statue)
 * Use: insert a vertex in graph
 */


int delete_vex(graph &G, int index);
/* 
 * Function Name: delete_vex
 * Module: Data structures
 * Parameter: graph &G, int index
 * Return: int(statue)
 * Use: delete a vertex in graph
 */


int insert_arc(graph &G, int src_vex, int dst_vex, int weight);
/* 
 * Function Name: insert_arc
 * Module: Data structures
 * Parameter: graph &G, int src_vex, int dst_vex, int weight
 * Return: int(statue)
 * Use: insert an arc in graph
 */


int delete_arc(graph &G, int src_vex, int dst_vex);
/* 
 * Function Name: delete_arc
 * Module: Data structures
 * Parameter: graph &G, int src_vex, int dst_vex
 * Return: int(statue)
 * Use: delete an arc in graph
 */


int dfs_traverse(graph &G);
/* 
 * Function Name: dfs_traverse
 * Module: Data structures
 * Parameter: graph &G
 * Return: int(statue)
 * Use: Depth_First Search traverse the graph
 */


int bfs_traverse(graph &G);
/* 
 * Function Name: bfs_traverse
 * Module: Data structures
 * Parameter: graph &G
 * Return: int(statue)
 * Use: Broadth_First Search traverse the graph
 */


#endif // !PY_GRAPH_H