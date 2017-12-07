/*
 * AUTHOR: Yue Pan
 * GITHUB: zxc479773533
 * E-MAIL: zxc479773533@gmail.com
 */

#include "my_binarytree.h"
#include "mylibqueue.h"

int init_binary_tree(binary_tree *T) {
/* 
 * Function Name: init_binary_tree
 * Module: Data structures
 * Parameter: binary_tree *T
 * Return: int(status)
 * Use: initial the binary tree
 */

  T->size = 0;
  T->depth = 0;
  T->root = NULL;
  return OK;
}

// assist function to free all nodes
void free_nodes(binary_tree_node *node) {
  if (node->left_child != NULL)
    free_nodes(node->left_child);
  if (node->right_child != NULL)
    free_nodes(node->right_child);
  free(node);
}

int destroy_bitree(binary_tree *T){
/* 
 * Function Name: destroy_bitree
 * Module: Data structures
 * Parameter: binary_tree *T
 * Return: int(status)
 * Use: destroy the binary tree
 */

  free_nodes(T->root);
  free(T);
  return OK;
}

// assist function to creat nodes
binary_tree_node* creat_nodes(int index, int node_num, int safe_tag) {
  binary_tree_node* node = (binary_tree_node*)malloc(sizeof(binary_tree_node));
  if (node == NULL)
    safe_tag = 0;
  node->id = index;
  node->key = index;
  node->left_child = NULL;
  node->right_child = NULL;
  if (index * 2 <= node_num)
    node->left_child = creat_nodes(index * 2, node_num, safe_tag);
  if (index * 2 + 1 <= node_num)
    node->right_child = creat_nodes(index * 2 + 1, node_num, safe_tag);
  return node;
}

int create_bitree(binary_tree *T, int node_num) {
/* 
 * Function Name: create_bitree
 * Module: Data structures
 * Parameter: binary_tree *T, int node_num
 * Return: int(status)
 * Use: create the binary tree with some nodes
 */

  if (node_num <= 0)
    return ERROR;
  int index = 1;
  int count = 1;
  int safe_tag = 1;
  while (count <= node_num) {
    count *= 2;
    T->depth++;
  }
  T->size = node_num;
  T->root = creat_nodes(index, node_num, safe_tag);
  if (safe_tag == 0) {
    free_nodes(T->root);
    T->size = 0;
    T->depth = 0;
    return ERROR;
  }
  else
    return OK;
}

// assist func to clear nodes
binary_tree_node* clear_nodes(binary_tree_node* node) {
  memset(node->value, 0, 256);
  if (node->left_child != NULL)
    node->left_child = clear_nodes(node->left_child);
  if (node->right_child != NULL)
    node->right_child = clear_nodes(node->right_child);
  return node;
}

int clear_bitree(binary_tree *T) {
/* 
 * Function Name: clear_bitree
 * Module: Data structures
 * Parameter: binary_tree *T
 * Return: int(status)
 * Use: clear the binary tree
 */

  T->size = 0;
  T->depth = 0;
  T->root = clear_nodes(T->root);
}

int is_bitree_empty(binary_tree T) {
/* 
 * Function Name: is_bitree_empty
 * Module: Data structures
 * Parameter: binary_tree T
 * Return: int(tree or false)
 * Use: judge if the binary tree is empty
 */

  return T.size;
}

int bitree_depth(binary_tree T) {
/* 
 * Function Name: bitree_depth
 * Module: Data structures
 * Parameter: binary_tree T
 * Return: int(status)
 * Use: get the depth of binary tree
 */

  return T.depth;
}

binary_tree_node* bitree_root(binary_tree T) {
/* 
 * Function Name: bitree_root
 * Module: Data structures
 * Parameter: binary_tree T
 * Return: binary_tree_node*
 * Use: get the root of binary tree
 */
  return T.root;
}

// assist function to get value of a node
void get_value(binary_tree_node* node, int key, char *value) {
  if (node == NULL)
    return ;
  if (node->key == key)
    value = node->value;
  else {
    get_value(node->left_child, key, value);
    get_value(node->right_child, key, value);
  }
}

int bitree_get_value(binary_tree T, int key, char *value) {
/* 
 * Function Name: bitree_get_value
 * Module: Data structures
 * Parameter: binary_tree T, int key, char *value
 * Return: int(status)
 * Use: get the value of a node
 */

  get_value(T.root, key, value);
  if (value == NULL)
    return ERROR;
  else
    return OK;
}

// assist function to set value of a node
void set_value(binary_tree_node *node, int key, char *value) {
  if (node == NULL)
    return ;
  if (node->key == key)
    strcpy(node->value, value);
  else {
    set_value(node->left_child, key, value);
    set_value(node->right_child, key,  value);
  }
}

int bitree_set_value(binary_tree *T, int key, char *value) {
/* 
 * Function Name: bitree_set_value
 * Module: Data structures
 * Parameter: binary_tree *T, int key, char *value
 * Return: int(status)
 * Use: set the value of a node
 */

  set_value(T->root, key, value);
  return OK;
}

// assist function to get parent
void get_parent(binary_tree_node* node, int key, binary_tree_node *parent) {
  if (node == NULL)
    return ;
  if ((node->left_child != NULL && node->left_child->key == key) ||
   (node->right_child != NULL && node->right_child->key == key))
    parent = node;
  else {
    get_parent(node->left_child, key, parent);
    get_parent(node->right_child, key, parent);
  }
}

binary_tree_node* bitree_parent(binary_tree T, int key) {
/* 
 * Function Name: bitree_parent
 * Module: Data structures
 * Parameter: binary_tree T, int key
 * Return: binary_tree_node*
 * Use: get parent of a node
 */

  binary_tree_node *parent = NULL;
  get_parent(T.root, key, parent);
  return parent;
}

// assist function to get left child
void get_left_child(binary_tree_node* node, int key, binary_tree_node* left_child) {
  if (node == NULL)
    return ;
  if (node->key == key)
    left_child = node->left_child;
  else {
    get_left_child(node->left_child, key, left_child);
    get_left_child(node->right_child, key, left_child);
  }
}

binary_tree_node* bitree_left_child(binary_tree T, int key) {
/* 
 * Function Name: bitree_left_child
 * Module: Data structures
 * Parameter: binary_tree T, int key
 * Return: binary_tree_node*
 * Use: get left child of a node
 */

  binary_tree_node *left_child = NULL;
  get_left_child(T.root, key, left_child);
  return left_child;
}
