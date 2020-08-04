#include "lemin.h"

void get_room(char *line, t_lemin *lemin, t_node **root)
{
  int i;
  int j;
  t_node *temp;
  t_node *ptr;

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
        exit(0); // error non digit
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
        exit(0); // error non digit
      }
    }
    temp->y = ft_atoi(&line[i]);
    i = i + (ft_numlen(temp->y) + 1);
  }
  temp->next = NULL;
  if ((*root) == NULL)
    (*root) = temp;
  else
  {
    printf("root is already taken\n");
    ptr = (*root);
    while (ptr->next != NULL)
      ptr = ptr->next;
    ptr->next = temp;
  }
}

void get_start_or_end_piece(int *i, t_lemin *lemin, t_node **root)
{
  int j;

  j = 0;
  if (ft_strstr(lemin->file[*i], "start"))
  {
    ft_printf("%s\n", lemin->file[*i + 1]);
    get_room(lemin->file[*i + 1], lemin, root);
  }
  if (ft_strstr(lemin->file[*i], "end"))
  {
      ft_printf("%s\n", lemin->file[*i + 1]);
      get_room(lemin->file[*i + 1], lemin, root);
  }
  *i = *i + 1;
}

void get_links()
{
}
