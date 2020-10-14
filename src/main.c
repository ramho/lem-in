/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoorntj <rhoorntj@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 17:33:10 by rhoorntj          #+#    #+#             */
/*   Updated: 2020/10/13 15:48:58 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	get_file_content(t_lemin *lemin)
{
	if (LEMIN_READ_BUFF < 1 || read(0, lemin->buff, 0) < 0)
		free_lemin(lemin);
	ft_bzero(lemin->buff, LEMIN_READ_BUFF);
	// lemin->direct = 0;
	while ((lemin->ret = read(0, lemin->buff, LEMIN_READ_BUFF)) > 0)
	{
		lemin->buff[lemin->ret] = 0;
		if (!(parse_buff(lemin))) // ?
			free_lemin(lemin); // ? break meme si code est bon ?
	}
	if (lemin->nb_start_out == 0 || lemin->nb_end_in == 0)
		exit(1);
	if (lemin->nb_start_out == lemin->nb_end_in)
		lemin->nb_path = lemin->nb_start_out;
	else if (lemin->nb_start_out > lemin->nb_end_in)
		lemin->nb_path = lemin->nb_end_in;
	else if (lemin->nb_start_out < lemin->nb_end_in)
		lemin->nb_path = lemin->nb_start_out;
}

int main()
{
	t_lemin *lemin;

	if (!(lemin = ft_memalloc(sizeof(t_lemin))))
		return (-1);
	get_file_content(lemin);
	if(lemin->direct == 1)
		print_direct(lemin);
	start_algo(lemin);
	if (lemin->nb_bellmanf_path < 1)
		return (0);
	get_path(lemin);
	print_path(lemin);
	// free_ants();
	return (0);
}
