/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoorntj <rhoorntj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 17:31:27 by rhoorntj          #+#    #+#             */
/*   Updated: 2020/09/30 18:28:46 by rhoorntj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void print_path(t_lemin *lemin)
{
	int i;
	int j;
	t_path *index;
	i = 1;

	while (i < lemin->nb_ants + 1)
	{
		j = 0;
		// index =
		while (j < lemin->nb_final_path && lemin->final_path_tab[j]->node != lemin->end_node)
		{
			printf("L%d-%s ", i, lemin->final_path_tab[j]->node->name);
			i++;
			lemin->final_path_tab[j] = lemin->final_path_tab[j]->next;
			j++;
		}
		printf("ants passed [%d] j = [%d]\n", i, j);
		printf("node [%s]\n", lemin->final_path_tab[j - 1]->node->name);
	}
}
