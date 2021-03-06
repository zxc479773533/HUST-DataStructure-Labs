/*
 * AUTHOR: Yue Pan
 * GITHUB: zxc479773533
 * E-MAIL: zxc479773533@gmail.com
 */

#ifndef PY_BINARY_TREE_H
#define PY_BINARY_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define OK 0
#define ERROR 1

#define LEFT 0
#define RIGHT 1

#define PRE_ORDER 0
#define IN_ORDER 1
#define POST_ORDER 2

// the struct of binary tree node
typedef struct binary_tree_node {
  int index;
  int value;
  struct binary_tree_node *left_child;
  struct binary_tree_node *right_child;
} binary_tree_node;

// the main struct of binary tree
typedef struct binary_tree {
  int id;
  int size;
  struct binary_tree_node *root;
  struct binary_tree *next;
} binary_tree;

// the struct for managin the binary tree
typedef struct Binary_tree_main {
  binary_tree *head;
} Binary_tree_main;

// the struct to save the binary tree
typedef struct Binary_tree_store {
  int id;
  int size;
  int *pre_index;
  int *pre_defination;
  int *in_index;
  int *in_defination;
} Binary_tree_store;

int init_binary_tree(binary_tree *T);
/* 
 * Function Name: init_binary_tree
 * Module: Data structures
 * Parameter: binary_tree *T
 * Return: int(status)
 * Use: initial the binary tree
 */


int destroy_bitree(binary_tree *T);
/* 
 * Function Name: destroy_bitree
 * Module: Data structures
 * Parameter: binary_tree *T
 * Return: int(status)
 * Use: destroy the binary tree
 */


int create_bitree(binary_tree *T, int *pre_index, int *pre_defination, int *in_index, int *in_defination, int difination_len);
/* 
 * Function Name: create_bitree
 * Module: Data structures
 * Parameter: binary_tree *T, int *pre_index, int *pre_defination, int *in_index, int *in_defination, int difination_len
 * Return: int(status)
 * Use: create the binary tree with some nodes
 */


int clear_bitree(binary_tree *T);
/* 
 * Function Name: clear_bitree
 * Module: Data structures
 * Parameter: binary_tree *T
 * Return: int(status)
 * Use: clear the binary tree
 */


int is_bitree_empty(binary_tree T);
/* 
 * Function Name: is_bitree_empty
 * Module: Data structures
 * Parameter: binary_tree T
 * Return: int(true or false)
 * Use: judge if the binary tree is empty
 */


int bitree_depth(binary_tree T);
/* 
 * Function Name: bitree_depth
 * Module: Data structures
 * Parameter: binary_tree T
 * Return: int(the depth)
 * Use: get the depth of binary tree
 */


binary_tree_node* bitree_root(binary_tree T);
/* 
 * Function Name: bitree_root
 * Module: Data structures
 * Parameter: binary_tree T
 * Return: binary_tree_node*
 * Use: get the root of binary tree
 */


int bitree_get_value(binary_tree T, int index);
/* 
 * Function Name: bitree_get_value
 * Module: Data structures
 * Parameter: binary_tree T, int index
 * Return: int(the value)
 * Use: get the value of a node
 */


int bitree_set_value(binary_tree *T, int index, int value);
/* 
 * Function Name: bitree_set_value
 * Module: Data structures
 * Parameter: binary_tree *T, int index, int value
 * Return: int(status)
 * Use: set the value of a node
 */


binary_tree_node* bitree_parent(binary_tree T, int index);
/* 
 * Function Name: bitree_parent
 * Module: Data structures
 * Parameter: binary_tree T, int index
 * Return: binary_tree_node*
 * Use: get parent of a node
 */


binary_tree_node* bitree_left_child(binary_tree T, int index);
/* 
 * Function Name: bitree_left_child
 * Module: Data structures
 * Parameter: binary_tree T, int index
 * Return: binary_tree_node*
 * Use: get left child of a node
 */


binary_tree_node* bitree_right_child(binary_tree T, int index);
/* 
 * Function Name: bitree_right_child
 * Module: Data structures
 * Parameter: binary_tree T, int index
 * Return: binary_tree_node*
 * Use: get right child of a node
 */


binary_tree_node* bitree_left_sibling(binary_tree T, int index);
/* 
 * Function Name: bitree_left_sibling
 * Module: Data structures
 * Parameter: binary_tree T, int index
 * Return: binary_tree_node*
 * Use: get left sibling of a node
 */


binary_tree_node* bitree_right_sibling(binary_tree T, int index);
/* 
 * Function Name: bitree_right_sibling
 * Module: Data structures
 * Parameter: binary_tree T, int index
 * Return: binary_tree_node*
 * Use: get right sibling of a node
 */


int bitree_insert_child(binary_tree *T, int index, int LorR, binary_tree *C);
/* 
 * Function Name: bitree_insert_child
 * Module: Data structures
 * Parameter: binary_tree *T, int index, int LorR, binary_tree *C
 * Return: int(status)
 * Use: insert a child tree in a binary tree
 */


int bitree_delete_child(binary_tree *T, int index, int LorR);
/* 
 * Function Name: bitree_delete_child
 * Module: Data structures
 * Parameter: binary_tree *T, int index, int LorR
 * Return: int(status)
 * Use: delete a child tree in a binary tree
 */


int bitree_preorder_traverse(binary_tree T);
/* 
 * Function Name: bitree_preorder_traverse
 * Module: Data structures
 * Parameter: binary_tree T
 * Return: int(status)
 * Use: preorder traverse and print the values
 */


int bitree_inorder_traverse(binary_tree T);
/* 
 * Function Name: bitree_inorder_traverse
 * Module: Data structures
 * Parameter: binary_tree T
 * Return: int(status)
 * Use: inorder traverse and print the values
 */


int bitree_postorder_traverse(binary_tree T);
/* 
 * Function Name: bitree_postorder_traverse
 * Module: Data structures
 * Parameter: binary_tree T
 * Return: int(status)
 * Use: postorder traverse and print the values
 */


int bitree_levelorder_traverse(binary_tree T);
/* 
 * Function Name: bitree_levelorder_traverse
 * Module: Data structures
 * Parameter: binary_tree T
 * Return: int(status)
 * Use: levelorder traverse and print the values
 */


#endif // !PY_