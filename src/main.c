#include "../includes/lemin.h"

void	get_file_content(t_lemin *lemin)
{
	int ret;
	int i;
	char *line;
	// printf("in get file content\n\n");
	ret = 0;
	i = 0;
	lemin->file=malloc(sizeof(char *) * 10000);
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
	start_algo(&lemin);
	get_path(&lemin);
	return(0);
}
