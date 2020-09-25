#include "../includes/lemin.h"

void get_path(t_lemin *lemin)
{
	printf("in get path\n");
  // int path;

  // path = 0;
  select_path(lemin);
  // ! \\ not for code
	printf("\n\n\n");
  t_edge *index;
index = lemin->edge_tab;
  while (index)
   { printf("edge [%s][%s] no_go [%d]\n", index->predecessor->name, index->successor->name, index->no_go);
   printf("reversed edge [%s][%s] no_go [%d]\n\n", index->reversed->predecessor->name, index->reversed->successor->name, index->reversed->no_go);

		index=index->next;
}


  // while (i < lemin->nb_path)
  // {
  //   if (get_next_node(lemin->node_tab[0]) == 1)// has to be starting node
  //     path += 1;
  //   i++;
  }

// }
//
// int get_next_node(t_node *start)
// {
//
//   links = start->links;
//   while (links)
//   {
//     if (lemin->edge_tab[hash_code(lemin->node_tab[i], links, ...)]->no_go == 0) // si edge est bon
//     {
//       add_node_link_to_final_path(link);
//       if (new_link = lemin->node_end)
//         return (1);
//       if (get_next_node(link) == 1)
//           return (1);
//     }
//     else if// si edge est pas bon
//     links = links-next;
//   }
//   return(-1);
// }
//
void select_path(t_lemin *lemin) // savoir si les edge sont doubles ou pas, dans le parsing voir si on peut eviter les doubles
{
  t_edge *edge;
  printf("enter select path\n");

	edge = lemin->edge_tab;
  while (edge)
  {
    // if (edge->reversed)
    // {
		printf("reversed\n");
		printf("edge [%s][%s] visited [%d]\n", edge->predecessor->name, edge->successor->name, edge->visited);
	    printf("reversed edge [%s][%s] visited [%d]\n\n", edge->reversed->predecessor->name, edge->reversed->successor->name, edge->reversed->visited);
      if (edge->visited == 1 && edge->reversed->visited == 1)
      {
        edge->no_go = 1;
        edge->reversed->no_go = 1;
      }
    // }
    edge = edge->next;
  }

}
