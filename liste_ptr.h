#include <stdlib.h>
#include <stdio.h>

typedef struct element{
  void * p_val;
  struct element* pred;
  struct element* succ;
}t_element;

typedef struct liste_s{
  void (*copier_elem)(void *, void *);
  void (*supprimer_elem)(void *);
  t_element* drapeau;
  t_element* ec;
  int nb_elem;
}t_liste;

extern
void init_liste(t_liste * liste, void (*copier_elem)(void *, void *), void (*supprimer_elem)(void *));

extern
int liste_vide(t_liste * liste);

extern
int hors_liste(t_liste * liste);

extern
void en_tete(t_liste * liste);

extern
void en_queue(t_liste * liste);

extern
void precedent(t_liste * liste);

extern
void suivant(t_liste * liste);

extern
void valeur_elt(t_liste * liste, void * v);
extern
void modif_elt(t_liste * liste, void * v);

extern
void oter_elt(t_liste * liste);

extern
void ajout_droit(t_liste * liste, void * pt);

extern
void ajout_gauche(t_liste * liste, void * pt);
