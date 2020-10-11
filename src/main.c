/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoorntj <rhoorntj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 17:33:10 by rhoorntj          #+#    #+#             */
/*   Updated: 2020/10/11 17:11:38 by rhoorntj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	get_file_content(t_lemin *lemin)
{
	if (LEMIN_READ_BUFF < 1 || read(0, lemin->buff, 0) < 0)
		return ;
	ft_bzero(lemin->buff, LEMIN_READ_BUFF);
	while ((lemin->ret = read(0, lemin->buff, LEMIN_READ_BUFF)) > 0)
	{
		lemin->buff[lemin->ret] = 0;
		if (!(parse_buff(lemin)))
			break ;
	}
	printf("[%d][%d] -- [%d]\n", lemin->nb_start_out, lemin->nb_end_in, lemin->nb_ants);
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
	float temps;
	clock_t t1, t2, t3;
	t_lemin *lemin;

	t1 = clock();
	if (!(lemin = ft_memalloc(sizeof(t_lemin))))
        return (-1);
	get_file_content(lemin);
	t2 = clock();
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	start_algo(lemin);
	// printf("ret = %d\n", ret);
	if (lemin->nb_bellmanf_path < 1)
		return(0);
	get_path(lemin);
	print_path(lemin);

	// printf("out\n");
	t3 = clock();
	temps = (float)(t3-t1)/CLOCKS_PER_SEC;
	printf("temps = %f\n", temps);
	return(0);
}
