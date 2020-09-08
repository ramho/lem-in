#include "../includes/lemin.h"

void bellman_ford(t_lemin *lemin)
{
	int i;
	int j;

	i = 0;
	while (i < lemin->number_of_nodes)
	{
		j = 0;
		while (j < lemin->number_of_edges)
		{
			if (ft_strcmp(lemin->node_tab[i]->name, lemin->edge_tab[j]->predecessor) == 0)
				try_reduce(lemin->node_tab[i], lemin->edge_tab[j]->successor,
					lemin->edge_tab[j]->weight, lemin);
			j++;
		}
		i++;
	}
}

void try_reduce(t_node *pre, char *sec, int w, t_lemin *lemin)
{
	int i;
	int pre_index;
	int sec_index;
	t_node *pre_node;

	i = 0;
	if (pre->duplicated == 1)
			pre_node = pre->dup_out;
	else
		pre_node = pre;
	//but in a hashtable instead of looping through the table
	while (i < lemin->number_of_nodes)
	{
		if (ft_strcmp(pre_node->name,lemin->node_tab[i]->name) == 0)
			pre_index = i; // keeping index of predecessor
		if (ft_strcmp(sec, lemin->node_tab[i]->name) == 0)
			sec_index = i; // keeping index of successor
		i++;
	}
	//changes values in reducing graph
	if (pre_node->infinity == 0 && lemin->node_tab[sec_index]->infinity == 1) // if not yet passed to the second node
	{
		lemin->node_tab[sec_index]->reach_cost = pre_node->reach_cost + w;
		lemin->node_tab[sec_index]->infinity = 0;
		lemin->node_tab[sec_index]->predecessor = ft_strdup(pre_node->name);

	}
	if (pre_node->infinity  == 0 && lemin->node_tab[sec_index]->infinity == 0) // if both nodes have already been connected to a previous one
	{
		if (lemin->node_tab[sec_index]->reach_cost > (pre_node->reach_cost + w))
		{
			lemin->node_tab[sec_index]->reach_cost = pre_node->reach_cost + w;
			ft_strdel(&lemin->node_tab[sec_index]->predecessor);
			lemin->node_tab[sec_index]->predecessor = ft_strdup(pre_node->name);
		}
	}
}
