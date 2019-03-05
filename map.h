#include <stdio.h>
#include <stdlib.h>

#include "coordonnees.h"
#include "salle.h"
#include "liste_ptr.h"


extern
t_coord * creer_coord(int absi, int ord);

extern
void copier_coord_cb(void * a, void * b);

extern
void supprimer_coord_cb(void * a);

extern
void init_map(t_salle * m_map[L][L]);

extern
int coord_valides(t_salle * m_map[L][L], int x, int y);

extern
void maj_coord_possible(t_salle * m_map[L][L], t_liste * l_coord , int x , int y);

extern
void genmap(t_salle * m_map[L][L], int n);
