#include "../includes/lemin.h"

void get_path(t_lemin *lemin)
{
  int path;

  path = 0;
  select_path(lemin);
  // ! \\ not for code
  // for (i = 0; i < lemin->number_of_edges; i++)
  //   printf("edge [%s][%s] no_go [%d]\n", lemin->edge_tab[i]->predecessor, lemin->edge_tab[i]->successor, lemin->edge_tab[i]->no_go);
  // printf("in get path\n");

  while (i < lemin->nb_path)
  {
    if (get_next_node(lemin->node_tab[0]) == 1)// has to be starting node
      path += 1;
    i++;
  }

}

int get_next_node(t_node *start)
{

  links = start->links;
  while (links)
  {
    if (lemin->edge_tab[hash_code(lemin->node_tab[i], links, ...)]->no_go == 0) // si edge est bon
    {
      add_node_link_to_final_path(link);
      if (new_link = lemin->node_end)
        return (1);
      if (get_next_node(link) == 1)
          return (1);
    }
    else if// si edge est pas bon
    links = links-next;
  }
  return(-1);
}

void select_path(t_lemin *lemin) // savoir si les edge sont doubles ou pas, dans le parsing voir si on peut eviter les doubles
{
  int i;
  printf("enter select path\n");
  i = 0;

  while (i < lemin->number_of_edges)
  {
    if (lemin->edge_tab[i]->reverse)
    {
      if (lemin->edge_tab[i]->visited == 1 && lemin->edge_tab[i]->reverse->visited == 1)
      {
        lemin->edge_tab[i]->no_go = 1;
        lemin->edge_tab[i]->reverse->no_go = 1;
      }
    }
    i++;
  }

}
