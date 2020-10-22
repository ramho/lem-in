/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoorntj <rhoorntj@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 17:54:55 by rhoorntj          #+#    #+#             */
/*   Updated: 2020/10/22 18:17:24 by Ramata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int find_smallest_value(int *tab, int tab_len)
{
	int i;
	int smallest;

// printf("in smallest tab len [%d]\n", tab_len);
	i = 1;
	smallest = 0;
	while (i < tab_len)
	{
		// printf("[%d]/[%d]\n", smallest, tab_len);
		if(tab[i] < tab[smallest])
			smallest = i;
		i++;
	}
	return (smallest);

}

void	dispatch_ant_in_path(t_lemin *lemin)
{
	int i;
	int j;

		i = 0;
		j = 0;
		// printf("in dispatch\n");
		while (j < lemin->nb_bellmanf_path)
		{
			j = find_smallest_value(lemin->len_tab, lemin->nb_bellmanf_path);
			// printf("j = %d \n", j);
			if (!(init_ants(lemin->ant_tab, i, lemin->final_path_tab[j])))
					free_error(lemin, 1, i);
			if (lemin->final_path_tab[j]->used == 0)
				lemin->final_path_tab[j]->used = 1;
			else
				lemin->len_tab[j] += 1;
			i++;
			if (i == lemin->nb_ants)
				return ;
		}
}
