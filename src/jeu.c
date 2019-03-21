#include "tout.h"

extern int nb_mob_tot;

int main(){
	int i = 0, j;
	t_salle * m_map[L][L];
	int m_pattern[4][NB_PATTERN][M][N];
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

  init_map( m_map );/*Création de la map*/
	remplir_pattern( m_pattern );/*Lecture du fichier qui contient les différents pattern*/

	genmap(m_map, NB_SALLE, m_pattern);/*Remplissage de la map*/

	for( j=3 ; j>0 ; j-- ){/*Compte à rebours*/
		clear();
		printw("---------- %i ----------\n", j );
		refresh();
		sleep(1);
	}

	while( ( joueur->pv > 0 ) && ( nb_mob_tot > 0 ) ){

		/*Gestion du joueur*/
		controle_joueur(joueur, m_map);

		/*Gestions des entités de la salle*/
		deplacer_projectile( m_map[joueur->x_map][joueur->y_map], joueur, i );
		deplacer_monstre( m_map[joueur->x_map][joueur->y_map], joueur , i );

		/*Affichage de la salle et de la map*/
		afficher_salle( m_map[joueur->x_map][joueur->y_map]->m_salle );
		afficher_map( m_map, joueur );

		/*Affichage des vies*/
		for( j=0  ; j<joueur->pv ; j++ ){
			printw("<3 ");
		}
		printw("\n");

		/*Affichage du nbre de monstres restant*/
		printw("NB MOB : %i\n", nb_mob_tot);

		/*Affichage du nomnre de projectiles dans la salle*/
		printw("NB PROJ = %i\n", m_map[joueur->x_map][joueur->y_map]->l_projectile->nb_elem);


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
