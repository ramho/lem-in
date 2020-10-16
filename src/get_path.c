/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoorntj <rhoorntj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 17:32:03 by rhoorntj          #+#    #+#             */
/*   Updated: 2020/10/14 18:18:42 by rhoorntj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	get_path(t_lemin *l)
{
	int	path;
	int	i;

	select_edge(l);
	if (!(l->final_path_tab = ft_memalloc(sizeof(t_path) * l->nb_bellmanf_path))
		|| !(l->len_tab = ft_memalloc(sizeof(int) * l->nb_bellmanf_path)))
		free_error(l, 2, 0);
	i = 0;
	path = 0;
	while (i < l->nb_bellmanf_path)
	{
		if (get_next_node(l->start_node, l, path) == 1)
			path += 1;
		else
			free(l->final_path_tab[path]);
		i++;
	}
	free_path(l->path_tab, l->nb_bellmanf_path);
	l->nb_bellmanf_path = path;
	count_length(l, path);
	if (l->nb_bellmanf_path > 1)
		sort_int_tab(l, l->nb_bellmanf_path);
}

void	select_edge(t_lemin *lemin)
{
	t_edge	*edge;

	edge = lemin->edge_tab;
	while (edge)
	{
		if (edge->visited == 0)
			edge->no_go = 1;
		if (edge->reversed)
		{
			if (edge->reversed->visited == 0)
				edge->reversed->no_go = 1;
			if (edge->visited == 1 && edge->reversed->visited == 1)
			{
				edge->no_go = 1;
				edge->reversed->no_go = 1;
			}
		}
		edge = edge->next;
	}
}

int		get_next_node(t_node *start, t_lemin *lemin, int i)
{
	t_link	*link;
	t_edge	*edge;

	link = start->links;
	while (link)
	{
		edge = lemin->edge_tab;
		if ((check_edge(start, link, i, lemin)) == 1)
			return (1);
		link = link->next;
	}
	return (0);
}

int		check_edge(t_node *start, t_link *link, int i, t_lemin *l)
{
	t_edge *ed;

	ed = l->edge_tab;
	while (ed)
	{
		if ((ed->predecessor == start && ed->successor == link->room
			&& ed->no_go == 0 && link->used == 0)
			|| (ed->reversed->predecessor == start
			&& ed->reversed->successor == link->room
			&& ed->reversed->no_go == 0 && link->used == 0))
		{
			link->used = 1;
			add_node_link_to_final_path(l, link->room, i);
			if (link->room == l->end_node)
				return (1);
			if (get_next_node(link->room, l, i) == 1)
				return (1);
		}
		else
			ed = ed->next;
	}
	return (0);
}

void	add_node_link_to_final_path(t_lemin *lemin, t_node *node, int i)
{
	t_path	*new;
	t_path	*index;

	if (!(new = ft_memalloc(sizeof(t_path))))
		free_error(lemin, 3, i);
	new->node = node;
	new->visited = 0;
	new->ant = 0;
	new->next = NULL;
	if (!(lemin->final_path_tab[i]))
		lemin->final_path_tab[i] = new;
	else
	{
		index = lemin->final_path_tab[i];
		while (index->next != NULL)
			index = index->next;
		index->next = new;
	}
}
