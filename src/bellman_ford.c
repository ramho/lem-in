/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellman_ford.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoorntj <rhoorntj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 17:31:48 by rhoorntj          #+#    #+#             */
/*   Updated: 2020/10/11 16:48:41 by rhoorntj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int bellman_ford(t_lemin *lemin)//, int *changed)
{
	int i;
	t_edge *tmp;
	int changed;

	i = 0;

	// printf("in bellman_ford \n");
	while (i < lemin->number_of_nodes - 1)
	{
		changed = 0;
		tmp = lemin->edge_tab;
		while (tmp)
		{
			if(tmp->visited == 0)
				try_reduce (tmp->predecessor, tmp->successor, tmp->weight, &changed);//, 0);
			if(tmp->reversed->visited == 0)
				try_reduce (tmp->reversed->predecessor, tmp->reversed->successor, tmp->reversed->weight, &changed);//, 0);
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
			try_reduce (tmp->predecessor, tmp->successor, tmp->weight, &changed);//, 1);
		if(tmp->reversed->visited == 0)
			try_reduce (tmp->reversed->predecessor, tmp->reversed->successor, tmp->reversed->weight, &changed);//, 1);
		tmp = tmp->next;
	}
	// printf("changed = %d\n", changed);
	if (changed == 1)
		return(1);
	return (0);
}

void try_reduce(t_node *pre, t_node *sec, int w, int *changed)//, int z)
{
	// printf("try reduce\n");
	t_node *pre_node;

	if (pre->duplicated == 1)
		pre_node = pre->dup_out;
	else
		pre_node = pre;
	if (pre_node->infinity == 0 && sec->infinity == 1) // if not yet passed to the second node
	{
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
	 else if (pre_node->infinity  == 0 && sec->infinity == 0) // if both nodes have already been connected to a previous one
	{
		if (sec->reach_cost > (pre_node->reach_cost + w))
		{
			*changed = 1;
			sec->reach_cost = pre_node->reach_cost + w;
			sec->predecessor = pre_node;
		}
	}
}
