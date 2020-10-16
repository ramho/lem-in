/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoorntj <rhoorntj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 17:09:29 by rhoorntj          #+#    #+#             */
/*   Updated: 2020/10/11 18:32:20 by rhoorntj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		get_coord(t_lemin *l, int *i, t_node *node)
{
	char	is_int;
	char	neg;

	is_int = 0;
	neg = 1;
	while (l->line[++(*i)] != '\n')
	{
		if ((l->line[*i] == '-') && (l->line[*i - 1] == ' '))
			neg = -1;
		else if (l->line[*i] >= '0' && l->line[*i] <= '9' && (is_int = 1))
			node->y = (node->y * 10) + (l->line[*i] - '0');
		else if (l->line[*i] == ' ')
		{
			if (is_int--)
				node->x = (node->y * neg);
			else
				return (0);
			neg = 1;
			node->y = 0;
		}
		else
			return (0);
	}
	node->y *= neg;
	return (is_int);
}

void	store_start_end_node(t_lemin *l, t_node *node)
{
	if (l->start_room == 1)
	{
		node->type = 1;
		node->infinity = 0;
		l->start_node = node;
		l->start_room++;
	}
	else
	{
		node->type = 2;
		node->infinity = 1;
		l->end_node = node;
		l->end_room++;
	}
}

int		store_node(t_lemin *l, t_node *node)
{
	t_node	*tmp;

	if (!(&l->node_tab[node->key]))
		l->node_tab[node->key] = node;
	else
	{
		tmp = l->node_tab[node->key];
		while (tmp)
		{
			if (ft_strequ(tmp->name, node->name))
				return (0);
			tmp = tmp->next;
		}
		node->next = l->node_tab[node->key];
		l->node_tab[node->key] = node;
	}
	return (1);
}

int		free_node(t_node *node)
{
	free(node->name);
	node->name = NULL;
	free(node);
	node = NULL;
	return (0);
}

int		parse_nodes(t_lemin *l)
{
	int		i;
	t_node	*node;

	if (!(node = (t_node*)ft_memalloc(sizeof(t_node))))
		return (0);
	node->links = NULL;
	i = -1;
	node->key = hash(l, &i, ' ');
	node->reach_cost = 0;
	node->ant = 0;
	if (!(node->predecessor = ft_memalloc(sizeof(t_node))) ||
		!(node->name = (char*)ft_memalloc(sizeof(char) * (i + 1))))
		return (0);
	ft_strncpy(node->name, l->line, i);
	node->name[i] = 0;
	if (!(get_coord(l, &i, node)))
		return (free_node(node));
	if ((l->start_room == 1) || (l->end_room == 1))
		store_start_end_node(l, node);
	else
		node->infinity = 1;
	if (!(store_node(l, node)))
		return (free_node(node));
	l->number_of_nodes++;
	return (1);
}
