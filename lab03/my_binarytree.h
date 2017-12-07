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

// the struct of binary tree node
typedef struct binary_tree_node {
  int id;
  int key;
  char value[256];
  binary_tree_node *left_child;
  binary_tree_node *right_child;
  binary_tree_node *parent;
} binary_tree_node;

// the main struct of binary tree
typedef struct binary_tree {
  int id;
  binary_tree_node *root;
  binary_tree *next;
} binary_tree;

// the struct for managin the binary tree
typedef struct Binary_tree_main {
  int num;
  binary_tree *head;
} Binary_tree_main;

int init_binary_tree(binary_tree *T);
/* 
 * Function Name: init_binary_tree
 * Module: Data structures
 * Parameter: binary_tree *T
 * Return: int(status)
 * Use: initial the binary tree
 */

int destroy_bitree(binary_tree *T);

int create_bitree(binary_tree *T, int node_num);

int clear_bitree(binary_tree *T);

int is_bitree_empty(binary_tree T);

int bitree_depth(binary_tree T);

int bitree_root(binary_tree T);

int bitree_value(binary_tree T, int key, char *value);

int bitree_assign(binary_tree *T, int key, char *value);

binary_tree_node* bitree_parent(binary_tree T, int key);

binary_tree_node* bitree_left_child(binary_tree T, int key);

binary_tree_node* bitree_right_child(binary_tree T, int key);

binary_tree_node* bitree_left_sibling(binary_tree T, int key);

binary_tree_node* bitree_right_sibling(binary_tree T, int key);

int bitree_insert_child(binary_tree *T, int ordered_key, int tag, char *value);

int bitree_insert_child_tree(binary_tree *T, int ordered_key, int tag, binary_tree *C);

int bitree_delete_child(binary_tree *T, int ordered_key, int tag);

int bitree_preorder_traverse(binary_tree T);

int bitree_inorder_traverse(binary_tree T);

int bitree_postorder_traverse(binary_tree T);

int bitree_levelorder_traverse(binary_tree T);


#endif // !PY_