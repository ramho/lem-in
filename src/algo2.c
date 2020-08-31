#include "../includes/lemin.h"

void write_path(t_lemin *lemin)
{
	printf_current_reach_cost(lemin, 0);
	t_node *tmp;
  t_path *head;
  t_path *new;
	int i;

	i = 0;

	while ( i < lemin->number_of_nodes)
	{
		printf(" if 1 start if 2 end ==> %d\n",lemin->node_tab[i]->type);
		if(lemin->node_tab[i]->type == 2)
		{
			tmp = malloc(sizeof(t_node *));
			tmp = lemin->node_tab[i];
      printf("end node is %s\n", tmp->name);
      break;
		}
		i++;
	}
  head = malloc(sizeof(t_path));
  head->name = ft_strdup(tmp->name);
  head->next = NULL;
  i = 0;
  while ( i < lemin->number_of_nodes)
  {
    tmp = NULL;
    tmp =  lemin->

  }
}
