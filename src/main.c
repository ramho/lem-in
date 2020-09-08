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


	lemin.t1 = clock();

	get_file_content(&lemin);
	if (!(parse_file(&lemin)))
	{
		printf("FILE ERROR\n");
		exit(0);
	}
	lemin.t2 = clock();
	lemin.temps1 = (float)(lemin.t2-lemin.t1)/CLOCKS_PER_SEC;
	start_algo(&lemin);
	get_path(&lemin);
	lemin.t3 = clock();
	lemin.temps2 = (float)(lemin.t3-lemin.t1)/CLOCKS_PER_SEC;
	printf("temps1 = %f temps2 = %f\n", lemin.temps1, lemin.temps2);
	return(0);
}
