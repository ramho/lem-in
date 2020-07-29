#include "lemin.h"

void get_room(char *line, t_lemin *lemin)
{
  int i;
  int j;

  i = 0;
  while (i < ft_strlen(line))
  {
    while (line[i] != ' ')
      i++;
    lemin->node->name = ft_strsub(line, 0, i);
    //check if digit else error
    j = i + 1;
    while ( line[j] != ' ')
    {
      if (ft_isdigit(line[j]))
      j++;
      else
      {
        ft_printf("ERROR\n");
        exit(0); // error non digit
      }
    }
    lemin->node->x = ft_atoi(&line[i + 1]);
    i = i + (ft_numlen(lemin->node->x) + 1);
    j = i;
    while (line[j] != '\0')
    {
      if (ft_isdigit(line[j]))
      j++;
      else
        exit(0); // error non digit
    }
    lemin->node->y = ft_atoi(&line[i]);
    i = i + (ft_numlen(lemin->node->y) + 1);
  }
}

void get_start_or_end_piece(int *i, t_lemin *lemin)
{
  int j;

  j = 0;
  if (ft_strstr(lemin->file[*i], "start"))
  {
    printf("%s\n", lemin->file[*i + 1]);
    get_room(lemin->file[*i + 1], lemin);
    // while ( j < ft_strlen(lemin->line[*i + 1]))
    // {
    //   while()
    //   j++;
    // }
  }
  // if (ft_strstr(lemin->file[*i], "end"))
  // {
  //     printf("%s\n", lemin->file[*i + 1]);
  //     get_room(lemin->file[*i + 1], lemin);
  // }
  *i = *i + 1;
}

void get_links()
{
}
