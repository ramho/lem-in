/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoorntj <rhoorntj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 17:31:27 by rhoorntj          #+#    #+#             */
/*   Updated: 2020/10/07 17:50:32 by rhoorntj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void print_path(t_lemin *lemin)
{
  printf("in printf path ants [%d]\n", lemin->nb_ants);
  printf("\n");
  int i;

    if(!(lemin->ant_tab = ft_memalloc(sizeof(t_ant) * lemin->nb_ants)))
      return;
      i = 0;
    if (lemin->nb_final_path == 1)
    {
      while( i < lemin->nb_ants )
      {
        init_ants(lemin->ant_tab, i,lemin->final_path_tab[0]);
        i++;
      }
    }
    else
      dispatch_ant_in_path(lemin);

	 //NOT FOR CODE
	 // i = 0;
	 // while ( i < lemin->nb_ants)
	 // {
		//  printf("start of room is [%s]\n",lemin->ant_tab[i]->path->node->name);
		//  i++;
	 // } NOT FOR CODE

    lemin->ant_in_end = 0;
	int count = 0;
    while (lemin->ant_in_end < lemin->nb_ants)
    {
      // i = 0;
      // while (i < lemin->nb_final_path)
      // {
      update_ant(lemin->ant_tab, lemin->nb_ants, lemin);
      print_ant(lemin->ant_tab, lemin->nb_ants, lemin);

    //   i++;
    // }
      printf("\n");
	  count++;
    }
	printf("lines %d\n", count);
}

void print_ant(t_ant **tab, int nb_ant, t_lemin *lemin)
{
  // printf("in print ant \n");
  int i;

  i = 0;
  while ( i < nb_ant)
  {
    if (tab[i]->node != NULL && tab[i]->no_print == 0)
    {
        printf("L%d-%s ", tab[i]->ant, tab[i]->node->name);
    }
    if (tab[i]->node == lemin->end_node)
      tab[i]->no_print = 1;
    i++;
  }
  // printf("\n");
}
