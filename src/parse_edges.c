/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_edges.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoorntj <rhoorntj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 17:08:45 by rhoorntj          #+#    #+#             */
/*   Updated: 2020/10/11 18:30:56 by rhoorntj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	reverse_edge(t_edge *ed)
{
	t_edge *reverse;

	if (!(reverse = (t_edge*)malloc(sizeof(t_edge))))
		return ;
	reverse->predecessor = ed->successor;
	reverse->successor = ed->predecessor;
	reverse->weight = 1;
	ed->reversed = reverse;
}


t_node	*get_edge_room(t_lemin *l, int i, int key, int place)
{
	t_node *tmp;

	tmp = l->node_tab[key];
	while (tmp)
	{
		if (ft_strnequ(tmp->name, l->line + place, i - place))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_new_link(t_node *room, t_node *room_to_link)
{
	t_link *link;
	t_link *tmp;

	if (!(link = (t_link*)ft_memalloc(sizeof(t_link))))
		return ;
	link->room = room_to_link;
	link->used = 0;
	tmp = room->links;
	if (!(tmp))
		room->links = link;
	else
	{
		while (tmp)
		{
			if (ft_strequ(tmp->room->name, room_to_link->name))
				return ; // "room_to_link already linked to the room"
			tmp = tmp->next;
		}
		link->next = room->links;
		room->links = link;
	}
	return ;
}

int		free_edge(t_edge *ed)
{
	free(ed);
	ed = NULL;
	return (0);
}

void store_new_edge(t_lemin *l, t_edge *ed)
{
	if (!(l->edge_tab))
		l->edge_tab = ed;
	else
	{
		ed->next = l->edge_tab;
		l->edge_tab = ed;
	}
}

void 	check_exit_entry(t_lemin *l, t_edge *ed)
{
	if ((ed->predecessor->key == l->start_node->key) || (ed->successor->key == l->start_node->key))
		l->nb_start_out += 1;
	if ((ed->predecessor->key == l->end_node->key) || (ed->successor->key == l->end_node->key))
		l->nb_end_in += 1;
}

int		parse_edges(t_lemin *l, int i, int key, int middle)
{
	t_edge *ed;

	if (!(ed = (t_edge*)ft_memalloc(sizeof(t_edge))))
		return (0);
	key = hash(l, &i, '-');
	middle = i;
	if (!(ed->predecessor = get_edge_room(l, i, key, 0)))
		return (free_edge(ed)); // "linked room a doesn't exit\n"
	key = hash(l, &i, '\n');
	if (!(ed->successor = get_edge_room(l, i, key, middle + 1)))
		return (free_edge(ed)); // "linked room b doesn't exit\n"
	if (((ed->predecessor == l->start_node) && (ed->successor == l->end_node))
			|| ((ed->successor == l->start_node) && (ed->predecessor == l->end_node)))
			l->direct = 1;
		// return (0); // end and start are connected
	ed->weight = 1;
	ed->next = NULL;
	reverse_edge(ed);
	l->number_of_edges +=2;
	check_exit_entry(l, ed);
	store_new_edge(l, ed);
	add_new_link(ed->successor, ed->predecessor);
	add_new_link(ed->predecessor, ed->successor);
	return (1);
}
