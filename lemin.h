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
  int weight;
  struct s_node *link; // linked list for links
}               t_node;

typedef struct  s_lemin
{
    int nb_ants;
    char **file;
    int table_size;
    t_node **tab;
}               t_lemin;

/*
**  main.c
*/
int main();
void get_file_content(t_lemin *lemin);
void parse_file(t_lemin *lemin);

/*
**  parse_file_hash.c
*/
void get_start_or_end_piece(int *i, t_lemin *lemin);//, t_node *temp);
void get_links(char *line, t_lemin *lemin);
void get_room(char *line, t_lemin *lemin);//, t_node *temp);

/*
**  hash_map.c
*/
void create_table(int size, t_lemin *lemin);
int hash_code(t_lemin *lemin, char* key);
void insert_node_in_table(t_lemin *lemin, t_node *node);

/*
**  extra_func.c
*/
char lookup(t_lemin *lemin, char* key);
void print_tab(t_lemin *lemin);



#endif
