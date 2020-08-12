#include "lemin.h"

int  seperate_nodes_links(t_lemin *lemin)
{
  int i;
  printf("in seperate nodes n links\n");

  i = 1;
  printf("here 111\n");
  lemin->file_edges = malloc(sizeof(char *) * lemin->table_size);
  printf("here 222\n");
  lemin->file_nodes = malloc(sizeof(char *) * lemin->table_size);
  printf("here 333\n");
  lemin->number_of_edges = 0;
  lemin->number_of_nodes = 2;
  printf("here \n");
  while (lemin->file[i] != NULL)
  {
    if (lemin->file[i][0] == '#' && lemin->file[i][1] == '#')
      get_start_or_end_piece(&i, lemin);
    else if (ft_strchr(lemin->file[i], '-'))
    {
      lemin->file_edges[lemin->number_of_edges] = ft_strdup(lemin->file[i]);
      lemin->number_of_edges++;
    }
    else if (ft_isalnum(lemin->file[i][0]))
    {
       lemin->file_nodes[lemin->number_of_nodes] = ft_strdup(lemin->file[i]);
       lemin->number_of_nodes++;
     }
    else if (lemin->file[i][0] == '#' && lemin->file[i][1] != '#')
      continue;
    i++;
  }
  // printf("nods %d - edge %d\n", lemin->number_of_nodes,lemin->number_of_edges);
  for ( i = 0; i < lemin->number_of_edges; i++)
    printf("edges are %s\n", lemin->file_edges[i]);
  printf("\n");
  for ( i = 0; i < lemin->number_of_nodes; i++)
      printf("nodes are %s\n", lemin->file_nodes[i]);
  return(1);
}
