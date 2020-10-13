/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoorntj <rhoorntj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 17:54:55 by rhoorntj          #+#    #+#             */
/*   Updated: 2020/10/11 17:21:52 by rhoorntj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	dispatch_ant_in_path(t_lemin *lemin)
{
	// printf("in dispatch_ant_in_path \n");
	int	i;
	int	j;

	if (!(lemin->ant_tab = ft_memalloc(sizeof(t_ant) * lemin->nb_ants)))
		return ;
	i = 0;
	j = 0;
	while (j < lemin->nb_bellmanf_path)
	{
		if (j == (lemin->nb_bellmanf_path - 2)) // avant dernier
		{
			choose_from_last_path(lemin,i, j);
			j = 0;
		}
		else
			choose_path_except_last(lemin, i, &j);
		i++;
		if (i == lemin->nb_ants)
			return ;
	}
}

void	choose_from_last_path(t_lemin *lemin, int i, int j)
{
	if (lemin->len_tab[j] > lemin->len_tab[j + 1])
	{
		if (!(init_ants(lemin->ant_tab, i, lemin->final_path_tab[j + 1])))
			return ; //FREE
		lemin->len_tab[j + 1] += 1;
	}
	else
	{
		if (!(init_ants(lemin->ant_tab, i, lemin->final_path_tab[0])))
			return ;
		lemin->len_tab[j] += 1;
	}
}

void	choose_path_except_last(t_lemin *lemin, int i, int *j)
{
	if (lemin->len_tab[*j] > lemin->len_tab[*j + 1])
	{
		if (!(init_ants(lemin->ant_tab, i, lemin->final_path_tab[*j + 1])))
			return ;
		lemin->len_tab[*j + 1] += 1;
		*j += 1;
	}
	else
	{
		if (!(init_ants(lemin->ant_tab, i, lemin->final_path_tab[*j])))
			return ;
		lemin->len_tab[*j] += 1;
	}
}
