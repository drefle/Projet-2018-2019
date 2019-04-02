#include "tout.h"


void init_liste(t_liste * liste, void (*supprimer_elem)(void *)){
  liste->drapeau = malloc(sizeof(t_element));
  liste->drapeau->succ = liste->drapeau;
  liste->drapeau->pred = liste->drapeau;
  liste->supprimer_elem = supprimer_elem;
  liste->ec = liste->drapeau;
  liste->nb_elem = 0;
}

int liste_vide(t_liste * liste){
  return(liste->drapeau->pred == liste->drapeau);
}

int hors_liste(t_liste * liste){
  return( liste->ec == liste->drapeau);
}

void en_tete(t_liste * liste){
  if(!liste_vide(liste)){
    liste->ec = liste->drapeau->succ;
  }
}

void en_queue(t_liste * liste){
  if(!liste_vide(liste)){
    liste->ec = liste->drapeau->pred;
  }
}

void precedent(t_liste * liste){
  if(!hors_liste(liste)){
    liste->ec = liste->ec->pred;
  }
}

void suivant(t_liste * liste){
  if(!hors_liste(liste)){
    liste->ec= liste->ec->succ;
  }
}

void valeur_elt_coord(t_liste * liste, t_coord * coord){
  if(!hors_liste(liste)){
    t_coord * temp = liste->ec->p_val;
    coord->absi = temp->absi;
    coord->ord = temp->ord;
  }
}

void modif_elt(t_liste * liste,void * v){
  if(!hors_liste(liste)){
    liste->supprimer_elem(liste->ec->p_val);
    liste->ec->p_val = v;
  }
}

void oter_elt(t_liste * liste){
  t_element* elem;
  if(!hors_liste(liste)){
    elem = liste->ec;
    liste->ec->succ->pred = liste->ec->pred;
    liste->ec->pred->succ = liste->ec->succ;
    liste->ec = liste->ec->pred;
    liste->supprimer_elem(elem->p_val);
    liste->nb_elem = liste->nb_elem - 1;
    free(elem);
  }
}

void ajout_droit(t_liste * liste, void * pt){
  t_element* nouv;

  if(liste_vide(liste) || !hors_liste(liste)){
    nouv = malloc(sizeof(t_element));
    nouv->succ = liste->ec->succ;
    nouv->pred = liste->ec;
    liste->ec->succ = nouv;
    nouv->succ->pred = nouv;
    nouv->p_val = pt;
    liste->ec = nouv;
    liste->nb_elem = liste->nb_elem + 1;
  }
}

void ajout_gauche(t_liste * liste, void * pt){
  t_element* nouv;
  if(liste_vide(liste) || !hors_liste(liste)){
    nouv = malloc(sizeof(t_element));
    nouv->succ = liste->ec;
    nouv->pred = liste->ec->pred;
    liste->ec->pred = nouv;
    nouv->pred->succ = nouv;
    nouv->p_val = pt;
    liste->ec = nouv;
    liste->nb_elem = liste->nb_elem + 1;
  }
}
