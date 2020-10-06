#include "../includes/lemin.h"

void init_ants(t_ant **tab, int nb_ant, t_path *path)
{
  // printf("in init ants\n");
    int i;
    t_ant *new;

    i = 0;
    while( i < nb_ant)
    {
      if(!(new = ft_memalloc(sizeof(t_ant))))
        return;
      new->ant = i+1;
      new->end = 0;
      new->no_print = 0;
      new->path = path;
      new->node = NULL;
      tab[i] = new;
      // printf("tab[%d] - %d node [%p]\n", i, tab[i]->ant, tab[i]->node);
      // free(new);
      i++;
    }
    // printf("\n");
    // i = 0;
    // while( i < nb_ant)
    // {
    //   printf("tab[%d] - %d\n",i, tab[i]->ant);
    //   i++;
    // }
}

void update_ant(t_ant **tab, int nb_ant, t_lemin *lemin)
{
  // printf("in update ant\n");
  int i;

  i = 0;
  while (i < nb_ant)
  {
      if(tab[i]->node == NULL)
      {
            move_ant(tab[i], lemin);
              // printf("====out of UPDate\n");
            // printf("return\n");
            return;
        }
      else
        move_ant(tab[i], lemin);
    i++;
  }
  // printf("====out of UPDate\n");
}

void move_ant(t_ant *ant, t_lemin *lemin)
{
  // printf("in move ant\n");
  if (ant->end == 0)
  {
    if( ant->node == NULL)
    {
      ant->node = ant->path->node;
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
