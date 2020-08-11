#include "lemin.h"

void create_table(t_lemin *lemin)
{
  int i;

  lemin->node_tab = malloc(sizeof(t_node *) * lemin->table_size);
  i = -1;
  while (i++ < lemin->table_size)
    lemin->node_tab[i] = NULL;
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
  printf("ENTER INSERT NODE------------------ name %s hash code %d\n", node->name, hash_code(lemin, node->name));
  i = -1;
  position = hash_code(lemin, node->name);
  new_node = malloc(sizeof(t_node));
  new_node = node;
  new_node->key = position;
  lemin->node_tab[position] = new_node;
  // printf("name %s\n", lemin->node_tab[position]->name);
}
