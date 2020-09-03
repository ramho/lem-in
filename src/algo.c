#include "../includes/lemin.h"

void reduce(t_lemin *lemin)
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
				try_reduce(lemin->node_tab[i]->name, lemin->edge_tab[j]->successor, lemin->edge_tab[j]->weight, lemin);
			j++;
		}
		i++;
	}
}

void try_reduce(char *pre, char *sec, int w, t_lemin *lemin)
{
	int i;
	int pre_index;
	int sec_index;
	int pre_cost_is_infinity;
	int sec_cost_is_infinity;
	int pre_current_cost;
	int sec_current_cost;


	i = 0;
	pre_current_cost = 0;
	sec_current_cost = 0;
	//but in a hashtable instead of looping through the table
	while (i < lemin->number_of_nodes)
	{
		if (ft_strcmp(pre,lemin->node_tab[i]->name) == 0)
		{
			pre_index = i; // keeping index of predecessor
			if (lemin->node_tab[i]->infinity == 1)
				pre_cost_is_infinity = 1;
			else
			{
				pre_cost_is_infinity = 0;
				pre_current_cost = lemin->node_tab[i]->reach_cost;
			}
		}
		if (ft_strcmp(sec, lemin->node_tab[i]->name) == 0)
		{
			sec_index = i; // keeping index of successor
			if (lemin->node_tab[i]->infinity == 1)
				sec_cost_is_infinity = 1;
			else
			{
				sec_cost_is_infinity = 0;
				sec_current_cost = lemin->node_tab[i]->reach_cost;
			}
		}
		i++;
	}
	//changes values in reducing graph
	if (pre_cost_is_infinity == 0 && sec_cost_is_infinity == 1) // if not yet passed to the second node
	{
		lemin->node_tab[sec_index]->reach_cost = pre_current_cost + w;
		lemin->node_tab[sec_index]->infinity = 0;
		lemin->node_tab[sec_index]->predecessor = ft_strdup(pre);
	}
	if (pre_cost_is_infinity == 0 && sec_cost_is_infinity == 0) // if both nodes have already been connected to a previous one
	{
		if (sec_current_cost > (pre_current_cost + w))
		{
			lemin->node_tab[sec_index]->reach_cost = pre_current_cost + w;
			ft_strdel(&lemin->node_tab[sec_index]->predecessor);
			lemin->node_tab[sec_index]->predecessor = ft_strdup(pre);
		}
	}
}

void start_algo(t_lemin *lemin)
{
	int i;

	i = 0;
	while(i < lemin->number_of_nodes - 1)
	{
		reduce(lemin);
		printf_current_reach_cost(lemin, i);
		i++;
	}
	// write_path(lemin);
}
