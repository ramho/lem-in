#include "../includes/lemin.h"
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
    if (ft_strcmp(new->node, lemin->node_tab[i]->name) == 0)
    {
      // free(new); // bug
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
  //!\\not part of code, just to print shortest path
  // index = head;
  // printf("shortest path is: ");
  // while (index != NULL)
  // {
  //   printf("%s ", index->node);
  //   index = index->next;
  // }
  // printf("\n");
}

void init_infinity(t_lemin *lemin)
{
	int i;

	i = 1;
	while ( i < lemin->number_of_nodes)
	{
		lemin->node_tab[i]->infinity = 1;
		i++;
	}
}

void start_algo(t_lemin *lemin)
{
	int i;
	int number_of_path;
	int x;

	number_of_path = 2; // sera sauvegardé dans struct lemin, nb_path
	lemin->path_tab = malloc(sizeof(t_path *) * number_of_path);
	x = 0;
	while (x < number_of_path)
	{
		i = 0;
		while(i < lemin->number_of_nodes)
		{
			bellman_ford(lemin);
			i++;
		}
    printf("reach cost end to start [%d]\n", lemin->node_tab[1]->reach_cost);
		save_path(lemin, x);
		suurballe(lemin, x);
		init_infinity(lemin);
		x++;
	}
	//!\\ not part of code, print different path
	t_path *index;
	i = 0;
	while(i < number_of_path)
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
