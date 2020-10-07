#include "../includes/lemin.h"

void  dispatch_ant_in_path(t_lemin *lemin)
{
  // printf("in dispatch\n");
  int i;
  int j;
  int p1;
  int p2;

  if(!(lemin->ant_tab = ft_memalloc(sizeof(t_ant) * lemin->nb_ants)))
    return;
  i = 0;
  j = 0;
  while ( i < lemin->nb_ants)
  {
    // printf("11\n");
    while(j < lemin->nb_final_path)
    {
      p1 = lemin->len_tab[j] + i;
      p2 = lemin->len_tab[j+ 1];

      if ( j == (lemin->nb_final_path - 2)) // avant dernier
      {
        if(p1 > p2)
        {
          init_ants(lemin->ant_tab, i, lemin->final_path_tab[j + 1]);
          lemin->len_tab[j+ 1] += 1;
          j++;
          i++;
        }
        else
          {
            init_ants(lemin->ant_tab, i, lemin->final_path_tab[0]);
            lemin->len_tab += 1;
            j = 0;
            i++;
          }
      }
      else
      {
        if (p1 > p2)
          {
            init_ants(lemin->ant_tab, i, lemin->final_path_tab[j + 1]);
            lemin->len_tab[j+ 1] += 1;
            j++;
            i++;
          }
        else
          {
            init_ants(lemin->ant_tab, i, lemin->final_path_tab[j]);
            lemin->len_tab[j] += 1;
            i++;
          }
      }
    }
  }
}

// void choose_path_for_ants(int p1, int p2, t_lemin *lemin)
// {
//
// }

void init_ants(t_ant **tab, int ant, t_path *path)
{
  // printf("in init ants\n");
    t_ant *new;

      if(!(new = ft_memalloc(sizeof(t_ant))))
        return;
      new->ant = ant+1;
      new->end = 0;
      new->no_print = 0;
      new->path = path;
      new->node = NULL;
      tab[ant] = new;
}

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
