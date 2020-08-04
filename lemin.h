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
  int link;
  struct s_node *next;
}               t_node;

typedef struct  s_lemin
{
    int nb_ants;
    char **file;
    int table_size;
    t_node **list;
}               t_lemin;

/*
**  main.c
*/
int main();
void get_file_content(t_lemin *lemin);
void parse_file(t_lemin *lemin);

/*
**  parse_file_hash.c // parse_file_llist.c
*/
// void get_start_or_end_piece(int *i, t_lemin *lemin, t_node **root);
void get_start_or_end_piece(int *i, t_lemin *lemin);
void get_links(t_lemin *lemin);
// void get_room(char *line, t_lemin *lemin, t_node **room);
void get_room(char *line, t_lemin *lemin);

/*
**  hash_map.c
*/
void create_table(int size, t_lemin *lemin);
int hash_code(t_lemin *lemin, char* key);
void insert_node_in_table(t_lemin *lemin, t_node *node);
char lookup(t_lemin *lemin, char* key);



#endif
