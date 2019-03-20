#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "tout.h"

#define N 46
#define M 26


int nb_mob_tot = 0;

extern
t_salle * creer_salle(){
    t_salle * salle = malloc(sizeof(t_salle));

    salle->l_monstre = malloc(sizeof(t_liste));
    init_liste(salle->l_monstre, copier_monstre_cb, supprimer_monstre_cb);

    salle->l_projectile = malloc(sizeof(t_liste));
    init_liste(salle->l_projectile, copier_projectile_cb, supprimer_projectile_cb);

    salle->etat = CACHE;
    return salle;
}

extern
void init_salle(t_salle * m_map[L][L], int x, int y){
  int i, j, k;
  int x_mob,y_mob,nb_mob;


  for( i=0 ; i<M ; i++){
      for( j=0 ; j<N ; j++){
          m_map[x][y]->m_salle[i][j] = 0;    /* Corps de la salle */
          /* BORDURES */
          m_map[x][y]->m_salle[0][j] = 2;    /* haut */
          m_map[x][y]->m_salle[i][0] = 2;    /* gauche */
          m_map[x][y]->m_salle[M-1][j] = 2;  /* bas */
          m_map[x][y]->m_salle[i][N-1] = 2;  /* droit */
      }
    }
/*Création des portes */
    if(m_map[x][y+1] != NULL){ /* Si salle à droite */
        for( i = 0 ; i < 3 ; i++){

           m_map[x][y]->m_salle[(M/2) + i][N-1] = 3;
           m_map[x][y]->m_salle[(M/2) - i][N-1] = 3;
       }
    }
    if(m_map[x][y-1] != NULL){ /* Si salle à gauche */
        for( i = 0 ; i < 3 ; i++){
           m_map[x][y]->m_salle[(M/2) + i][0] = 3;
           m_map[x][y]->m_salle[(M/2) - i][0] = 3;
       }
    }
    if(m_map[x+1][y] != NULL){ /* Si salle en bas */
        for( i = 0 ; i < 3 ; i++){
           m_map[x][y]->m_salle[M-1][(N/2) + i] = 3;
           m_map[x][y]->m_salle[M-1][(N/2) - i] = 3;
       }
    }
    if(m_map[x-1][y] != NULL){  /* Si salle en haut */
        for( i = 0 ; i < 3 ; i++){
           m_map[x][y]->m_salle[0][(N/2) + i] = 3;
           m_map[x][y]->m_salle[0][(N/2) - i] = 3;
       }
    }
  /*Fin création portes*/

  /* Création des monstre */
  if( (x!=L/2) || (y!=L/2) ){
    nb_mob=(rand()%3)+2;
    nb_mob_tot += nb_mob;
    for(k=0 ; k < nb_mob ; k++){
      do{
        x_mob = ( rand() % (M-5) ) + 2;
        y_mob = ( rand() % (N-5) ) + 2;
      }while(m_map[x][y]->m_salle[x_mob][y_mob] != 0);
      en_tete(m_map[x][y]->l_monstre);
      ajout_droit(m_map[x][y]->l_monstre,creer_monstre(x_mob ,y_mob, (rand() % 2) + 6 ));
      m_map[x][y]->m_salle[x_mob][y_mob]=4;
    }
  }else{
    m_map[L/2][L/2]->etat = VIDE;
    maj_map(m_map, L/2, L/2);
  }
}

/* Affichage de la matrice */
extern
void afficher_salle(int mat[M][N]){
  int i, j;

  for( i=0 ; i<M ; i++){
    for( j=0 ; j<N ; j++){
      if(mat[i][j] == 1){
        attron(A_BOLD);
        attron(COLOR_PAIR(1));
        printw("0");
        attroff(A_BOLD);
        attroff(COLOR_PAIR(1));
      }
      else if(mat[i][j] == 2) {
        attron(A_BOLD);
        attron(COLOR_PAIR(1));
        printw("/");
        attroff(A_BOLD);
        attroff(COLOR_PAIR(1));
      }
      else if(mat[i][j] == 3) {
        attron(A_BOLD);
        attron(COLOR_PAIR(2));
        printw("-");
        attroff(A_BOLD);
        attroff(COLOR_PAIR(2));
      }
      else if(mat[i][j] == 4){
        attron(A_BOLD);
        attron(COLOR_PAIR(4));
        printw("M");
        attroff(A_BOLD);
        attroff(COLOR_PAIR(4));
      }
      else if(mat[i][j] == 8){
        attron(A_BOLD);
        attron(COLOR_PAIR(3));
        printw("*");
        attroff(A_BOLD);
        attroff(COLOR_PAIR(3));
      }
      else
        printw(" ");
      printw("|");
    }
    printw("\n");
  }
}

void creer_mat_distance(int mat[M][N], int mat_distance[M][N]){
  int i,j,n;
  int est_pleine;

  for( i=0 ; i<M ; i++){
        for( j=0 ; j<N ; j++){
            /* BORDURES */
          if( mat[i][j] == 2 || mat[i][j] == 3 || mat[i][j] == 8)
            mat_distance[i][j] = -1; /* Obstacles */
          else if( mat[i][j] == 1 )
            mat_distance[i][j] = 1; /* Position joueur */
          else
            mat_distance[i][j] = 0; /* Corps de la salle */
        }
    }

    n = 1;
    est_pleine = 0;
    while( !est_pleine ){
      est_pleine = 1;
      for( i=0 ; i<M ; i++){
        for( j=0 ; j<N ; j++){
          if( mat_distance[i][j] == n ){
            if( mat_distance[i+1][j] == 0 ){
              mat_distance[i+1][j] = n+1;
              est_pleine = 0;
            }
            if( mat_distance[i][j+1] == 0 ){
              mat_distance[i][j+1] = n+1;
              est_pleine = 0;
            }
            if( mat_distance[i-1][j] == 0 ){
              mat_distance[i-1][j] = n+1;
              est_pleine = 0;
            }
            if( mat_distance[i][j-1] == 0 ){
              mat_distance[i][j-1] = n+1;
              est_pleine = 0;
            }
          }
        }
      }
      n++;
    }
}

extern
void afficher_mat_distance(int mat_distance[M][N]){
  int i, j;

  for( i=0 ; i<M ; i++){
    for( j=0 ; j<N ; j++){
      printf("%2d|", mat_distance[i][j]);
    }
    printf("\n");
  }
}
