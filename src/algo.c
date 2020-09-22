#include "../includes/lemin.h"

// sauvegarde le chemin trouver par bellmanford dans un tableau
void save_path(t_lemin *lemin, int index_path)
{
	// printf("in save path\n");
	t_path *new;
	t_path *head;
	t_path *index;


	// printf("reach cost each node %d\n", lemin->end_node->reach_cost);

	head = malloc(sizeof(t_path));
	lemin->path_tab[index_path] = head;
	head->node = lemin->end_node;
	new = malloc(sizeof(t_path));
	new->node = head->node->predecessor;
	new->next = NULL;
	head->next = new;
	// printf("5.5 %s \n", new->node->name);
	while (new->node->predecessor)// != lemin->start_node->name)
	{
		index = head;
		while (index->next != NULL)
			index = index->next;
		new = malloc(sizeof(t_path));
		new->node = index->node->predecessor;
		index->next = new;
		if(new->node == lemin->start_node)
			break;
	}
	//
	//
	//
	// // !\\not part of code, just to print shortest path
	index = head;
	printf("shortest path[%d] is: ", index_path);
	while (index != NULL)
	{
		printf("%s ", index->node->name);
		index = index->next;
	}
	printf("\n\n");
}

//
void init_infinity_and_reach_cost(t_lemin *lemin)
{
	int i;
	int j;

	i = 1;
	j = 1;
	// printf("in init\n");
	t_edge *index = lemin->edge_tab;
	while (index)
	{
		index->predecessor->infinity = 1;
		index->successor->infinity = 1;
		index = index->next;
	}
	lemin->start_node->infinity = 0;
}

void start_algo(t_lemin *lemin)
{
	int i;
	int x;

	// printf("nb of edges %d\n", lemin->number_of_edges);
	printf("nb of path %d and ants %d\n", lemin->nb_path, lemin->nb_ants);
	// printf("in start algo\n");

	lemin->path_tab = malloc(sizeof(t_path *) * lemin->nb_path);
	x = 0;

	while (x < lemin->nb_path)
	{

		bellman_ford(lemin);//, &changed);
		// printf("--------------------------------------------------\n");
		save_path(lemin, x);
		suurballe(lemin, x);
		init_infinity_and_reach_cost(lemin);
		i = 0;
		x++;
		// printf("--------------------------------------------------\n");
	}
	// //!\\ not part of code, print different path
	// for(i = 0; i < lemin->number_of_edges; i++)
	//   printf("edge [%s][%s] is visited %d\n", lemin->edge_tab[i]->predecessor, lemin->edge_tab[i]->successor, lemin->edge_tab[i]->visited);
	// t_path *index;
	// i = 0;
	// while(i < lemin->nb_path)
	// {
	// 	index = lemin->path_tab[i];
	// 	while (index != NULL)
	// 	{
	// 		printf("%s ", index->node);
	// 		index = index->next;
	// 	}
	// 	i++;
	// 	printf("\n");
	// }
}
