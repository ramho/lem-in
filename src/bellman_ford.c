#include "../includes/lemin.h"

int bellman_ford(t_lemin *lemin)//, int *changed)
{
	int i;
	// int j;
	t_edge *tmp;
	int changed;

	i = 0;

	// printf("in bellman_ford \n");
	while (i < lemin->number_of_nodes - 1)
	{
		// j = 0;
		changed = 0;
		// printf("here\n");
		tmp = lemin->edge_tab;
		while (tmp)
		{
			// printf("tmp[%s][%s] visite [%d] // reversed tmp[%s][%s] visite [%d]\n", tmp->predecessor->name, tmp->successor->name, tmp->visited, tmp->reversed->predecessor->name, tmp->reversed->successor->name, tmp->reversed->visited);
			if(tmp->visited == 0)
				try_reduce (tmp->predecessor, tmp->successor, tmp->weight, &changed, 0);
			if(tmp->reversed->visited == 0)
				try_reduce (tmp->reversed->predecessor, tmp->reversed->successor, tmp->reversed->weight, &changed, 0);
			tmp = tmp->next;
		}
					// printf("[%d]/%d=============== changed [%d]\n", i, lemin->number_of_nodes , changed);
					// if (changed == 0)
					// {
					// 	printf("BREAK\n");
					// 	return(0);
					// }
		// printf("out\n");
		i++;
	}
	// printf("neg cycle test\n");
	tmp = lemin->edge_tab;
	changed = 0;
	while (tmp)
	{
		if(tmp->visited == 0)
			try_reduce (tmp->predecessor, tmp->successor, tmp->weight, &changed, 1);
		if(tmp->reversed->visited == 0)
			try_reduce (tmp->reversed->predecessor, tmp->reversed->successor, tmp->reversed->weight, &changed, 1);
		tmp = tmp->next;
	}
	// printf("changed = %d\n", changed);
	if (changed == 1)
		return(1);
	return (0);
}

void try_reduce(t_node *pre, t_node *sec, int w, int *changed, int z)
{
	// printf("in try reduce [%s][%s] weight [%d] \n", pre->name, sec->name, w);
	t_node *pre_node;
	int in = 0; // check if not will have a predecssor otherwise will seg when printf

	if (pre->duplicated == 1)
		pre_node = pre->dup_out;
	else
		pre_node = pre;
// printf("----->>pre %s inf [%d] - sec %s inf[%d] -- weight %d\n\n", pre_node->name, pre_node->infinity, sec->name, sec->infinity, w);
	if (pre_node->infinity == 0 && sec->infinity == 1) // if not yet passed to the second node
	{
		// printf("enter if infinity\n");
		in = 1;
		*changed = 1;
		sec->reach_cost = pre_node->reach_cost + w;
		sec->infinity = 0;
		sec->predecessor = pre_node;
		if (sec->duplicated == 1)
		{
			sec->dup_out->reach_cost = pre_node->reach_cost + w;
			sec->dup_out->infinity = 0;
			sec->dup_out->predecessor = pre_node;
		}

	}
	// printf("333\n");

	 if (pre_node->infinity  == 0 && sec->infinity == 0) // if both nodes have already been connected to a previous one
	{
		// printf("enter if not infinity\n");
		if (sec->reach_cost > (pre_node->reach_cost + w))
		{
			// printf("------>enter in if\n");
			in = 1;
			*changed = 1;
			sec->reach_cost = pre_node->reach_cost + w;
			sec->predecessor = pre_node;
		}
	}
	// if( z == 0)
	// {
	// if (in > 0)
	// 	printf("name [%s] pre [%s] reach cost [%d]\n\n", sec->name, sec->predecessor->name, sec->reach_cost);
	// }
// printf("predecessor [%s] --> sec[%s]\n", pre_node->name, sec->name);//, sec->predecessor->name);
}

// {
// 	int i;
// 	int pre_index;
// 	int sec_index;
// 	t_node *pre_node;
//
// // printf("in try reduce\n");
// 	i = 0;
// 	if (pre->duplicated == 1)
// 	{
// 		// printf("DUP    ");
// 			pre_node = pre->dup_out;
// 		}
// 	else
// 		pre_node = pre;
// 	// printf("111\n");
// 	//but in a hashtable instead of looping through the table
// 	while (i < lemin->number_of_nodes)
// 	{
// 		if (ft_strcmp(pre_node->name,lemin->node_tab[i]->name) == 0)
// 			pre_index = i; // keeping index of predecessor
// 		if (ft_strcmp(sec, lemin->node_tab[i]->name) == 0)
// 			sec_index = i; // keeping index of successor
// 		i++;
// 	}
// 		// printf("222\n");
// 	printf("START node %s [%d] inf[%d]- node %s [%d] inf [%d]\n", pre_node->name, pre_node->reach_cost, pre_node->infinity,lemin->node_tab[sec_index]->name, lemin->node_tab[sec_index]->reach_cost, lemin->node_tab[sec_index]->infinity );
// 	//changes values in reducing graph
// 	if (pre_node->infinity == 0 && lemin->node_tab[sec_index]->infinity == 1) // if not yet passed to the second node
// 	{
// 		// printf("enter if infinity\n");
// 		lemin->node_tab[sec_index]->reach_cost = pre_node->reach_cost + w;
// 		lemin->node_tab[sec_index]->infinity = 0;
// 		lemin->node_tab[sec_index]->predecessor = ft_strdup(pre_node->name);
// 		if (lemin->node_tab[sec_index]->duplicated == 1)
// 		{
// 			lemin->node_tab[sec_index]->dup_out->reach_cost = pre_node->reach_cost + w;
// 			lemin->node_tab[sec_index]->dup_out->infinity = 0;
// 			lemin->node_tab[sec_index]->dup_out->predecessor = ft_strdup(pre_node->name);
// 		}
//
// 	}
// 		// printf("333\n");
// 		// printf("%s [%d] - %s [%d]\n", pre_node->name, pre_node->infinity, lemin->node_tab[sec_index]->name, lemin->node_tab[sec_index]->infinity);
// 	else if (pre_node->infinity  == 0 && lemin->node_tab[sec_index]->infinity == 0) // if both nodes have already been connected to a previous one
// 	{
// 		// printf("enter if not infinity\n");
// 		if (lemin->node_tab[sec_index]->reach_cost > (pre_node->reach_cost + w))
// 		{
// 			lemin->node_tab[sec_index]->reach_cost = pre_node->reach_cost + w;
// 			ft_strdel(&lemin->node_tab[sec_index]->predecessor);
// 			lemin->node_tab[sec_index]->predecessor = ft_strdup(pre_node->name);
// 		}
// 	}
// 	printf("END node %s [%d] inf[%d]- node %s [%d] inf [%d]\n", pre_node->name, pre_node->reach_cost, pre_node->infinity,lemin->node_tab[sec_index]->name, lemin->node_tab[sec_index]->reach_cost, lemin->node_tab[sec_index]->infinity );
// }
