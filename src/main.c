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
	float temps1,temps2;
	clock_t t1, t2, t3;
	// printf("00\n");
	t1 = clock();
	// printf("11\n");
	get_file_content(&lemin);
	// printf("22 ---------------\n");
	if (!(parse_file(&lemin)))
	{
		printf("FILE ERROR\n");
		exit(0);
	}
	t2 = clock();
	temps1 = (float)(t2-t1)/CLOCKS_PER_SEC;
	printf("-----------------------------------\n");
	// printf("33--------------------\n");
	start_algo(&lemin);
	get_path(&lemin);
	t3 = clock();
	temps2 = (float)(t3-t1)/CLOCKS_PER_SEC;
	printf("temps1 = %f temps2 = %f\n", temps1, temps2);
	return(0);
}
