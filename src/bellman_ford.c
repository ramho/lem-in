/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellman_ford.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoorntj <rhoorntj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 17:31:48 by rhoorntj          #+#    #+#             */
/*   Updated: 2020/10/11 18:58:34 by rhoorntj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		bellman_ford(t_lemin *lemin)
{
	int		i;
	t_edge	*tmp;
	int		changed;

	i = 0;
	while (i < lemin->number_of_nodes - 1)
	{
		changed = 0;
		tmp = lemin->edge_tab;
		while (tmp)
		{
			if (tmp->visited == 0)
				try_reduce (tmp->predecessor, tmp->successor,
					tmp->weight, &changed);
			if (tmp->reversed->visited == 0)
				try_reduce (tmp->reversed->predecessor,
					tmp->reversed->successor, tmp->reversed->weight, &changed);
			tmp = tmp->next;
		}
		i++;
	}

	return (0);
}

void	try_reduce(t_node *pre, t_node *sec, int w, int *changed)
{
	t_node	*pre_node;

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
	else if (pre_node->infinity == 0 && sec->infinity == 0) // if both nodes have already been connected to a previous one
	{
		if (sec->reach_cost > (pre_node->reach_cost + w))
		{
			*changed = 1;
			sec->reach_cost = pre_node->reach_cost + w;
			sec->predecessor = pre_node;
		}
	}
}
