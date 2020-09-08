#include "../includes/lemin.h"

void get_nodes(char **tab, t_lemin *lemin)
{
	int i;
	int j;
	int k;
	t_node *temp;

  lemin->node_name=malloc(sizeof(char *) * lemin->number_of_nodes);
  lemin->node_tab=malloc(sizeof(t_node *) * lemin->number_of_nodes);
	temp = malloc(sizeof(t_node));
  i = 0;
	while(i < lemin->number_of_nodes)
	{
    j = 0;
    k = 0;
		while (j < ft_strlen(tab[i]))
		{
			while (tab[i][j] != ' ')
				j++;
			temp->name = ft_strsub(tab[i], 0, j);
			k = j + 1;
			while ( tab[i][k] != ' ')
			{
				if (ft_isdigit(tab[i][k]))
					k++;
				else
				{
					ft_printf("%s ERROR x\n", tab[i]);
					exit(0);
				}
			}
			temp->x = ft_atoi(&tab[i][j + 1]);
			j = j + (ft_numlen(temp->x) + 1);
			k = j + 1;
			while (tab[i][k] != '\0')
			{
				if (k <= ft_strlen(tab[i]) && ft_isdigit(tab[i][k]))
					k++;
				else
				{
					ft_printf("ERROR y\n");
					exit(0);
				}
			}
			temp->y = ft_atoi(&tab[i][j]);
			j = j + (ft_numlen(temp->y) + 1);
		}
    fill_node_tab(i, lemin, temp);
		i++;
	}
}

void fill_node_tab(int i, t_lemin *lemin, t_node *temp)
{
  lemin->node_tab[i]=malloc(sizeof(t_node));
  lemin->node_tab[i]->name = ft_strdup(temp->name);
  lemin->node_tab[i]->x = temp->x;
  lemin->node_tab[i]->y = temp->y;
  lemin->node_tab[i]->type = 0;
  lemin->node_tab[i]->infinity = 1;
  if (i == 0)
  {
    lemin->node_tab[i]->type = 1; //start node
    lemin->node_tab[i]->reach_cost = 0;
    lemin->node_tab[i]->infinity = 0;
		lemin->start_node = lemin->node_tab[i]->name;
  }
  if (i == 1)
  {
    lemin->node_tab[i]->type = 2;// end node
		lemin->end_node = lemin->node_tab[i]->name;
  }
}
