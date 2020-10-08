/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoorntj <rhoorntj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 17:31:39 by rhoorntj          #+#    #+#             */
/*   Updated: 2020/09/30 17:58:00 by rhoorntj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"


int save_path(t_lemin *lemin, int index_path)
{
	t_path *new;
	t_path *head;
	t_path *index;

	if(!(head = ft_memalloc(sizeof(t_path))))
		return(0);
	lemin->path_tab[index_path] = head;
	head->node = lemin->end_node;
	if(!(new = ft_memalloc(sizeof(t_path))))
		return(0);
	if( !(new->node = ft_memalloc(sizeof(t_node))))
		return(0);
	new->node = head->node->predecessor;
	new->next = NULL;
	head->next = new;
	while (new != NULL)
	{
		if (new->node->predecessor == NULL)
			return(0);
		if (new->node == new->node->predecessor->predecessor)
			return(0);
		index = head;
		while (index->next != NULL)
			index = index->next;
		if (!(new = ft_memalloc(sizeof(t_path))))
			return(0);
		new->node = index->node->predecessor;
		new->next = NULL;
		index->next = new;
		if(new->node == lemin->start_node)
			return(1);
		if (new->node == lemin->end_node)
			return(0);
	}
	if (new->node != lemin->start_node)
		return(0);
	return(1);
}

void init_infinity_and_reach_cost(t_lemin *lemin)
{
	int i;
	int j;
	t_edge *index;

	i = 1;
	j = 1;
	index = lemin->edge_tab;
	while (index)
	{
		index->predecessor->infinity = 1;
		index->predecessor->reach_cost = 0;
		if(!(index->predecessor->predecessor = ft_memalloc(sizeof(t_node))))
			return;
		index->successor->infinity = 1;
		index->successor->reach_cost = 0;
	if(!(index->successor->predecessor = ft_memalloc(sizeof(t_node))))
		return;
		index = index->next;
	}
	lemin->start_node->infinity = 0;
}

int start_algo(t_lemin *lemin)
{
	int i;
	int x;
	int ret;

	if (lemin->nb_ants == 1)
		lemin->nb_path = 1;
	lemin->path_tab = malloc(sizeof(t_path *) * lemin->nb_path);
	x = 0;
	lemin->nb_final_path = 0;
	while (x < lemin->nb_path)
	{

		if (bellman_ford(lemin) == 1)
			return(0);
		//check path before saving it
		ret = 0;
		ret = save_path(lemin, lemin->nb_final_path);
		lemin->nb_final_path += ret;
		if (ret != 0 || (x + 1) < lemin->nb_path)
		{
			suurballe(lemin, lemin->nb_final_path - 1);
			init_infinity_and_reach_cost(lemin);
		}
		i = 0;
		x++;
	}
  return(0);
}
