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
binary_tree_node* creat_nodes(int index, int node_num, int *safe_tag) {
  binary_tree_node* node = (binary_tree_node*)malloc(sizeof(binary_tree_node));
  if (node == NULL)
    *safe_tag = 0;
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
  T->root = creat_nodes(index, node_num, &safe_tag);
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
void get_left_child(binary_tree_node *node, int key, binary_tree_node *left_child) {
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

// assist function to get right child
void get_right_child(binary_tree_node *node, int key, binary_tree_node *right_child) {
  if (node == NULL)
    return ;
  if (node->key == key)
    right_child = node->right_child;
  else {
    get_right_child(node->left_child, key, right_child);
    get_right_child(node->right_child, key, right_child);
  }
}

binary_tree_node* bitree_right_child(binary_tree T, int key) {
/* 
 * Function Name: bitree_right_child
 * Module: Data structures
 * Parameter: binary_tree T, int key
 * Return: binary_tree_node*
 * Use: get right child of a node
 */

  binary_tree_node *right_child = NULL;
  get_right_child(T.root, key, right_child);
  return right_child;  
}

// assist function to get left sibling
void get_left_sibling(binary_tree_node *node, int key, binary_tree_node *left_silbing) {
  if (node == NULL || node->left_child->key == key)
    return ;
  if (node->right_child->key == key)
    left_silbing = node->left_child;
  else {
    get_left_sibling(node->left_child, key, left_silbing);
    get_left_sibling(node->right_child, key, left_silbing);
  }
}

binary_tree_node* bitree_left_sibling(binary_tree T, int key) {
/* 
 * Function Name: bitree_left_sibling
 * Module: Data structures
 * Parameter: binary_tree T, int key
 * Return: binary_tree_node*
 * Use: get left sibling of a node
 */

  binary_tree_node *left_sibling = NULL;
  if (T.root->key != key)
    get_left_sibling(T.root, key, left_sibling);
  return left_sibling;
}

// assist function to get right sibling
void get_right_sibling(binary_tree_node *node, int key,  binary_tree_node *right_sibling) {
  if (node == NULL || node->right_child->key == key)
    return ;
  if (node->left_child->key == key)
    right_sibling = node->right_child;
  else {
    get_right_sibling(node->left_child, key, right_sibling);
    get_right_sibling(node->right_child, key, right_sibling);
  }
}

binary_tree_node* bitree_right_sibling(binary_tree T, int key) {
/* 
 * Function Name: bitree_right_sibling
 * Module: Data structures
 * Parameter: binary_tree T, int key
 * Return: binary_tree_node*
 * Use: get right sibling of a node
 */

  binary_tree_node *right_sibling;
  if (T.root->key != key)
    get_right_sibling(T.root, key, right_sibling);
  return right_sibling;
}

// assist function to insert node
binary_tree_node* insert_node(binary_tree_node *node, int ordered_key, int tag, int key, char *value, int *safe_tag, int *depth) {
  if (node == NULL)  {
    return NULL;
  }
  else if (node->key == ordered_key) {
    // insert left child
    if (tag == 0) {
      if (node->left_child != NULL)
        *safe_tag = 0;
      else {
        node->left_child = (binary_tree_node*)malloc(sizeof(binary_tree_node));
        if (node->left_child != NULL) {
          node->left_child->id = node->id * 2;
          node->key = key;
          strcpy(node->value, value);
          node->left_child->left_child = NULL;
          node->right_child->right_child = NULL;
          if (1 << (*depth - 1) <= node->left_child->id)
            (*depth)++;
        }
        else
          *safe_tag = 0;
      }
    }
    // insert right child
    else {
      if (node->right_child != NULL)
        *safe_tag = 0;
      else {
        node->right_child = (binary_tree_node*)malloc(sizeof(binary_tree_node));
        if (node->right_child != NULL) {
          node->right_child->id = node->id * 2;
          node->key = key;
          strcpy(node->value, value);
          node->left_child = NULL;
          node->right_child = NULL;
          if (1 << (*depth - 1) <= node->right_child->id)
            (*depth)++;
        }
        else
          *safe_tag = 0;
      }
    }
  }
  else {
    node->left_child = insert_node(node->left_child, ordered_key, tag, key, value, safe_tag, depth);
    node->right_child = insert_node(node->right_child, ordered_key, tag, key, value, safe_tag, depth);
  }
  return node;
}

int bitree_insert_node(binary_tree *T, int ordered_key, int tag, int key, char *value) {
/* 
 * Function Name: bitree_insert_node
 * Module: Data structures
 * Parameter: binary_tree *T, int ordered_key, int tag, int key, char *value
 * Return: int(status)
 * Use: insert a node in a binary tree
 */

  // a safe tag to judge whether insert ok
  int safe_tag = 1;
  if (T->root == NULL) {
    T->root = (binary_tree_node*)malloc(sizeof(binary_tree_node));
    T->root->id = 1;
    T->root->key = key;
    strcpy(T->root->value, value);
    T->root->left_child = NULL;
    T->root->right_child = NULL;
    T->size = 1;
    T->depth = 1;
    return OK;
  }
  T->root = insert_node(T->root, ordered_key, tag, key, value, &safe_tag, &T->depth);
  if (safe_tag == 1) {
    T->size++;
    return OK;
  }
  else
    return ERROR;
}

// generate the node id and tree depth
binary_tree_node *generate_id(binary_tree_node *node, int id, int *depth) {
  if (node == NULL)
    return NULL;
  node->id = id;
  if (1 << (*depth - 1) <= node->id)
    (*depth)++;
  node->left_child = generate_id(node->left_child, id * 2, depth);
  node->right_child = generate_id(node->right_child, id * 2 + 1, depth);
  return node;
}

// assist function to insert child tree
binary_tree_node* insert_child_tree(binary_tree_node *node, int ordered_key, int tag, binary_tree *C, int *depth) {
  if (node == NULL) {
    return NULL;
  }
  else if (node->key == ordered_key) {
    // insert left child tree
    if (tag == 0) {
      C->root->right_child = node->left_child;
      node->left_child = C->root;
      node = generate_id(node, node->id, depth);
    }
    // insert right child tree
    else {
      C->root->right_child = node->right_child;
      node->right_child = C->root;
      node = generate_id(node, node->id, depth);
    }
  }
  else {
    node->left_child = insert_child_tree(node->left_child, ordered_key, tag, C, depth);
    node->left_child = insert_child_tree(node->left_child, ordered_key, tag, C, depth);
  }
  return node;
}

int bitree_insert_child_tree(binary_tree *T, int ordered_key, int tag, binary_tree *C) {
/* 
 * Function Name: bitree_insert_child_tree
 * Module: Data structures
 * Parameter: binary_tree *T, int ordered_key, int tag, binary_tree *C
 * Return: int(status)
 * Use: insert a child tree in a binary tree
 */

  if (T->root == NULL || C->root->right_child != NULL)
    return ERROR;
  T->root = insert_child_tree(T->root, ordered_key, tag, C, &T->depth);
  T->size += C->size;
  return OK;
}

binary_tree_node* delete_child_tree(binary_tree_node *node, int order_key, int tag, int *safe_tag) {
  if (node == NULL)
    return NULL;
  else if (node->key == order_key) {
    // delete left child tree
    if (tag == 0) {
      if (node->left_child != NULL) {
        *safe_tag = 1;
        free_nodes(node->left_child);
        node->left_child = NULL;
      }
    }
    // delete right child tree
    else {
      if (node->right_child != NULL) {
        *safe_tag = 1;
        free_nodes(node->right_child);
        node->right_child = NULL;
      }
    }
  }
  else {
    node->left_child = delete_child_tree(node->left_child, order_key, tag, safe_tag);
    node->right_child = delete_child_tree(node->right_child, order_key, tag, safe_tag);
  }
  return node;
}

// assist function to count the tree node after delete a child tree
void count_tree(binary_tree_node *node, int *size, int *depth) {
  if (node == NULL)
    return ;
  else {
    (*size)++;
    if (1 << (*depth - 1) <= node->id)
      (*depth)++;
    count_tree(node->left_child, size, depth);
    count_tree(node->right_child, size, depth);
  }
}

int bitree_delete_child_tree(binary_tree *T, int ordered_key, int tag)  {
/* 
 * Function Name: bitree_delete_child_tree
 * Module: Data structures
 * Parameter: binary_tree *T, int ordered_key, int tag, binary_tree *C
 * Return: int(status)
 * Use: delete a child tree in a binary tree
 */

  if (T->root == NULL)
    return ERROR;
  int safe_tag = 0;
  T->root = delete_child_tree(T->root, ordered_key, tag, &safe_tag);
  T->size = 0;
  T->depth = 0;
  count_tree(T->root, &T->size, &T->depth);
  return OK;
}

// assist function to preorder traverse the binary tree
void preorder_traverse(binary_tree_node *node) {
  if (node == NULL)
    printf("NULL\n");
  else {
    printf("Key: %d, value: %s\n", node->key, node->value);
  }
  preorder_traverse(node->left_child);
  preorder_traverse(node->right_child);
}

int bitree_preorder_traverse(binary_tree T) {
/* 
 * Function Name: bitree_preorder_traverse
 * Module: Data structures
 * Parameter: binary_tree T
 * Return: int(status)
 * Use: preorder traverse and print the values
 */

  if (T.root == NULL)
    return ERROR;
  printf("Preorder traverse:\n");
  printf("Tree size: %d\n",  T.size);
  printf("Tree depth: %d\n",  T.depth);
  preorder_traverse(T.root);
  return OK;
}

// assist function to inorder traverse the binary tree
void inorder_traverse(binary_tree_node *node) {
  inorder_traverse(node->left_child);
  if (node == NULL)
    printf("NULL\n");
  else {
    printf("Key: %d, value: %s\n", node->key, node->value);
  }
  inorder_traverse(node->right_child);
}

int bitree_inorder_traverse(binary_tree T) {
/* 
 * Function Name: bitree_inorder_traverse
 * Module: Data structures
 * Parameter: binary_tree T
 * Return: int(status)
 * Use: inorder traverse and print the values
 */

  if (T.root == NULL)
    return ERROR;
  printf("Inorder traverse:\n");
  printf("Tree size: %d\n",  T.size);
  printf("Tree depth: %d\n",  T.depth);
  inorder_traverse(T.root);
  return OK;
}

// assist function to postorder traverse the binary tree
void postorder_traverse(binary_tree_node *node) {
  postorder_traverse(node->left_child);
  postorder_traverse(node->right_child);
  if (node == NULL)
    printf("NULL\n");
  else {
    printf("Key: %d, value: %s\n", node->key, node->value);
  }
}

int bitree_postorder_traverse(binary_tree T) {
/* 
 * Function Name: bitree_postorder_traverse
 * Module: Data structures
 * Parameter: binary_tree T
 * Return: int(status)
 * Use: postorder traverse and print the values
 */

  if (T.root == NULL)
    return ERROR;
  printf("Postorder traverse:\n");
  printf("Tree size: %d\n",  T.size);
  printf("Tree depth: %d\n",  T.depth);
  postorder_traverse(T.root);
  return OK;
}

int bitree_levelorder_traverse(binary_tree T) {
/* 
 * Function Name: bitree_levelorder_traverse
 * Module: Data structures
 * Parameter: binary_tree T
 * Return: int(status)
 * Use: levelorder traverse and print the values
 */

  if (T.root == NULL)
    return ERROR;
  LinkQueue my_node_queue;
  InitQueue(&my_node_queue);
  binary_tree_node *node;
  printf("Levelorder traverse:\n");
  printf("Tree size: %d\n",  T.size);
  printf("Tree depth: %d\n",  T.depth);
  // use a queue to levelorder traverse the  binary tree
  EnQueue(&my_node_queue, T.root);
  while (!IsEmpty(&my_node_queue)) {
    node = DeQueue(&my_node_queue);
    printf("Key: %d, value: %s\n", node->key, node->value);
    if (node->left_child != NULL)
      EnQueue(&my_node_queue, node->left_child);
    if (node->right_child != NULL)
      EnQueue(&my_node_queue, node->right_child);
  }
  return OK;
}