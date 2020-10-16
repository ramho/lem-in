#include "../includes/lemin.h"

void	free_edges(t_lemin *l)
{
	t_edge	*tmp;
	t_edge	*tmp_bis;

	tmp = l->edge_tab;
	while (tmp)
	{
		tmp_bis = tmp->next;
		free(tmp);
		tmp = NULL;
		tmp = tmp_bis;
	}
}

void	free_path(t_path **path, int size)
{
	int		i;
	t_path	*tmp;
	t_path	*bis;

	i = 0;
	while (i < size)
	{
		tmp = path[i];
		while (tmp)
		{
			bis = tmp->next;
			free(tmp);
			tmp = bis;
		}
		i++;
	}
	free(path);
}

void	free_links(t_link *head)
{
	t_link	*tmp;

	tmp = head->next;
	free(head);
	while (tmp)
	{
		tmp = tmp->next;
		free(tmp);
	}
}

void	free_nodes(t_lemin *l)
{
	int	i;

	i = 0;
	while (i < HASH_SIZE - 1)
	{
		if (l->node_tab[i])
		{
			ft_strdel(&l->node_tab[i]->name);
			free(l->node_tab[i]);
		}
		i++;
	}
}
