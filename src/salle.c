#include "tout.h"

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


static
void init_pattern(int m_pattern[4][NB_PATTERN][M][N]){
  int i, j, k, l ;
  for( i=0 ; i<4 ; i++){
    for( j=0 ; j<NB_PATTERN ; j++ ){
      for( k=0 ; k<M ; k++ ){
        for( l=0 ; l<N ; l++ ){
          m_pattern[i][j][k][l] = 0;
        }
      }
    }
  }
}


extern
void remplir_pattern(int m_pattern[4][NB_PATTERN][M][N]){
  FILE* fichier;
  int coin = 0;
  int choix = 0;
  int x;
  int y;

  fichier = fopen("res/pattern.txt","r");

  init_pattern(m_pattern);

  do{
    fscanf(fichier,"%i %i", &x, &y);
    if( x<0 ){
      if( y == -1 ){
        choix++;
      }
      else{
        coin++;
        choix = 0;
      }
    }else{
      m_pattern[coin][choix][x][y] = 1;
    }


  }while( (coin < 4) && (choix < NB_PATTERN) );

  fclose(fichier);
}


extern
void init_salle(t_salle * m_map[L][L], int x, int y, int m_pattern[4][NB_PATTERN][M][N]){
  int i, j, k;
  int x_mob, y_mob, nb_mob ;
  int choix_HG, choix_HD, choix_BG, choix_BD ;

  for( i=0 ; i<M ; i++){
      for( j=0 ; j<N ; j++){

          m_map[x][y]->m_salle[i][j] = 0;    /* Corps de la salle */
          /* BORDURES */
          m_map[x][y]->m_salle[0][j] = MUR;    /* haut */
          m_map[x][y]->m_salle[i][0] = MUR;    /* gauche */
          m_map[x][y]->m_salle[M-1][j] = MUR;  /* bas */
          m_map[x][y]->m_salle[i][N-1] = MUR;  /* droit */
      }
    }
/*Création des portes */
    if(m_map[x][y+1] != NULL){ /* Si salle à droite */
        for( i = 0 ; i < 3 ; i++){

           m_map[x][y]->m_salle[(M/2) + i][N-1] = PORTE;
           m_map[x][y]->m_salle[(M/2) - i][N-1] = PORTE;
       }
    }
    if(m_map[x][y-1] != NULL){ /* Si salle à gauche */
        for( i = 0 ; i < 3 ; i++){
           m_map[x][y]->m_salle[(M/2) + i][0] = PORTE;
           m_map[x][y]->m_salle[(M/2) - i][0] = PORTE;
       }
    }
    if(m_map[x+1][y] != NULL){ /* Si salle en bas */
        for( i = 0 ; i < 3 ; i++){
           m_map[x][y]->m_salle[M-1][(N/2) + i] = PORTE;
           m_map[x][y]->m_salle[M-1][(N/2) - i] = PORTE;
       }
    }
    if(m_map[x-1][y] != NULL){  /* Si salle en haut */
        for( i = 0 ; i < 3 ; i++){
           m_map[x][y]->m_salle[0][(N/2) + i] = PORTE;
           m_map[x][y]->m_salle[0][(N/2) - i] = PORTE;
       }
    }

  /*Fin création portes*/
  /*Création des obstacles*/
  remplir_pattern(m_pattern);


  choix_HG = rand() % NB_PATTERN;
  choix_HD = rand() % NB_PATTERN;
  choix_BG = rand() % NB_PATTERN;
  choix_BD = rand() % NB_PATTERN;
  for( i=0 ; i<M ; i++){
    for( j=0 ; j<N ; j++){
      if( m_pattern[0][choix_HG][i][j] || m_pattern[1][choix_HD][i][j] || m_pattern[2][choix_BG][i][j] || m_pattern[3][choix_BD][i][j] ){
        m_map[x][y]->m_salle[i][j] = MUR;
      }
    }
  }

  /*Fin création obstacles*/
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
      ajout_droit(m_map[x][y]->l_monstre,creer_monstre(x_mob ,y_mob, (rand() % 2) + 3 ));
      m_map[x][y]->m_salle[x_mob][y_mob] = MONSTRE;
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
      if(mat[i][j] == JOUEUR){
        attron(A_BOLD);
        attron(COLOR_PAIR(VERT));
        printw("0");
        attroff(A_BOLD);
        attroff(COLOR_PAIR(VERT));
      }
      else if(mat[i][j] == MUR) {
        attron(A_BOLD);
        attron(COLOR_PAIR(ROUGE));
        printw("/");
        attroff(A_BOLD);
        attroff(COLOR_PAIR(ROUGE));
      }
      else if(mat[i][j] == PORTE) {
        attron(A_BOLD);
        attron(COLOR_PAIR(VERT));
        printw("-");
        attroff(A_BOLD);
        attroff(COLOR_PAIR(VERT));
      }
      else if(mat[i][j] == MONSTRE){
        attron(A_BOLD);
        attron(COLOR_PAIR(JAUNE));
        printw("M");
        attroff(A_BOLD);
        attroff(COLOR_PAIR(JAUNE));
      }
      else if(mat[i][j] == PROJECTILE){
        attron(A_BOLD);
        attron(COLOR_PAIR(BLEU));
        printw("*");
        attroff(A_BOLD);
        attroff(COLOR_PAIR(BLEU));
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
          if( mat[i][j] == MUR || mat[i][j] == PORTE || mat[i][j] == PROJECTILE)
            mat_distance[i][j] = -1; /* Obstacles */
          else if( mat[i][j] == JOUEUR )
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
