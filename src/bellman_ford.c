#include "../includes/lemin.h"

void bellman_ford(t_lemin *lemin)
{
	int i;
	// int j;
	t_edge *tmp;

	i = 0;
	printf("in bellamn %d\n", lemin->number_of_nodes);
	while (i < lemin->number_of_nodes)
	{
		// j = 0;
		printf("here\n");
		tmp = lemin->edge_tab;
		while (tmp->next != NULL)
		{
			printf("%s - %s\n", tmp->predecessor->name, tmp->successor->name);
			// try_reduce(tmp->predecessor, tmp->successor)
		// 	if (ft_strcmp(lemin->node_tab[i]->name, lemin->edge_tab[j]->predecessor) == 0 && lemin->edge_tab[j]->visited == 0)
		// 	{
				// printf("edge [%s][%s] is visited %d times\n", lemin->edge_tab[j]->predecessor, lemin->edge_tab[j]->successor, lemin->edge_tab[j]->visited);
				// try_reduce(lemin->node_tab[i], lemin->edge_tab[j]->successor, lemin->edge_tab[j]->weight, lemin);
					printf("===============\n");
				// }

		// 	j++;
			tmp = tmp->next;
			printf("in\n");
		}
		printf("out\n");
		i++;
	}
	// printf_current_reach_cost(lemin, 0);
}

// void try_reduce(t_node *pre, char *sec, int w, t_lemin *lemin)
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
