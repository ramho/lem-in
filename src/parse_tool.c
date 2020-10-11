/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoorntj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 17:07:32 by rhoorntj          #+#    #+#             */
/*   Updated: 2020/10/11 17:08:21 by rhoorntj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

// -----parse_tool.c--------
int		hash(t_lemin *l, int *i, char c)
{
	int odd;
	int key;
	int oups;

	key = 0;
	oups = *i + 1;
	while (l->line[++(*i)] != c && l->line[*i] != '\n')
	{
		odd = ((*i - oups) % 2) ? 3 : 2;
		key = (key * 19) + l->line[*i] - odd + ((l->line[*i] - 32) * odd) + 32;
	}
	return (key % HASH_SIZE);
}
// -----parse_tool.c END----"
