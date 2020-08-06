#include "lemin.h"

void print_tab(t_lemin *lemin)
{
  int position = 0;
  t_node *list;

  list = lemin->tab[0];
  while (position < lemin->table_size)
  {
    if (lemin->tab[position] == NULL)
      printf("list is NULL\n");
    else
    {
      list = lemin->tab[position];
      printf("[%d] Name: %s coord: %d-%d\n", position, list->name, list->x, list->y);
    }
    list = lemin->tab[position++];
  }
}

char lookup(t_lemin *lemin, char* key)
{
  int position;
  t_node *list;

  position = hash_code(lemin, key);
  list = lemin->tab[position];
  if (ft_strstr(list->name,key))
      return (list->weight);
  return (-1);
}
