#include "lemin.h"

void parse_file(t_lemin *lemin)
{
	int i;

	lemin->nb_ants = ft_atoi(lemin->file[0]);
	create_table(lemin->table_size, lemin);
	i = 1;
	while (lemin->file[i] != NULL)
	{
		if (lemin->file[i][0] == '#' && lemin->file[i][1] == '#')
			get_start_or_end_piece(&i, lemin);
		else if (ft_strchr(lemin->file[i], '-'))
				get_links(0);
		else if (ft_isalnum(lemin->file[i][0]))
			 get_room(lemin->file[i], lemin);

		// else if ( lemin->file[i][0] == '#' && lemin->file[i][1] != '#')
		// 	continue;
		i++;
		// printf("in parse file while line %s\n", lemin->file[i]);
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
	while ((ret = get_next_line(0, &line)))
	{
		lemin->file[i]=ft_strdup(line);
		i++;
	}
	lemin->file[i] = NULL;
	lemin->table_size = i;// get number of lines and more for table
	if (ret == -1)
		exit(0);
}

int main()
{
	t_lemin lemin;

	get_file_content(&lemin);
	parse_file(&lemin);
	printf("out of parse file\n");

	// printf("name %s x %d y %d\n", lemin.node->name, lemin.node->x, lemin.node->y);
	return(0);
}
