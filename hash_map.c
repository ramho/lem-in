#include "lemin.h"

void create_table(int size, t_lemin *lemin)
{
  int i;

  lemin->table_size = size;
  lemin->tab = malloc(sizeof(t_node *) * size);
  i = -1;
  while (i++ < size)
    lemin->tab[i] = NULL;
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
  t_node *new_node;
  int i;

  // printf("name of node sent %s\n", node->name);
  i = -1;
  position = hash_code(lemin, node->name);
  new_node = malloc(sizeof(t_node));
  new_node = node;
  new_node->key = position;

  new_node->link = malloc(sizeof(char *) * 1000);
  i = -1;
  while (i++ < 5) // number can be count
    new_node->link[i] = NULL;
  lemin->tab[position] = new_node;
}
