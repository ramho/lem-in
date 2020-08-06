#include "lemin.h"

void get_links( t_lemin *lemin)
{
  char *edge1;
  char *edge2;
  int i;
  int j;
  int k;

  i = 0;
  while(lemin->file_links[i])
  {
    j = 0;
    while(j < ft_strlen(lemin->file_links[i]))
    {
      while (lemin->file_links[i][j] != '-')
        j++;
      edge1 = ft_strsub(lemin->file_links[i], 0, j);
      k = j + 1;
      while (lemin->file_links[i][j])
        j++;
      edge2 = ft_strsub(lemin->file_links[i],k, j);
      save_links(edge1, edge2, lemin);
      // ft_strdel(&edge1);
      // ft_strdel(&edge2);
    }
  i++;
  }
  // printf("name %s link %s\n", lemin->tab[hash_code(lemin,edge1)]->name, lemin->tab[hash_code(lemin,edge1)]->link[0]);
}

void save_links(char *edge1, char *edge2, t_lemin *lemin)
{
  int i;
  printf("1 %s et 2 %s\n", edge1, edge2);
  i = 0;
  if (lemin->tab[hash_code(lemin, edge1)]->link[i] != NULL)
  {
    while (lemin->tab[hash_code(lemin, edge1)]->link[i])
    {
      // if ( lemin->tab[hash_code(lemin, edge1)]->link[i] == edge2)
      //   return;
      i++;
    }
    lemin->tab[hash_code(lemin, edge1)]->link[i]=malloc(sizeof(char));
    lemin->tab[hash_code(lemin, edge1)]->link[i] = edge2;
  }
  else
  {
    lemin->tab[hash_code(lemin, edge1)]->link[i]=malloc(sizeof(char));
    lemin->tab[hash_code(lemin, edge1)]->link[i] = edge2;
  }
}
