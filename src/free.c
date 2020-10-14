#include "../includes/lemin.h"

void free_lemin(t_lemin *lemin)
{
  free(lemin);
  lemin = NULL;
  exit(-1);
}

void free_node(t_node *node)
{
  ft_strdel(&node->name);
  if (node->predecessor)
  free(node->predecessor);
  node->predecessor = NULL;
  free_links(node->links);
  if (node->duplicated == 1)
    free_node(node->dup_out);
  node = NULL;
}

void free_edge(t_lemin *l)
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
  free_lemin(l);
}
