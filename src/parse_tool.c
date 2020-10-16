/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoorntj <rhoorntj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 17:07:32 by rhoorntj          #+#    #+#             */
/*   Updated: 2020/10/11 18:30:19 by rhoorntj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		hash(t_lemin *l, int *i, char c)
{
	int		odd;
	int		key;
	int		oups;

	key = 0;
	oups = *i + 1;
	while (l->line[++(*i)] != c && l->line[*i] != '\n')
	{
		odd = ((*i - oups) % 2) ? 3 : 2;
		key = (key * 19) + l->line[*i] - odd + ((l->line[*i] - 32) * odd) + 32;
	}
	return (key % HASH_SIZE);
}

int		free_edge(t_edge *ed)
{
	free(ed);
	ed = NULL;
	return (0);
}

void	check_exit_entry(t_lemin *l, t_edge *ed)
{
	if ((ed->predecessor->key == l->start_node->key)
	|| (ed->successor->key == l->start_node->key))
		l->nb_start_out += 1;
	if ((ed->predecessor->key == l->end_node->key)
	|| (ed->successor->key == l->end_node->key))
		l->nb_end_in += 1;
}
