#include "../includes/lemin.h"
//
void create_dup_room(t_lemin *lemin, t_node *node)
{

	node->duplicated = 1;
	node->dup_out = malloc(sizeof(t_node));
	node->dup_out->name = node->name;
	node->dup_out->reach_cost = 0;
	node->dup_out-> infinity = 1;
}
//
void suurballe(t_lemin *lemin, int path_index)
{
  int i;
  t_path *index;
  t_edge *edge;
  t_node *pre_path;
  t_node *suc_path;

  printf("in suurballe\n");
//
  index = lemin->path_tab[path_index];
  while(index->next)
  {
    pre_path = index->node;
    suc_path = index->next->node;
    i = 0;
	edge = lemin->edge_tab;

    while (edge)
    {
        // printf("pre %s suc %s ------ edge pre [%s]  edge suc [%s]\n", pre->name,suc->name, edge->predecessor->name, edge->successor->name);
      if ((pre_path == edge->predecessor) && (suc_path == edge->successor))
      {
        // printf("pre %s VS [%s] // suc %s VS [%s]\n", pre, lemin->edge_tab[i]->predecessor, suc, lemin->edge_tab[i]->successor);
        edge->weight = -1;
        if (suc_path != lemin->start_node)
          create_dup_room(lemin, suc_path);
          // printf("[%s][%s] visite [%d]\n", lemin->edge_tab[i]->predecessor, lemin->edge_tab[i]->successor, lemin->edge_tab[i]->visited);
      }
      if ((suc_path == edge->predecessor) && (pre_path == edge->successor))
      {
        // printf("suc %s VS PRE-tab[%s] // pre %s VS SUC-tab[%s]\n", suc, lemin->edge_tab[i]->predecessor, pre, lemin->edge_tab[i]->successor);
        // lemin->edge_tab[i]->weight = lemin->number_of_edges * 10;
        edge->visited = 1;
        // printf("[%s][%s] visite [%d]\n", lemin->edge_tab[i]->predecessor, lemin->edge_tab[i]->successor, lemin->edge_tab[i]->visited);
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
