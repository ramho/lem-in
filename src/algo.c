#include "../includes/lemin.h"

// sauvegarde le chemin trouver par bellmanford dans un tableau
void save_path(t_lemin *lemin, int index_path)
{
  t_node *tmp;
  t_path *new;
  t_path *head;
  t_path *index;
  int i;

  i = 0;
  tmp = NULL;
  head = malloc(sizeof(t_path));
  lemin->path_tab[index_path] = head;
	head->node = lemin->end_node;
  new = malloc(sizeof(t_path));
  new->node = lemin->node_tab[1]->predecessor; // should be a t_node * in structure
  new->next = NULL;
  head->next = new;
  i = 1;
  while (i < lemin->number_of_nodes)
  {
    if (ft_strcmp(new->node, lemin->node_tab[i]->name) == 0) // compare pointers ?
    {
      // free(new); // bug
      lemin->node_tab[i]->visited += 1;
      new = malloc(sizeof(t_path));
      new->node = ft_strdup(lemin->node_tab[i]->predecessor);
      new->next = NULL;
      i = 0;
      index = head;
      while (index->next!= NULL)
        index = index->next;
      index->next = new;
    }
    i++;
  }
  // !\\not part of code, just to print shortest path
  // index = head;
  // printf("shortest path is: ");
  // while (index != NULL)
  // {
  //   printf("%s ", index->node);
  //   index = index->next;
  // }
  // printf("\n");
}

void init_infinity_and_reach_cost(t_lemin *lemin)
{
	int i;

	i = 1;
	while ( i < lemin->number_of_nodes)
	{
		lemin->node_tab[i]->infinity = 1;
    	lemin->node_tab[i]->reach_cost = 0;
		printf("predecessor is %s\n", lemin->node_tab[i]->predecessor);
		if(lemin->node_tab[i]->predecessor)
			free(lemin->node_tab[i]->predecessor);

		i++;
	}
}

void start_algo(t_lemin *lemin)
{
	int i;
	int x;

  // printf("nb of edges %d\n", lemin->number_of_edges);
  printf("nb of path %d\n", lemin->nb_path);

	lemin->path_tab = malloc(sizeof(t_path *) * lemin->nb_path);
	x = 0;
	while (x < lemin->nb_path)
	{
		i = lemin->number_of_nodes;
		while(--i)
		{
      bellman_ford(lemin);
			// if(bellman_ford(lemin) == 0)
			// 	break;
		}
    // printf("reach cost end to start [%d]\n", lemin->node_tab[1]->reach_cost);
    // bellman_ford(lemin);
    save_path(lemin, x);
		suurballe(lemin, x);
    printf("apre suurballe\n");
    i = 0;
    while(i < lemin->number_of_edges)
    {
      printf("[%s][%s] w[%d] visité [%d]\n", lemin->edge_tab[i]->predecessor,lemin->edge_tab[i]->successor,lemin->edge_tab[i]->weight, lemin->edge_tab[i]->visited);
      i++;
    }
		init_infinity_and_reach_cost(lemin);
		x++;
    printf("----------------------------------------------------------------------\n");
	}
	//!\\ not part of code, print different path
	t_path *index;
	i = 0;
	while(i < lemin->nb_path)
	{
		index = lemin->path_tab[i];
		while (index != NULL)
		{
			printf("%s ", index->node);
			index = index->next;
		}
		i++;
		printf("\n");
	}
}
