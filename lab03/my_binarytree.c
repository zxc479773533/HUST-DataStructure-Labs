/*
 * AUTHOR: Yue Pan
 * GITHUB: zxc479773533
 * E-MAIL: zxc479773533@gmail.com
 */

#include "my_binarytree.h"
#include "mylibqueue.c"

// assist fuction to search array
int search_array(int *array, int size, int target){
  int i;
  for(i = 0; i < size; i++) {
    if(array[i] == target)
      return i;
  }
  return -1;
}

int init_binary_tree(binary_tree *T) {
/* 
 * Function Name: init_binary_tree
 * Module: Data structures
 * Parameter: binary_tree *T
 * Return: int(status)
 * Use: initial the binary tree
 */

  T->size = 0;
  T->root = NULL;
  return OK;
}

// assist function to free all nodes
void free_nodes(binary_tree_node *node) {
  if (node == NULL)
    return ;
  // free left child
  if (node->left_child != NULL)
    free_nodes(node->left_child);
  // free right child
  if (node->right_child != NULL)
    free_nodes(node->right_child);
  // free self
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

// assist function to create nodes
binary_tree_node *create_nodes(int *ind1, int *def1, int *ind2, int *def2, int max_pos, int min_pos, int *pos) {
  // start
  if (pos == NULL) {
    int new_pos = 0;
    return create_nodes(ind1, def1, ind2, def2, max_pos, min_pos, &new_pos);
  }
  // get root pos in inorder defination
  int root_pos = search_array(def2 + min_pos, max_pos - min_pos, def1[*pos]);
  if (root_pos == -1)
    return NULL;
  else
    root_pos += min_pos;
  // create a node
  binary_tree_node *root = (binary_tree_node*)malloc(sizeof(binary_tree_node));
  root->index = ind1[*pos];
  root->value = def1[*pos];
  (*pos)++;
  // the left of root in preorder defination is the left child tree
  root->left_child = create_nodes(ind1, def1, ind2, def2, root_pos, min_pos, pos);
  // the right of root in preorder defination is the right child tree
  root->right_child = create_nodes(ind1, def1, ind2, def2, max_pos, root_pos + 1, pos);
  return root;
}

int create_bitree(binary_tree *T, int *pre_index, int *pre_defination, int *in_index, int *in_defination, int difination_len) {
/* 
 * Function Name: create_bitree
 * Module: Data structures
 * Parameter: binary_tree *T, int *pre_index, int *pre_defination, int *in_index, int *in_defination, int difination_len
 * Return: int(status)
 * Use: create the binary tree with some nodes
 */

  if (difination_len <= 0)
    return ERROR;
  T->size = difination_len;
  T->root = create_nodes(pre_index, pre_defination, in_index, in_defination, difination_len, 0, NULL);
  return OK;
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
  free_nodes(T->root);
  T->root = NULL;
  return OK;
}

int is_bitree_empty(binary_tree T) {
/* 
 * Function Name: is_bitree_empty
 * Module: Data structures
 * Parameter: binary_tree T
 * Return: int(tree or false)
 * Use: judge if the binary tree is empty
 */

  if (T.size == 0)
    return TRUE;
  else
    return FALSE;
}

// assist function to get depth
int get_depth(binary_tree_node *node, int depth) {
  if (node == NULL)
    return depth;
  // count left depth
  int left_depth = get_depth(node->left_child, depth + 1);
  // count right depth
  int right_depth = get_depth(node->right_child, depth + 1);
  // return the bigger of left and right depth
  return left_depth > right_depth ? left_depth : right_depth;
}

int bitree_depth(binary_tree T) {
/* 
 * Function Name: bitree_depth
 * Module: Data structures
 * Parameter: binary_tree T
 * Return: int(the depth)
 * Use: get the depth of binary tree
 */

  return get_depth(T.root, 0);
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
int get_value(binary_tree_node* node, int index) {
  if (node == NULL)
    return 0;
  if (node->index == index)
    return node->value;
  else {
    // find in left child tree
    int find_left = get_value(node->left_child, index);
    // find in right child tree
    int find_right = get_value(node->right_child, index);
    return find_left | find_right;
  }
}

int bitree_get_value(binary_tree T, int index) {
/* 
 * Function Name: bitree_get_value
 * Module: Data structures
 * Parameter: binary_tree T, int index
 * Return: int(the value)
 * Use: get the value of a node
 */

  if (T.root == NULL)
    return 0;
  return get_value(T.root, index);
}

// assist function to set value of a node
void set_value(binary_tree_node *node, int index, int value, int *safe_tag) {
  if (node == NULL)
    return ;
  if (node->index == index) {
    node->value = value;
    // safe tag == 1 means set succeed
    *safe_tag = 1;
  }
  else {
    // set in left child tree
    set_value(node->left_child, index, value, safe_tag);
    // set in right child tree
    set_value(node->right_child, index, value, safe_tag);
  }
}

int bitree_set_value(binary_tree *T, int index, int value) {
/* 
 * Function Name: bitree_set_value
 * Module: Data structures
 * Parameter: binary_tree *T, int index, int value
 * Return: int(status)
 * Use: set the value of a node
 */

  int safe_tag = 0;
  set_value(T->root, index, value, &safe_tag);
  if (safe_tag == 1)
    return OK;
  else
    return ERROR;
}

// assist function to get parent
binary_tree_node* get_parent(binary_tree_node* node, int index) {
  if (node == NULL)
    return NULL;
  if ((node->left_child != NULL && node->left_child->index == index) ||
   (node->right_child != NULL && node->right_child->index == index))
    return node;
  // find in left child tree
  binary_tree_node *parent = get_parent(node->left_child, index);
  // find in right child tree
  if (parent == NULL)
    parent = get_parent(node->right_child, index);
  return parent;
}

binary_tree_node* bitree_parent(binary_tree T, int index) {
/* 
 * Function Name: bitree_parent
 * Module: Data structures
 * Parameter: binary_tree T, int key
 * Return: binary_tree_node*
 * Use: get parent of a node
 */

  return get_parent(T.root, index);
}

// assist function to get child
binary_tree_node* get_child(binary_tree_node *node, int LorR, int index) {
  if (node == NULL)
    return NULL;
  if (node->index == index) {
    if (LorR == LEFT)
      return node->left_child;
    else
      return node->right_child;
  }
  // find in left child tree
  binary_tree_node *child = get_child(node->left_child, LorR, index);
  // find in right child tree
  if (child == NULL)
    child = get_child(node->right_child, LorR, index);
  return child;
}

binary_tree_node* bitree_left_child(binary_tree T, int index) {
/* 
 * Function Name: bitree_left_child
 * Module: Data structures
 * Parameter: binary_tree T, int index
 * Return: binary_tree_node*
 * Use: get left child of a node
 */

  return get_child(T.root, LEFT, index);
}

binary_tree_node* bitree_right_child(binary_tree T, int index) {
/* 
 * Function Name: bitree_right_child
 * Module: Data structures
 * Parameter: binary_tree T, int index
 * Return: binary_tree_node*
 * Use: get right child of a node
 */

  return get_child(T.root, RIGHT, index);  
}

// assist function to get left sibling
binary_tree_node* get_sibling(binary_tree_node *node, int LorR, int index) {
  if (node == NULL)
    return NULL;
  // get right child's left sibling
  if (node->left_child != NULL && node->left_child->index == index && LorR == RIGHT)
    return node->right_child;
  // get left child's right sibling
  else if (node->right_child != NULL && node->right_child->index == index && LorR == LEFT)
    return node->left_child;
  // find in left child tree
  binary_tree_node *sibling = get_sibling(node->left_child, LorR, index);
  // find in right child tree
  if (sibling == NULL)
    sibling = get_sibling(node->right_child, LorR, index);
  return sibling;
}

binary_tree_node* bitree_left_sibling(binary_tree T, int index) {
/* 
 * Function Name: bitree_left_sibling
 * Module: Data structures
 * Parameter: binary_tree T, int index
 * Return: binary_tree_node*
 * Use: get left sibling of a node
 */

  return get_sibling(T.root, LEFT, index);
}

binary_tree_node* bitree_right_sibling(binary_tree T, int index) {
/* 
 * Function Name: bitree_right_sibling
 * Module: Data structures
 * Parameter: binary_tree T, int index
 * Return: binary_tree_node*
 * Use: get right sibling of a node
 */

  return get_sibling(T.root, RIGHT, index);
}

// assist function to insert child tree
binary_tree_node* insert_child_tree(binary_tree_node *node, int index, int LorR, binary_tree_node *sub_tree) {
  if (node == NULL)
    return NULL;
  if (node->index == index) {
    binary_tree_node *tmp_node;
    // insert as left child
    if (LorR == LEFT) {
      tmp_node = node->left_child;
      node->left_child = sub_tree;
    }
    // insert as right child
    else {
      tmp_node = node->right_child;
    }
      node->right_child = tmp_node;    
  }
  // find in left child tree
  node->left_child = insert_child_tree(node->left_child, index, LorR, sub_tree);
  // find in right child tree
  node->right_child = insert_child_tree(node->right_child, index, LorR, sub_tree);
  return node;
}

int bitree_insert_child_tree(binary_tree *T, int index, int LorR, binary_tree *C) {
/* 
 * Function Name: bitree_insert_child
 * Module: Data structures
 * Parameter: binary_tree *T, int index, int LorR, binary_tree_node *sub_tree
 * Return: int(status)
 * Use: insert a child tree in a binary tree
 */

  if (T->root == NULL || C->root == NULL || C->root->right_child != NULL)
    return ERROR;
  T->size += C->size;  
  T->root = insert_child_tree(T->root, index, LorR, C->root);
  return OK;
}

// assist function to search a node
int search_bitree(binary_tree_node *node, int index) {
  if (node == NULL)
    return 0;
  if (node->index == index)
    return 1;
  return search_bitree(node->left_child, index) | search_bitree(node->right_child, index);
}

// assist function to count binary tree nodes
int count_bitree(binary_tree_node *node) {
  if (node == NULL)
    return 0;
  return 1 + count_bitree(node->left_child) + count_bitree(node->right_child);
}


binary_tree_node* delete_child_tree(binary_tree_node *node, int index, int LorR) {
  if (node == NULL)
    return NULL;
  if (node->index == index) {
    // delete left child tree
    if (LorR == LEFT) {
      free_nodes(node->left_child);
      node->left_child = NULL;
    }
    // delete right child tree
    else {
      free_nodes(node->right_child);
      node->right_child = NULL;
    }
  }
  // find in left child tree
  node->left_child = delete_child_tree(node->left_child, index, LorR);
  // find in right child tree
  node->right_child = delete_child_tree(node->right_child, index, LorR);
  return node;
}

int bitree_delete_child_tree(binary_tree *T, int index, int LorR)  {
/* 
 * Function Name: bitree_delete_child
 * Module: Data structures
 * Parameter: binary_tree *T, int index, int LorR
 * Return: int(status)
 * Use: delete a child tree in a binary tree
 */

  if (T->root == NULL || !search_bitree(T->root, index))
    return ERROR;
  T->root = delete_child_tree(T->root, index, LorR);
  T->size = count_bitree(T->root);
  return OK;
}

// assist function to traverse the binary tree
void traverse_bitree(binary_tree_node *node, int order) {
  if (node == NULL)
    return ;
  if (order == PRE_ORDER) {
    printf("Index: %d, value: %d\n", node->index, node->value);
    traverse_bitree(node->left_child, order);
    traverse_bitree(node->right_child, order);
  }
  else if (order == IN_ORDER) {
    traverse_bitree(node->left_child, order);
    printf("Index: %d, value: %d\n", node->index, node->value);
    traverse_bitree(node->right_child, order);
  }
  else if (order == POST_ORDER) {
    traverse_bitree(node->left_child, order);
    traverse_bitree(node->right_child, order);
    printf("Index: %d, value: %d\n", node->index, node->value);
  }
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
  printf("Tree size: %d\n", T.size);
  traverse_bitree(T.root, PRE_ORDER);
  return OK;
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
  traverse_bitree(T.root, IN_ORDER);
  return OK;
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
  traverse_bitree(T.root, POST_ORDER);
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
  // use a queue to levelorder traverse the  binary tree
  EnQueue(&my_node_queue, T.root);
  while (!IsEmpty(&my_node_queue)) {
    node = DeQueue(&my_node_queue);
    printf("Index: %d, value: %d\n", node->index, node->value);
    if (node->left_child != NULL)
      EnQueue(&my_node_queue, node->left_child);
    if (node->right_child != NULL)
      EnQueue(&my_node_queue, node->right_child);
  }
  return OK;
}