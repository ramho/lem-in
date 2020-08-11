#ifndef BELLMAN_H
# define BELLMAN_H

# include "libft/libft.h"
# include <stdio.h>

void get_graph();
void init_reducing_graph();
void reduce();
int try_reduce(char pre[], char sec[], int w);
void printf_current_reach_cost();
void shortest_path();
int main();


#endif
