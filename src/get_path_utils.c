/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ramata <Ramata@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 16:38:30 by Ramata            #+#    #+#             */
/*   Updated: 2020/10/22 16:41:16 by Ramata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	sort_int_tab(t_lemin *lemin, int size)
{
	int		i;
	int		j;
	int		tmp;
	t_path	*buf;

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

void	count_length(t_lemin *l, int path)
{
	int		i;
	t_path	*index;

	i = 0;
	while (i < path)
	{
		index = l->final_path_tab[i];
		while (index)
		{
			index->used = 0;
			l->len_tab[i] += 1;
			index = index->next;
		}
		i++;
	}
}
