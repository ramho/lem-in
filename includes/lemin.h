#ifndef LEMIN_H
# define LEMIN_H

# include "../libft/libft.h"
# include <stdio.h>
# include <time.h>
# define LEMIN_READ_BUFF 1
# define LINE_SIZE 100
# define HASH_SIZE 1000000

//# define PLUS_GRAND INT_MAX

typedef struct s_path
{
  char *name;
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
  unsigned long key; // for hash map but name can also be the key
  char *name;
  int type; // 1 is start and 2 is end
  int x;
  int y;
  int reach_cost;
  int infinity;
  char *predecessor;
  struct s_node *next;
  t_link *links; // linked list for links
}               t_node;

typedef struct s_edge
{
    t_node *predecessor;
    t_node *successor;
    int weight;
    int visited;
	struct s_edge *next;
}              t_edge;

typedef struct  s_lemin
{
	int ret;
	char buff[LEMIN_READ_BUFF + 1];
	int i; // index in buff
	char line[LINE_SIZE];
	int i_line; // index in line
	char parse_flag;
	char end_buff;
	int rest;
	int end_line;
	int	hash_tag;
	int	space;
	char get_out;
	// int first_space;
	int	tiret;
	char start_room;
	char end_room;
	// int count_buff;
	// int hash_map[HASH_SIZE];
	int x;
	int y;

    int nb_ants;
    char **file;
    int table_size;

    // char *start_node;
    // char *end_node;
	int	nb_start_out;
	int	nb_end_in;

    char **file_edges; //save only links
    char **file_nodes; // save only nodes
    int number_of_nodes; // count of nodes
    int number_of_edges;

    t_node *node_tab[HASH_SIZE + 1];
	t_node start_node;
	t_node end_node;

    t_edge *edge_tab;
    char **node_name;

    // t_path *head;
    t_path **path_tab;
    int nb_path;// not is use yet

    t_path **final_path_tabs;
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
void reduce(t_lemin *lemin);
void try_reduce(char* pre, char* sec, int w, t_lemin *lemin);
void init_infinity(t_lemin *lemin);

/*
**  algo2.c
*/
void save_path(t_lemin *lemin, int index_path);
void modify_graph_for_bhandari(t_lemin *lemin, int path_index);

/*
**  get_path.c
*/
void get_path(t_lemin *lemin);
char *recursive_get_path(t_lemin *lemin, char *pre_node, t_path * head);

/*
**  extra_func.cs
*/
char lookup(t_lemin *lemin, char* key);
void print_tab(t_lemin *lemin);
void shortest_path(t_lemin *lemin);
void printf_current_reach_cost(t_lemin *lemin, int iteration);

#endif
