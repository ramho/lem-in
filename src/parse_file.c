// #include "../includes/lemin.h"
//
//
// t_link	*ft_create_link(char *room)
// {
// 	t_link *link;
//
// 	if (!(link = (t_link *)malloc(sizeof(t_link))))
// 		return (NULL);
// 	link->room = room;
// 	link->next = NULL;
// 	return (link);
// }
//
// void	ft_push_link_front(t_link **begin_list, char *room)
// {
// 	t_link *link;
//
// 	if (*begin_list)
// 	{
// 		link = ft_create_link(room);
// 		link->next = *begin_list;
// 		*begin_list = link;
// 	}
// 	else
// 		*begin_list = ft_create_link(room);
// }
//
// int parse_file(t_lemin *lemin)
// {
// 	int i;
// 	// printf("in parse file \n\n");
//
// 	//---------check if ants_nb = only digit-----------
// 	i = -1;
// 	while (lemin->file[0][++i])
// 	{
// 		if (!(ft_isdigit(lemin->file[0][i])))
// 			return (0);
// 	}
// 	//----------end check-------------------------------
// // printf("in parse file 222 \n\n");
// 	// ---------check ants format-----------------------
// 	if ((lemin->nb_ants = ft_atoi(lemin->file[0])) < 1)
// 		return (0);
// 	//----------- end check-----------------------------
//
// 	//-----------get number node & edge + check order---
//
// 	int node_flag;
//
// 	i = 0;
// 	node_flag = 1;
//
// 	seperate_nodes_edges(lemin);
//   	// printf("11\n");
//  	get_nodes(lemin->file_nodes, lemin);
// // printf("22\n");
//   get_edges(lemin);
// 	// printf("33\n");
// 	return (1);
// }
//
// int  seperate_nodes_edges(t_lemin *lemin)
// {
//   int i;
//   // printf("in seperate nodes n links\n");
//
//   i = 1;
//   lemin->file_edges = malloc(sizeof(char *) * lemin->table_size);
//   lemin->file_nodes = malloc(sizeof(char *) * lemin->table_size);
//   lemin->number_of_edges = 0;
//   lemin->number_of_nodes = 2;
//   // printf("hallo %d\n", lemin->table_size);
//   while (lemin->file[i] != NULL)
//   {
//     if (lemin->file[i][0] == '#' && lemin->file[i][1] == '#')
//       get_start_or_end_piece(&i, lemin);
//     else if (ft_strchr(lemin->file[i], '-'))
//     {
//       // printf("hallo 22\n");
//       lemin->file_edges[lemin->number_of_edges] = ft_strdup(lemin->file[i]);
//       lemin->number_of_edges++;
//     }
//     else if (ft_isalnum(lemin->file[i][0]))
//     {
//       // printf("hallo 33 line %s\n", lemin->file[i]);
//        lemin->file_nodes[lemin->number_of_nodes] = ft_strdup(lemin->file[i]);
//        lemin->number_of_nodes++;
//      }
//     // else if (lemin->file[i][0] == '#' && lemin->file[i][1] != '#')
//     //   continue;
//     i++;
//   }
//   // not part of code, just to check the content is correct in nodes and edges
//   // for ( i = 0; i < lemin->number_of_edges; i++)
//   //   printf("edges are %s\n", lemin->file_edges[i]);
//   // printf("\n");
//   // for ( i = 0; i < lemin->number_of_nodes; i++)
//   //     printf("nodes are %s\n", lemin->file_nodes[i]);
//   lemin->number_of_edges *= 2;
// 	printf("END\n");
//   return(1);
// }
//
// void get_start_or_end_piece(int *i, t_lemin *lemin)
// {
//
//   if (ft_strstr(lemin->file[*i], "start"))
//     {
//       lemin->file_nodes[0] = ft_strdup(lemin->file[*i + 1]);
//     }
//   if (ft_strstr(lemin->file[*i], "end"))
//       {
//      lemin->file_nodes[1] = ft_strdup(lemin->file[*i + 1]);
//       }
//   *i = *i + 1;
// }
//
// void get_edges( t_lemin *lemin)
// {
//
// 	int i;
// 	int j;
// 	int k;
// 	int z;
//
// 	// ---GET start/out & end/in links-------------------------
// 	char **rooms;
// 	// printf("in get edges nb of edge [%d]\n", lemin->number_of_edges);
//
// lemin->nb_start_out = 0;
// lemin->nb_end_in = 0;
// 	i = 0;
//
// 	if (!(lemin->node_tab[0]->links = (t_link *)malloc(sizeof(t_link))))
// 	return ;
// 	lemin->node_tab[0]->links = NULL;
// 	lemin->node_tab[0]->links = NULL;
//
//
// 	while(i < lemin->number_of_edges/2)
// 	{
// 		rooms = ft_strsplit(lemin->file_edges[i], '-');
// 		// printf("line is %s\n", lemin->file_edges[i]);
// 		if (!(ft_strcmp(rooms[0], lemin->node_tab[0]->name)))
// 		{
// 			// printf("here 1\n");
// 			ft_push_link_front(&lemin->node_tab[0]->links, rooms[1]);
// 			lemin->nb_start_out++;
// 		}
// 		if (!(ft_strcmp(rooms[1], lemin->node_tab[0]->name)))
// 		{
// 			// printf("here 2\n");
// 			ft_push_link_front(&lemin->node_tab[0]->links, rooms[0]);
// 			lemin->nb_start_out++;
// 		}
// 		if (!(ft_strcmp(rooms[0], lemin->node_tab[1]->name)))
// 		{
// 			ft_push_link_front(&lemin->node_tab[1]->links, rooms[1]);
// 			lemin->nb_end_in++;
// 		}
// 		if (!(ft_strcmp(rooms[1], lemin->node_tab[1]->name)))
// 		{
// 			ft_push_link_front(&lemin->node_tab[1]->links, rooms[0]);
// 			lemin->nb_end_in++;
// 		}
// 		i++;
// 	}
// 	printf("nb start out %i\n", lemin->nb_start_out);
// 	printf("nb end in %i\n", lemin->nb_end_in);
// 	if (lemin->nb_start_out == lemin->nb_end_in)
// 		lemin->nb_path = lemin->nb_start_out;
// 	else if (lemin->nb_start_out > lemin->nb_end_in)
// 		lemin->nb_path = lemin->nb_end_in;
// 	else if (lemin->nb_start_out < lemin->nb_end_in)
// 		lemin->nb_path = lemin->nb_start_out;
//
//
//
// 	// ---end GET---------------------------------------------
//
// 	// ---PRINT links-----------------------------------------
// 	// t_link *tmp;
// 	//
// 	// printf("---------print start links\n");
// 	// tmp = lemin->node_tab[0]->links;
// 	// while (tmp->next)
// 	// {
// 	// 	printf("%s\n", tmp->room);
// 	// 	tmp = tmp->next;
// 	// }
// 	// printf("%s\n", tmp->room); // one more print to get last iteration data
// 	//
// 	// printf("---------print end links\n");
// 	// tmp = lemin->node_tab[1]->links;
// 	// while (tmp->next)
// 	// {
// 	// 	printf("%s\n", tmp->room);
// 	// 	tmp = tmp->next;
// 	// }
// 	// printf("%s\n", tmp->room);
// 	//
// 	// printf("---------reprint start links\n"); //to see if can re-use (t_link *links) in t_node node_tab without modifying original adress---> OK
// 	// tmp = lemin->node_tab[0]->links;
// 	// while (tmp->next)
// 	// {
// 	// 	printf("%s\n", tmp->room);
// 	// 	tmp = tmp->next;
// 	// }
// 	// printf("%s\n", tmp->room);
// 	//
// 	// printf("--------------------\n");
// 	// end PRINT----------------------------------------------
//
//
// 	i = 0;
// 	z = 0;
//
// 	lemin->edge_tab =malloc(sizeof(t_edge *) * lemin->number_of_edges * 3); // 3 pour le dedoublement des nodes
//   	while(i < lemin->number_of_edges/2)
//   	{
// 		// printf("line is [%s]\n", lemin->file_edges[i]);
//     	lemin->edge_tab[z] =malloc(sizeof(t_edge));
//     	j = 0;
//     	while(j < ft_strlen(lemin->file_edges[i]))
//     	{
//       		while (lemin->file_edges[i][j] != '-')
//         		j++;
//       		lemin->edge_tab[z]->predecessor = ft_strsub(lemin->file_edges[i], 0, j);
//       		k = j + 1;
//       		while (lemin->file_edges[i][j])
//         		j++;
//       		lemin->edge_tab[z]->successor = ft_strsub(lemin->file_edges[i],k, j);
//       		lemin->edge_tab[z]->weight = 1;
//
//       		lemin->edge_tab[z + 1]=malloc(sizeof(t_edge));
// 					lemin->edge_tab[z]->reverse = lemin->edge_tab[z + 1];
//       		lemin->edge_tab[z + 1]->predecessor = ft_strdup(lemin->edge_tab[z]->successor);
//       		lemin->edge_tab[z + 1]->successor = ft_strdup(lemin->edge_tab[z]->predecessor);
//       		lemin->edge_tab[z + 1]->weight = 1;
//
//       // printf("[%d]edge [%s][%s] - [%d]reverse[%s][%s]\n\n", z,lemin->edge_tab[z]->predecessor, lemin->edge_tab[z]->successor, z + 1, lemin->edge_tab[z + 1]->predecessor, lemin->edge_tab[z + 1]->successor );
//     	}
//   		z += 2;
//   		i++;
//   	}
// }
