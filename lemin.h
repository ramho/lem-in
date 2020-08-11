#ifndef LEMIN_H
# define LEMIN_H

# include "libft/libft.h"
# include <stdio.h>

# define PLUS_GRAND INT_MAX

typedef struct s_node
{
  int key; // for hash map but name can also be the key
  char *name;
  char *type;
  int x;
  int y;
  int reach_cost;
  int infinity;
  // char **link; // linked list for links
}               t_node;

typedef struct edges
{
    char *predecessor;
    char *successor;
    int weight;
}              t_edges;

typedef struct  s_lemin
{
    int nb_ants;
    char **file;
    int table_size;
    char **file_links; //save only links lines

    int start_end;

    int number_of_nodes; // count of nodes
    int number_of_edges;

    t_node **node_tab;
    t_edges **edges_tab;
    char **node_name;
}               t_lemin;

/*
**  main.c
*/
int main();
void get_file_content(t_lemin *lemin);
void parse_file(t_lemin *lemin);

/*
**  parse_file.c
*/
void get_start_or_end_piece(int *i, t_lemin *lemin);
void get_room(char *line, t_lemin *lemin);

/*
**  hash_map.c
*/
void create_table(t_lemin *lemin);
int hash_code(t_lemin *lemin, char* key);
void insert_node_in_table(t_lemin *lemin, t_node *node);

/*
**  extra_func.c
*/
char lookup(t_lemin *lemin, char* key);
void print_tab(t_lemin *lemin);
void shortest_path();
void printf_current_reach_cost(int iteration);

/*
**  parse_links.c
*/
void get_links(t_lemin *lemin);
void save_links(char *edge1, char *edge2, t_lemin *lemin);

/*
**  algo.c
*/
void start_algo(t_lemin *lemin);



#endif
