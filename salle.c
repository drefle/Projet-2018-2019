#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "tout.h"

#define N 48
#define M 26

extern
t_salle * creer_salle(){
    t_salle * salle = malloc(sizeof(t_salle));
    return salle;
}

extern
void init_salle(t_salle * m_map[L][L], int x, int y){
  int i, j, k;
  int x_mob,y_mob,nb_mob;

  m_map[x][y]->l_monstre = malloc(sizeof(t_liste));
  init_liste(m_map[x][y]->l_monstre, copier_monstre_cb, supprimer_monstre_cb);
  m_map[x][y]->l_projectile = malloc(sizeof(t_liste));
  init_liste(m_map[x][y]->l_projectile, copier_projectile_cb, supprimer_projectile_cb);
  nb_mob=(rand()%3)+2;
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
  for(k=0 ; k < nb_mob ; k++){
    fprintf(stderr, "%s\n", "ok1" );
    do{
      x_mob = ( rand() % (M-5) ) + 2;
      y_mob = ( rand() % (N-5) ) + 2;
    }while(m_map[x][y]->m_salle[x_mob][y_mob] != 0);
    en_tete(m_map[x][y]->l_monstre);
    ajout_droit(m_map[x][y]->l_monstre,creer_monstre(x_mob ,y_mob));
    m_map[x][y]->m_salle[x_mob][y_mob]=4;
    fprintf(stderr, "%s\n", "ok2" );
  }
  fprintf(stderr, "%s\n", "ok3" );
}

/* Affichage de la matrice */
extern
void afficher_salle(int mat[M][N]){
  int i, j;


  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);

  for( i=0 ; i<M ; i++){
    for( j=0 ; j<N ; j++){
      if(mat[i][j] == 1){
        attron(A_BOLD);
        attron(COLOR_PAIR(1));
        printw("0");
        attroff(A_BOLD);
        attroff(COLOR_PAIR(1));
        printw("|");
      }
      else if(mat[i][j] == 2) {
        attron(A_BOLD);
        attron(COLOR_PAIR(1));
        printw("/");
        attroff(A_BOLD);
        attroff(COLOR_PAIR(1));
        printw("|");
      }
      else if(mat[i][j] == 3) {
        attron(A_BOLD);
        attron(COLOR_PAIR(2));
        printw("-");
        attroff(A_BOLD);
        attroff(COLOR_PAIR(2));
        printw("|");
      }
      else if(mat[i][j] == 4){
        attron(A_BOLD);
        attron(COLOR_PAIR(3));
        printw("M");
        attroff(A_BOLD);
        attroff(COLOR_PAIR(3));
        printw("|");
      }
      else if(mat[i][j] == 8){
        attron(A_BOLD);
        attron(COLOR_PAIR(3));
        printw("*");
        attroff(A_BOLD);
        attroff(COLOR_PAIR(3));
        printw("|");
      }
      else
        printw(" |");
    }
    printw("\n");
  }
}
