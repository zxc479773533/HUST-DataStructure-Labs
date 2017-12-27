/*
 * AUTHOR: Yue Pan
 * GITHUB: zxc479773533
 * E-MAIL: zxc479773533@gmail.com
 */

#include "main.h"

void print_menu(void) {
/* 
 * Function Name: print_menu
 * Module: Main control
 * Parameter: None
 * Return: None
 * Use: print the menu
 */

  printf("+--------------------------------------------------------------------+\n");
  printf("|               Welcome to panyue's graph demo system!               |\n");
  printf("|               Here are some functions you can call:                |\n");
  printf("|                                                                    |\n");
  printf("|              1: creat_graph            2: destory_graph            |\n");
  printf("|              3: locate_vex             4: get_vex_value            |\n");
  printf("|              5: set_vex_value          6: set_arc_weight           |\n");
  printf("|              7: first_adj_vex          8: next_adj_vex             |\n");
  printf("|              9: insert_vex            10: delete_vex               |\n");  
  printf("|             11: insert_arc            12: delete_arc               |\n");
  printf("|             13: dfs_traverse          14: bfs_traverse             |\n");
  printf("|             15: ls_list                0: quit                     |\n");
  printf("|                                                                    |\n");
  printf("|Enter the number of the function and see the usage and call it!     |\n");
  printf("|Enter 0 to quit the demo system.                                    |\n");
  printf("|                                                                    |\n");
  printf("|Copyrite (C) 2017 Yue Pan                                           |\n");
  printf("|Github: zxc479773533                                                |\n");
  printf("+--------------------------------------------------------------------+\n");
  printf("\n");
  printf("Your choose: ");
}

void load_data(Graph_main *Main_G) {
/* 
 * Function Name: load_data
 * Module: Main control
 * Parameter: Graph_main *Main_T
 * Return: None
 * Use: load link list from database
 */

  // open data file
  FILE *fp = fopen("graphdb", "rb");
  if (fp == NULL)
    return ;

  graph graphs, *a_graph = &graphs;
  a_graph->next = NULL;

  int size = 0xff;
  while (1) {
    Graph_store def;
    graph *tmp_graph = NULL;
    size = fread(&def, sizeof(Graph_store), 1, fp);
    if (size == 0)
      break;

    tmp_graph = (graph*)malloc(sizeof(graph));
    memset(tmp_graph, 0, sizeof(graph));
    
    fread(def.v_indexs, sizeof(int) * def.vertex_num, 1, fp);
    fread(def.v_values, sizeof(int) * def.vertex_num, 1, fp);
    fread(def.a_matrix, sizeof(int) * def.vertex_num * def.vertex_num, 1, fp);
    creat_graph(tmp_graph, def.kind, def.vertex_num, def.arc_num, def.v_indexs, def.v_values, def.a_matrix);

    tmp_graph->id = def.id;
    tmp_graph->next = NULL;
    a_graph->next = tmp_graph;
    a_graph = a_graph->next;
  }

  Main_G->head = graphs.next;

  // close file
  fclose(fp);
}

// assist function to save graph
void traverse_and_save(graph *G, int *indexs, int* values, int *matrix, int size) {
  vertex_node *a_node = G->first_vertex;
  int pos = 0;
  while (a_node != NULL) {
    indexs[pos] = a_node->index;
    values[pos] = a_node->value;
    arc_node *an_arc = a_node->first_arc;
    while (an_arc != NULL) {
      *(matrix + pos * size + get_vex_pos(G, an_arc->vertex)) = an_arc->weight;
      an_arc = an_arc->next;
    }
    pos++;
    a_node = a_node->next;
  }
}

void save_data(Graph_main *Main_G) {
/* 
 * Function Name: save_data
 * Module: Main control
 * Parameter: Graph_main *Main_T
 * Return: None
 * Use: save link list from database
 */

  // open data files
  FILE *fp = fopen("graphdb", "wb");
  if (fp == NULL)
    return ;
  
  graph *a_graph = Main_G->head;
  while (a_graph != NULL) {
    Graph_store def;
    def.id = a_graph->id;
    def.kind = a_graph->kind;
    def.vertex_num = a_graph->vertex_num;
    def.arc_num = a_graph->arc_num;
    def.v_indexs = (int*)malloc(sizeof(int) * def.vertex_num);
    def.v_values = (int*)malloc(sizeof(int) * def.vertex_num);
    def.a_matrix = (int*)malloc(sizeof(int) * def.vertex_num * def.vertex_num);
    memset(def.a_matrix, 0, sizeof(int) * def.vertex_num * def.vertex_num);
    traverse_and_save(a_graph, def.v_indexs, def.v_values, def.a_matrix, def.vertex_num);
    fwrite(&def, sizeof(Graph_store), 1, fp);
    fwrite(def.v_indexs, sizeof(int) * def.vertex_num, 1, fp);
    fwrite(def.v_values, sizeof(int) * def.vertex_num, 1, fp);
    fwrite(def.a_matrix, sizeof(int) * def.vertex_num * def.vertex_num, 1, fp);
    a_graph = a_graph->next;
  }

  // close file
  fclose(fp);
}

int main(void) {
  // a variable to save the function choose
  int function_choose = 0xff;

  while (function_choose != 0) {

    // print the menu
    print_menu();
    scanf("%d", &function_choose);
    Graph_main Main_G;
    Main_G.head = NULL;
    load_data(&Main_G);

    // some variable to save the parameters
    int id, kind, v_num, a_num, index, value, src, dst, weight;
    graph *G = NULL;

    switch(function_choose) {
      case 1:
        printf("/*\n");
        printf(" * Function Name: creat_graph\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: graph &G, int v_num, int kind,\n");
        printf(" * int a_num, int *v_indexs, int *v_values, int *a_matrix\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: create a graph\n");
        printf(" */\n");
        printf("\n");
        printf("                                              Format: id kind v_num a_num\n");
        printf("Then, enter the graph id, kind, vertex num, arc num : ");

        scanf("%d %d %d %d", &id, &kind, &v_num, &a_num);
        G = Main_G.head;
        while (G != NULL) {
          if (G->id == id)
            break;
          G = G->next;
        }
        if (G != NULL) {
          printf("Creat error, this graph is already exists!\n");
        }
        else {
          int *v_indexs = (int*)malloc(sizeof(int) * v_num);
          int *v_values = (int*)malloc(sizeof(int) * v_num);
          int *a_matrix = (int*)malloc(sizeof(int) * v_num * v_num);
          printf("Please enter the node info (Format: index value):\n");
          for (int i = 0; i < v_num; i++) { scanf("%d %d", &v_indexs[i], &v_values[i]); }
          printf("please enter the adjacency matrix:\n");
          for (int i = 0; i < v_num; i++) {
            for (int j = 0; j < v_num; j++) { scanf("%d", a_matrix + i * v_num + j); }
          }
          graph new_G;
          creat_graph(&new_G, kind, v_num, a_num, v_indexs, v_values, a_matrix);
          printf("Create graph %d succeed!\n", id);
          new_G.id = id;
          new_G.next = Main_G.head;
          Main_G.head = &new_G;
        }

        printf("\n");
        break;

      case 2:
        printf("/*\n");
        printf(" * Function Name: destory_graph\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: graph &G\n");
        printf(" * Return: int(status)\n");
        printf(" * Use: destory a graph\n");
        printf(" */\n");
        printf("\n");
        printf("Then, enter the graph id: ");

        scanf("%d", &id);
        G = Main_G.head;
        if (G->id == id) {
          Main_G.head = Main_G.head->next;
          destory_graph(G);
          printf("Graph %d has been delected!", id);
          printf("\n");
          break;
        }
        else {
          while (G->next != NULL) {
            if (G->next->id == id)
              break;
            G = G->next;
          }
        }
        if (G->next == NULL) {
          printf("Destory error, this graph is not exists!\n");
        }
        else {
          graph *to_be_del = G->next;
          G->next = G->next->next;
          destory_graph(to_be_del);
          printf("Graph %d has been deleted!\n", id);
        }

        printf("\n");
        break;

      case 3:
        printf("/*\n");
        printf(" * Function Name: locate_vex\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: graph *G, int value\n");
        printf(" * Return: int(the index)\n");
        printf(" * Use: find a vertex in graph\n");
        printf(" */\n");
        printf("\n");
        printf("                                   Format: id value\n");
        printf("Then, enter the graph id and vertex value: ");

        scanf("%d %d", &id, &value);
        G = Main_G.head;
        while (G != NULL) {
          if (G->id == id)
            break;
          G = G->next;
        }
        if (G == NULL) {
          printf("Error, this graph is not exists!\n");
        }
        else {
          printf("The index is %d.\n", locate_vex(G, value));
        }

        printf("\n");
        break;

      case 4:
        printf("/*\n");
        printf(" * Function Name: get_vex_value\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: graph *G, int index\n");
        printf(" * Return: int(the index)\n");
        printf(" * Use: find a value of a vertex\n");
        printf(" */\n");
        printf("\n");
        printf("                                   Format: id index\n");
        printf("Then, enter the graph id and vertex index: ");

        scanf("%d %d", &id, &index);
        G = Main_G.head;
        while (G != NULL) {
          if (G->id == id)
            break;
          G = G->next;
        }
        if (G == NULL) {
          printf("Error, this graph is not exists!\n");
        }
        else {
          printf("The value of %d is %d.\n", index, get_vex_value(G, index));
        }

        printf("\n");
        break;

      case 5:
        printf("/*\n");
        printf(" * Function Name: set_vex_value\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: graph &G, int index, int value\n");
        printf(" * Return: int(the index)\n");
        printf(" * Use: set a vertex's value\n");
        printf(" */\n");
        printf("\n");
        printf("                                          Format: id index value\n");
        printf("Then, enter the graph id, vertex index and value: ");

        scanf("%d %d %d", &id, &index, &value);
        G = Main_G.head;
        while (G != NULL) {
          if (G->id == id)
            break;
          G = G->next;
        }
        if (G == NULL) {
          printf("Error, this graph is not exists!\n");
        }
        else {
          if (set_vex_value(G, index, value) == OK) {
            printf("Set value %d of index %d succeed!\n", value, index);
          }
          else {
            printf("Error, the index %d is not exists!\n", index);
          }
        }

        printf("\n");
        break;

      case 6:
        printf("/*\n");
        printf(" * Function Name: set_arc_weight\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: graph *G, int src_index, int dst_index, int weight\n");
        printf(" * Return: int(the index)\n");
        printf(" * Use: set an arc's weight\n");
        printf(" */\n");
        printf("\n");
        printf("                                                     Format: id src_index dst_index weight\n");
        printf("Then, enter the graph id, src and dst index, and arc weight: ");

        scanf("%d %d %d %d", &id, &src, &dst, &weight);
        G = Main_G.head;
        while (G != NULL) {
          if (G->id == id)
            break;
          G = G->next;
        }
        if (G == NULL) {
          printf("Error, this graph is not exists!\n");
        }
        else {
          if (set_arc_weight(G, src, dst, weight) == OK) {
            printf("Set the arc between %d and %d weight %d succeed!\n", src, dst, weight);
          }
          else {
            printf("Set error, this arc is not exists!\n");
          }
        }

        printf("\n");
        break;

      case 7:
        printf("/*\n");
        printf(" * Function Name: first_adj_vex\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: graph &G, int index\n");
        printf(" * Return: vertex_node*(the first vertex)\n");
        printf(" * Use: get the fitst adjacency vertex\n");
        printf(" */\n");
        printf("\n");
        printf("                            Format: id index\n");
        printf("Then, enter the graph id and index: ");

        scanf("%d %d", &id, &index);
        G = Main_G.head;
        while (G != NULL) {
          if (G->id == id)
            break;
          G = G->next;
        }
        if (G == NULL) {
          printf("Error, this graph is not exists!\n");
        }
        else {
          vertex_node *first_adj_vertex = first_adj_vex(G, index);
          if (first_adj_vertex == NULL) {
            printf("Error, the required vertex is not exists!\n");
          }
          else {
            printf("The first adjacency vertex of %d is %d.\n", index, first_adj_vertex->index);
          }
        }

        printf("\n");
        break;

      case 8:
        printf("/*\n");
        printf(" * Function Name: next_adj_vex\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: graph &G, int index, int now_index\n");
        printf(" * Return: vertex_node*(the next vertex)\n");
        printf(" * Use: get the next adjacency vertex\n");
        printf(" */\n");
        printf("\n");
        printf("                                       Format: id index now_index\n");
        printf("Then, enter the graph id, index and now index: ");

        int now_index;
        scanf("%d %d %d", &id, &index, &now_index);
        G = Main_G.head;
        while (G != NULL) {
          if (G->id == id)
            break;
          G = G->next;
        }
        if (G == NULL) {
          printf("Error, this graph is not exists!\n");
        }
        else {
          vertex_node *next_adj_vertex = next_adj_vex(G, index, now_index);
          if (next_adj_vertex == NULL) {
            printf("Error, the required vertex is not exists!\n");
          }
          else {
            printf("The nex adjacency vertex is %d.\n", next_adj_vertex->index);
          }
        }

        printf("\n");
        break;

      case 9:
        printf("/*\n");
        printf(" * Function Name: insert_vex\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: graph *G, int index, int value\n");
        printf(" * Return: int(statue)\n");
        printf(" * Use: insert a vertex in graph\n");
        printf(" */\n");
        printf("\n");
        printf("                                   Format: id index value\n");
        printf("Then, enter the graph id, index and value: ");

        scanf("%d %d %d", &id, &index, &value);
        G = Main_G.head;
        while (G != NULL) {
          if (G->id == id)
            break;
          G = G->next;
        }
        if (G == NULL) {
          printf("Error, this graph is not exists!\n");
        }
        else {
          if (insert_vex(G, index, value) == OK) {
            printf("Insert vertex %d succeed!\n", index);
          }
          else {
            printf("Error, please check your input!\n");
          }
        }

        printf("\n");
        break;

      case 10:
        printf("/*\n");
        printf(" * Function Name: delete_vex\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: graph &G, int index\n");
        printf(" * Return: int(statue)\n");
        printf(" * Use: delete a vertex in graph\n");
        printf(" */\n");
        printf("\n");
        printf("                            Format: id index\n");
        printf("Then, enter the graph id and index: ");

        scanf("%d %d", &id, &index);
        G = Main_G.head;
        while (G != NULL) {
          if (G->id == id)
            break;
          G = G->next;
        }
        if (G == NULL) {
          printf("Error, this graph is not exists!\n");
        }
        else {
          if (delete_vex(G, index) == OK) {
            printf("Delete vertex %d succeed!\n", index);
          }
          else {
            printf("Error, this vertex is not exists!\n");
          }
        }

        printf("\n");
        break;

      case 11:
        printf("/*\n");
        printf(" * Function Name: insert_arc\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: graph &G, int src_vex, int dst_vex, int weight\n");
        printf(" * Return: int(statue)\n");
        printf(" * Use: insert an arc in graph\n");
        printf(" */\n");
        printf("\n");
        printf("                                                 Format: id src_index dst_index weight\n");
        printf("Then, enter the graph id, src and dst index, and weight: ");

        scanf("%d %d %d %d", &id, &src, &dst, &weight);
        G = Main_G.head;
        while (G != NULL) {
          if (G->id == id)
            break;
          G = G->next;
        }
        if (G == NULL) {
          printf("Error, this graph is not exists!\n");
        }
        else {
          if (insert_arc(G, src, dst, weight) == OK) {
            printf("Insert arc between %d and %d weight %d succeed!\n", src, dst, weight);
          }
          else {
            printf("Error, please check your input!\n");
          }
        }

        printf("\n");\
        break;

      case 12:
        printf("/*\n");
        printf(" * Function Name: delete_arc\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: graph &G, int src_vex, int dst_vex\n");
        printf(" * Return: int(statue)\n");
        printf(" * Use: delete an arc in graph\n");
        printf(" */\n");
        printf("\n");
        printf("                                     Format: id src_index dst_index weight\n");
        printf("Then, enter the graph id, src and dst index: ");

        scanf("%d %d %d", &id, &src, &dst);
        G = Main_G.head;
        while (G != NULL) {
          if (G->id == id)
            break;
          G = G->next;
        }
        if (G == NULL) {
          printf("Error, this graph is not exists!\n");
        }
        else {
          if (delete_arc(G, src, dst) == OK) {
            printf("Delete the arc between %d and %d succeed!\n", src, dst);
          }
          else {
            printf("Error, this arc is not exists!\n");
          }
        }

        printf("\n");
        break;

      case 13:
        printf("/*\n");
        printf(" * Function Name: dfs_traverse\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: graph &G\n");
        printf(" * Return: int(statue)\n");
        printf(" * Use: Depth_First Search traverse the graph\n");
        printf(" */\n");
        printf("\n");
        printf("Then, enter the graph id: ");

        scanf("%d", &id);
        G = Main_G.head;
        while (G != NULL) {
          if (G->id == id)
            break;
          G = G->next;
        }
        if (G == NULL) {
          printf("Error, this graph is not exists!\n");
        }
        else {
          if (dfs_traverse(G) == ERROR)
            printf("Error, this graph is empty!\n");
        }

        printf("\n");
        break;

      case 14:
        printf("/*\n");
        printf(" * Function Name: bfs_traverse\n");
        printf(" * Module: Data structures\n");
        printf(" * Parameter: graph &G\n");
        printf(" * Return: int(statue)\n");
        printf(" * Use: Broadth_First Search traverse the graph\n");
        printf(" */\n");
        printf("\n");
        printf("Then, enter the graph id: ");

        scanf("%d", &id);
        G = Main_G.head;
        while (G != NULL) {
          if (G->id == id)
            break;
          G = G->next;
        }
        if (G == NULL) {
          printf("Error, this graph is not exists!\n");
        }
        else {
          if (bfs_traverse(G) == ERROR)
            printf("Error, this graph is empty!\n");
        }

        printf("\n");
        break;
      
      case 15:
        G = Main_G.head;
        while (G != NULL) {
          printf("ID: %d\n", G->id);
          G = G->next;
        }

        printf("\n");
        break;
      
      case 0:
        printf("Thanks for using my demo system!\n");
        break;
      
      default:
        printf("You entered the wrong num, please re-enter the num.\n");
        break;
    }

    save_data(&Main_G);
  }

  return 0;
}