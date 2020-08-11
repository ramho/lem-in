#include "lemin.h"

void get_links( t_lemin *lemin)
{
  int i;
  int j;
  int k;

  i = 0;
  lemin->edges_tab =malloc(sizeof(char *));
  while(lemin->file_links[i])
  {
    j = 0;
    while(j < ft_strlen(lemin->file_links[i]))
    {
      while (lemin->file_links[i][j] != '-')
        j++;
      lemin->edges_tab[i] =malloc(sizeof(char *));
      lemin->edges_tab[i]->predecessor = ft_strsub(lemin->file_links[i], 0, j);
      k = j + 1;
      while (lemin->file_links[i][j])
        j++;
      lemin->edges_tab[i] =malloc(sizeof(char *));
      lemin->edges_tab[i]->successor = ft_strsub(lemin->file_links[i],k, j);
      lemin->edges_tab[i]->weight = 1;

    }
  i++;
  }
  lemin->number_of_edges = i;
}
