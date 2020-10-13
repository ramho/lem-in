/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_buff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoorntj <rhoorntj@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 17:10:48 by rhoorntj          #+#    #+#             */
/*   Updated: 2020/10/13 15:28:53 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		is_valid_char(t_lemin *l)
{
	if (!l->i_line && l->buff[l->i] == 'L') // si c'est le 1er caractere de la ligne && que c'est un 'L'
		return (0);
	if ((l->buff[l->i] >= 'a' && l->buff[l->i] <= 'z') ||
			(l->buff[l->i] >= 'A' && l->buff[l->i] <= 'Z') ||
			(l->buff[l->i] >= '0' && l->buff[l->i] <= '9') ||
			(l->buff[l->i] == '#') || (l->buff[l->i] == ' ') ||
			(l->buff[l->i] == '-') || (l->buff[l->i] == '_') ||
			(l->buff[l->i] == ':'))
		return (1);
	return (0);
}

void	do_valid_char_op(t_lemin *l)
{
	if (((l->buff[l->i] == '#') && l->i_line < 2))
		l->hash_tag += (l->i_line + 1);
	if (l->buff[l->i] == ' ')
		l->space += 1;
	if (l->buff[l->i] == '-')
		l->tiret += 1;
	l->line[l->i_line] = l->buff[l->i];
	l->i++;
	l->i_line++;
}

int		do_end_line_op(t_lemin *l)
{
	if (!l->i_line)
	{
		printf("ERROR : empty line\n");
		return (0);
	}
	l->line[l->i_line] = l->buff[l->i];
	l->line[l->i_line + 1] = 0;
	if (!(parse_line(l)))
		l->error = l->i_line + 1;
	if (l->end_buff && !l->end_line)
	{
		if (l->error)
			return (0);
		write(1, l->line, l->i_line + 1);
		l->end_buff = 0;
		l->rest = l->i + 1;
	}
	l->i++;
	l->end_line = l->i - l->error;
	l->i_line = 0;
	return (1);
}

void	write_buff_op(t_lemin *l)
{
	if (l->end_line)
	{
		if (l->end_line - l->rest)
			write(1, &l->buff[l->rest], l->end_line - l->rest);
		l->rest = 0;
		l->end_line = 0;
	}
	if (l->i_line)
		l->end_buff = 1;
	l->i = 0;
}

int		parse_buff(t_lemin *l)
{
	while (l->buff[l->i])
	{
		if (is_valid_char(l))
		{
			do_valid_char_op(l);
		}
		else if (l->buff[l->i] == '\n')
		{
			if (!(do_end_line_op(l)))
				return (0);
		}
		else
			return (0);
		if (!l->buff[l->i] || l->error)
		{
			write_buff_op(l);
			return (1);
		}
	}
	return (1);
}
