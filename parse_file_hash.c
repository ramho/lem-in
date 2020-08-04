#include "lemin.h"

void get_room(char *line, t_lemin *lemin)
{
  int i;
  int j;
  t_node *temp;

printf("in get room, line --> %s\n", line);
  i = 0;
  temp = malloc(sizeof(t_node));
  while (i < ft_strlen(line))
  {
    while (line[i] != ' ')
      i++;
    temp->name = ft_strsub(line, 0, i);
    j = i + 1;
    while ( line[j] != ' ')
    {
      if (ft_isdigit(line[j]))
      j++;
      else
      {
        ft_printf("ERROR x\n");
        exit(0);
      }
    }
    temp->x = ft_atoi(&line[i + 1]);
    i = i + (ft_numlen(temp->x) + 1);
    j = i + 1;
    while (line[j] != '\0')
    {
      if (j <= ft_strlen(line) && ft_isdigit(line[j]))
        j++;
      else
      {
        ft_printf("ERROR y\n");
        exit(0);
      }
    }
    temp->y = ft_atoi(&line[i]);
    i = i + (ft_numlen(temp->y) + 1);
  }
 insert_node_in_table(lemin, temp);
}

void get_start_or_end_piece(int *i, t_lemin *lemin)
{
  int j;

  j = 0;
  if (ft_strstr(lemin->file[*i], "start"))
    get_room(lemin->file[*i + 1], lemin);
  if (ft_strstr(lemin->file[*i], "end"))
      get_room(lemin->file[*i + 1], lemin);
  *i = *i + 1;
}

void get_links()
{
  printf("getting links\n");
}
