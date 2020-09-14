#include "../includes/lemin.h"

void	parse_edges(t_lemin *l)
{
	// printf("\n------------------parse_edges----------------\n");
	int i;

	i = -1;
	while(l->line[++i])
	{
		// printf("%c", l->line[i]);
	}
	return;
}

void	parse_nodes(t_lemin *l)
{
	// printf("\n------------------parse_nodes----------------\n");
	int i;
	int x = 0;
	int y = 0;
	int neg = 1;
	char ixt = 0;
	unsigned long hash;
	int odd = 0;
	static int collision = 0;

	hash = 0;
	i = -1;
	while(l->line[++i] != ' ')
	{
		odd = (i % 2) ? 3 : 2;
		// printf("odd [%i]\n", odd);
		// printf("char [%c]\n", l->line[i]);
		hash = (hash * 19) + l->line[i] - odd + ((l->line[i] - 32) * odd) + 32;
	}
	hash %= HASH_SIZE;
	// printf("%s", l->line);
	printf("\nHASH = %lu\n", hash);
	if (!l->hash_map[hash])
		l->hash_map[hash] = 1;
	else
	{
		l->hash_map[hash]++;
		printf("collision : %i\n", collision++);
	}
	i++;
	while (l->line[i] != '\n')
	{
		if ((l->line[i] == '-') && (l->line[i - 1] == ' '))
		{
			neg = -1;
		}
		else if (l->line[i] >= '0' && l->line[i] <= '9')
		{
			y *= 10;
			y += (l->line[i] - '0');
			ixt = 1;
		}
		else if (l->line[i] == ' ')
		{
			if (ixt)
				x = (y * neg);
			else
			{
				printf("no int\n");
				return;
			}
			neg = 1;
			y = 0;
		}
		else
		{
			printf("wrong coord format\n");
			return;
		}
		i++;
	}
	y *= neg;
	printf("---- coord : x = %i , y = %i \n", x, y);
	return;
}

void	parse_ant(t_lemin *l)
{
	int i;

	i = -1;
	// printf("------------------parse_ant----------------\n");

	while (l->line[++i] != '\n')
	{
		// printf("[%c]\n", l->line[i]);
		if (l->line[i] >= '0' && l->line[i] <= '9')
		{
			l->nb_ants *= 10;
			l->nb_ants += (l->line[i] - '0');
		}
		else
		{
			printf("wrong nb_ant format\n");
			return;
		}
		if (l->nb_ants < 0 || l->nb_ants > INT_MAX)
		{
			printf("not positive int\n");
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
		printf("start\n");
		l->start_room = 1;
	}
	else if (!(ft_strncmp("##end\n", l->line, 6)))
	{
		printf("end\n");
		l->start_end = 1;
	}
	else
	{
		return;
	}
	return;
}

void	parse_comment(t_lemin *l)
{
	return;
}

void parse_line(t_lemin *l)
{
	// printf("##################parse_line################\n");
	// printf("hash_tag = %i\n", l->hash_tag);
	// printf("space = %i\n", l->space);
	// printf("tiret = %i\n", l->tiret);
	// printf("%i\n", l->parse_flag);

	if (l->hash_tag == 3)
		parse_command(l);
	else if (l->hash_tag == 1)
		parse_comment(l);
	else if (l->parse_flag == 2)
		parse_edges(l);
	else if (l->parse_flag == 1)
	{
		if (!l->tiret)
			parse_nodes(l);
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
		printf("caca\n");
		return;
	}


	l->hash_tag = 0;
	l->space = 0;
	l->tiret = 0;
	// write(1, l->buff, l->i);
	// printf("%i\n", lemin->nb_ants); //
}

void parse_buff(t_lemin *l)
{
		// static intmax_t	parse_node = 0;
		// printf("\n###############parse_node %ji ################\n", ++parse_node);
	// write(1, &l->buff[l->i] , 1);
	// write(1, l->buff + l->i, l->ret - l->i);
		//
		// if (l->i)
		// {
		// 	l->i_line = 0;
		// 	printf("coucou\n");
		//
		// }
	while (l->buff[l->i])
	{
		// if (l->buff[l->i] == '#')
		// 	continue; // check if comment? start?/=2?(>stop||>stock) end?/=2?(>stop||>stock) other?(>ignore)
		if ((l->buff[l->i] >= 'a' && l->buff[l->i] <= 'z') || \
		(l->buff[l->i] >= 'A' && l->buff[l->i] <= 'Z') || \
		(l->buff[l->i] >= '0' && l->buff[l->i] <= '9') || \
		(l->buff[l->i] == '#') || (l->buff[l->i] == ' ') || (l->buff[l->i] == '-') || (l->buff[l->i] == '_') || (l->buff[l->i] == ':'))
		{
			// printf("--------char-------\n");
			// printf("--- i_buff :%i\n", l->i);
			// printf("--- i_line :%i\n", l->i_line);
			// printf("--- slash :%i\n", l->slash);
			// printf("--- rest :%i\n", l->rest);
			// printf("--- end_buff :%i\n", l->end_buff);
			if (((l->buff[l->i] == '#') && l->i_line < 2))
				l->hash_tag += (l->i_line + 1);
			if (l->buff[l->i] == ' ')
				l->space += 1;
			if (l->buff[l->i] == '-')
				l->tiret += 1;
			l->line[l->i_line] = l->buff[l->i];
			l->i++;
			l->i_line++;
			// printf("--- line :%s\n", l->line);
			// printf("--- buff :[%s]\n", l->buff);
			// printf("--------------------\n");
			// increment hash_key
		}
		// if (l->i == l->ret)
		else if (l->buff[l->i] == '\n')
		{
			// write(1, "-----------------line\n", 22);
			// printf("--- i_buff :%i\n", l->i);
			// printf("--- i_line :%i\n", l->i_line);
			// printf("--- slash :%i\n", l->slash);
			// printf("--- rest :%i\n", l->rest);
			// printf("--- end_buff :%i\n", l->end_buff);
			// printf("--- line :%s\n", l->line);
			// printf("--- buff :[%s]\n", l->buff);
			if (!l->i_line)
			{
				printf("empty line\n");
				return;
			}
			l->line[l->i_line] = l->buff[l->i];
			l->line[l->i_line + 1] = 0;
			parse_line(l);
			if (l->end_buff && !l->slash)
			{
				// write(1,"\n######write###### |", 20);
				// write(1, l->line, l->i_line + 1);
				// write(1,"|\n\n", 3);
				l->end_buff = 0;
				l->rest = l->i + 1;
			}
			l->i++;
			l->slash = l->i;
			l->i_line = 0;
			// write(1, "-----------------end_line\n", 26);
		}
		else
		{
			printf("end_buff2\n");
			return;
		}
		if (!l->buff[l->i])
		{
			// ++l->count_buff;
			// write(1, "%i\n", l->count_buff);
			if (l->slash)
			{
				// write(1, "-----------------start end_buff\n", 32);
				// printf("--- i_buff :%i\n", l->i);
				// printf("--- i_line :%i\n", l->i_line);
				// printf("--- slash :%i\n", l->slash);
				// printf("--- rest :%i\n", l->rest);
				// printf("--- end_buff :%i\n", l->end_buff);
				// printf("--- line :%s\n", l->line);
				// printf("--- buff :[%s]\n", l->buff);
				// printf("--------------------\n");
				// write(1,"\n######write###### |", 20);
				if (l->slash - l->rest)
					// write(1, &l->buff[l->rest], l->slash - l->rest);
				// write(1,"|\n\n", 3);
				l->rest = 0;
				l->slash = 0;
			}
			// write(1, "-----------------end end_buff\n", 30);
			if (l->i_line)
				l->end_buff = 1;
			l->i = 0;
			return;
		}
	}
}

void	get_file_content(t_lemin *lemin)
{
	//-------->BIG BANG------------------------
	float temps;
	clock_t t1, t2;

	t1 = clock();
	if (LEMIN_READ_BUFF < 1 || read(0, lemin->buff, 0) < 0)
		return ;
	lemin->parse_flag = 0;
	lemin->end_buff = 0;
	lemin->rest = 0;
	lemin->nb_ants = 0;
	lemin->i = 0;
	lemin->i_line = 0; //
	lemin->slash = 0; //
	lemin->hash_tag = 0;
	lemin->space = 0;
	lemin->tiret = 0;
	int x = -1;
	while (++x < HASH_SIZE)
		lemin->hash_map[x] = 0;
	ft_bzero(lemin->buff, LEMIN_READ_BUFF);
	// lemin->count_buff = 0;
	while ((lemin->ret = read(0, lemin->buff, LEMIN_READ_BUFF)) > 0)
	{
		// printf("end_buff3\n");
		// printf("%i\n", lemin->parse_flag);
		lemin->buff[lemin->ret] = 0;
		// if (!lemin->parse_flag)
		// 	parse_ant(lemin); // ok
		// if (lemin->parse_flag == 1)
		parse_buff(lemin);
		// if (lemin->parse_flag == 2)
		// 	parse_edges(lemin);
		// if (lemin->parse_flag == 3)
	}
	t2 = clock();
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	printf("temps = %f\n", temps);
	int w = -1;
	int tic = 0;
	while(++w < HASH_SIZE)
	{
		if (lemin->hash_map[w] > tic)
			tic = lemin->hash_map[w];
	}
	printf("%i\n", tic);
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



	int i;
	int ret;
	char *line;
	// printf("in get file content\n\n");
	ret = 0;
	i = 0;
	lemin->file = malloc(sizeof(char *) * 10000);
	while ((ret = get_next_line(0, &line)) > 0)
	{
		lemin->file[i] = ft_strdup(line);
		i++;
	}
	lemin->file[i] = NULL;
	lemin->table_size = i;// get number of lines and more for table
	if (ret < 0 || i < 5) // 5 because otherwise not enough rooms
	{
		printf("FILE ERROR");
		exit(0);
	}
	// print file--------------------------------
	i = -1;
	while (++i < lemin->table_size)
		printf("%s\n", lemin->file[i]);
	// end print file ---------------------------
}

//	while get_next_line


int main()
{
	t_lemin lemin;

	get_file_content(&lemin);
	// printf("11\n");
	if (!(parse_file(&lemin)))
	{
		printf("FILE ERROR\n");
		exit(0);
	}
	// printf("22\n");
	start_algo(&lemin);
	get_path(&lemin);
	return(0);
}
