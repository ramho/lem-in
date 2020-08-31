#include "../includes/lemin.h"

void parse_file(t_lemin *lemin)
{
	// printf("in parse file \n\n");
	lemin->nb_ants = ft_atoi(lemin->file[0]);
	seperate_nodes_edges(lemin);
  // printf("11\n");
  get_nodes(lemin->file_nodes, lemin);
  // printf("22\n");
  get_edges(lemin);
}

int  seperate_nodes_edges(t_lemin *lemin)
{
  int i;
  // printf("in seperate nodes n links\n");

  i = 1;
  lemin->file_edges = malloc(sizeof(char *) * lemin->table_size);
  lemin->file_nodes = malloc(sizeof(char *) * lemin->table_size);
  lemin->number_of_edges = 0;
  lemin->number_of_nodes = 2;
  // printf("hallo %d\n", lemin->table_size);
  while (lemin->file[i] != NULL)
  {
    if (lemin->file[i][0] == '#' && lemin->file[i][1] == '#')
      get_start_or_end_piece(&i, lemin);
    else if (ft_strchr(lemin->file[i], '-'))
    {
      // printf("hallo 22\n");
      lemin->file_edges[lemin->number_of_edges] = ft_strdup(lemin->file[i]);
      lemin->number_of_edges++;
    }
    else if (ft_isalnum(lemin->file[i][0]))
    {
      // printf("hallo 33 line %s\n", lemin->file[i]);
       lemin->file_nodes[lemin->number_of_nodes] = ft_strdup(lemin->file[i]);
       lemin->number_of_nodes++;
     }
    else if (lemin->file[i][0] == '#' && lemin->file[i][1] != '#')
      continue;
    i++;
  }
  // notpart of code, just to check the content is correct in nodes and edges
  // for ( i = 0; i < lemin->number_of_edges; i++)
  //   printf("edges are %s\n", lemin->file_edges[i]);
  // printf("\n");
  // for ( i = 0; i < lemin->number_of_nodes; i++)
  //     printf("nodes are %s\n", lemin->file_nodes[i]);
  lemin->number_of_edges *= 2;
  return(1);
}

void get_start_or_end_piece(int *i, t_lemin *lemin)
{

  if (ft_strstr(lemin->file[*i], "start"))
    {
      lemin->file_nodes[0] = ft_strdup(lemin->file[*i + 1]);
    }
  if (ft_strstr(lemin->file[*i], "end"))
      {
     lemin->file_nodes[1] = ft_strdup(lemin->file[*i + 1]);
      }
  *i = *i + 1;
}

void get_edges( t_lemin *lemin)
{
  int i;
  int j;
  int k;
  int z;

  // printf("in get edges %d\n", lemin->number_of_edges);
  i = 0;
  z = 0;
  lemin->edge_tab =malloc(sizeof(t_edge *) * lemin->number_of_edges * 2);
  while(lemin->file_edges[i])
  {
    lemin->edge_tab[z] =malloc(sizeof(t_edge));
    j = 0;
    while(j < ft_strlen(lemin->file_edges[i]))
    {
      while (lemin->file_edges[i][j] != '-')
        j++;
      lemin->edge_tab[z]->predecessor = ft_strsub(lemin->file_edges[i], 0, j);
      k = j + 1;
      while (lemin->file_edges[i][j])
        j++;
      lemin->edge_tab[z]->successor = ft_strsub(lemin->file_edges[i],k, j);
      lemin->edge_tab[z]->weight = 1;
      lemin->edge_tab[z + 1]=malloc(sizeof(t_edge));
      lemin->edge_tab[z + 1]->predecessor = ft_strdup(lemin->edge_tab[z]->successor);
      lemin->edge_tab[z + 1]->successor = ft_strdup(lemin->edge_tab[z]->predecessor);
      lemin->edge_tab[z + 1]->weight = 1;
      // printf("[%d]edge [%s][%s] - [%d]reverse[%s][%s]\n\n", z,lemin->edge_tab[z]->predecessor, lemin->edge_tab[z]->successor, z + 1, lemin->edge_tab[z + 1]->predecessor, lemin->edge_tab[z + 1]->successor );
    }
  z += 2;
  i++;
  }
}