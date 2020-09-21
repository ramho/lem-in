// #include "../includes/lemin.h"
//
// void create_dup_room(t_lemin *lemin, t_node **tab, char *node)
// {
//   int i;
//   int index;
//   // printf("in create dup room\n");
//
//   i = 0;
//   index = 0;
//   while (i < lemin->number_of_nodes && index == 0)
//   {
//     if (ft_strcmp(node,tab[i]->name) == 0)
//       index = i;
//     i++;
//   }
//   tab[index]->duplicated = 1;
//   tab[index]->dup_out = malloc(sizeof(t_node));
//   tab[index]->dup_out->name = ft_strdup(tab[index]->name);
//   tab[index]->dup_out->reach_cost = 0;
//   tab[index]->dup_out-> infinity = 1;
// }
//
// void suurballe(t_lemin *lemin, int path_index)
// {
//   int i;
//   t_path *index;
//   char *pre;
//   char *suc;
//
//   // printf("in suurballe\n");
//
//   index = lemin->path_tab[path_index];
//   while(index->next != NULL)
//   {
//     pre = index->node;
//     suc = index->next->node;
//     i = 0;
//
//     while (i < lemin->number_of_edges)
//     {
//         // printf("pre %s suc %s\n", pre,suc);
//       if (ft_strcmp(pre, lemin->edge_tab[i]->predecessor) == 0
//       && ft_strcmp(suc,lemin->edge_tab[i]->successor) == 0)//
//       {
//         // printf("pre %s VS [%s] // suc %s VS [%s]\n", pre, lemin->edge_tab[i]->predecessor, suc, lemin->edge_tab[i]->successor);
//         lemin->edge_tab[i]->weight = -1;
//         if (ft_strcmp(suc, lemin->start_node))
//           create_dup_room(lemin, lemin->node_tab, suc);
//           printf("[%s][%s] visite [%d]\n", lemin->edge_tab[i]->predecessor, lemin->edge_tab[i]->successor, lemin->edge_tab[i]->visited);
//       }
//       if ((ft_strcmp(suc, lemin->edge_tab[i]->predecessor) == 0)
//         && (ft_strcmp(pre,lemin->edge_tab[i]->successor) == 0))
//       {
//         // printf("suc %s VS PRE-tab[%s] // pre %s VS SUC-tab[%s]\n", suc, lemin->edge_tab[i]->predecessor, pre, lemin->edge_tab[i]->successor);
//         // lemin->edge_tab[i]->weight = lemin->number_of_edges * 10;
//         lemin->edge_tab[i]->visited = 1;
//         printf("[%s][%s] visite [%d]\n", lemin->edge_tab[i]->predecessor, lemin->edge_tab[i]->successor, lemin->edge_tab[i]->visited);
//       }
//       i++;
//     }
//     index = index->next;
//   }
//   //!\\ not part of code, check the content of the edges
//   i = 0;
//   while(i < lemin->number_of_edges)
//   {
//     // printf("[%s][%s] w[%d] visité [%d]\n", lemin->edge_tab[i]->predecessor,lemin->edge_tab[i]->successor,lemin->edge_tab[i]->weight, lemin->edge_tab[i]->visited);
//     i++;
//   }
// }
