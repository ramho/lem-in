#include "../includes/lemin.h"

void get_path(t_lemin *lemin)
{
  int i;
  int j;
  int nb_path = 2; // will be a value that is calculated and stored in lemin after
  t_path *head;
  printf("in get path\n");

  lemin->final_path_tabs = malloc(sizeof(t_path *) * nb_path);
  head = malloc(sizeof(t_path));
  head->name = ft_strdup(lemin->edge_tab[0]->predecessor);
  lemin->final_path_tabs[0] = head;
  i = 1;
  j = 0;
  while (i < nb_path)
  {
    // while ( != )
    recursive_get_path(lemin, lemin->final_path_tabs[j]->name,head);
    // t_path *index;
    // index = lemin->final_path_tabs[j];
    // while (index->next != NULL)
    //   {
    //     printf("path is %s ", index->name);
    //     index= index->next;
    //   }
    i++;
    j++;
  }
}


char *recursive_get_path(t_lemin *lemin, char *pre_node, t_path * head )
{
  int i;
  t_path *index;
  t_path *new;
  printf("in recursive get path\n");

  i = 0;
  while (i < lemin->number_of_edges)
  {
    if (ft_strcmp(pre_node,lemin->edge_tab[i]->predecessor) == 0)
    {
      if(lemin->edge_tab[i]->visited == 1)
      {
        new = malloc(sizeof(t_path));
        new->name = ft_strdup(lemin->edge_tab[i]->successor);
        new->next = NULL;
        index = head;
        while(index->next != NULL)
        {
          index = index->next;
        }
        index->next = new;
        index = head;
        i = 0;
        while (index != NULL)
          {
            printf("path is %s ", index->name);
            i++;
            index= index->next;
          }
        return (new->name);

      }
    }
    i++;
  }

  printf("out of recursive loop, no match\n");
  return(NULL);
}
