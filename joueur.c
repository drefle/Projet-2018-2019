#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#include "tout.h"


#define N 46
#define M 26
#define L 12


/**
* \file joueur.c
* \author Adrien P. - Paul PDC. - David C. - Paul C.
* \date 04/03/2019
* \brief Permet le mouvement du joueur à travers les salles
*/

extern
t_joueur * creer_joueur(int xm, int ym, int xs, int ys, int pv){
    t_joueur * joueur = malloc(sizeof(t_joueur));
    joueur->x_map = xm;
    joueur->y_map = ym;
    joueur->x_salle = M/2;
    joueur->y_salle = N/2;
    joueur->x_mouv = 0;
    joueur->y_mouv = 0;
    joueur->pv = pv;
    return joueur;
}


/* Test sur la validité des coordonées */
extern
int est_franchissable(int x, int y, int salle[M][N]){
	return (salle[x][y] == 0);
}


extern
void deplacer_joueur(t_salle * m_map[L][L], t_joueur * joueur){
  if(est_franchissable( ((joueur->x_salle) + (joueur->x_mouv)) , ((joueur->y_salle) + (joueur->y_mouv)) , m_map[joueur->x_map][joueur->y_map]->m_salle) ){
    m_map[joueur->x_map][joueur->y_map]->m_salle[joueur->x_salle][joueur->y_salle] = 0;
    joueur->x_salle += joueur->x_mouv;
    joueur->y_salle += joueur->y_mouv;
  }
  else {
    if( m_map[joueur->x_map][joueur->y_map]->m_salle[joueur->x_salle + joueur->x_mouv][joueur->y_salle + joueur->y_mouv] == 3){
      m_map[joueur->x_map][joueur->y_map]->m_salle[joueur->x_salle][joueur->y_salle] = 0;
      joueur->x_map += joueur->x_mouv;
      joueur->y_map += joueur->y_mouv;
      maj_map(m_map, joueur->x_map, joueur->y_map);
      if(joueur->x_mouv == 1){
        joueur->x_salle = 1;
      }
      if(joueur->x_mouv == -1){
        joueur->x_salle = M - 2;
      }
      if(joueur->y_mouv == 1){
        joueur->y_salle = 1;
      }
      if(joueur->y_mouv == -1){
        joueur->y_salle = N - 2;
      }
    }
  }
  m_map[joueur->x_map][joueur->y_map]->m_salle[joueur->x_salle][joueur->y_salle] = 1;
}


extern
void controle_joueur(t_joueur * joueur, t_salle * m_map[L][L]){
  char c;
  int boucle = 1;

  c = getch();

  switch (c){
    case 'z': joueur->x_direction = joueur->x_mouv = -1; joueur->y_direction = joueur->y_mouv = 0; flushinp();
    break;
    case 's': joueur->x_direction = joueur->x_mouv = 1; joueur->y_direction = joueur->y_mouv = 0; flushinp();
    break;
    case 'q': joueur->y_direction = joueur->y_mouv = -1; joueur->x_direction = joueur->x_mouv = 0; flushinp();
    break;
    case 'd': joueur->y_direction = joueur->y_mouv = 1; joueur->x_direction = joueur->x_mouv = 0; flushinp();
    break;
    case ' ': if( (m_map[joueur->x_map][joueur->y_map]->m_salle[ joueur->x_salle + joueur->x_direction][ joueur->y_salle + joueur->y_direction] != 2) && (m_map[joueur->x_map][joueur->y_map]->m_salle[ joueur->x_salle + joueur->x_direction][ joueur->y_salle + joueur->y_direction] !=3 ) ){ // Vérifie que le projectile n'est pas créé dans un mur ou une porte.
                en_tete(m_map[joueur->x_map][joueur->y_map]->l_projectile);
                ajout_droit(m_map[joueur->x_map][joueur->y_map]->l_projectile,creer_projectile(m_map[joueur->x_map][joueur->y_map], joueur->x_salle, joueur->y_salle, joueur->x_direction,joueur->y_direction , 1)); flushinp();
              }
    break;
    default: joueur->x_mouv = 0; joueur->y_mouv = 0;flushinp();
    break;
  }

  deplacer_joueur(m_map, joueur);
}
