/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoorntj <rhoorntj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 17:33:10 by rhoorntj          #+#    #+#             */
/*   Updated: 2020/09/30 18:18:05 by rhoorntj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int	hash(t_lemin *l, int *i, char c)
{
	int odd;
	int key;
	int oups;

	key = 0;
	oups = *i + 1;
	while(l->line[++(*i)] != c)
	{
		odd = ((*i - oups) % 2) ? 3 : 2;
		key = (key * 19) + l->line[*i] - odd + ((l->line[*i] - 32) * odd) + 32;
	}
	return (key % HASH_SIZE);
}

void	reverse_edge(t_edge *ed)
{
	t_edge *reverse;

	if (!(reverse = (t_edge*)malloc(sizeof(t_edge))))
		return;
	reverse->predecessor = ed->successor;
	reverse->successor = ed->predecessor;
	reverse->weight = 1;
	ed->reversed = reverse;
}

void add_new_link(t_node *room, t_node *room_to_link)
{
	t_link *link;
	t_link *tmp;
// printf("room [%s] - link[%s]\n", room->name, room_to_link->name);
	if (!(link = ft_memalloc(sizeof(t_link))))
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
			{
				// printf("room_to_link already linked to the room");
				return ;
			}
			tmp = tmp->next;
		}
		link->next = room->links;
		room->links = link;
	}
	// printf("room [%s] linked to [%s]\n", room->name, room->links->room->name);
	return ;
}

t_node *get_edge_room(t_lemin *l, int i, int key, int place)
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

int	parse_edges(t_lemin *l)
{

	int i;
	int key;
	int middle;
	t_edge *ed;

	if (!(ed = (t_edge*)malloc(sizeof(t_edge))))
		return (0);
	i = -1;
	key = hash(l, &i, '-');
	middle = i;
	if (!(ed->predecessor = get_edge_room(l, i, key, 0)))
	{
		printf("linked room a doesn't exit\n");
		return (0);
	}
	key = hash(l, &i, '\n');
	if (!(ed->successor = get_edge_room(l, i, key, middle + 1)))
	{
		printf("linked room b doesn't exit\n");
		return (0);
	}
	ed->weight = 1;
	ed->next = NULL;
	reverse_edge(ed);
	l->number_of_edges +=2;
	if ((ed->predecessor->key == l->start_node->key) || (ed->successor->key == l->start_node->key))
			l->nb_start_out += 1;
	if ((ed->predecessor->key == l->end_node->key) || (ed->successor->key == l->end_node->key))
		l->nb_end_in += 1;
	if (!(l->edge_tab))
		l->edge_tab = ed;
	else
	{
		ed->next = l->edge_tab;
		l->edge_tab = ed;
	}
	add_new_link(ed->successor, ed->predecessor);
	add_new_link(ed->predecessor, ed->successor);
	return (1);
}

int	parse_nodes(t_lemin *l)
{
	// printf("in parse nodes \n");
	int i;
	int neg = 1;
	char is_int = 0;
	int odd = 0;
	t_node *node;
	static int collision = 0;

	if (!(node = ft_memalloc(sizeof(t_node))))
		return (0);
	i = -1;
	node->key = hash(l, &i, ' ');

	if (!(node->name = ft_memalloc(sizeof(char) * (i + 1))))
		return (0);
	ft_strncpy(node->name, l->line, i);
	node->name[i] = 0;

	while (l->line[++i] != '\n')
	{
		if ((l->line[i] == '-') && (l->line[i - 1] == ' '))
			neg = -1;
		else if (l->line[i] >= '0' && l->line[i] <= '9')
		{
			node->y *= 10;
			node->y += (l->line[i] - '0');
			is_int = 1;
		}
		else if (l->line[i] == ' ')
		{
			if (is_int)
				node->x = (node->y * neg);
			else
			{
				printf("no int\n");
				return (0);
			}
			neg = 1;
			node->y = 0;
		}
		else
		{
			printf("wrong coord format\n");
			return (0);
		}
	}
	node->y *= neg;
	// ----------------------------START
	node->reach_cost = 0;
	node->ant = 0;
	//add 10/20
	node->predecessor = ft_memalloc(sizeof(t_node));
	//end add 10/20

	// ------------------------------END
	if (l->start_room == 1)
	{
		// ----------------------------START
		node->infinity = 0;
		// ------------------------------END
		l->start_node = node;
		l->start_room++;
	}
	else if (l->end_room == 1)
	{
		// ----------------------------START
		node->infinity = 1;
		// ------------------------------END
		l->end_node = node;
		l->end_room++;
	}
	// ----------------------------START
	else
		node->infinity = 1;
	// ------------------------------END

	l->number_of_nodes++;

	t_node *tmp;
	if (!(&l->node_tab[node->key]))
		l->node_tab[node->key] = node;
	else
	{
		tmp = l->node_tab[node->key];
		while (tmp)
		{
			if (ft_strequ(tmp->name, node->name))
			{
				printf("duplicate room\n");
				exit(0);
			}
			tmp = tmp->next;
		}
		node->next = l->node_tab[node->key];
		l->node_tab[node->key] = node;
	}
	return (1);
}

void	parse_ant(t_lemin *l)
{
	int i;

	i = -1;
	while (l->line[++i] != '\n')
	{
		if (l->line[i] >= '0' && l->line[i] <= '9')
		{
			l->nb_ants *= 10;
			l->nb_ants += (l->line[i] - '0');
		}
		else
		{
			printf("ERROR : wrong nb_ant format\n");

			// return;
		}
		if (l->nb_ants < 0 || l->nb_ants > INT_MAX)
		{
			printf("ERROR : not positive int\n");
			// return;
		}
	}
	l->parse_flag = 1;
}

void	parse_command(t_lemin *l)
{
	int i;
	// printf("in parse command\n");
	if (!(ft_strncmp("##start\n", l->line, 8)))
	{
		if (l->start_room == 2)
		{
			printf("2nd start room\n");
			exit (0);
		}
		l->start_room++;
	}
	else if (!(ft_strncmp("##end\n", l->line, 6)))
	{
		if (l->end_room == 2)
		{
			printf("2nd end room\n");
			exit (0);
		}
		l->end_room++;
	}
	else
		printf("unknown command : IGNORED\n");
}

void	parse_comment(t_lemin *l)
{
	return;
}

int parse_line(t_lemin *l)
{
	// printf("in parse line \n");
	if (l->hash_tag == 3)
		parse_command(l);
	else if (l->hash_tag == 1)
		parse_comment(l);
	else if (l->parse_flag == 2 && !l->space)
	{
		parse_edges(l);
	}
	else if (l->parse_flag == 1)
	{
		if (!l->tiret)
		{
			if (!(parse_nodes(l)))
				return (0);
		}
		else
		{
			l->parse_flag++;
			parse_edges(l);
		}
	}
	else if (!l->parse_flag)
		parse_ant(l);
	else
	{
		printf("ERROR : wrong line format\n");
		return (0);
	}
	l->hash_tag = 0;
	l->space = 0;
	l->tiret = 0;
	return (1);
}

int parse_buff(t_lemin *l)
{
	// printf("in parse buff\n");
	while (l->buff[l->i])
	{
		if ((l->buff[l->i] >= 'a' && l->buff[l->i] <= 'z') || \
		(l->buff[l->i] >= 'A' && l->buff[l->i] <= 'Z') || \
		(l->buff[l->i] >= '0' && l->buff[l->i] <= '9') || \
		(l->buff[l->i] == '#') || (l->buff[l->i] == ' ') || (l->buff[l->i] == '-') || (l->buff[l->i] == '_') || (l->buff[l->i] == ':'))
		{
			if (((l->buff[l->i] == '#') && l->i_line < 2))
				l->hash_tag += (l->i_line + 1);
			if (l->buff[l->i] == ' ')
				l->space += 1;
			if (l->buff[l->i] == '-')
				l->tiret += 1;
			l->line[l->i_line] = l->buff[l->i];
			l->i++;
			l->i_line++;
		}
		else if (l->buff[l->i] == '\n')
		{
			if (!l->i_line)
			{
				printf("ERROR : empty line\n");
				return (0);
			}
			l->line[l->i_line] = l->buff[l->i];
			l->line[l->i_line + 1] = 0;
			if (!(parse_line(l)))
				return (0);
			if (l->end_buff && !l->end_line)
			{
				write(1, l->line, l->i_line + 1);
				l->end_buff = 0;
				l->rest = l->i + 1;
			}
			l->i++;
			l->end_line = l->i;
			l->i_line = 0;
		}
		else
		{
			printf("end_buff2\n");
			return (0);
		}
		if (!l->buff[l->i])
		{
			if (l->end_line)
			{
				if (l->end_line - l->rest)
					write(1, &l->buff[l->rest], l->end_line - l->rest);
				l->rest = 0;
				l->end_line = 0;
			}
			if (l->i_line)
				l->end_buff = 1;
			l->i = 0;
			return (1);
		}
	}
	return (1);
}

void	get_file_content(t_lemin *lemin)
{
	float temps;
	clock_t t1, t2;
	printf("in get file content\n");
	t1 = clock();
	if (LEMIN_READ_BUFF < 1 || read(0, lemin->buff, 0) < 0)
		return ;
	ft_bzero(lemin->buff, LEMIN_READ_BUFF); //
	while ((lemin->ret = read(0, lemin->buff, LEMIN_READ_BUFF)) > 0)
	{
		lemin->buff[lemin->ret] = 0;
		if (!(parse_buff(lemin)))
			break;
	}
	// add 10/20
	// printf("start [%s] end [%s]\n", lemin->start_node->name, lemin->end_node->name);
	if (lemin->nb_start_out == 0 || lemin->nb_end_in == 0)
		exit(1);
	//end add 10/20
	if (lemin->nb_start_out == lemin->nb_end_in)
		lemin->nb_path = lemin->nb_start_out;
	else if (lemin->nb_start_out > lemin->nb_end_in)
		lemin->nb_path = lemin->nb_end_in;
	else if (lemin->nb_start_out < lemin->nb_end_in)
		lemin->nb_path = lemin->nb_start_out;

}

int main()
{
	float temps;
	clock_t t1, t2, t3;
	t_lemin *lemin;

	t1 = clock();
	if (!(lemin = ft_memalloc(sizeof(t_lemin))))
        return (-1);
	get_file_content(lemin);
	t2 = clock();
	printf("start [%s] end [%s] path [%d] \n", lemin->start_node->name, lemin->end_node->name, lemin->nb_path);
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	// printf("start room [%s] linked to [%s]\n", lemin->start_node->name, lemin->start_node->links->room->name);
	start_algo(lemin);
	// printf("ret = %d\n", ret);
	if (lemin->nb_bellmanf_path < 1)
		return(0);
	get_path(lemin);
	print_path(lemin);

	// printf("out\n");
	t3 = clock();
	temps = (float)(t3-t1)/CLOCKS_PER_SEC;
	printf("temps = %f\n", temps);
	return(0);
}
