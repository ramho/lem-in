#include "../includes/lemin.h"

void get_path(t_lemin *lemin)
{
  int i;
  int j;
  int k;
  int nb_path = 2; // will be a value that is calculated and stored in lemin after
  t_path *head;
  t_path *index;

  i = 0;
  k = 0;
  lemin->final_path_tabs = malloc(sizeof(t_path *) * nb_path);
  head = malloc(sizeof(t_path));s
  index = lemin->final_path_tabs[k];
	while (i < lemin->number_of_nodes)
	{
		j = 0;
		while (j < lemin->number_of_edges)
		{
			if (ft_strcmp(lemin->node_tab[i]->name,lemin->edge_tab[j]->predecessor) == 0)
      {
        if(lemin->edge_tab[j]->visited == 1)
          index->name = ft_strdup(lemin->edge_tab[j]->successor);
      }

			j++;
		}
		i++;
	}

}
 
