#include "lemin.h"

void parse_file(t_lemin *lemin)
{
	printf("in parse file \n\n");
	lemin->nb_ants = ft_atoi(lemin->file[0]);

	// lemin->node_name = malloc(sizeof(char *));
	seperate_nodes_links(lemin);
}

void	get_file_content(t_lemin *lemin)
{
	int ret;
	int i;
	char *line;
	printf("in get file content\n\n");
	ret = 0;
	i = 0;
	lemin->file=malloc(sizeof(char *));
	while ((ret = get_next_line(0, &line)) > 0)
	{
		lemin->file[i]=ft_strdup(line);
		i++;
	}
	lemin->file[i] = NULL;
	lemin->table_size = i;// get number of lines and more for table
	if (ret < 0 || i < 5) // 5 because otherwise not enough rooms
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
	// get_links(&lemin);
	// printf("here is i %d\n", lemin.number_of_nodes);
	// int i;
	// for (i = 0; i < lemin.number_of_nodes; i ++)
	// 	printf("name %s\n", lemin.node_name[i]);
	// start_algo(&lemin);
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
