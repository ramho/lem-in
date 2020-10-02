/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoorntj <rhoorntj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 17:32:03 by rhoorntj          #+#    #+#             */
/*   Updated: 2020/09/30 18:22:46 by rhoorntj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void get_path(t_lemin *lemin)
{
	// printf("in get path\n");
  int path;
	int i;

  select_path(lemin);
	lemin->final_path_tab = ft_memalloc(sizeof(t_path) * lemin->nb_final_path);
	path = 0;
	i = 0;
	int ret = 0;
	t_path *head;
  while (i < lemin->nb_final_path)
  {
	  // printf("start of path finding [%d]\n", i);
	  // add_node_link_to_final_path(lemin, lemin->start_node, i);
	  ret = get_next_node(lemin->start_node, lemin, path);
    if (ret == 1)// has to be starting node
     {
		 // printf("ret = %d\n", ret);
		  path += 1;
	  }
	  else
	 	free(lemin->final_path_tab[path]);
    i++;
	// printf("=============\n");
  }
	i = 0;
	t_path *index;
	while (i < path)
	{
		index = lemin->final_path_tab[i];
		printf("path [%d] is --> ", i);
		while (index)
		{
			printf("%s  ", index->node->name);
			index = index->next;
		}
		i++;
		printf("\n");
	}
}

void select_path(t_lemin *lemin) // savoir si les edge sont doubles ou pas, dans le parsing voir si on peut eviter les doubles
{
  t_edge *edge;
  // printf("enter select path\n");
	edge = malloc(sizeof(t_edge));
	// printf("11 edge tab[%s]\n", lemin->edge_tab->predecessor->name);
	edge = lemin->edge_tab;
	// printf("here\n");
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


int get_next_node(t_node *start, t_lemin *lemin, int i)
{
	// printf("in get next node [%d]\n", i);
	t_link *link;
	t_edge *edge;

	link = ft_memalloc(sizeof(t_link));
	link = start->links;
	edge = malloc(sizeof(t_edge)); // not necessary

	while (link)
	{
		// if (link->used == 1)
		// 	return(0);
		// printf("link [%s]\n", link->room->name);
		edge = lemin->edge_tab;
		while (edge)
		{
			// printf("edge [%s][%s] - no-go [%d]\n", edge->predecessor->name, edge->successor->name, edge->no_go);
			if ((edge->predecessor == start && edge->successor == link->room && edge->no_go == 0 && link->used == 0)
			|| (edge->reversed->predecessor == start && edge->reversed->successor == link->room && edge->reversed->no_go == 0 && link->used == 0)) // si edge est bon
			{
				link->used = 1;

				add_node_link_to_final_path(lemin, link->room, i);
				if (link->room == lemin->end_node)
				{
					return (1);
				}

				if (get_next_node(link->room, lemin, i) == 1)
					{
						// printf("get next room returned 1\n");
						return (1);
					}
			}
			else // si edge est pas bon
				edge = edge->next;
		}
		link = link->next;
	}
	// printf("path not possible\n");
	return(0);
}


void add_node_link_to_final_path(t_lemin *lemin, t_node *node, int i)
{
	t_path *new;
	t_path *index;

	new = ft_memalloc(sizeof(t_path));
	new->node = node;
	new->visited = 0;
	new->next = NULL;
	if (!(lemin->final_path_tab[i]))
		lemin->final_path_tab[i] = new;
	else
	{
		index = lemin->final_path_tab[i];
		while (index->next != NULL)
		{
			// printf(" --- in loop node is [%s]\t", index->node->name );
			index = index->next;

		}
		// printf("\n");

		index->next = new;
	}
}
