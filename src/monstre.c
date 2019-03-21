#include "tout.h"

extern
t_monstre * creer_monstre(int x_salle, int y_salle, int vit){
  t_monstre * pt;
  pt = malloc(sizeof(t_monstre));
  pt->x_salle = x_salle;
  pt->y_salle = y_salle;
  pt->x_mouv = 0;
  pt->y_mouv = 0;
  pt->vitesse = vit;
  pt->last_dir = H;
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

extern
void deplacer_monstre(t_salle * salle, t_joueur * j, int i){ // Déplace et verifie si un projectile touche qqchose
  t_liste * l_monstre = salle->l_monstre;
  t_monstre * m;

  int mat_distance[M][N];
  int dist_monstre;
  creer_mat_distance(salle->m_salle, mat_distance);

  dist_monstre = 0;
  en_tete(l_monstre);
  while(!hors_liste(l_monstre)){
    m =  l_monstre->ec->p_val;

    salle->m_salle[m->x_salle][m->y_salle] = 0;

    dist_monstre = mat_distance[m->x_salle][m->y_salle];
    if(i % m->vitesse == 0){
      if( dist_monstre == 2){
        j->pv--;
      }else if( m->last_dir == V ){//Permet de les faire se déplacer en diagonale plutot qu'en 2 grandes lignes droites

        if( mat_distance[m->x_salle][m->y_salle+1] == dist_monstre-1 && salle->m_salle[m->x_salle][m->y_salle+1] == 0 ){
          m->y_salle++;

        }else if( mat_distance[m->x_salle][m->y_salle-1] == dist_monstre-1 && salle->m_salle[m->x_salle][m->y_salle-1] == 0 ){
          m->y_salle--;

        }else if( mat_distance[m->x_salle+1][m->y_salle] == dist_monstre-1 && salle->m_salle[m->x_salle+1][m->y_salle] == 0 ){
          m->x_salle++;

        }else if( mat_distance[m->x_salle-1][m->y_salle] == dist_monstre-1 && salle->m_salle[m->x_salle-1][m->y_salle] == 0 ){
          m->x_salle--;
        }
        m->last_dir = H;
      }else{
        if( mat_distance[m->x_salle+1][m->y_salle] == dist_monstre-1 && salle->m_salle[m->x_salle+1][m->y_salle] == 0 ){
          m->x_salle++;

        }else if( mat_distance[m->x_salle-1][m->y_salle] == dist_monstre-1 && salle->m_salle[m->x_salle-1][m->y_salle] == 0 ){
          m->x_salle--;

        }else if( mat_distance[m->x_salle][m->y_salle+1] == dist_monstre-1 && salle->m_salle[m->x_salle][m->y_salle+1] == 0 ){
          m->y_salle++;

        }else if( mat_distance[m->x_salle][m->y_salle-1] == dist_monstre-1 && salle->m_salle[m->x_salle][m->y_salle-1] == 0 ){
          m->y_salle--;
        }
        m->last_dir = V;

      }
    }
    salle->m_salle[m->x_salle][m->y_salle] = MONSTRE;
    suivant(l_monstre);

  }
}
