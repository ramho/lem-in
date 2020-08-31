#include "../includes/lemin.h"

void write_path(t_lemin *lemin)
{
  printf_current_reach_cost(lemin, 0);
  t_node *tmp;
  t_path *head;
  t_path *new;
  t_path *index;
  int i;

  i = 0;

  while (i < lemin->number_of_nodes)
  {
    // printf("if 1 start if 2 end ==> %d\n",lemin->node_tab[i]->type);
    if(lemin->node_tab[i]->type == 2)
    {
      tmp = malloc(sizeof(t_node *));
      tmp = lemin->node_tab[i];
      // printf("end node is %s\n", tmp->name);
      break;
    }
    i++;
  }
  head = malloc(sizeof(t_path));
  head->name = ft_strdup(tmp->name);
  new = malloc(sizeof(t_path));
  new->name = ft_strdup(lemin->node_tab[i]->predecessor);
  new->next = NULL;
  head->next = new;
  i = 1;
  while (i < lemin->number_of_nodes)
  {
    // printf("cmp %s - %s\n",new->name, lemin->node_tab[i]->name );
    if (ft_strcmp(new->name, lemin->node_tab[i]->name) == 0)
    {
      // free(new); // bug
      new = malloc(sizeof(t_path));
      new->name = ft_strdup(lemin->node_tab[i]->predecessor);
      new->next = NULL;
      i = 0;
      index = head;
      while (index->next!= NULL)
        index = index->next;
      index->next = new;
    }
    i++;
  }
  index = head;
  printf("shortest path is: ");
  while (index != NULL)
  {
    printf("%s ", index->name);
    index = index->next;
  }
}
