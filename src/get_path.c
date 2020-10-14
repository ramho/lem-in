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


void get_path(t_lemin *lemin)
{
	int path;
	int i;
	t_path *index;

	select_edge(lemin);
	lemin->final_path_tab = ft_memalloc(sizeof(t_path) * lemin->nb_bellmanf_path);
	lemin->len_tab = ft_memalloc(sizeof(int) * lemin->nb_bellmanf_path);
	path = 0;
	i = 0;
	while (i < lemin->nb_bellmanf_path)
	{
		if (get_next_node(lemin->start_node, lemin, path) == 1)
			path += 1;
		else
			free(lemin->final_path_tab[path]);
		i++;
	}
	lemin->nb_bellmanf_path = path;
	i = 0;
	while (i < path)
	{
		index = lemin->final_path_tab[i];
		while (index)
		{
			lemin->len_tab[i] += 1;
			index = index->next;
		}
		i++;

	}
	if (lemin->nb_bellmanf_path > 1)
		sort_int_tab(lemin, lemin->nb_bellmanf_path);
	//
	//
	// i = 0;
	// printf("THE PATH ARE: \n");
	// while (i < path)
	// {
	//   index = lemin->final_path_tab[i];
	//   while (index)
	//   {
	//     printf("[%s] ", index->node->name);
	//     index = index->next;
	//   }
	//   printf("[%d]\n\n", lemin->len_tab[i]);
	//   i++;
	// }
	// printf("\n\n");
}

void select_edge(t_lemin *lemin)
{
	t_edge *edge;

	if (!(edge = malloc(sizeof(t_edge))))
		return ; // FREE
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


int get_next_node(t_node *start, t_lemin *lemin, int i) //recursive
{
	t_link *link;
	t_edge *edge;

	if (!(link = ft_memalloc(sizeof(t_link))))
		return (0); // FREE
	link = start->links;
	while (link)
	{
		edge = lemin->edge_tab;
		if ((check(edge, start, link, i, lemin)) == 1)
			return(1);
		link = link->next;
	}
	return (0); // FREE, path not possiblr, add a check before
}

int check(t_edge *ed, t_node *start, t_link *link, int i, t_lemin *l)
{
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
	return(0);
}

void add_node_link_to_final_path(t_lemin *lemin, t_node *node, int i)
{
	t_path *new;
	t_path *index;

	if(!(new = ft_memalloc(sizeof(t_path))))
		return ; // FREE
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

void sort_int_tab(t_lemin *lemin, int size)
{
	int i;
	int j;
	int tmp;
	t_path *buf;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < (size - 1))
		{
			if (lemin->len_tab[j] > lemin->len_tab[j + 1])
			{
				tmp = lemin->len_tab[j];
				buf = lemin->final_path_tab[j];
				lemin->len_tab[j] = lemin->len_tab[j + 1];
				lemin->final_path_tab[j] = lemin->final_path_tab[j + 1];
				lemin->len_tab[j + 1] = tmp;
				lemin->final_path_tab[j + 1] = buf;
			}
			j++;
		}
		i++;
	}
}
