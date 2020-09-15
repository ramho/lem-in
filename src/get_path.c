#include "../includes/lemin.h"

void get_path(t_lemin *lemin)
{
  int i;
  int j;
  t_path *head;
  t_path *new;
  t_path *index;
  // printf("in get path\n");
  //
  // i = 0;
  // while (i < lemin->number_of_nodes)
  // {
  //   printf(" Node %s has been visited %d times\n", lemin->node_tab[i]->name, lemin->node_tab[i]->visited);
  //   i++;
  // }
  // i = 0;
  // while (i < lemin->number_of_edges)
  // {
  //   printf(" edge %s to %s has been visited %d times\n", lemin->edge_tab[i]->predecessor, lemin->edge_tab[i]->successor, lemin->edge_tab[i]->visited);
  //   i++;
  // }

  // lemin->final_path_tabs = malloc(sizeof(t_path *) * lemin->nb_path);
  // head = malloc(sizeof(t_path));
  // head->node = lemin->node_tab[0];
  // lemin->final_path_tabs[0] = head;
  // i = 1;
  // j = 0;
  // while (i < nb_path)
  // {
  //
  //   // new->node = recursive_get_path(lemin, lemin->final_path_tabs[j]->node,head);
  //   new->next = NULL;
  //   index = head;
  //   while (index->next!= NULL)
  //     index = index->next;
  //   index->next = new;
  //
  //
  // }
}
//
//
// t_node *recursive_get_path(t_lemin *lemin, t_node *pre_node, t_path * head )
// {
//   int i;
//   t_path *index;
//   t_path *new;
//   printf("in recursive get path\n");
//
//   i = 0;
//   while (i < lemin->number_of_edges)
//   {
//     if (ft_strcmp(pre_node->name,lemin->edge_tab[i]->predecessor) == 0)
//     {
//       if(lemin->edge_tab[i]->visited == 1)
//       {
//         new = malloc(sizeof(t_path));
//         new->node = ft_strdup(lemin->edge_tab[i]->successor);
//         new->next = NULL;
//         index = head;
//         while(index->next != NULL)
//         {
//           index = index->next;
//         }
//         index->next = new;
//         index = head;
//         i = 0;
//         while (index != NULL)
//           {
//             printf("path is %s ", index->node);
//             i++;
//             index= index->next;
//           }
//         return (new);
//
//       }
//     }
//     i++;
//   }
//
//   printf("out of recursive loop, no match\n");
//   return(NULL);
// }
