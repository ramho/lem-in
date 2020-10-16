/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoorntj <rhoorntj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 17:33:40 by rhoorntj          #+#    #+#             */
/*   Updated: 2020/10/14 16:58:36 by rhoorntj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	create_dup_room(t_lemin *lemin, t_node *node)
{
	node->duplicated = 1;
	if (!(node->dup_out = malloc(sizeof(t_node))))
		free_first_path(lemin);
	node->dup_out->name = node->name;
	node->dup_out->reach_cost = 0;
	node->dup_out->infinity = 1;
}

void	check_if_valid(t_node *pre, t_node *suc, t_edge *edge, t_lemin *lemin)
{
	if ((pre == edge->predecessor) && (suc == edge->successor))
	{
		edge->weight = -1;
		if (suc != lemin->start_node)
			create_dup_room(lemin, suc);
	}
	if ((pre->name == edge->reversed->predecessor->name)
		&& (suc->name == edge->reversed->successor->name))
	{
		edge->reversed->weight = -1;
		if (suc != lemin->start_node)
			create_dup_room(lemin, suc);
	}
	if ((suc == edge->predecessor) && (pre == edge->successor))
		edge->visited = 1;
	if ((suc->name == edge->reversed->predecessor->name)
		&& (pre->name == edge->reversed->successor->name))
		edge->reversed->visited = 1;
}

void	suurballe(t_lemin *lemin, int path_index)
{
	t_path	*index;
	t_edge	*edge;
	t_node	*pre_path;
	t_node	*suc_path;

	index = lemin->path_tab[path_index];
	while (index->next)
	{
		pre_path = index->node;
		suc_path = index->next->node;
		edge = lemin->edge_tab;
		while (edge)
		{
			check_if_valid(pre_path, suc_path, edge, lemin);
			edge = edge->next;
		}
		index = index->next;
	}
}
