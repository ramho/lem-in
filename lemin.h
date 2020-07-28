#ifndef LEMIN_H
# define LEMIN_H

# include "libft/libft.h"
# include <stdio.h>


typedef struct  s_lemin
{
    char **file;
}               t_lemin;

int main();
void get_file_content(t_lemin *lemin);
void parse_file(t_lemin *lemin);

void get_start_or_end_piece(t_lemin *lemin);
void get_links(t_lemin *lemin);
void get_rooms(t_lemin *lemin);



#endif
