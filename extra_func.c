#include "lemin.h"

void print_tab(t_lemin *lemin)
{
  int position = 0;

  while (position < lemin->table_size)
  {
    if (lemin->node_tab[position] == NULL)
      printf("[%d] list is NULL\n", position);
    else
    {
      printf("[%d] name %s infinity %d\n", position, lemin->node_tab[position]->name, lemin->node_tab[position]->infinity);
    }
    position++;
  }
}

// char lookup(t_lemin *lemin, char* key)
// {
//   int position;
//   t_node *list;
//
//   position = hash_code(lemin, key);
//   list = lemin->node_tab[position];
//   if (ft_strstr(list->name,key))
//       return (list->weight);
//   return (-1);
// }

// void shortest_path()
// {
//   int i,j,negative_cycle_exist;
//   FILE *output_file;
//
//   output_file = fopen("output.txt", "w");
//   fputs("Shortest path : \nstate | predecessor | reach_cost\n", output_file);
//   for ( i = 0; i < number_of_states; i++)
//   {
//     if (graph_reducing[i].infinity == 1)
//       fprintf(output_file, "%5s | %11s | infinity\n", graph_reducing[i].state_name, graph_reducing[i].predecessor);
//     else
//     fprintf(output_file, "%5s | %11s | %5d\n", graph_reducing[i].state_name, graph_reducing[i].predecessor, graph_reducing[i].reach_cost);
//   }
//   negative_cycle_exist = 0;
//   for (i = 0; i < number_of_states; i++)
//   {
//     for (j = 0; j < number_of_edges; j++)
//     {
//       if (ft_strcmp(graph_states[i].state_name, graph_relations[j].predecessor) == 0)
//         negative_cycle_exist = try_reduce(graph_states[i].state_name, graph_relations[j].successor, graph_relations[j].weight);
//     }
//   }
//   if ( negative_cycle_exist == 1)
//     fprintf(output_file, "\na negative cycle exist\n");
//   else
//     fprintf(output_file, "\nno negative cycle exist\n");
//   fclose(output_file);
// }
//
// void printf_current_reach_cost(int iteration)
// {
//   printf("Current reducing state after iteration %d :\n", iteration);
//   int i;
//
//   for (i = 0; i < number_of_states; i++)
//       printf("%3s |%3s |%3d\n", graph_reducing[i].state_name, graph_reducing[i].predecessor,graph_reducing[i].reach_cost);
// }
