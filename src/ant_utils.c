/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoorntj <rhoorntj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 17:54:32 by rhoorntj          #+#    #+#             */
/*   Updated: 2020/10/11 16:47:46 by rhoorntj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void update_ant(t_ant **tab, int nb_ant, t_lemin *lemin)
{
  // printf("in update ant\n");
  int i;
  static int flag;

  i = 0;
  flag = 0;
  while (i < nb_ant)
  {
      if(tab[i]->node->name == NULL)
      {
            flag += move_ant(tab[i], lemin);
            // printf("flag [%d]\n", flag);
            if (flag % lemin->nb_bellmanf_path == 0)
            {
              return;
            }
        }
      else
        move_ant(tab[i], lemin);
    i++;
  }

}

int move_ant(t_ant *ant, t_lemin *lemin)
{
  // printf("in move ant\n");
  if (ant->end == 0)
  {
    // printf("in IF ant [%p] [%s] ant in path[%p]\n", ant, ant->node->name, ant->path);
    if( ant->node->name == NULL)
    {
      if( ant->path->ant == 1)
        return (0);
      // printf("hallo 11\n");
      ant->node = ant->path->node;
      // printf("hallo22\n");
      ant->path->ant = 1;
      // printf("hallo33\n");
    }
    else
    {
      // printf("in ELSE\n");
      ant->path->ant = 0;
      ant->path = ant->path->next;
      ant->path->ant = 1;
      ant->node = ant->path->node;
    }
    if (ant->node == lemin->end_node)
    {
      // printf ("in if END NODE\n");
      lemin->ant_in_end += 1;
      ant->end = 1;
    }
  }
  return(1);
}

void	init_ants(t_ant **tab, int ant, t_path *path)
{
	t_ant	*new;
  // printf(" in INIT ANTS , path [%p]\n", path);
	if (!(new = ft_memalloc(sizeof(t_ant))))
		return ;
	new->ant = ant+1;
	new->end = 0;
	new->no_print = 0;
	new->path = path;
	new->node = ft_memalloc(sizeof(t_node));
	tab[ant] = new;
}
