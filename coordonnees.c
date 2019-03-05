#include <stdlib.h>
#include "coordonnees.h"

extern
t_coord * creer_coord(int absi, int ord){
  t_coord * pt;
  pt = malloc(sizeof(t_coord));
  pt->absi = absi;
  pt->ord = ord;
}

static
void copier_coord(t_coord * a, t_coord * b){
  b->absi = a->absi;
  b->ord = a->ord;
}

extern
void copier_coord_cb(void * a, void * b){
  copier_coord(a,b);
}

static
void supprimer_coord(t_coord * a){
  free(a);
}

extern
void supprimer_coord_cb(void * a){
  supprimer_coord(a);
}
