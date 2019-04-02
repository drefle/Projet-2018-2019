#include "tout.h"

extern int nb_mob_tot;

int main(){
	int running =1;
	SDL_Window* pWindow = NULL;
	SDL_Renderer *salle_render=NULL;
	SDL_Keycode touche;
	t_res *ressource = malloc(sizeof(t_res));
	int i = 0, j;
	t_salle * m_map[L][L];
	int m_pattern[4][NB_PATTERN][M][N];
	t_joueur * joueur = creer_joueur(L/2, L/2, M/2, N/2, 6);
	srand(time(NULL));
	pWindow = SDL_CreateWindow("The Biding of Isaac REMASTERED",SDL_WINDOWPOS_UNDEFINED,
																SDL_WINDOWPOS_UNDEFINED,
												 				1080,
												  				650,
												  				SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);

	salle_render = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
	if(salle_render == NULL){
			fprintf(stderr, "Erreur à la création du renderer\n");
			exit(EXIT_FAILURE);
	}
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
if(pWindow){
	/*fprintf(stderr,"ok fenetre\n");*/

			while(( ( joueur->pv > 0 ) && ( nb_mob_tot > 0 )) && running ){
				SDL_Event e;
				/*fprintf(stderr,"ok condition jeu\n");*/
				while(SDL_PollEvent(&e)) {
				/*	fprintf(stderr,"ok pollevent\n");*/
				touche = e.key.keysym.sym;
				if(touche == SDLK_ESCAPE){
					running =0;
				}
				controle_joueur(joueur, m_map,touche);
				deplacer_projectile( m_map[joueur->x_map][joueur->y_map], joueur, i );
				deplacer_monstre( m_map[joueur->x_map][joueur->y_map], joueur , i );

				/*Affichage de la salle et de la map*/
				afficher_salle( m_map[joueur->x_map][joueur->y_map]->m_salle,salle_render,ressource );

				afficher_map( m_map, joueur );
				fprintf(stderr,"ok afficher map");
				/*Affichage des vies*/
				for( j=0  ; j<joueur->pv ; j++ ){
					printw("<3 ");
				}
				printw("\n");

				/*Affichage du nbre de monstres restant*/
				printw("NB MOB : %i\n", nb_mob_tot);

				/*Affichage du nomnre de projectiles dans la salle*/
				printw("NB PROJ = %i\n", m_map[joueur->x_map][joueur->y_map]->l_projectile->nb_elem);

				fprintf(stderr,"ok fin windowevent");
				i = (i + 1) % 50000;
				refresh();
				usleep( (1.0/TICK) * 1000000 );
				clear();
			}
		}
	}
	SDL_DestroyWindow(pWindow);
	if( joueur->pv > 0 ){
		printw("OMG WHAT A PROPLAYER\n");
		refresh();
	}
	else{
		printw("LOOOOOOOSER\n");
		refresh();
	}
/* Doit être avant TTF_Quit() */
	TTF_Quit();
		SDL_Quit();
return 0;
}
