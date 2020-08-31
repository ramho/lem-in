#include "bellman.h"

typedef struct state_name
{
    char state_name[100];
}              state_name;
state_name graph_states[100];
int number_of_states;

typedef struct edges
{
    char predecessor[100];
    char successor[100];
    int weight;
}              edges;
edges graph_relations[100];
int number_of_edges;

typedef struct scp
{
  char state_name[100];
  int reach_cost;
  int infinity;
  char predecessor[100];
}              scp;
scp graph_reducing[100];

void get_graph()
{
  int i;
  int j;
  int s;
  char file[100];
  char c;

FILE *input_file = fopen("input.txt", "r");
fgets(file, 255, input_file);
j = 0;
s = 0;
i = 0;
while ( i < ft_strlen(file))
{
  c = file[i];
  if( c != ',')
  {
    if (c != '\n')
    {
      graph_states[s].state_name[j] = c;
      j++;
    }
  }
  else
  {
    j = 0;
    s++;
  }
  i++;
}
number_of_states = s + 1;
printf("Graph states: ");
for(i = 0; i < number_of_states; i++)
  printf("(%s)", graph_states[i].state_name); // getting nodes
printf("\nThe initial state is : %s", graph_states[0].state_name);
printf("\nGraph Edges :\n");
j = 0;
while (!feof(input_file))
{
  fscanf(input_file, "%s %s %d", graph_relations[j].predecessor, graph_relations[j].successor, &graph_relations[j].weight);
  j++;
}
number_of_edges = j;
for ( i = 0; i < number_of_edges - 1; i++) // getting edges
  printf("[%d] %3s |%3s |%3d\n", i, graph_relations[i].predecessor, graph_relations[i].successor,graph_relations[i].weight);
fclose(input_file);
}

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

void reduce()
{
  int i;
  int j;
  for (i = 0; i < number_of_states; i++)
  {
    for ( j = 0; j < number_of_edges; j++)
    {
      // printf("reduce -- graph name %s -- %s predecessor\n", graph_reducing[i].state_name, graph_relations[j].predecessor);
      if (ft_strcmp(graph_reducing[i].state_name, graph_relations[j].predecessor) == 0)
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
    // printf("1 - Name of predecessor is %s/(%s)\n", graph_reducing[sec_index].predecessor, pre);
  }
  if (pre_cost_is_infinity == 0 && sec_cost_is_infinity == 0)
  {
    if (sec_current_cost > (pre_current_cost + w))
    {
      graph_reducing[sec_index].reach_cost = pre_current_cost + w;
      ft_strcpy(graph_reducing[sec_index].predecessor, pre);
      // printf("2 - Name of predecessor is %s/(%s)\n", graph_reducing[sec_index].predecessor, pre);
      changed = 1;
    }
  }
  // printf("\n");
  return (changed);
  }

void printf_current_reach_cost(int iteration)
{
  printf("Current reducing state after iteration %d :\n", iteration);
  int i;

  for (i = 0; i < number_of_states; i++)
      printf("%3s |%3s |%3d\n", graph_reducing[i].state_name, graph_reducing[i].predecessor,graph_reducing[i].reach_cost);
}

void shortest_path()
{
  int i,j,negative_cycle_exist;
  FILE *output_file;

  output_file = fopen("output.txt", "w");
  fputs("Shortest path : \nstate | predecessor | reach_cost\n", output_file);
  for ( i = 0; i < number_of_states; i++)
  {
    if (graph_reducing[i].infinity == 1)
      fprintf(output_file, "%5s | %11s | infinity\n", graph_reducing[i].state_name, graph_reducing[i].predecessor);
    else
    fprintf(output_file, "%5s | %11s | %5d\n", graph_reducing[i].state_name, graph_reducing[i].predecessor, graph_reducing[i].reach_cost);
  }
  negative_cycle_exist = 0;
  for (i = 0; i < number_of_states; i++)
  {
    for (j = 0; j < number_of_edges; j++)
    {
      if (ft_strcmp(graph_states[i].state_name, graph_relations[j].predecessor) == 0)
        negative_cycle_exist = try_reduce(graph_states[i].state_name, graph_relations[j].successor, graph_relations[j].weight);
    }
  }
  if ( negative_cycle_exist == 1)
    fprintf(output_file, "\na negative cycle exist\n");
  else
    fprintf(output_file, "\nno negative cycle exist\n");
  fclose(output_file);
}

int main()
{
  int i;

  get_graph();
  init_reducing_graph(); //tart is zero and the rest is infinity
  i = 0;
  while(i < number_of_states) // -1 because all vertices except start
  {
    reduce();
    // printf_current_reach_cost(i);
    printf("i[%d] number of states[%d]\n", i, number_of_states);
    i++;
  }
  shortest_path();
  return(0);
}
