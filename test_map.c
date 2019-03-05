#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>
#include "joueur.h"

#define N 48
#define M 26
#define L 12
#define TICK 40

void main(){
	t_salle * m_map[L][L];
	t_joueur * joueur = creer_joueur(L/2, L/2, M/2, N/2);
	srand(time(NULL));
	int boucle = 1;
	float refresh = 1 / TICK * 1000000;

	initscr();
	keypad(stdscr, TRUE);
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	start_color();

  init_map(m_map);/*Création de la map*/
	genmap(m_map,20);/*Remplissage de la map*/

	while(boucle){
		controle_joueur(joueur, m_map);
		clear();
		afficher_salle(m_map[joueur->x_map][joueur->y_map]->m_salle);
		afficher_map(m_map,joueur);

		usleep(50000);


	}

	sleep(3);

	endwin();
}
