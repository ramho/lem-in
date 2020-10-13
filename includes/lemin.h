/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoorntj <rhoorntj@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 17:35:55 by rhoorntj          #+#    #+#             */
/*   Updated: 2020/10/13 15:49:06 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "../libft/libft.h"
# include <stdio.h>
# include <time.h>
# include <stdlib.h>
# include <unistd.h>
# define LEMIN_READ_BUFF 65536
# define LINE_SIZE 100
# define HASH_SIZE 1000000

typedef struct s_lemin t_lemin;
typedef struct s_node 	t_node;
typedef struct s_edge   t_edge;
typedef struct s_path   t_path;
typedef struct s_link   t_link;
typedef struct s_ant    t_ant;

struct 					s_node
{
  unsigned long key; // for hash map but name can also be the key
  char *name;
  int type; // 1 is start and 2 is end
  int x;
  int y;
  int reach_cost;
  int infinity;
  int ant;
  t_node *predecessor;
  t_node *next;
  int duplicated;
  struct s_link *links; // linked list for links

  t_node *dup_out;
};

struct s_edge
{
    t_node *predecessor;
    t_node *successor;
    int weight;
    int visited;
	int no_go;
	t_edge *reversed;
	t_edge *next;
};

struct s_path
{
  t_node *node;
  int visited;
  int ant;
  t_path * next;
};

struct s_link
{
    t_node *room;
	   int used;
    t_link *next;
};

struct s_ant
{
  int ant;
  int end;
  int no_print;
  t_path *path;
  t_node *node;
};

struct  s_lemin
{
	int error;



	int ret;
	char buff[LEMIN_READ_BUFF + 1];
	int i; // index in buff
	char line[LINE_SIZE];
	int i_line; // index in line
	char parse_flag;
	char end_buff;
	int rest;
	int end_line;
	int	hash_tag;
	int	space;
	char get_out;

	int	tiret;
	char start_room;
	char end_room;

	int x;
	int y;

    int nb_ants;
    char **file;
    int table_size;

	int	nb_start_out;
	int	nb_end_in;

    char **file_edges; //save only links
    char **file_nodes; // save only nodes
    int number_of_nodes; // count of nodes
    int number_of_edges;

    t_node *node_tab[HASH_SIZE + 1];
	t_node *start_node;
	t_node *end_node;

    t_edge *edge_tab;
    char **node_name;

    // t_path *head;
    t_path **path_tab;
    t_path **final_path_tab;
    int nb_path;// not is use yet
	int nb_bellmanf_path;
	int *len_tab;

  t_ant ** ant_tab;

    t_path **final_path_tabs;

    int ant_in_end;


};

/*
**  main.c
*/
int main();
void	get_file_content(t_lemin *lemin);

/*
**  parse_tool.c.c
*/
int		hash(t_lemin *l, int *i, char c);

/*
**  parse_edge.c
*/
void	reverse_edge(t_edge *ed);
t_node	*get_edge_room(t_lemin *l, int i, int key, int place);
void	add_new_link(t_node *room, t_node *room_to_link);
int		free_edge(t_edge *ed);
int		parse_edges(t_lemin *l, int i, int key, int middle);
void 	store_new_edge(t_lemin *l, t_edge *ed);
void 	check_exit_entry(t_lemin *l, t_edge *ed);

/*
** parse_node.c
*/
int		get_coord(t_lemin *l, int *i, t_node *node);
void	store_start_end_node(t_lemin *l, t_node *node);
int		store_node(t_lemin *l, t_node *node);
int		free_node(t_node *node);
int		parse_nodes(t_lemin *l);

/*
** parse_buff.c
*/
int		parse_buff(t_lemin *l);
void	write_buff_op(t_lemin *l);
int		do_end_line_op(t_lemin *l);
int		is_valid_char(t_lemin *l);
void	do_valid_char_op(t_lemin *l);

/*
** parse_line.c
*/
void	parse_ant(t_lemin *l);
int		parse_command(t_lemin *l);
int		parse_flag_one(t_lemin *l);
int		parse_line(t_lemin *l);
/*
**  algo.c
*/
int init_save_path(t_lemin *lemin, int index_path);
int save_path(t_lemin *lemin, t_path *head, t_path *new);
void init_infinity(t_lemin *lemin);
int start_algo(t_lemin *lemin);

/*
**  bellman_ford.c
*/
int bellman_ford(t_lemin *lemin);
void try_reduce(t_node *pre, t_node *sec, int w, int *changed);

/*
**  suurballe.c
*/
void create_dup_room( t_node *node);
void suurballe(t_lemin *lemin, int path_index);
void	check_edge(t_node *pre, t_node *suc, t_edge *edge, t_lemin *lemin);

/*
**  get_path.c
*/
void get_path(t_lemin *lemin);
void select_edge(t_lemin *lemin);
int get_next_node(t_node *start, t_lemin *lemin, int i);
void add_node_link_to_final_path(t_lemin *lemin, t_node *node, int i);
void sort_int_tab(t_lemin *lemin, int size);

/*
**	print.c
*/
void print_path(t_lemin *lemin);
void print_ant(t_ant **tab, int nb_ant, t_lemin *lemin);

/*
**  ant_utils.c
*/
void update_ant(t_ant **tab, int nb_ant, t_lemin *lemin);
int move_ant(t_ant *ant, t_lemin *lemin);
int init_ants(t_ant **tab, int nb_ant, t_path *path);

/*
**  path_utils.c
*/
void  dispatch_ant_in_path(t_lemin *lemin);
void choose_from_last_path(t_lemin *lemin, int i, int j);
void choose_path_except_last(t_lemin *lemin, int i, int *j);

/*
**  free.c
*/
void free_struct(t_lemin *lemin);

#endif
