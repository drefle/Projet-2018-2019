#include "tout.h"

extern
t_coord * creer_coord(int absi, int ord){
  t_coord * pt;
  pt = malloc(sizeof(t_coord));
  pt->absi = absi;
  pt->ord = ord;
  return pt;
}

static
void supprimer_coord(t_coord * a){
  free(a);
}

extern
void supprimer_coord_cb(void * a){
  supprimer_coord(a);
}
