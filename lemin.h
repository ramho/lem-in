#ifndef LEMIN_H
# define LEMIN_H

# include "libft/libft.h"
# include <stdio.h>

typedef struct s_node
{
  char *name;
  int x;
  int y;
  int link;
}               t_node;

typedef struct  s_lemin
{
    int nb_ants;
    char **file;
    t_node *node;
}               t_lemin;

int main();
void get_file_content(t_lemin *lemin);
void parse_file(t_lemin *lemin);

void get_start_or_end_piece(int *i, t_lemin *lemin);
void get_links(t_lemin *lemin);
void get_room(char *line, t_lemin *lemin);



#endif
