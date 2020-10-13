/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoorntj <rhoorntj@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 17:10:23 by rhoorntj          #+#    #+#             */
/*   Updated: 2020/10/13 15:44:41 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	parse_ant(t_lemin *l)
{
	int i;

	i = -1;
	while (l->line[++i] != '\n')
	{
		if (l->line[i] >= '0' && l->line[i] <= '9')
		{
			l->nb_ants *= 10;
			l->nb_ants += (l->line[i] - '0');
		}
		else
			free_struct(l) ; // "ERROR : wrong nb_ant format\n"
		if (l->nb_ants < 0 || l->nb_ants > INT_MAX)
			free_struct(l) ; // "ERROR : not positive int\n"
	}
	l->parse_flag = 1;
}

int		parse_command(t_lemin *l)
{
	if (!(ft_strncmp("##start\n", l->line, 8)))
	{
		if (l->start_room || l->end_room == 1)
			return (0);
		l->start_room++;
	}
	if (!(ft_strncmp("##end\n", l->line, 6)))
	{
		if (l->end_room || l->start_room == 1)
			return (0);
		l->end_room++;
	}
	return (1);
}

int		parse_flag_one(t_lemin *l)
{
	if (!l->tiret)
	{
		if (!(parse_nodes(l)))
			return (0);
	}
	else
	{
		if (l->start_room + l->end_room != 4)
			return (0); // "ERROR : no start or end room."
		l->parse_flag++;
		if (!(parse_edges(l, -1, 0, 0)))
			return (0);
	}
	return (1);
}

int		parse_line(t_lemin *l)
{
	if (l->hash_tag == 1)
		NULL;
	else if (l->hash_tag == 3)
	{
		if (!(parse_command(l)))
			return (0);
	}
	else if (l->parse_flag == 2 && !l->space)
	{
		if (!(parse_edges(l, -1, 0, 0)))
			return (0);
	}
	else if (l->parse_flag == 1)
	{
		if (!(parse_flag_one(l)))
			return (0);
	}
	else if (!l->parse_flag)
		parse_ant(l);
	else
		return (0); // "ERROR : wrong line format\n"
	l->hash_tag = 0;
	l->space = 0;
	l->tiret = 0;
	return (1);
}
