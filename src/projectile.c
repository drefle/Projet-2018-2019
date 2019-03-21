#include "tout.h"

extern int nb_mob_tot;

static
void supprimer_projectile(t_projectile * p){
  free(p);
}

extern
void supprimer_projectile_cb(void * p){
  supprimer_projectile(p);
}

static
void copier_projectile(t_projectile * a, t_projectile * b){
  a->x = b->x ;
  a->y = b->y ;
  a->mouv_x = b->mouv_x ;
  a->mouv_y = b->mouv_y ;
  a->vitesse = b->vitesse ;
}


extern
void copier_projectile_cb(void * a, void * b){
  copier_projectile(a,b);
}


extern
t_projectile * creer_projectile(int x, int y, int mouv_x, int mouv_y, int vit){ // Creation d'un projectile.
    t_projectile * p = malloc(sizeof(t_projectile));
    p->x = x + mouv_x;
    p->y = y + mouv_y;
    p->mouv_x = mouv_x;
    p->mouv_y = mouv_y;
    p->vitesse = vit;


    return p;
}


extern
void supprimer_monstre_coord(t_salle * salle, int x, int y){
  t_liste * l_monstre = salle->l_monstre;

  en_tete(l_monstre);
  t_monstre * m;
  while(!hors_liste(l_monstre)){ //Vérifie quel monstre a été touché
    m = l_monstre->ec->p_val;

    if(x == m->x_salle && y == m->y_salle){
      salle->m_salle[m->x_salle][m->y_salle] = 0;
      oter_elt(l_monstre);
      nb_mob_tot--;
      if( liste_vide(l_monstre) ){
        salle->etat = VIDE;
      }
    }
    suivant(l_monstre);
  }
}


extern
void tirer_projectile(t_salle * salle, int x, int y, int mouv_x, int mouv_y, int vit){

  if( salle->m_salle[x + mouv_x][y + mouv_y] == 0 ){

    en_tete(salle->l_projectile);
    ajout_droit(salle->l_projectile, creer_projectile(x, y, mouv_x, mouv_y , vit));
    salle->m_salle[x + mouv_x][y + mouv_y] = PROJECTILE;
  }else{
    if( salle->m_salle[x + mouv_x][y + mouv_y] == MONSTRE){
      supprimer_monstre_coord( salle, x + mouv_x, y + mouv_y );
    }
  }
}





extern
void deplacer_projectile(t_salle * salle, t_joueur * j,int i){ // Déplace et verifie si un projectile touche qqchose
  t_liste * l_projectile = salle->l_projectile;
  t_projectile * p;

  en_tete(l_projectile);
  while(!hors_liste(l_projectile)){
    p =  l_projectile->ec->p_val;

    if(i % p->vitesse == 0){
      salle->m_salle[p->x][p->y] = 0;
      p->x += p->mouv_x;
      p->y += p->mouv_y;
    }

    if( salle->m_salle[p->x][p->y] !=0 ){ // Vérifie si le projectile touche qqchose
      if( salle->m_salle[p->x][p->y] == JOUEUR){ // Joueur touché
        j->pv--;
      }
      else if( salle->m_salle[p->x][p->y] == MONSTRE){ // Un Monstre touché
        supprimer_monstre_coord(salle, p->x, p->y);
      }
      oter_elt(l_projectile);
    }else{
        salle->m_salle[p->x][p->y] = PROJECTILE;
    }
      suivant(l_projectile);
  }

}
