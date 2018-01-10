/*
 * AUTHOR: Yue Pan
 * GITHUB: zxc479773533
 * E-MAIL: zxc479773533@gmail.com
 */

#include "my_graph.h"
#include "mylibqueue.c"

// assist function to search a vertex in graph
vertex_node* search_graph(graph *G, int index) {
  vertex_node *a_node = G->first_vertex;
  while (a_node != NULL) {
    // find the vertex
    if (a_node->index == index)
      break;
    a_node = a_node->next;
  }
  return a_node;
}

// assist function to search an arc in graph
arc_node* search_arc(graph *G, int src_vex, int dst_vex) {
  vertex_node *src_node = search_graph(G, src_vex);
  if (src_node == NULL)
    return NULL;
  arc_node *an_arc = src_node->first_arc;
  while (an_arc != NULL) {
    // find the arc
    if (an_arc->vertex == dst_vex)
      break;
    an_arc = an_arc->next;
  }
  return an_arc;
}

int creat_graph(graph *G, int kind, int v_num, int a_num, int *v_indexs, int *v_values, int *a_matrix) {
/* 
 * Function Name: creat_graph
 * Module: Data structures
 * Parameter: graph &G, int kind, int v_num, int a_num, int *v_indexs, int *v_values, int *a_matrix
 * Return: int(status)
 * Use: create a graph
 */

  int i, j;
  int status = OK;
  G->kind = kind;
  // insert vertexs
  for(i = 0; i < v_num; i++) {
    status = insert_vex(G, v_indexs[i], v_values[i]);
  }
  // insert arcs
  for (i = 0; i < v_num; i++) {
    for (j = 0; j < v_num; j++) {
      if (*(a_matrix + i * v_num + j) != 0) {
        insert_arc(G, v_indexs[i], v_indexs[j], *(a_matrix + i * v_num + j));
      }
    }
  }
  G->vertex_num = v_num;
  G->arc_num = a_num;
  return status;
}

int destory_graph(graph *G) {
/* 
 * Function Name: destory_graph
 * Module: Data structures
 * Parameter: graph &G
 * Return: int(status)
 * Use: destory a graph
 */

  vertex_node *a_node = G->first_vertex;
  // free nodes
  while (a_node != NULL) {
    vertex_node *tmp_node = a_node;
    a_node = a_node->next;
    free(tmp_node);
  }
  if (G->first_vertex != NULL)
    return ERROR;
  // free graph
  free(G);
  if (G != NULL)
    return ERROR;
  return OK;
}

int locate_vex(graph *G, int value) {
/* 
 * Function Name: locate_vex
 * Module: Data structures
 * Parameter: graph &G, int value
 * Return: int(the index)
 * Use: find a vertex in graph
 */

  vertex_node *a_node = G->first_vertex;
  while (a_node != NULL) {
    // find the vertex
    if (a_node->value == value)
      return a_node->index;
    a_node = a_node->next;
  }
  return 0;
}

int get_vex_value(graph *G, int index) {
/* 
 * Function Name: get_vex_value
 * Module: Data structures
 * Parameter: graph &G, int index
 * Return: int(the value)
 * Use: find a value of a vertex
 */

  vertex_node *a_node = G->first_vertex;
  while (a_node != NULL) {
    // find the vertex
    if (a_node->index == index)
      return a_node->value;
    a_node = a_node->next;
  }
  return 0;
}

int set_vex_value(graph *G, int index, int value) {
/* 
 * Function Name: set_vex_value
 * Module: Data structures
 * Parameter: graph &G, int index, int value
 * Return: int(statue)
 * Use: set a vertex's value
 */

  vertex_node *a_node = G->first_vertex;
  while (a_node != NULL) {
    // find the vertex
    if (a_node->index == index) {
      a_node->value = value;
      break;
    }
    a_node = a_node->next;
  }
  if (a_node == NULL)
    return ERROR;
  else
    return OK;
}

int set_arc_weight(graph *G, int src_index, int dst_index, int weight) {
/* 
 * Function Name: set_arc_weight
 * Module: Data structures
 * Parameter: graph *G, int src_index, int dst_index, int weight
 * Return: int(statue)
 * Use: set an arc's weight
 */

  arc_node *arc = search_arc(G, src_index, dst_index);
  if (arc == NULL)
    return ERROR;
  arc->weight = weight;
  // if the graph is undirected, also set the weight of "dst" to "src"
  if (G->kind == UNDIRECTED_GRAPH || G->kind == UNDIRECTED_NET) {
    arc = search_arc(G, dst_index, src_index);
    arc->weight = weight;
  }
  return OK;
}

vertex_node* first_adj_vex(graph *G, int index) {
/* 
 * Function Name: first_adj_vex
 * Module: Data structures
 * Parameter: graph &G, int index
 * Return: vertex_node*(the first vertex)
 * Use: get the fitst adjacency vertex
 */

  vertex_node *a_node = G->first_vertex;
  vertex_node *first_adj_vertex = NULL;
  while (a_node != NULL) {
    // find the vertex
    if (a_node->index == index) {
      // search in graph
      if (a_node->first_arc != NULL)
        first_adj_vertex = search_graph(G, a_node->first_arc->vertex);
      break;
    }
    a_node = a_node->next;
  }
  return first_adj_vertex;
}

vertex_node* next_adj_vex(graph *G, int index, int now_index) {
/* 
 * Function Name: next_adj_vex
 * Module: Data structures
 * Parameter: graph &G, int index, int now_index
 * Return: vertex_node*(the next vertex)
 * Use: get the next adjacency vertex
 */

  // the same as first_adj_index
  if (now_index == index)
    return first_adj_vex(G, index);
  // others
  vertex_node *a_node = G->first_vertex;
  vertex_node *next_adj_vertex = NULL;
  while (a_node != NULL) {
    // find the vertex
    if (a_node->index == index) {
      arc_node *an_arc = a_node->first_arc;
      while (an_arc != NULL) {
        // find the now_index
        if (an_arc->vertex == now_index && an_arc->next != NULL) {
          next_adj_vertex = search_graph(G, an_arc->next->vertex);
          break;
        }
        an_arc = an_arc->next;
      }
      break;
    }
    a_node = a_node->next;
  }
  return next_adj_vertex;
}

int insert_vex(graph *G, int index, int value) {
/* 
 * Function Name: insert_vex
 * Module: Data structures
 * Parameter: graph &G, int index, int value
 * Return: int(statue)
 * Use: insert a vertex in graph
 */

  if (search_graph(G, index) != NULL)
    return ERROR;
  vertex_node *new_vex = (vertex_node*)malloc(sizeof(vertex_node));
  if (new_vex == NULL)
    return ERROR;
  // set new vertex
  G->vertex_num++;
  new_vex->index = index;
  new_vex->value = value;
  new_vex->first_arc = NULL;
  new_vex->next = NULL;
  // insert in the first
  if (G->first_vertex == NULL)
    G->first_vertex = new_vex;
  // insert in behind the lase
  else {
    vertex_node *a_node = G->first_vertex;
    while (a_node->next != NULL)
      a_node = a_node->next;
    a_node->next = new_vex;
  }
  return OK;
}

int delete_vex(graph *G, int index) {
/* 
 * Function Name: delete_vex
 * Module: Data structures
 * Parameter: graph &G, int index
 * Return: int(statue)
 * Use: delete a vertex in graph
 */

  if (search_graph(G, index) == NULL)
    return ERROR;
  G->vertex_num--;

  // delete the arc whose dst is index
  vertex_node *a_node = G->first_vertex;
  while (a_node != NULL) {
    arc_node *an_arc = a_node->first_arc;
    if (an_arc == NULL) {
      a_node = a_node->next;
      continue;
    }
    // if delete the first arc
    if (an_arc->vertex == index) {
      a_node->first_arc = a_node->first_arc->next;
      free(an_arc);
      G->arc_num--;
      a_node = a_node->next;
      continue;
    }
    // find the arc whose dst is index
    while (an_arc->next != NULL) {
      if (an_arc->next->vertex == index) {
        arc_node *tmp_arc = an_arc->next;
        an_arc->next = an_arc->next->next;
        free(tmp_arc);
        G->arc_num--;
        break;
      }
      an_arc = an_arc->next;
    }
    a_node = a_node->next;
  }

  // delete the arc whose src is index
  a_node = G->first_vertex;
  // if delete the first node
  if (a_node->index == index) {
    // free the arcs
    arc_node *an_arc = a_node->first_arc;
    while (an_arc != NULL) {
      arc_node *tmp_arc = an_arc;
      an_arc = an_arc->next;
      free(tmp_arc);
      G->arc_num--;
    }
    // free the vertex
    G->first_vertex = G->first_vertex->next;
    free(a_node);
    return OK;
  }
  while (a_node->next != NULL) {
    // find the vertex to delete
    if (a_node->next->index == index) {
      vertex_node *tmp_node = a_node->next;      
      // free the arcs
      arc_node *an_arc = tmp_node->first_arc;
      while (an_arc != NULL) {
        arc_node *tmp_arc = an_arc;
        an_arc = an_arc->next;
        free(tmp_arc);
        G->arc_num--;
      }
      // free the node
      a_node->next = a_node->next->next;
      free(tmp_node);
    }
    a_node = a_node->next;
  }
  return OK;
}

// assist function to add an arc in graph
void add_an_arc(vertex_node *src_vex, int dst_vex, int weight) {
  arc_node *new_arc = (arc_node*)malloc(sizeof(arc_node));
  new_arc->vertex = dst_vex;
  new_arc->weight = weight;
  new_arc->next = NULL;
  // insert in first
  if (src_vex->first_arc == NULL)
    src_vex->first_arc = new_arc;
  // insert behind the last
  else {
    arc_node *an_arc = src_vex->first_arc;
    while (an_arc->next != NULL)
      an_arc = an_arc->next;
    an_arc->next = new_arc;
  }
}

int insert_arc(graph *G, int src_vex, int dst_vex, int weight) {
/* 
 * Function Name: insert_arc
 * Module: Data structures
 * Parameter: graph &G, int src_vex, int dst_vex, int weight
 * Return: int(statue)
 * Use: insert an arc in graph
 */

  vertex_node *src_vex_node = search_graph(G, src_vex);
  vertex_node *dst_vex_node = search_graph(G, dst_vex);
  if (src_vex_node == NULL || dst_vex_node == NULL)
    return ERROR;
  if (search_arc(G, src_vex, dst_vex) != NULL)
    return ERROR;
  // if the graph is undirected, also add arc "dst to src"
  if (G->kind == UNDIRECTED_GRAPH || G->kind == UNDIRECTED_NET) {
    add_an_arc(dst_vex_node, src_vex, weight);
    G->arc_num++;
  }
  add_an_arc(src_vex_node, dst_vex, weight);
  G->arc_num++;
  return OK;
}

// assist function to delete an arc
void del_an_arc(vertex_node *src_vex, int dst_vex) {
  // if delete first
  if (src_vex->first_arc->vertex == dst_vex) {
    arc_node *tmp_arc = src_vex->first_arc;
    src_vex->first_arc = src_vex->first_arc->next;
    free(tmp_arc);
  }
  // traverse and find the arc
  else {
    arc_node *an_arc = src_vex->first_arc;
    while (an_arc->next != NULL) {
      if (an_arc->next->vertex == dst_vex) {
        arc_node *tmp_arc = an_arc->next;
        an_arc->next = an_arc->next->next;
        free(tmp_arc);
      }
      an_arc = an_arc->next;
    }
  }
}

int delete_arc(graph *G, int src_vex, int dst_vex) {
/* 
 * Function Name: delete_arc
 * Module: Data structures
 * Parameter: graph &G, int src_vex, int dst_vex
 * Return: int(statue)
 * Use: delete an arc in graph
 */

  vertex_node *src_vex_node = search_graph(G, src_vex);
  vertex_node *dst_vex_node = search_graph(G, dst_vex);
  if (src_vex_node == NULL || dst_vex_node == NULL)
    return ERROR;
  if (search_arc(G, src_vex, dst_vex) == NULL)
    return ERROR;
  // if the graph is undirected, also delete the arc "dst to src"
  if (G->kind == UNDIRECTED_GRAPH || G->kind == UNDIRECTED_NET) {
    del_an_arc(dst_vex_node, src_vex);
    G->arc_num--;
  }
  del_an_arc(src_vex_node, dst_vex);
  G->arc_num--;
  return OK;
}

// assist function to get a vertex's position
int get_vex_pos(graph *G, int index) {
  int pos = 0;
  vertex_node *a_node = G->first_vertex;
  while (a_node->index != index) {
    pos++;
    a_node = a_node->next;
  }
  return pos;
}

// assist function to epth_First Search traverse
void DFS(graph *G, vertex_node *vertex, int *visit, int pos) {
  visit[pos] = 1;
  printf("Index: %d, value %d\n", vertex->index, vertex->value);
  vertex_node *a_node = NULL;
  for (a_node = first_adj_vex(G, vertex->index); a_node != NULL; 
  a_node = next_adj_vex(G, vertex->index, a_node->index)) {
    int pos = get_vex_pos(G, a_node->index);
    // if not visited, just visit it
    if (!visit[pos])
      DFS(G, a_node, visit, pos);
   }
}

int dfs_traverse(graph *G) {
/* 
 * Function Name: dfs_traverse
 * Module: Data structures
 * Parameter: graph &G
 * Return: int(statue)
 * Use: Depth_First Search traverse the graph
 */

  vertex_node *a_node = G->first_vertex;
  if (a_node == NULL)
    return ERROR;
  int pos = 0;
  int *visit = (int*)malloc(sizeof(int) * G->vertex_num);
  memset(visit, 0, sizeof(int) * G->vertex_num);
  printf("Graph: %d\n", G->id);
  printf("DFS traverse:\n");
  printf("Vertex num: %d\n", G->vertex_num);
  while (a_node != NULL) {
    if (!visit[pos])
      DFS(G, a_node, visit, pos);
    a_node = a_node->next;
    pos++;
  }
  return OK;
}

int bfs_traverse(graph *G) {
/* 
 * Function Name: bfs_traverse
 * Module: Data structures
 * Parameter: graph &G
 * Return: int(statue)
 * Use: Broadth_First Search traverse the graph
 */

  vertex_node *traverse_node = G->first_vertex;
  vertex_node *node = NULL;
  if (traverse_node == NULL)
    return ERROR;
  int pos = 0;
  int *visit = (int*)malloc(sizeof(int) * G->vertex_num);
  memset(visit, 0, sizeof(int) * G->vertex_num);
  LinkQueue my_node_queue;
  InitQueue(&my_node_queue);
  printf("Graph: %d\n", G->id);
  printf("BFS traverse:\n");
  printf("Vertex num: %d\n", G->vertex_num);
  // use a queue to bfs traverse the graph
  while (traverse_node != NULL) {
    if (!visit[pos]) {
      visit[pos] = 1;
      EnQueue(&my_node_queue, traverse_node);
      while (!IsEmpty(&my_node_queue)) {
        node = DeQueue(&my_node_queue);
        printf("Index: %d, value %d\n", node->index, node->value);
        vertex_node *a_node = NULL;
        for (a_node = first_adj_vex(G, node->index); a_node != NULL; 
        a_node = next_adj_vex(G, node->index, a_node->index)) {
          int next_pos = get_vex_pos(G, a_node->index);
          // if not visited, just visit it
          if (!visit[next_pos]) {
            visit[next_pos] = 1;
            EnQueue(&my_node_queue, a_node);
          }
        }
      }
    }
    traverse_node = traverse_node->next;
    pos++;
  }
  return OK;
}