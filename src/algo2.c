#include "../includes/lemin.h"

void save_path(t_lemin *lemin, int index_path)
{
  t_node *tmp;
  t_path *new;
  t_path *head;
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
  lemin->path_tab[index_path] = head;
  head->name = ft_strdup(tmp->name);
  new = malloc(sizeof(t_path));
  new->name = ft_strdup(lemin->node_tab[i]->predecessor);
  new->next = NULL;
  head->next = new;
  i = 1;
  while (i < lemin->number_of_nodes)
  {
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
  //!\\not part of code, just to print shortest path
  index = head;
  printf("shortest path is: ");
  while (index != NULL)
  {
    printf("%s ", index->name);
    index = index->next;
  }
  printf("\n");
}

void modify_graph_for_bhandari(t_lemin *lemin, int path_index)
{
  int i;
  t_path *index;
  char *pre;
  char *suc;

  index = lemin->path_tab[path_index];
  while(index->next != NULL)
  {
    pre = index->name;
    suc = index->next->name;
    i = 0;

    while (i < lemin->number_of_edges)
    {
        // printf("pre %s suc %s\n", pre,suc);
      if (ft_strcmp(pre, lemin->edge_tab[i]->predecessor) == 0
      && ft_strcmp(suc,lemin->edge_tab[i]->successor) == 0)
      {
        // printf("pre %s VS [%s] // suc %s VS [%s]\n", pre, lemin->edge_tab[i]->predecessor, suc, lemin->edge_tab[i]->successor);
        lemin->edge_tab[i]->weight = -1;
      }
      if ((ft_strcmp(suc, lemin->edge_tab[i]->predecessor) == 0)
        && (ft_strcmp(pre,lemin->edge_tab[i]->successor) == 0))
      {
        // printf("suc %s VS PRE-tab[%s] // pre %s VS SUC-tab[%s]\n", suc, lemin->edge_tab[i]->predecessor, pre, lemin->edge_tab[i]->successor);
        lemin->edge_tab[i]->weight = lemin->number_of_edges * 10;
      }
      i++;
    }
    index = index->next;
  }
  i = 0;
  while(i < lemin->number_of_edges)
  {
    // printf("[%s][%s] w[%d]\n", lemin->edge_tab[i]->predecessor,lemin->edge_tab[i]->successor,lemin->edge_tab[i]->weight);
    i++;
  }
}
