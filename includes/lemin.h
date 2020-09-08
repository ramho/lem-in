#ifndef LEMIN_H
# define LEMIN_H

# include "../libft/libft.h"
# include <stdio.h> //
# include <time.h> //

typedef struct s_path
{
  struct s_node *node;
  struct s_path * next;
}             t_path;

typedef struct s_link
{
    char *room;
    struct s_link *next;
}              t_link;

// coucou

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

  int collision;
  int duplicated;
  struct s_node *dup_out;
  t_link *links; // linked list for links
}               t_node;

typedef struct edges
{
    char *predecessor;
    char *successor;
    int weight;
    int visited;
}              t_edge;

typedef struct  s_lemin
{

    int nb_ants;
    char **file;
    int table_size;

    char *start_node;
    char *end_node;

    char **file_edges; //save only links
    char **file_nodes; // save only nodes

    int start_end;

    int number_of_nodes; // count of nodes
    int number_of_edges;

    t_node **node_tab;
    t_edge **edge_tab;
    char **node_name;

    // t_path *head;
    t_path **path_tab;
    int nb_path;// not is use yet

    t_path **final_path_tabs;

    //
    float temps1, temps2;
    clock_t t1, t2, t3;
    //
}               t_lemin;

/*
**  main.c
*/
int main();
void get_file_content(t_lemin *lemin);


/*
**  parse_file.c
*/
int parse_file(t_lemin *lemin);
int  seperate_nodes_edges(t_lemin *lemin);
void get_start_or_end_piece(int *i, t_lemin *lemin);
void get_edges( t_lemin *lemin);

/*
** parse_file2.c
*/
void get_nodes(char **tab, t_lemin *lemin);
void fill_node_tab(int i, t_lemin *lemin, t_node *temp);
t_link	*ft_create_link(char *room);
void	ft_push_link_front(t_link **begin_list, char *room);


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
void init_infinity(t_lemin *lemin);
void save_path(t_lemin *lemin, int index_path);

/*
**  suurballe.c
*/
void suurballe(t_lemin *lemin, int path_index);

/*
**  get_path.c
*/
void get_path(t_lemin *lemin);
char *recursive_get_path(t_lemin *lemin, char *pre_node, t_path * head);

/*
**  extra_func.c
*/
char lookup(t_lemin *lemin, char* key);
void print_tab(t_lemin *lemin);
void shortest_path(t_lemin *lemin);
void printf_current_reach_cost(t_lemin *lemin, int iteration);

/*
**  bellman_ford.c
*/
void bellman_ford(t_lemin *lemin);
void try_reduce(t_node *pre, char *sec, int w, t_lemin *lemin);

/*
**  get_path.c
*/
void get_path(t_lemin *lemin);
t_node *recursive_get_path(t_lemin *lemin, t_node *pre_node, t_path * head);

#endif
