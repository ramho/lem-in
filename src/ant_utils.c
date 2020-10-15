/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoorntj <rhoorntj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 17:54:32 by rhoorntj          #+#    #+#             */
/*   Updated: 2020/10/11 18:30:56 by rhoorntj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void update_ant(t_ant **tab, int nb_ant, t_lemin *lemin)
{
	int i;
	static int flag;

	i = 0;
	flag = 0;
	while (i < nb_ant)
	{
		if (tab[i]->node->name == NULL)
		{
			flag += move_ant(tab[i], lemin);
			if (flag % lemin->nb_bellmanf_path == 0)
			{
				return ;
			}
		}
		else
			move_ant(tab[i], lemin);
		i++;
	}

}

int move_ant(t_ant *ant, t_lemin *lemin)
{
	if (ant->end == 0)
	{
		if ( ant->node->name == NULL)
		{
			if ( ant->path->ant == 1)
				return (0);
			ant->node = ant->path->node;
			ant->path->ant = 1;
		}
		else
		{
			ant->path->ant = 0;
			ant->path = ant->path->next;
			ant->path->ant = 1;
			ant->node = ant->path->node;
		}
		if (ant->node == lemin->end_node)
		{
			lemin->ant_in_end += 1;
			ant->end = 1;
		}
	}
	return (1);
}

int	init_ants(t_ant **tab, int ant, t_path *path)
{
	t_ant	*new;
	//
	if (!(new = ft_memalloc(sizeof(t_ant))))
		return (0);
	new->ant = ant+1;
	new->end = 0;
	new->no_print = 0;
	new->path = path;
	if (!(new->node = ft_memalloc(sizeof(t_node))))
		return (0);
	tab[ant] = new;
	return (1);
}
