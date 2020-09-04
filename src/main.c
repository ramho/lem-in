#include "../includes/lemin.h"



void	get_file_content(t_lemin *lemin)
{
	int ret;
	int i;
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
