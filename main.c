#include "lemin.h"

void parse_file(t_lemin *lemin)
{
	int i;
	int j;

	lemin->nb_ants = ft_atoi(lemin->file[0]);
	lemin->file_links = malloc(sizeof(char *));
	create_table(lemin->table_size, lemin);
	i = 1;
	j = 0;
	while (lemin->file[i] != NULL)
	{
		if (lemin->file[i][0] == '#' && lemin->file[i][1] == '#')
			get_start_or_end_piece(&i, lemin);
		else if (ft_strchr(lemin->file[i], '-'))
		{
			lemin->file_links[j] = lemin->file[i];
			j++;
		}
		else if (ft_isalnum(lemin->file[i][0]))
			 get_room(lemin->file[i], lemin);
		else if ( lemin->file[i][0] == '#' && lemin->file[i][1] != '#')
			continue;
		i++;
	}
}

void	get_file_content(t_lemin *lemin)
{
	int ret;
	int i;
	char *line;

	ret = 0;
	i = 0;
	lemin->file=malloc(sizeof(char *) * 1000);
	while ((ret = get_next_line(0, &line)) > 0)
	{
		lemin->file[i]=ft_strdup(line);
		i++;
	}
	lemin->file[i] = NULL;
	lemin->count = 0;
	lemin->table_size = i;// get number of lines and more for table
	if (ret < 0 || i < 5)
	{
		printf("FILE ERROR");
		exit(0);
	}
}

int main()
{
	t_lemin lemin;

	get_file_content(&lemin);
	parse_file(&lemin);
	get_links(&lemin);
	get_route(&lemin);
	// int i = 0;
	// while(lemin.tab[hash_code(&lemin, "D")]->link[i])
	// {
	// 	printf("link is %s\n",lemin.tab[hash_code(&lemin, "D")]->link[i]);
	// 	i++;
	// }
	// printf("out of parse file\n");
	// print_tab(&lemin);
	// printf("lookup is %d\n",lookup(&lemin, "E"));
	return(0);
}
