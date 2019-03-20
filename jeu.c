#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>
#include "tout.h"


#define M 26
#define N 46
#define L 12
#define TICK 20
#define NB_SALLE 3

extern int nb_mob_tot;

int main(){
	int i =0, j;
	int mat_distance[M][N];
	t_salle * m_map[L][L];
	t_joueur * joueur = creer_joueur(L/2, L/2, M/2, N/2, 6);
	srand(time(NULL));


	initscr();
	keypad(stdscr, TRUE);
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);

  init_map(m_map);/*Création de la map*/
	genmap(m_map, NB_SALLE);/*Remplissage de la map*/

/*	m_map[L/2][L/2]->m_salle[M/2][N/2] = 1;
	m_map[L/2][L/2]->m_salle[M-2][40] = 2;
	m_map[L/2][L/2]->m_salle[M-3][40] = 2;
	m_map[L/2][L/2]->m_salle[M-4][40] = 2;
	m_map[L/2][L/2]->m_salle[M-5][40] = 2;
	m_map[L/2][L/2]->m_salle[M-6][40] = 2;
	m_map[L/2][L/2]->m_salle[M-7][40] = 2;
	m_map[L/2][L/2]->m_salle[M-7][41] = 2;
	m_map[L/2][L/2]->m_salle[M-7][42] = 2;
	m_map[L/2][L/2]->m_salle[M-7][43] = 2;

	creer_mat_distance(m_map[L/2][L/2]->m_salle, mat_distance);
	afficher_mat_distance( mat_distance	);
*/

	for( j=3 ; j>0 ; j--){//Compte à rebours
		clear();
		printw("---------- %i ----------\n",j);
		refresh();
		sleep(1);
	}

	while( ( joueur->pv > 0 ) && ( nb_mob_tot > 0 ) ){

		controle_joueur(joueur, m_map);

		deplacer_projectile(m_map[joueur->x_map][joueur->y_map],joueur,i);
		deplacer_monstre(m_map[joueur->x_map][joueur->y_map],joueur,i);

		afficher_salle(m_map[joueur->x_map][joueur->y_map]->m_salle);
		afficher_map(m_map,joueur);

		for( j=0  ; j<joueur->pv ; j++){
			printw("<3 ");
		}
		printw("\n");

		printw("NB MOB : %i\n", nb_mob_tot);


		i = (i + 1) % 50000;

		refresh();
		usleep( (1.0/TICK) * 1000000 );
		clear();
	}

	if( joueur->pv > 0 ){
		printw("OMG WHAT A PROPLAYER\n");
		refresh();
	}
	else{
		printw("LOOOOOOOSER\n");
		refresh();
	}
	sleep(5);

	endwin();
}
