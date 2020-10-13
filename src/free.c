#include "../includes/lemin.h"

void free_struct(t_lemin *lemin)
{
  free(lemin);
  lemin = NULL;
  exit(-1);
}
