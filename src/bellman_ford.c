#include "../includes/lemin.h"

int bellman_ford(t_lemin *lemin)//, int *changed)
{
	int i;
	t_edge *tmp;
	int changed;

	i = 0;

	printf("in bellman_ford \n");
	while (i < lemin->number_of_nodes - 1)
	{
		changed = 0;
		tmp = lemin->edge_tab;
		while (tmp != NULL)
		{
			// printf("tmp pre %s tmp suc %s\n", tmp->predecessor->name, tmp->successor->name);
			// printf("tmp[%s][%s] visite [%d] // reversed tmp[%s][%s] visite [%d]\n", tmp->predecessor->name, tmp->successor->name, tmp->visited, tmp->reversed->predecessor->name, tmp->reversed->successor->name, tmp->reversed->visited);
			if(tmp->visited == 0)
				try_reduce (tmp->predecessor, tmp->successor, tmp->weight, &changed, 0);
			if(tmp->reversed->visited == 0)
				try_reduce (tmp->reversed->predecessor, tmp->reversed->successor, tmp->reversed->weight, &changed, 0);
			tmp = tmp->next;
			if (tmp == NULL)
				break;
				// printf("NULL\n");
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
	(void)z;
	// printf("try reduce\n");
	// printf("in try reduce [%s](%d)[%s](%d) \n", pre->name, pre->reach_cost, sec->name, sec->reach_cost);
	t_node *pre_node;
	int in = 0; // check if not will have a predecssor otherwise will seg when printf

	if (pre->duplicated == 1)
		pre_node = pre->dup_out;
	else
		pre_node = pre;
	// printf("pre %s suc %s\n", pre->name, sec->name);
// printf("----->>pre %s inf [%d] - sec %s inf[%d] -- weight %d\n\n", pre_node->name, pre_node->infinity, sec->name, sec->infinity, w);
	if (pre_node->infinity == 0 && sec->infinity == 1) // if not yet passed to the second node
	{
		// printf("enter if infinity\n");
		// printf(" AVANT suc node [%s] reach_cost [%d]\n", sec->name, sec->reach_cost);
		in = 1;
		*changed = 1;
		sec->reach_cost = pre_node->reach_cost + w;
		sec->infinity = 0;
		sec->predecessor = malloc(sizeof(t_node));

		sec->predecessor = pre_node;
		if (sec->duplicated == 1)
		{
			sec->dup_out->reach_cost = pre_node->reach_cost + w;
			sec->dup_out->infinity = 0;
			sec->dup_out->predecessor = malloc(sizeof(t_node));
			sec->dup_out->predecessor = pre_node;
		}
		// printf(" APRES sec node [%s] reach_cost [%d]\n", sec->name, sec->reach_cost);
	}
	// printf("333\n");

	 if (pre_node->infinity  == 0 && sec->infinity == 0) // if both nodes have already been connected to a previous one
	{
		// printf("enter if not infinity\n");
		if (sec->reach_cost > (pre_node->reach_cost + w))
		{
			// printf(" AVANT sec node [%s] reach_cost [%d]\n", sec->name, sec->reach_cost);
			// printf("------>enter in if\n");
			in = 1;
			*changed = 1;
			sec->reach_cost = pre_node->reach_cost + w;
			sec->predecessor= malloc(sizeof(t_node));
			sec->predecessor = pre_node;
			// printf(" APRES sec node [%s] reach_cost [%d]\n", sec->name, sec->reach_cost);
		}
	}
	// if( z == 0)
	// {
	// if (in > 0)
	// 	printf("name [%s] pre [%s] reach cost [%d]\n\n", sec->name, sec->predecessor->name, sec->reach_cost);
	// }
// printf("predecessor [%s] --> sec[%s]\n", pre_node->name, sec->name);//, sec->predecessor->name);
}
