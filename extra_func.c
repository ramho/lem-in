#include "liemin.h"

void print_list(t_lemin *lemin, char *key)
{
  int position = 0;
  t_node *list;

  list = lemin->list[0];
  while (position < lemin->table_size)
  {
    if (lemin->list[position] == NULL)
      printf("list is NULL\n");
    else
    {
      list = lemin->list[position];
      printf("Name: %s coord: %d-%d\n", list->name, list->x, list->y);
    }
    list = lemin->list[position++];
  }
}

char lookup(t_lemin *lemin, char* key)
{
  int position;
  t_node *list;
  t_node *temp;

  position = hash_code(lemin, key);
  list = lemin->list[position];
  temp = list;
  while (temp)
  {
    if (temp->name == key)
      return (temp->x);
    temp = temp->next;
  }
  return (-1);
}
