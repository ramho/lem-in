#include "lemin.h"


void init_reducing_graph()
{
  int i;
  ft_strcpy(graph_reducing[0].state_name, graph_states[0].state_name);
  // printf("!!- reducing name %s states name %s\n", graph_reducing[0].state_name, graph_states[0].state_name );
  graph_reducing[0].infinity = 0;
  graph_reducing[0].reach_cost = 0;
  for (i = 1; i < number_of_states; i++)
  {
    strcpy(graph_reducing[i].state_name, graph_states[i].state_name);
    graph_reducing[i].infinity = 1;
  }
  // printf("states graph name %s - reducing graph name %s infinity %d reach cost %d\n", graph_states[0].state_name, graph_reducing[0].state_name,graph_reducing[0].infinity, graph_reducing[0].reach_cost );
}

void reduce(t_lemin *lemin)
{
  int i;
  int j;

  i = -1;
  while (i++ < lemin->number_of_nodes) // count number of nodes
  {
    j = -1;
    while (j++ < lemin->number_of_edges)
    {

      if (ft_strcmp(lemin->tab[hash_code(lemin, )].state_name, lemin->edges_tab[j].predecessor) == 0)
      {
        try_reduce(graph_reducing[i].state_name, graph_relations[j].successor, graph_relations[j].weight);
      }
    }
  }
}

int try_reduce(char pre[], char sec[], int w)
{
  int changed, i, pre_index, sec_index;
  int pre_cost_is_infinity, sec_cost_is_infinity;
  int pre_current_cost = 0, sec_current_cost = 0;

  changed = 0;
  // printf("-- try reduce -- edge pre [%s] - edge sec [%s] = weight [%d]\n", pre, sec,w);
  // looking/retrieving for value of each Node, can you the hashcode to keep immediately
  for (i = 0; i < number_of_states; i++)
  {
    if (ft_strcmp(pre,graph_reducing[i].state_name) == 0)
    {
      pre_index = i; // keeping index of predecessor
      if (graph_reducing[i].infinity == 1)
        pre_cost_is_infinity = 1;
      else
      {
        pre_cost_is_infinity = 0;
        pre_current_cost = graph_reducing[i].reach_cost;
      }
    }
    if (ft_strcmp(sec, graph_reducing[i].state_name) == 0)
    {
      sec_index = i; // keeping index of successor
      if (graph_reducing[i].infinity == 1)
        sec_cost_is_infinity = 1;
      else
      {
        sec_cost_is_infinity = 0;
        sec_current_cost = graph_reducing[i].reach_cost;
      }
    }
  }
  // printf("pre index %d[%d] - sec index %d[%d]\n", pre_index, pre_cost_is_infinity, sec_index, sec_cost_is_infinity);
  //changes values in reducing graph
  if (pre_cost_is_infinity == 0 && sec_cost_is_infinity == 1)
  {
    graph_reducing[sec_index].reach_cost = pre_current_cost + w;
    graph_reducing[sec_index].infinity = 0;
    ft_strcpy(graph_reducing[sec_index].predecessor, pre);
    changed = 1;
    // printf("1 - Name of precedessor is %s/(%s)\n", graph_reducing[sec_index].predecessor, pre);
  }
  if (pre_cost_is_infinity == 0 && sec_cost_is_infinity == 0)
  {
    if (sec_current_cost > (pre_current_cost + w))
    {
      graph_reducing[sec_index].reach_cost = pre_current_cost + w;
      ft_strcpy(graph_reducing[sec_index].predecessor, pre);
      // printf("2 - Name of precedessor is %s/(%s)\n", graph_reducing[sec_index].predecessor, pre);
      changed = 1;
    }
  }
  // printf("\n");
  return (changed);
  }

void start_algo(t_lemin *lemin)
{
  int i;

  i = 0;
  while(i < number_of_states)
  {
    reduce(lemin);
    printf_current_reach_cost(i);
    // printf("i[%d] number of states[%d]\n", i, number_of_states);
    i++;
  }
  shortest_path();
  return(0);
}
