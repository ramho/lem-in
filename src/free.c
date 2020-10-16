/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ramata <Ramata@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 16:38:15 by Ramata            #+#    #+#             */
/*   Updated: 2020/10/16 16:38:20 by Ramata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	free_everything(t_lemin *lemin)
{
	free_path(lemin->final_path_tab, lemin->nb_bellmanf_path);
	free_ant(lemin->ant_tab, lemin->nb_ants);
	free_nodes(lemin);
	free_edges(lemin);
	free(lemin);
	lemin = NULL;
}

void	free_lemin(t_lemin *lemin)
{
	free(lemin);
	lemin = NULL;
	exit(-1);
}

void	free_error(t_lemin *l, int error, int size)
{
	if (error == 1)
	{
		free_ant(l->ant_tab, size);
		free(l->ant_tab);
		error = 3;
	}
	if (error == 2)
	{
		if (l->final_path_tab)
			free(l->final_path_tab);
		if (l->len_tab)
			free(l->len_tab);
	}
	if (error == 3)
	{
		free_path(l->final_path_tab, size);
		free(l->len_tab);
	}
	free_first_path(l);
}

void	free_first_path(t_lemin *lemin)
{
	free_path(lemin->path_tab, lemin->nb_bellmanf_path);
	free_nodes(lemin);
	free_edges(lemin);
	free_lemin(lemin);
}

void	free_ant(t_ant **tab, int ants)
{
	int	i;

	i = ants;
	while (i >= 0)
	{
		if (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
		}
		i--;
	}
}
