#ifndef LEMIN_H
# define LEMIN_H

# include "../libft/libft.h"
# include <stdio.h> //

//# define PLUS_GRAND INT_MAX

typedef struct s_path
{
  char *name;
  struct s_path * next;
}             t_path;

typedef struct s_node
{
  int key; // for hash map but name can also be the key
  char *name;
  int type; // 1 is start and 2 is end
  int x;
  int y;
  int reach_cost;
  int infinity;
  char *predecessor;
  // char **link; // linked list for links
}               t_node;

typedef struct edges
{
    char *predecessor;
    char *successor;
    int weight;
}              t_edge;

typedef struct  s_lemin
{
    int nb_ants;
    char **file;
    int table_size;

    char * start_node;
    char *end_node;

    char **file_edges; //save only links
    char **file_nodes; // save only nodes

    int start_end;

    int number_of_nodes; // count of nodes
    int number_of_edges;

    t_node **node_tab;
    t_edge **edge_tab;
    char **node_name;
}               t_lemin;

/*
**  main.c
*/
int main();
void get_file_content(t_lemin *lemin);


/*
**  parse_file.c
*/
void parse_file(t_lemin *lemin);
int  seperate_nodes_edges(t_lemin *lemin);
void get_start_or_end_piece(int *i, t_lemin *lemin);
void get_edges( t_lemin *lemin);

/*
** parse_file2.c
*/
void get_nodes(char **tab, t_lemin *lemin);
void fill_node_tab(int i, t_lemin *lemin, t_node *temp);


/*
**  hash_map.c
*/
void create_table(t_lemin *lemin);
int hash_code(t_lemin *lemin, char* key);
void insert_node_in_table(t_lemin *lemin, t_node *node);

/*
**  algo.c
*/
void start_algo(t_lemin *lemin);
void reduce(t_lemin *lemin);
void try_reduce(char* pre, char* sec, int w, t_lemin *lemin);

/*
**  algo2.c
*/
void write_path(t_lemin *lemin);


/*
**  extra_func.cs
*/
char lookup(t_lemin *lemin, char* key);
void print_tab(t_lemin *lemin);
void shortest_path(t_lemin *lemin);
void printf_current_reach_cost(t_lemin *lemin, int iteration);

#endif