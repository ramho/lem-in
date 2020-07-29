#include "lemin.h"

void get_room(char *line, t_lemin *lemin, t_node *root)
{
  int i;
  int j;
  t_node temp;
  t_node *ptr;

  i = 0;
  while (i < ft_strlen(line))
  {
    while (line[i] != ' ')
      i++;
    printf("test 111\n");
    temp.name = ft_strsub(line, 0, i);
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
    printf("test 222\n");
    temp.x = ft_atoi(&line[i + 1]);
    printf("test 333\n");
    i = i + (ft_numlen(temp.x) + 1);
    j = i;
    while (line[j] != '\0')
    {
      if (ft_isdigit(line[j]))
      j++;
      else
        exit(0); // error non digit
    }
    printf("test 444\n");
    temp.y = ft_atoi(&line[i]);
    printf("test 555\n");
    i = i + (ft_numlen(temp.y) + 1);
  }
  temp.next = NULL;
  if (root == NULL)
    root = &temp;
  else
  {
    ptr = root;
    while (ptr->next != NULL)
      ptr = ptr->next;
    ptr->next = &temp;
  }
}

void get_start_or_end_piece(int *i, t_lemin *lemin, t_node *root)
{
  int j;

  j = 0;
  if (ft_strstr(lemin->file[*i], "start"))
  {
    printf("%s\n", lemin->file[*i + 1]);
    get_room(lemin->file[*i + 1], lemin, root);
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
