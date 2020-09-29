#include "../includes/lemin.h"

void get_path(t_lemin *lemin)
{
	// printf("in get path\n");
  int path;
	int i;

  select_path(lemin);
  // ! \\ not for code
// 	printf("\n\n\n");
// 	printf("after select path\n\n");
//   t_edge *index;
// index = lemin->edge_tab;
//   while (index)
//    { printf("edge [%s][%s] no_go [%d]\n", index->predecessor->name, index->successor->name, index->no_go);
//    printf("reversed edge [%s][%s] no_go [%d]\n\n", index->reversed->predecessor->name, index->reversed->successor->name, index->reversed->no_go);
//
// 		index=index->next;
// }
// printf("out of select path\n");
	lemin->final_path_tab = ft_memalloc(sizeof(t_path) * lemin->nb_final_path);
	path = 0;
	i = 0;
  while (i < lemin->nb_final_path)
  {
    if (get_next_node(lemin->start_node, lemin, path) == 1)// has to be starting node
      path += 1;
    i++;
  }

}


void add_node_link_to_final_path(t_lemin *lemin, t_link *link, int i)
{
	t_path *new;
	t_path *index;

	new = ft_memalloc(sizeof(t_path));
	new->node = link->room;
	new->next = NULL;
	if (!(lemin->final_path_tab[i]))
		lemin->final_path_tab[i] = new;
	else
	{
		// index = lemin->final_path_tab[i];
		// while (index)
		// 	index = index->next;
		// index = new;
			new->next = lemin->final_path_tab[i];
			lemin->final_path_tab[i] = new;
	}
}

int get_next_node(t_node *start, t_lemin *lemin, int i)
{
	// printf("in get next node\n");
	t_link *link;
	t_edge *edge;

	link = ft_memalloc(sizeof(t_link));
	link = start->links;
	edge = malloc(sizeof(t_edge));
	edge = lemin->edge_tab;
	// printf("link [%s]\n",link->room->name);
	while (link)
	{
		while (edge)
		{
			if (edge->predecessor == start && edge->successor == link->room && edge->no_go == 0) // si edge est bon
			{
				add_node_link_to_final_path(lemin, link, i);
				if (link->room == lemin->end_node)
					return (1);
				if (get_next_node(link->room, lemin, i) == 1)
					return (1);
			}
			else // si edge est pas bon
				edge = edge->next;
		}
		link = link->next;
	}
	return(1);
}

void select_path(t_lemin *lemin) // savoir si les edge sont doubles ou pas, dans le parsing voir si on peut eviter les doubles
{
  t_edge *edge;
  // printf("enter select path\n");


	edge = malloc(sizeof(t_edge));
	// printf("11 edge tab[%s]\n", lemin->edge_tab->predecessor->name);
	edge = lemin->edge_tab;
	// printf("here\n");
  while (edge)
  {
	  // printf("there\n");
    if (edge->reversed)
    {
		// printf("reversed\n");
		// printf("edge [%s][%s] visited [%d]\n", edge->predecessor->name, edge->successor->name, edge->visited);
	    // printf("reversed edge [%s][%s] visited [%d]\n\n", edge->reversed->predecessor->name, edge->reversed->successor->name, edge->reversed->visited);
      if (edge->visited == 1 && edge->reversed->visited == 1)
      {
        edge->no_go = 1;
        edge->reversed->no_go = 1;
      }
    }
    edge = edge->next;
  }

}
