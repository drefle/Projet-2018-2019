#include "tout.h"

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
    joueur->x_direction = 1;
    joueur->y_direction = 0;
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
    if( m_map[joueur->x_map][joueur->y_map]->m_salle[joueur->x_salle + joueur->x_mouv][joueur->y_salle + joueur->y_mouv] == PORTE){
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
  m_map[joueur->x_map][joueur->y_map]->m_salle[joueur->x_salle][joueur->y_salle] = JOUEUR;
}


extern
void controle_joueur(t_joueur * joueur, t_salle * m_map[L][L],SDL_Keycode key){
    switch (key){
      case SDLK_UP : joueur->x_direction = joueur->x_mouv = -1; joueur->y_direction = joueur->y_mouv = 0;
      fprintf(stderr,"ok up");
      break;
      case SDLK_DOWN : joueur->x_direction = joueur->x_mouv = 1; joueur->y_direction = joueur->y_mouv = 0;
      fprintf(stderr,"ok down");
      break;
      case SDLK_LEFT : joueur->y_direction = joueur->y_mouv = -1; joueur->x_direction = joueur->x_mouv = 0;
      fprintf(stderr,"ok left");
      break;
      case SDLK_RIGHT : joueur->y_direction = joueur->y_mouv = 1; joueur->x_direction = joueur->x_mouv = 0;
      fprintf(stderr,"ok right");
      break;
      case SDLK_SPACE : tirer_projectile( m_map[joueur->x_map][joueur->y_map], joueur->x_salle, joueur->y_salle, joueur->x_direction, joueur->y_direction, 1 ); flushinp();
      fprintf(stderr,"ok space");
      break;
      default: joueur->x_mouv = 0; joueur->y_mouv = 0;
      break;
    }

fprintf(stderr,"ok controle joueur");
  deplacer_joueur( m_map, joueur );
}
