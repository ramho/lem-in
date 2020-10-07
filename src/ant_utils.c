/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoorntj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 17:54:32 by rhoorntj          #+#    #+#             */
/*   Updated: 2020/10/07 17:54:35 by rhoorntj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void update_ant(t_ant **tab, int nb_ant, t_lemin *lemin)
{
  // printf("in update ant\n");
  int i;
  int flag;

  i = 0;
  flag = lemin->nb_final_path;
  while (i < nb_ant)
  {
      if(tab[i]->node == NULL)
      {
            move_ant(tab[i], lemin);
            // flag--;
            // if (flag != 1)
            // {
              // printf("i [%d] final path [%d]\n", i, lemin->nb_final_path);
              return;
            // }
        }
      else
        move_ant(tab[i], lemin);
    i++;
  }

}

void move_ant(t_ant *ant, t_lemin *lemin)
{
  // printf("in move ant\n");
  if (ant->end == 0)
  {
    if( ant->node == NULL)
    {
      ant->node = ant->path->node;
      // printf("node is %s\n", ant->path->node->name);
    }
    else
    {
      ant->path = ant->path->next;
      ant->node = ant->path->node;
    }
  if (ant->node == lemin->end_node)
  {
    lemin->ant_in_end += 1;
    ant->end = 1;
  }
}
}
