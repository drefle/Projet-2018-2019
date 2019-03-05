#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>

#include "map.h"

#define N 48
#define M 26
#define L 12



extern
void init_map(t_salle * m_map[L][L]){
	int i,j;
	for(i=0 ; i<L ;i++){
		for(j=0 ; j<L ;j++){
			m_map[i][j]=NULL;
		}
	}
  m_map[L/2][L/2] = creer_salle();
}

extern
int coord_valides(t_salle * m_map[L][L], int x, int y){

	if(m_map[x][y] != NULL){
		return 0;
	}

	if( ((x <= 0) || (x >= L-1)) || ((y <= 0) || (y >= L-1)) ){
		return 0;
	}

	if( (m_map[x][y-1]!= NULL) && (m_map[x-1][y]!= NULL) ){
		if(m_map[x-1][y-1]!= NULL){
			return 0;
		}
	}
	if( (m_map[x-1][y]!= NULL) && (m_map[x][y+1]!= NULL) ){
		if(m_map[x-1][y+1]!= NULL){
			return 0;
			}
		}
	if( (m_map[x+1][y]!= NULL) && (m_map[x][y-1]!= NULL) ){
		if(m_map[x+1][y-1]!= NULL){
			return 0;
			}
		}
	if( (m_map[x][y+1]!= NULL) && (m_map[x+1][y]!= NULL) ){
		if(m_map[x+1][y+1]!= NULL){
			return 0;
			}
		}
		return 1;
}

extern
void maj_coord_possible(t_salle * m_map[L][L], t_liste * l_coord , int x , int y){

	if( !coord_valides(m_map,x,y) ){
		t_coord * temp = creer_coord(-1,-1);

		en_tete(l_coord);
		valeur_elt(l_coord, temp);
		while( (( temp->absi != x ) || ( temp->ord != y )) && ( !hors_liste(l_coord) ) ){
			suivant(l_coord);
			valeur_elt(l_coord, temp);
		}
		if( !hors_liste(l_coord) ){
			oter_elt(l_coord);
		}
		free(temp);
	}
	else{
		en_tete(l_coord);
		ajout_droit(l_coord, creer_coord(x,y) );
	}

}

extern
void genmap(t_salle * m_map[L][L], int n){
	int i, j;
	t_liste * l_coord = malloc(sizeof(t_liste));
	t_coord * coord = creer_coord(-1,-1);
	int x = L/2;
	int y = L/2;
	int choix_coord;

	init_liste(l_coord,copier_coord_cb,supprimer_coord_cb);

	for( i=0 ; i<n ; i++ ){

		maj_coord_possible(m_map,l_coord,x,y-1);
		maj_coord_possible(m_map,l_coord,x-1,y);
		maj_coord_possible(m_map,l_coord,x+1,y);
		maj_coord_possible(m_map,l_coord,x,y+1);

		choix_coord =	rand()%(l_coord->nb_elem);

		en_tete(l_coord);
		for( j=0 ; j<choix_coord ; j++ ){
			suivant(l_coord);
		}
		valeur_elt(l_coord,coord);
		oter_elt(l_coord);

		x = coord->absi;
		y = coord->ord;
		m_map[x][y] = creer_salle();
	}
	free(l_coord);
	free(coord);

	for( i=0 ; i<L ; i++){
		for( j=0 ; j<L ; j++){
			if( m_map[i][j] != NULL ){
				init_salle(m_map, i, j);
			}
		}
	}
}
