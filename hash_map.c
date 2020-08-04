#include "lemin.h"

void create_table(int size, t_lemin *lemin)
{
  int i;

  lemin->table_size = size;
  lemin->list = malloc(sizeof(t_node *) * size);
  i = -1;
  while (i++ < size)
    lemin->list[i] = NULL;
}

int hash_code(t_lemin *lemin, char *key) // ameliorer!!
{
  int hash_value;
  int c;

  hash_value = 0;
  while ((c = *key++))
    hash_value += c + 19;
  return (hash_value % lemin->table_size);
}

void insert_node_in_table(t_lemin *lemin, t_node *node)
{
  int position;
  t_node *list;
  t_node *new_node;
  t_node *temp;

  position = hash_code(lemin, node->name);
  list = lemin->list[position];
  new_node = malloc(sizeof(t_node));
  temp = list;
  while (temp)
  {
    if (temp->name == node->name)
    {
      temp = node;
      return;
    }
    temp = temp->next;
  }
new_node->key = position;
new_node = node;
new_node->next = list;
lemin->list[position] = new_node;
}

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
      printf("Pos [%d] - Name: %s - Coord: %d-%d\n", hash_code(lemin, list->name), list->name, list->x, list->y);
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
