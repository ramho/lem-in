#include "../includes/lemin.h"
//
void create_dup_room(t_lemin *lemin, t_node *node)
{

	node->duplicated = 1;
	node->dup_out = malloc(sizeof(t_node));
	node->dup_out->name = node->name;
	node->dup_out->reach_cost = 0;
	node->dup_out->infinity = 1;
}
//
void suurballe(t_lemin *lemin, int path_index)
{
  t_path *index;
  t_edge *edge;
  t_node *pre_path;
  t_node *suc_path;

	// printf("\n------------\n");
  // printf("in suurballe\n");
  // printf("------------\n\n");

  index = lemin->path_tab[path_index];
  while(index->next)
  {
    pre_path = index->node;
    suc_path = index->next->node;
	edge = lemin->edge_tab;
    while (edge)
    {
      if ((pre_path == edge->predecessor) && (suc_path == edge->successor))
      {
        edge->weight = -1;
        if (suc_path != lemin->start_node)
          create_dup_room(lemin, suc_path);
      }
	  if ((pre_path->name == edge->reversed->predecessor->name) && (suc_path->name == edge->reversed->successor->name))
	  {
		edge->reversed->weight = -1;
		if (suc_path != lemin->start_node)
		  create_dup_room(lemin, suc_path);
	  }
      if ((suc_path == edge->predecessor) && (pre_path == edge->successor))
      {
        edge->visited = 1;
      }
	  if ((suc_path->name == edge->reversed->predecessor->name) && (pre_path->name == edge->reversed->successor->name))
      {
        edge->reversed->visited = 1;
      }
      edge = edge->next;
    }
    index = index->next;
  }
//   //!\\ not part of code, check the content of the edges
//   i = 0;
//   while(i < lemin->number_of_edges)
//   {
//     // printf("[%s][%s] w[%d] visité [%d]\n", lemin->edge_tab[i]->predecessor,lemin->edge_tab[i]->successor,lemin->edge_tab[i]->weight, lemin->edge_tab[i]->visited);
//     i++;
//   }
}
