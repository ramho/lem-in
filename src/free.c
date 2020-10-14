#include "../includes/lemin.h"

void free_lemin(t_lemin *lemin)
{
  free(lemin);
  lemin = NULL;
  exit(-1);
}

void free_nodes(t_lemin *l)
{
  int i;

  i = 0;
  while (i < HASH_SIZE)
  {
    if (l->node_tab[i] != NULL)
      free_full_node(l->node_tab[i]);
    i++;
    }
}

void free_full_node(t_node *node)
{
  ft_strdel(&node->name);
  if (node->predecessor)
  free(node->predecessor);
  node->predecessor = NULL;
  free_links(node->links);
  if (node->duplicated == 1)
  free_node(node->dup_out);
  free(node);
  node = NULL;
}

void free_edges(t_lemin *l)
{
  t_edge *tmp;
  t_edge *tmp_bis;

  tmp = l->edge_tab;
  while (tmp)
  {
    tmp_bis = tmp->next;
    free(tmp);
    tmp = NULL;
    tmp = tmp_bis;
  }
}

void free_path(t_path *path)
{
  t_path *tmp;
  t_path *bis;

  tmp = path;
  while (tmp)
  {
    bis = tmp->next;
    free(tmp->node);
    tmp->node = NULL;
	free(tmp);
    tmp = bis;
  }
}

void free_links(t_link *head)
{
  t_link *tmp;

  tmp = head->next;
  free(head);
  while (tmp)
  {
    tmp = tmp->next;
    free(tmp);
  }
}

void free_ant(t_ant **tab, int ants)
{
  int i;

  i = 0;
  while (i < ants)
  {
    free(tab[i]->node);
    tab[i]->node = NULL;
    free(tab[i]);
    tab[i] = NULL;
    i++;
  }
}

void free_error(t_lemin *l, int error)
{
	int i;

  if (error == 1)
  {
    free_nodes(l);
    free_edges(l);
  }
  if (error == 2)
  {
	  i = l->nb_bellmanf_path;
	  while (i <= 0)
	  {
		  if(l->path_tab[i])
		  	free_path(l->path_tab[i]);
		  i--;
	  }
	  free_nodes(l);
	  free_edges(l);
  }
  free_lemin(l);
}
