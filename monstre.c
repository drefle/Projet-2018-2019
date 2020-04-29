#include <stdlib.h>
#include "tout.h"

extern
t_monstre * creer_monstre(int x_salle, int y_salle){
  t_monstre * pt;
  pt = malloc(sizeof(t_monstre));
  pt->x_salle = x_salle;
  pt->y_salle = y_salle;
  pt->x_mouv = 0;
  pt->y_mouv = 0;
  pt->vitesse = 0;
  return pt;
}

static
void copier_monstre(t_monstre * a, t_monstre * b){
  b->x_salle = a->x_salle;
  b->y_salle = a->y_salle;
  b->x_mouv = a->x_mouv;
  b->y_mouv = a->y_mouv;
  b->vitesse = a->vitesse;
}

extern
void copier_monstre_cb(void * a, void * b){
  copier_monstre(a,b);
}

static
void supprimer_monstre(t_monstre * a){
  free(a);
}

extern
void supprimer_monstre_cb(void * a){
  supprimer_monstre(a);
}
