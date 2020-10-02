/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoorntj <rhoorntj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 17:31:27 by rhoorntj          #+#    #+#             */
/*   Updated: 2020/10/02 18:30:24 by rhoorntj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void print_path_for_one(t_lemin *lemin)
{
	printf("in printf for one\n");
	int hill;
	int i;
	int j;
	t_path *index;

	i = 1;
	hill = 1;
	while (hill)
	{
		while (i <= lemin->nb_ants)
		{
			j = 0;
			while(lemin->final_path_tab[j])
			{
				// printf("j [\n", j);
				index = lemin->final_path_tab[j];
				add_ant_to_path(index, i);
				loop_in_path(index);
				j++;
			}
			printf("\n");
			i++;
		}
		hill = 0;
	}
}


void add_ant_to_path(t_path *index , int i)
{
	index->node->ant = i;
	index->visited = 1;
	printf("000 L%d-%s ", index->node->ant, index->node->name);
}

void loop_in_path(t_path *index, int i)
{
	while(index)
	{
		// printf("node [%s] ant [%d]  ", index->node->name, index->node->ant);
		// printf("1\n");

		{

			if(index->next)
			{
				index->next->node->ant = index->node->ant;
			// printf("next node [%s] ant [%d]\t", index->next->node->name, index->next->node->ant);
			}

			printf("111 L%d-%s  ", index->node->ant, index->node->name);

		}
		// printf("node [%s] ant [%d]\n", index->node->name, index->node->ant);
		// printf("node next [%s] ant [%d]\n", index->node->next->name, index->next->node->ant);
		// printf("----------------next\n");
		index = index->next;
		// printf("5\n");
	}
}



void print_path(t_lemin *lemin)
{
// 	printf("print path\n");
// 	int i;
// 	int j;
// 	int hill = 1;
// 	t_path *index;
//

		if( lemin->nb_final_path == 1)
		{
			print_path_for_one(lemin);
			return;
		}
// 	i = 1;
// 	printf("\n");
// 	while (hill)
// 	{
// 		j = 0;
// 		printf("j/path number [%d][%d]\n",j, lemin->nb_final_path);
// 		while (j < lemin->nb_final_path )
// 		{
// 			check_for_ant(lemin->final_path_tab[j], &i);
// 			j++;
// 		}
// 		printf("\n");
// 		j = 0;
// 		// while (j < lemin->nb_final_path )//&& lemin->final_path_tab[j]->node != lemin->end_node)
// 		// {
// 			// printf("here [%p]\n", lemin->final_path_tab[j]);
// 			index = lemin->final_path_tab[j];
// 			// printf("here [%p]\n",index);
// 			while (index)
// 			{
// 				// printf("there\t");
// 				check_for_ant_bis(index, &i);
// 				index = index->next;
//
// 			}
// 			// printf("HERE\n");
// 			// printf("HERE i [%d] room [%s]\n",i , lemin->final_path_tab[j]->node->name);
// 			// printf("L%d-%s ",i , lemin->final_path_tab[j]->node->name);
// 			// printf("THERE\n");
// 			// i++;
// 			// lemin->final_path_tab[j] = lemin->final_path_tab[j]->next;
// 		// 	j++;
// 		// }
// 		hill = 0;
// 		// printf("ants passed [%d] j = [%d]\n", i, j);
// 		// printf("node [%s]\n", lemin->final_path_tab[j - 1]->node->name);
// 	}
// 	hill = 0;
//
}
//
// int check_for_ant(t_path *path, int *i)
// {
// 	// printf("in check for ant\n");
// 	// printf("path node name ant [%d]\n", path->node->ant);
// 		// printf("1\n");
// 		path->node->ant = *i;
// 		// printf("2\n");
// 		// path->next->node->ant = *i;
// 		// printf("3\n");
// 		*i += 1;
// 		printf("L%d-%s ",path->node->ant, path->node->name);
// 		// printf("4\n");
// 		// return(1);
// 	// else
// 	//  printf("L%d-%s ",lemin->final_path_tab[j]->node->ant, lemin->final_path_tab[j]->node->name);
// 	return(1);
// }
//
// int check_for_ant_bis(t_path *path, int *i)
// {
// 	// printf("in check for ants BIS\t");
// 	if(path->next)
// 		path->next->node->ant = path->node->ant;
// 	path->node->ant += 1;
// 	// *i += 1;
// 	printf("L%d-%s ",path->node->ant, path->node->name);
// return(1);
// }
