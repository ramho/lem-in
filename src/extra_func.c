#include "../includes/lemin.h"

void print_tab(t_lemin *lemin)
{
	int position = 0;

	while (position < lemin->table_size)
	{
		if (lemin->node_tab[position] == NULL)
			printf("[%d] list is NULL\n", position);
		else
		{
			printf("[%d] name %s infinity %d\n", position, lemin->node_tab[position]->name, lemin->node_tab[position]->infinity);
		}
		position++;
	}
}

// char lookup(t_lemin *lemin, char* key)
// {
//   int position;
//   t_node *list;
//
//   position = hash_code(lemin, key);
//   list = lemin->node_tab[position];
//   if (ft_strstr(list->name,key))
//       return (list->weight);
//   return (-1);
// }



void printf_current_reach_cost(t_lemin *lemin, int iteration)
{
	printf("Current reducing state after iteration %d :\n", iteration);
	int i;

	for (i = 0; i < lemin->number_of_nodes; i++)
	{
		if (lemin->node_tab[i])
			printf("%10s |%10s |%10d\n", lemin->node_tab[i]->name, lemin->node_tab[i]->predecessor->name,lemin->node_tab[i]->reach_cost);
	}
}

// void print_links()
