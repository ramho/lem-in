#include "../includes/lemin.h"

// -----parse_tool.c--------
int		hash(t_lemin *l, int *i, char c)
{
	int odd;
	int key;
	int oups;

	key = 0;
	oups = *i + 1;
	while (l->line[++(*i)] != c && l->line[*i] != '\n')
	{
		odd = ((*i - oups) % 2) ? 3 : 2;
		key = (key * 19) + l->line[*i] - odd + ((l->line[*i] - 32) * odd) + 32;
	}
	return (key % HASH_SIZE);
}
// -----parse_tool.c END----

// -----parse_edges.c--------
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
	if (((ed->predecessor == l->start_node) && (ed->successor == l->end_node)) \
	|| ((ed->successor == l->start_node) && (ed->predecessor == l->end_node)))
		return (0); // "room start and end connected"
	//------store new_edge----------------
	if (!(l->edge_tab))
		l->edge_tab = ed;
	else
	{
		ed->next = l->edge_tab;
		l->edge_tab = ed;
	}
	// printf("[%s-%s]\n", l->edge_tab->predecessor->name, l->edge_tab->successor->name);
	//------end store new_edge------------
	//-----store linked node--------------
	add_new_link(ed->successor, ed->predecessor);
	add_new_link(ed->predecessor, ed->successor);
	//-------end store linked node--------
	return (1);
}
// -----parse_edges.c END----

// -----parse_node.c--------
int		get_coord(t_lemin *l, int *i, t_node *node)
{
	char is_int;
	char neg;

	is_int = 0;
	neg = 1;
	while (l->line[++(*i)] != '\n')
	{
		if ((l->line[*i] == '-') && (l->line[*i - 1] == ' '))
			neg = -1;
		else if (l->line[*i] >= '0' && l->line[*i] <= '9' && (is_int = 1))
			node->y = (node->y * 10) + (l->line[*i] - '0');
		else if (l->line[*i] == ' ')
		{
			if (is_int--)
				node->x = (node->y * neg);
			else
				return (0);
			neg = 1;
			node->y = 0;
		}
		else
			return (0);
	}
	node->y *= neg;
	return (is_int);
}

void	store_start_end_node(t_lemin *l, t_node *node)
{
	if (l->start_room == 1)
	{
		node->type = 1;
		l->start_node = node;
		l->start_room++;
	}
	else
	{
		node->type = 2;
		l->end_node = node;
		l->end_room++;
	}
}

int		store_node(t_lemin *l, t_node *node)
{
	t_node *tmp;

	if (!(&l->node_tab[node->key]))
		l->node_tab[node->key] = node;
	else
	{
		tmp = l->node_tab[node->key];
		while (tmp)
		{
			if (ft_strequ(tmp->name, node->name))
				return (0); // "duplicate room"
			tmp = tmp->next;
		}
		node->next = l->node_tab[node->key];
		l->node_tab[node->key] = node;
	}
	return (1);
}

int		free_node(t_node *node)
{
	free(node->name);
	node->name = NULL;
	free(node);
	node = NULL;
	return (0);
}

int		parse_nodes(t_lemin *l)
{
	int i;
	t_node *node;

	if (!(node = (t_node*)ft_memalloc(sizeof(t_node))))
		return (0);
	node->links = NULL;
	// printf("######### ROOM #########\n");
	// printf("line       : %s", l->line);
	// printf("name       : %s\n", node->name);
	// printf("x          : %i\n", node->x);
	// printf("y          : %i\n", node->y);
	// printf("hash key   : %lu\n", node->key);
	// printf("start room : %i\n", l->start_room);
	// printf("end room   : %i\n", l->end_room);
	// printf("########################\n");
	i = -1;
	node->key = hash(l, &i, ' ');
	if (!(node->name = (char*)ft_memalloc(sizeof(char) * (i + 1))))
		return (0);
	ft_strncpy(node->name, l->line, i);
	node->name[i] = 0;
	if (!(get_coord(l, &i, node)))
		return (free_node(node));
	if ((l->start_room == 1) || (l->end_room == 1))
		store_start_end_node(l, node);
	if (!(store_node(l, node)))
		return (free_node(node));
	l->number_of_nodes++;
	return (1);
}
// -----parse_node.c END----

// -----parse_line.c--------
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
			return; // "ERROR : wrong nb_ant format\n"
		if (l->nb_ants < 0 || l->nb_ants > INT_MAX)
			return; // "ERROR : not positive int\n"
	}
	l->parse_flag = 1;
}

int		parse_command(t_lemin *l)
{
	if (!(ft_strncmp("##start\n", l->line, 8)))
	{
		if (l->start_room || l->end_room == 1)
			return (0);
		l->start_room++;
	}
	if (!(ft_strncmp("##end\n", l->line, 6)))
	{
		if (l->end_room || l->start_room == 1)
			return (0);
		l->end_room++;
	}
	return (1);
}

int		parse_flag_one(t_lemin *l)
{
	if (!l->tiret)
	{
		if (!(parse_nodes(l)))
			return (0);
	}
	else
	{
		l->parse_flag++;
		if (!(parse_edges(l, -1, 0, 0)))
			return (0);
	}
	return (1);
}

int		parse_line(t_lemin *l)
{
	// printf("hash_tag   : %i\n", l->hash_tag);
	// printf("space      : %i\n", l->space);
	// printf("tiret      : %i\n", l->tiret);
	// printf("parse flag : %i\n", l->parse_flag);
	if (l->hash_tag == 3)
	{
		if (!(parse_command(l)))
			return (0);
	}
	else if (l->parse_flag == 2 && !l->space)
	{
		if (!(parse_edges(l, -1, 0, 0)))
			return (0);
	}
	else if (l->parse_flag == 1)
	{
		if (!(parse_flag_one(l)))
			return (0);
	}
	else if (!l->parse_flag)
		parse_ant(l);
	else
		return (0); // "ERROR : wrong line format\n"
	l->hash_tag = 0;
	l->space = 0;
	l->tiret = 0;
	return (1);
}
// -----parse_line.c END----

// -----parse_buff.c--------
int		is_valid_char(t_lemin *l)
{
	if ((l->buff[l->i] >= 'a' && l->buff[l->i] <= 'z') || \
	(l->buff[l->i] >= 'A' && l->buff[l->i] <= 'Z') || \
	(l->buff[l->i] >= '0' && l->buff[l->i] <= '9') || \
	(l->buff[l->i] == '#') || (l->buff[l->i] == ' ') || \
	(l->buff[l->i] == '-') || (l->buff[l->i] == '_') || \
	(l->buff[l->i] == ':'))
		return (1);
	return (0);
}

void	do_valid_char_op(t_lemin *l)
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

int		do_end_line_op(t_lemin *l)
{
	if (!l->i_line)
	{
		printf("ERROR : empty line\n");
		return (0);
	}
	l->line[l->i_line] = l->buff[l->i];
	l->line[l->i_line + 1] = 0;
	if (!(parse_line(l)))
		l->error = l->i_line + 1;
	if (l->end_buff && !l->end_line)
	{
		if (l->error)
			return (0);
		write(1, l->line, l->i_line + 1);
		l->end_buff = 0;
		l->rest = l->i + 1;
	}
	l->i++;
	l->end_line = l->i - l->error;
	l->i_line = 0;
	return (1);
}

void	write_buff_op(t_lemin *l)
{
	if (l->end_line)
	{
		// write(1, "-----------------start end_buff\n", 32);
		// printf("--- i_buff :%i\n", l->i);
		// printf("--- i_line :%i\n", l->i_line);
		// printf("--- end_line :%i\n", l->end_line);
		// printf("--- rest :%i\n", l->rest);
		// printf("--- end_buff :%i\n", l->end_buff);
		// printf("--- line :%s\n", l->line);
		// printf("--- buff :[%s]\n", l->buff);
		// printf("--------------------\n");
		if (l->end_line - l->rest)
			write(1, &l->buff[l->rest], l->end_line - l->rest);
		l->rest = 0;
		l->end_line = 0;
	}
	if (l->i_line)
		l->end_buff = 1;
	l->i = 0;
}

int		parse_buff(t_lemin *l)
{
	while (l->buff[l->i])
	{
		if (is_valid_char(l))
		{
			// printf("--------char-------\n");
			// printf("--- i_buff   : %i\n", l->i);
			// printf("--- i_line   : %i\n", l->i_line);
			// printf("--- end_line : %i\n", l->end_line);
			// printf("--- rest     : %i\n", l->rest);
			// printf("--- end_buff : %i\n", l->end_buff);
			// printf("--- line     : %s\n", l->line);
			// printf("--- buff     : %s\n", l->buff);
			// printf("--------------------\n");
			do_valid_char_op(l);
			// printf("--------char-------\n");
			// printf("--- i_buff   : %i\n", l->i);
			// printf("--- i_line   : %i\n", l->i_line);
			// printf("--- end_line : %i\n", l->end_line);
			// printf("--- rest     : %i\n", l->rest);
			// printf("--- end_buff : %i\n", l->end_buff);
			// printf("--- line     : %s\n", l->line);
			// printf("--- buff     : %s\n", l->buff);
			// printf("--------------------\n");
		}
		else if (l->buff[l->i] == '\n')
		{
			// printf("--------char-------\n");
			// printf("--- i_buff   : %i\n", l->i);
			// printf("--- i_line   : %i\n", l->i_line);
			// printf("--- end_line : %i\n", l->end_line);
			// printf("--- rest     : %i\n", l->rest);
			// printf("--- end_buff : %i\n", l->end_buff);
			// printf("--- line     : %s\n", l->line);
			// printf("--- buff     : %s\n", l->buff);
			// printf("--------------------\n");
			if (!(do_end_line_op(l)))
				return (0);
		}
		else
			return (0);
		if (!l->buff[l->i] || l->error)
		{
			write_buff_op(l);
			return (1);
		}
	}
	return (1);
}
// -----parse_buff.c END-----

void	get_file_content(t_lemin *lemin)
{
	// float temps;
	// clock_t t1, t2;
	// t1 = clock();

	if (LEMIN_READ_BUFF < 1 || read(0, lemin->buff, 0) < 0)
		return ;
	ft_bzero(lemin->buff, LEMIN_READ_BUFF);
	while ((lemin->ret = read(0, lemin->buff, LEMIN_READ_BUFF)) > 0)
	{
		lemin->buff[lemin->ret] = 0;
		if (!(parse_buff(lemin)))
			break ;
	}

	// t2 = clock();
	// temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	// printf("temps = %f\n", temps);

	//------CHECK ALL ROOM PRESENCE
	// int w = -1;
	// t_node *tmp;
	// int count = 0;
	// while(++w < HASH_SIZE)
	// {
	// 	if (lemin->node_tab[w])
	// 	{
	// 		count++;
	// 		printf("%s\n", lemin->node_tab[w]->name);
	// 		if (lemin->node_tab[w]->next)
	// 		{
	// 			printf("##########################%i\n", w);
	// 			tmp = lemin->node_tab[w]->next;
	// 			while (tmp)
	// 			{
	// 				count++;
	// 				printf("in list [%s]\n", tmp->name);
	// 				tmp = tmp->next;
	// 				if (count >= 4)
	// 					printf("_______________________________________\n");
	// 			}
	// 		}
	// 	}
	// }
	// printf("%i\n", count);
	//------CHECK ALL ROOM PRESENCE END

	//------CHECK ALL ROOM LINKED
	// int w = -1;
	// t_link *tmp_l;
	// while(++w < HASH_SIZE)
	// {
	// 	if (lemin->node_tab[w])
	// 	{
	// 		printf("\nROOM : %s\n", lemin->node_tab[w]->name);
	// 		if (lemin->node_tab[w]->links)
	// 		{
	// 			tmp_l = lemin->node_tab[w]->links;
	// 			while (tmp_l)
	// 			{
	// 				printf("has link to [%s]\n", tmp_l->room->name);
	// 				tmp_l = tmp_l->next;
	// 			}
	// 		}
	// 	}
	// }
	//------CHECK ALL ROOM LINKED END


	exit(0);
	// -------DATA<----------------------------



	//------TEST-------------------------------
	// int i;
	// int ret;
	// char *line;
	// float temps;
	// clock_t t1, t2;
	//
	// ret = 0;
	// i = 0;
	// t1 = clock();
	// while ((ret = get_next_line(0, &line)) > 0)
	// {
	// 	printf("%s\n", line);
	// 	i++;
	// }
	// t2 = clock();
	// temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	// printf("temps = %f\n", temps);
	// exit(0);
	//------END-TEST---------------------------
}

int		main()
{
	t_lemin *lemin;

	if (!(lemin = ft_memalloc(sizeof(t_lemin))))
		return (1);
	get_file_content(lemin);
	// start_algo(&lemin);
	// get_path(&lemin);
	free(lemin);
	return (0);
}
