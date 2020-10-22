/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoorntj <rhoorntj@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 17:31:27 by rhoorntj          #+#    #+#             */
/*   Updated: 2020/10/22 17:28:10 by Ramata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	print_path(t_lemin *lemin)
{
	int		i;
	int		count;

	count = 0;
	if (!(lemin->ant_tab = ft_memalloc(sizeof(t_ant) * lemin->nb_ants)))
		free_error(lemin, 3, lemin->nb_bellmanf_path);
	i = 0;
	if (lemin->nb_bellmanf_path == 1)
	{
		while (i < lemin->nb_ants)
		{
			if (!(init_ants(lemin->ant_tab, i, lemin->final_path_tab[0])))
				free_error(lemin, 1, i);
			i++;
		}
	}
	else
		dispatch_ant_in_path(lemin);
	while (lemin->ant_in_end < lemin->nb_ants)
	{
		// printf("11\n");
		update_ant(lemin->ant_tab, lemin->nb_ants, lemin);
		// printf("22\n");
		print_ant(lemin->ant_tab, lemin->nb_ants, lemin);
		ft_printf("\n");
		count++;
	}
	ft_printf("%d lines\n", count);
}

void	print_ant(t_ant **tab, int nb_ant, t_lemin *lemin)
{
	int		i;

	i = 0;
	while (i < nb_ant)
	{
		if (tab[i]->node->name != NULL && tab[i]->no_print == 0)
			ft_printf("L%d-%s ", tab[i]->ant, tab[i]->node->name);
		if (tab[i]->node == lemin->end_node)
			tab[i]->no_print = 1;
		i++;
	}
}

void	print_direct(t_lemin *l)
{
	int		i;

	i = 1;
	while (i <= l->nb_ants)
	{
		ft_printf("L%d_%s\n", i, l->end_node->name);
		i++;
	}
	exit(1);
}
