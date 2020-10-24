/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoorntj <rhoorntj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 17:32:03 by rhoorntj          #+#    #+#             */
/*   Updated: 2020/10/24 17:38:32 by rhoorntj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	get_path(t_lemin *l)
{
	int	path;
	int	i;

	printf("fourmis [%d] path [%d]\n", l->nb_ants, l->nb_bellmanf_path);
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
		// else
		// {
		// 	if(l->final_path_tab[path])
		// 		free(l->final_path_tab[path]);
		// }
		i++;
	}
	if (path == 0)
	{
		ft_printf("ERROR\n");
		exit(-1);
	}
	free_path(l->path_tab, l->nb_bellmanf_path);
	l->nb_bellmanf_path = path;
	count_length(l, path);
	if (l->nb_bellmanf_path > 1)
		sort_int_tab(l, l->nb_bellmanf_path);


	// 
	// printf("final path [%d]	\n", l->nb_bellmanf_path);
	// i = 0;
	// t_path * index;
	// while (i < l->nb_bellmanf_path)
	// {
	// 	printf("[%d] ", i);
	// 	index = l->final_path_tab[i];
	// 	while (index)
	// 	{
	// 		printf("%s ", index->node->name);
	// 		index = index->next;
	// 	}
	// 	printf("\n");
	// 	// printf("	[%d]\n", l->len_tab[i]);
	// 	i++;
	// }
	// printf("\n\n");
}

void	select_edge(t_lemin *lemin)
{
	t_edge	*edge;

	edge = lemin->edge_tab;
	while (edge)
	{
		// printf(" pre [%s] suc [%s] visited [%d] edge no-go [%d]\n", edge->predecessor->name, edge->successor->name, edge->visited, edge->no_go);
		// printf(" REV pre [%s] suc [%s] visited [%d] edge no-go [%d]\n\n", edge->reversed->predecessor->name, edge->reversed->successor->name, edge->reversed->visited, edge->reversed->no_go);
		if (edge->visited == 0)
		{
			// printf("NO GO\n");
			edge->no_go = 1;
		}
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
		// printf(" pre [%s] suc [%s] visited [%d] edge no-go [%d]\n", edge->predecessor->name, edge->successor->name, edge->visited, edge->no_go);
		// printf(" REV pre [%s] suc [%s] visited [%d] edge no-go [%d]\n", edge->reversed->predecessor->name, edge->reversed->successor->name, edge->reversed->visited, edge->reversed->no_go);
		// printf("----\n");
		edge = edge->next;
	}
}

int		get_next_node(t_node *start, t_lemin *lemin, int i)
{
	// printf(" [%d] in get next node node [%s]\n",i, start->name);
	t_link	*link;
	t_edge	*edge;

	link = start->links;
	while (link)
	{
		edge = lemin->edge_tab;
		if ((check_edge(start, link, i, lemin)) == 1)
		{
			// printf("out of check edge == 1\n");
			return (1);
		}
		// printf("out of check edge == 0\n");
		link = link->next;
	}
	// printf("out of get next node == 0");
	return (0);
}

int		check_edge(t_node *start, t_link *link, int i, t_lemin *l)
{
	// printf("[%d] in check edge [%s]\n", i, start->name);
	t_edge *ed;

	ed = l->edge_tab;
	while (ed)
	{
		// printf(" start/link[%s][%s] - edge [%s][%s] link used [%d] edge no-go [%d]\n", start->name, link->room->name, ed->predecessor->name, ed->successor->name, link->used, ed->no_go);
		if ((ed->predecessor == start && ed->successor == link->room
			&& ed->no_go == 0 && link->used == 0)
			|| (ed->reversed->predecessor == start
			&& ed->reversed->successor == link->room
			&& ed->reversed->no_go == 0 && link->used == 0))
		{
			link->used = 1;
			add_node_link_to_path(l, link->room, i);
			if (link->room == l->end_node)
			{

				return (1);
			}
			if (get_next_node(link->room, l, i) == 1)
			{
				return (1);
			}
		}
		else
			ed = ed->next;
	}
	return (0);
}

void	add_node_link_to_path(t_lemin *lemin, t_node *node, int i)
{
	// printf("[%d] in add node link to final path --> node [%s]\n", i,node->name);
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
