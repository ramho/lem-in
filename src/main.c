// #include "../includes/lemin.h"
//
//
//
// void	get_file_content(t_lemin *lemin)
// {
// 	int ret;
// 	int i;
// 	char *line;
// 	// printf("in get file content\n\n");
// 	ret = 0;
// 	i = 0;
// 	lemin->file = malloc(sizeof(char *) * 10000);
// 	while ((ret = get_next_line(0, &line)) > 0)
// 	{
// 		lemin->file[i] = ft_strdup(line);
// 		i++;
// 	}
// 	lemin->file[i] = NULL;
// 	lemin->table_size = i;// get number of lines and more for table
// 	if (ret < 0 || i < 5) // 5 because otherwise not enough rooms
// 	{
// 		printf("FILE ERROR");
// 		exit(0);
// 	}
// 	// print file--------------------------------
// 	i = -1;
// 	while (++i < lemin->table_size)
// 		printf("%s\n", lemin->file[i]);
// 	// end print file ---------------------------
// }
//
// int main()
// {
// 	t_lemin lemin;
// 	float temps1,temps2;
// 	clock_t t1, t2, t3;
// 	// printf("00\n");
// 	t1 = clock();
// 	// printf("11\n");
// 	get_file_content(&lemin);
// 	// printf("22 ---------------\n");
// 	if (!(parse_file(&lemin)))
// 	{
// 		printf("FILE ERROR\n");
// 		exit(0);
// 	}
// 	t2 = clock();
// 	temps1 = (float)(t2-t1)/CLOCKS_PER_SEC;
// 	printf("-----------------------------------\n");
// 	// printf("33--------------------\n");
// 	start_algo(&lemin);
// 	get_path(&lemin);
// 	t3 = clock();
// 	temps2 = (float)(t3-t1)/CLOCKS_PER_SEC;
// 	printf("temps1 = %f temps2 = %f\n", temps1, temps2);
// 	return(0);
// }






//JECARERE

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
		// printf("%c", l->line[*i]);
		odd = ((*i - oups) % 2) ? 3 : 2;
		key = (key * 19) + l->line[*i] - odd + ((l->line[*i] - 32) * odd) + 32;
	}
	// printf("===== %d\n", key % HASH_SIZE);
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
void	parse_edges(t_lemin *l)
{
	// printf("\n------------------parse_edges----------------\n");
	int i;
	int key;
	int key2;
	t_node *a;
	t_node *b;
	int middle;
	int end;
	// t_node *tmp;

	i = -1;
	key = hash(l, &i, '-');
	// middle = i;
	// key = hash(l, &i, '\n')
	// tmp = l->node_tab[key];
	if (l->node_tab[key])
		a = l->node_tab[key];
	else
	{
		printf("linked room a doesn't exit\n");
		exit (0);
	}

	key2 = hash(l, &i, '\n');
	if (l->node_tab[key2])
		b = l->node_tab[key2];
	else
	{
		printf("linked room b doesn't exit\n");
		exit (0);
	}
	// printf("[%s-%s]\n", a->name, b->name);


	t_edge *ed;

	if (!(ed = (t_edge*)malloc(sizeof(t_edge))))
		return;
	ed->predecessor = a;
	ed->successor = b;
	ed->weight = 1;


//START ajout RH
// printf("key start[%s] %lu key end[%s] %lu\n", l->start_node->name, l->start_node->key,l->end_node->name, l->end_node->key);
// printf( "key[%s] %lu key[%s] %lu\n", a->name, a->key, b->name, b->key);
// printf("\n a name ->%s/key[%lu] , b  ->%s/key[%lu]\n", a->name, a->key, b->name, b->key);
// printf("start %p end %p ==== a %p b %p\n", &l->start_node, &l->end_node, a, b);
	// printf("[%s] == %s/%s [%s] == %s/%s\n", l->start_node.name, a->name, b->name, l->end_node.name, a->name, b->name );

	reverse_edge(ed);
	if (a->key == l->start_node->key || b->key == l->start_node->key)
	{
		// printf("here\n");
		l->nb_start_out += 1;
	}
	if (a->key == l->end_node->key || b->key == l->end_node->key)
	{
		// printf("there\n");
		l->nb_end_in += 1;
	}

// END ajout RH
	if (!(l->edge_tab))
	{
		l->edge_tab = ed;
	}
	else
	{
		ed->next = l->edge_tab;
		l->edge_tab = ed;
	}
	// printf("%s\n", "coucou");

	// printf("(%s)\n", l->edge_tab->predecessor->name);
	// printf("(%s)\n", l->edge_tab->successor->name);


	return;
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
	node->reach_cost = 0;
	if (l->start_room == 1)
	{
		node->infinity = 0;
		l->start_node = node;
		l->start_room++;
		// printf("START address [%p] VS node address [%p]\n", l->start_node, node);
	}
	else if (l->end_room == 1)
	{
		// printf("END\n");
			node->infinity = 1;
		l->end_node = node;
		l->end_room++;
	}
	else
			node->infinity = 1;
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
	//START ajout RH , pur nombre de path
	// printf("start %d - end %d\n", lemin->nb_start_out, lemin->nb_end_in);
		if (lemin->nb_start_out == lemin->nb_end_in)
			lemin->nb_path = lemin->nb_start_out;
		else if (lemin->nb_start_out > lemin->nb_end_in)
			lemin->nb_path = lemin->nb_end_in;
		else if (lemin->nb_start_out < lemin->nb_end_in)
			lemin->nb_path = lemin->nb_start_out;
	//END ajout RH
	t2 = clock();
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	printf("temps = %f\n", temps);

}

int main()
{
	float temps;
	clock_t t1, t2;
	t_lemin *lemin;

t1 = clock();
	if (!(lemin = malloc(sizeof(t_lemin))))
        return (1);
	get_file_content(lemin);
	start_algo(lemin);
	// get_path(&lemin);
	printf("out\n");
	t2 = clock();
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	printf("temps = %f\n", temps);
	return(0);
}
