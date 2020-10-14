#include "../includes/lemin.h"

void free_lemin(t_lemin *lemin)
{
  free(lemin);
  lemin = NULL;
  exit(-1);
}
