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

void add_new_link(t_node *room, t_node *room_to_link)
{
	t_node *tmp;

	printf("coucou\n");
	tmp = room->links;
	if (!(tmp))
	{
		tmp = room_to_link;
		printf("room linked = %s\n", tmp->name);
	}
	else
	{
		while (tmp)
		{
			if (ft_strequ(tmp->name, room_to_link->name))
			{
				printf("room_to_link already linked to the room");
				return ;
			}
			tmp = tmp->next;
		}
		tmp = room_to_link;
		printf("room linked = %s\n", tmp->name);
	}
	return ;
}

int	parse_edges(t_lemin *l)
{
	// printf("\n------------------parse_edges----------------\n");
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
	//------------------------------------
	return (1);
}

int	parse_nodes(t_lemin *l)
{
	// printf("\n------------------parse_nodes----------------\n");
	int i;
	int neg = 1;
	char is_int = 0;
	int odd = 0;
	t_node *node;
	static int collision = 0;

	if (!(node = (t_node*)malloc(sizeof(t_node))))
		return (0);
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
	// ---------hash fonction-------------
	// while(l->line[++i] != ' ')
	// {
	// 	odd = (i % 2) ? 3 : 2;
	// 	node->key = (node->key * 19) + l->line[i] - odd + ((l->line[i] - 32) * odd) + 32;
	// }
	// node->key %= HASH_SIZE;
	// -----------------------------------

	if (!(node->name = (char*)malloc(sizeof(char) * (i + 1))))
		return (0);
	ft_strncpy(node->name, l->line, i);
	node->name[i] = 0;
	// printf("[room %s hash %lu]\n", node->name, node->key);

	// if (!l->hash_map[node->key])
	// 	l->hash_map[node->key] = 1;
	// else
	// {
	// 	l->hash_map[node->key]++;
	// 	// printf("collision : %i\n", collision++);
	// }

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
	if (l->start_room == 1)
	{
		// printf("START\n");
		node->type = 1;
		l->start_node = *node;
		l->start_room++;
	}
	else if (l->end_room == 1)
	{
		// printf("END\n");
		node->type = 2;
		l->end_node = *node;
		l->end_room++;
	}
	l->number_of_nodes++;
	// printf("########################\n");
	// printf("line       : %s", l->line);
	// printf("name       : %s\n", node->name);
	// printf("x          : %i\n", node->x);
	// printf("y          : %i\n", node->y);
	// printf("hash key   : %lu\n", node->key);
	// printf("start room : %i\n", l->start_room);
	// printf("end room   : %i\n", l->end_room);
	// printf("###### STOCK ROOM ######\n");

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
	// printf("------------------parse_ant----------------\n");
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
			return;
		}
		if (l->nb_ants < 0 || l->nb_ants > INT_MAX)
		{
			printf("ERROR : not positive int\n");
			return;
		}
	}
	l->parse_flag = 1;
}

void	parse_command(t_lemin *l)
{
	int i;

	// printf("------------------parse_command----------------\n");
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
	// printf("##################parse_line################\n");
	// printf("hash_tag   : %i\n", l->hash_tag);
	// printf("space      : %i\n", l->space);
	// printf("tiret      : %i\n", l->tiret);
	// printf("parse flag : %i\n", l->parse_flag);
	if (l->hash_tag == 3)
		parse_command(l);
	else if (l->hash_tag == 1)
		parse_comment(l);
	else if (l->parse_flag == 2 && !l->space)
	{
		if (!(parse_edges(l)))
			return (0);
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
			if (!(parse_edges(l)))
				return (0);
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
	while (l->buff[l->i])
	{
		if ((l->buff[l->i] >= 'a' && l->buff[l->i] <= 'z') || \
		(l->buff[l->i] >= 'A' && l->buff[l->i] <= 'Z') || \
		(l->buff[l->i] >= '0' && l->buff[l->i] <= '9') || \
		(l->buff[l->i] == '#') || (l->buff[l->i] == ' ') || (l->buff[l->i] == '-') || (l->buff[l->i] == '_') || (l->buff[l->i] == ':'))
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
			if (((l->buff[l->i] == '#') && l->i_line < 2))
				l->hash_tag += (l->i_line + 1);
			if (l->buff[l->i] == ' ')
				l->space += 1;
			if (l->buff[l->i] == '-')
				l->tiret += 1;
			l->line[l->i_line] = l->buff[l->i];
			l->i++;
			l->i_line++;
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
				// write(1,"\n######write_LINE###### |", 25);
				write(1, l->line, l->i_line + 1);
				// write(1,"|\n\n", 3);
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
				// write(1, "-----------------start end_buff\n", 32);
				// printf("--- i_buff :%i\n", l->i);
				// printf("--- i_line :%i\n", l->i_line);
				// printf("--- end_line :%i\n", l->end_line);
				// printf("--- rest :%i\n", l->rest);
				// printf("--- end_buff :%i\n", l->end_buff);
				// printf("--- line :%s\n", l->line);
				// printf("--- buff :[%s]\n", l->buff);
				// printf("--------------------\n");
				// write(1,"\n######write_BUFF###### |", 25);
				if (l->end_line - l->rest)
					write(1, &l->buff[l->rest], l->end_line - l->rest);
				// write(1,"|\n\n", 3);
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
	// -------->BIG BANG------------------------
	float temps;
	clock_t t1, t2;

	t1 = clock();
	if (LEMIN_READ_BUFF < 1 || read(0, lemin->buff, 0) < 0)
		return ;
	// if (!(lemin->node_tab = (t_node **)malloc(sizeof(t_node *) * (HASH_SIZE + 1))))
	// 	return ;

	// int x = -1;
	// while (++x < HASH_SIZE)
	// 	lemin->hash_map[x] = 0;
	ft_bzero(lemin->buff, LEMIN_READ_BUFF); //
	while ((lemin->ret = read(0, lemin->buff, LEMIN_READ_BUFF)) > 0)
	{
		lemin->buff[lemin->ret] = 0;
		if (!(parse_buff(lemin)))
			break;
	}

	t2 = clock();
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	printf("temps = %f\n", temps);
	printf("number of nodes%i\n", lemin->number_of_nodes);

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
	int w = -1;
	t_node *tmp;
	while(++w < HASH_SIZE)
	{
		if (lemin->node_tab[w])
		{
			printf("ROOM : %s\n", lemin->node_tab[w]->name);
			if (lemin->node_tab[w]->links)
			{
				tmp = lemin->node_tab[w]->links;
				while (tmp)
				{
					printf("has link to [%s]\n", tmp->name);
					tmp = tmp->next;
				}
			}
		}
	}
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

int main()
{
	t_lemin *lemin;

	if (!(lemin = malloc(sizeof(t_lemin))))
        return (1);

    get_file_content(lemin);
    free(lemin);
	// printf("11\n");
	// if (!(parse_file(&lemin)))
	// {
	// 	printf("FILE ERROR\n");
	// 	exit(0);
	// }
	// // printf("22\n");
	// start_algo(&lemin);
	// get_path(&lemin);
	return(0);
}
