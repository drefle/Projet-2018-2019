#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <ncurses.h>


#define N 46
#define M 26
#define L 12

#define     TICK 15
#define NB_SALLE 3

#define NB_PATTERN 3

#define ROUGE 1
#define  VERT 2
#define  BLEU 3
#define JAUNE 4
#define BLANC 5

#define     JOUEUR 1
#define        MUR 2
#define      PORTE 3
#define    MONSTRE 4
#define PROJECTILE 8


typedef struct s_joueur t_joueur;
typedef struct s_monstre t_monstre;
typedef struct s_coord t_coord;
typedef struct s_projectile t_projectile;
typedef struct s_salle t_salle;
typedef struct s_element t_element;
typedef struct s_liste t_liste;


/*######################COORD######################*/

struct s_coord{
  int absi;
  int ord;
};

extern
t_coord * creer_coord(int absi, int ord);
/**
* \fn t_coord * creer_coord(int absi, int ord)
* \brief
* \param
* \param
*/

extern
void supprimer_coord_cb(void * a);
/**
* \fn void supprimer_coord_cb(void * a)
* \brief
* \param
*/

/*###################### LISTE PTR ######################*/

/* STRUCTURE */
struct s_element{
  void * p_val;
  struct s_element* pred;
  struct s_element* succ;
};

/* STRUCTURE */
struct s_liste{
  void (*supprimer_elem)(void *);
  t_element* drapeau;
  t_element* ec;
  int nb_elem;
};

extern
void init_liste(t_liste * liste, void (*supprimer_elem)(void *));

extern
int liste_vide(t_liste * liste);

extern
int hors_liste(t_liste * liste);

extern
void en_tete(t_liste * liste);

extern
void en_queue(t_liste * liste);

extern
void precedent(t_liste * liste);

extern
void suivant(t_liste * liste);

extern
void valeur_elt_coord(t_liste * liste, t_coord*  coord);

extern
void modif_elt(t_liste * liste, void * v);

extern
void oter_elt(t_liste * liste);

extern
void ajout_droit(t_liste * liste, void * pt);

extern
void ajout_gauche(t_liste * liste, void * pt);

/*##################SALLE##########################*/

/**
* \file salle.h
* \author Adrien P. - Paul PDC. - David C. - Paul C.
* \date 04/03/2019
* \brief Permet le mouvement du joueur à travers les salles
*/

/* STRUCTURE */

typedef enum {CACHE, VU, VIDE} t_etat;

struct s_salle{
    int m_salle[M][N];
    t_liste * l_monstre;
    t_liste * l_projectile;
    t_etat etat;
};


/* FONCTIONS */

extern
t_salle * creer_salle();
/**
* \fn t_salle * creer_salle()
* \brief créer la salle (allocation mémoire pour la structure salle et les listes montre et projectile + définition de l'etat de la salle)
*/

extern
void init_salle(t_salle * m_map[L][L], int x, int y, int m_pattern[4][NB_PATTERN][M][N]);
/**
* \fn void init_salle(t_salle * m_map[L][L], int x, int y, int m_pattern[4][NB_PATTERN][M][N])
* \brief Création des mur, des portes ,des obstacles et des montres
* \param m_map[L][L] matrice contenant des pointeurs sur salle
* \param x, y coordonnées sur la map
* \param m_pattern[4][NB_PATTERN][M][N]) matrice contenant les patterns d'obstacles pour le salles
*/

extern
void afficher_salle(int mat[M][N]);
/**
* \fn void afficher_salle(int mat[M][N])
* \brief affiche la salle
* \param mat[M][N] la matrice de la salle
*/

extern
void creer_mat_distance(int mat[M][N], int mat_distance[N][N]);
/**
* \fn void creer_mat_distance(int mat[M][N], int mat_distance[N][N])
* \brief remplie une matrice avec la distance au joueur en chaque case
* \param mat[M][N] matrice de la salle
* \param mat_distance[N][N] matrice à remplir
*/

extern
void afficher_mat_distance(int mat_distance[M][N]);
/**
* \fn void afficher_mat_distance(int mat_distance[M][N])
* \brief affiche la mat_distance[M][N]
* \param mat_distance[M][N] matrice à afficher
*/

extern
void remplir_pattern(int m_pattern[4][NB_PATTERN][M][N]);
/**
* \fn void remplir_pattern(int m_pattern[4][NB_PATTERN][M][N])
* \brief remplie la matrice m_pattern[4][NB_PATTERN][M][N] grâce à un fichier.txt
* \param mat_distance[M][N] matrice à remplir
*/




/*################### MAP #########################*/



extern
void init_map(t_salle * m_map[L][L]);
/**
* \fn void init_map(t_salle * m_map[L][L])
* \brief initialise la map a NULL sauf la salle centrale
* \param m_map[L][L] la map
*/

extern
void afficher_map(t_salle * m_map[L][L], t_joueur * joueur);
/**
* \fn void afficher_map(t_salle * m_map[L][L], t_joueur * joueur)
* \brief affiche la map
* \param m_map[L][L] la map
* \param joueur le joueur
*/

extern
int coord_valides(t_salle * m_map[L][L], int x, int y);
/**
* \fn int coord_valides(t_salle * m_map[L][L], int x, int y)
* \brief Vérifie si les coordonnées sont valides pour la création de la map
* \param m_map[L][L] la map
* \param x, y les coordonnées sur la map
*/

extern
void maj_coord_possible(t_salle * m_map[L][L], t_liste * l_coord , int x , int y);
/**
* \fn void maj_coord_possible(t_salle * m_map[L][L], t_liste * l_coord , int x , int y)
* \brief
* \param m_map[L][L] la map
* \param
*/

extern
void genmap(t_salle * m_map[L][L], int n, int m_pattern[4][NB_PATTERN][M][N]);
/**
* \fn void genmap(t_salle * m_map[L][L], int n, int m_pattern[4][NB_PATTERN][M][N])
* \brief
* \param
* \param
*/

extern
void maj_map(t_salle * m_map[L][L], int x, int y);
/**
* \fn void maj_map(t_salle * m_map[L][L], int x, int y)
* \brief met à jour l'etat des salle
* \param m_map[L][L] la map
* \param x, y les coordonnées sur la map
*/



/*########################## JOUEUR ##############################*/


/**
* \file joueur.h
* \author Adrien P. - Paul PDC. - David C. - Paul C.
* \date 04/03/2019
* \brief Primitives des fonctions utilisés dans joueur.c pour permettre le déplacement d'un joueur à travers les salles
*/

struct s_joueur{
    int x_map;
    int y_map;
    int x_salle;
    int y_salle;
    int x_mouv;
    int y_mouv;
    int x_direction;
    int y_direction;
    int pv;
};

/* FONCTIONS */

extern
t_joueur * creer_joueur(int xm, int ym, int xs, int ys, int  pv);
/**
* \fn t_joueur * creer_joueur(int xm, int ym, int xs, int ys)
* \brief Créer un joueur le positionne à la base de la map et centre de la 1ere salle
* \param xm,ym,xs,ys Coordonées dans la salle et dans la map
*/

extern
int est_franchissable(int x, int y, int salle[M][N]);
/**
* \fn int est_franchissable(int x, int y, int mat[M][N])
* \brief Verifie si la coordonée n'est pas un obstacle, bordure, porte etc.
* \param x,y,mat[M][N] Coordonées dans la matrice de la salle
*/

extern
void deplacer_joueur(t_salle * m_map[L][L], t_joueur * joueur);
/**
* \fn void deplacer_joueur(int mat[M][N], t_joueur * joueur, int joueur->x_mouv, int joueur->y_mouv)
* \brief Changement de position du joueur si la coordonée suivant est franchissable
* \param t_joueur_*_joueur Pointeur sur la structure joueur
* \param joueur−>x_mouv,joueur->y_mouv Operation sur la position
*/

extern
void controle_joueur(t_joueur * joueur, t_salle * m_map[L][L]);
/**
* \fn void controle_joueur(t_joueur * joueur, t_salle * m_map[L][L])
* \brief Récuperation des touches utilisé pour déplacement du joueur,
* \param t_joueur_*_joueur Pointeur sur la structure joueur
* \param t_salle_*_m_map[L][L] Matrice (map) de pointeurs sur la salle actuelle
*/



/*################### MONSTRE #########################*/

typedef enum {H, V} t_dir;
struct s_monstre{
  int x_salle;
  int y_salle;
  int x_mouv;
  int y_mouv;
  int vitesse;
  t_dir last_dir;
};


extern
t_monstre * creer_monstre(int x_salle, int y_salle, int vit);
/**
* \fn t_monstre * creer_monstre(int x_salle, int y_salle, int vit)
* \brief Créer un monstre avec des coordonnées et une vitesse
* \param x_salle, y_salle coordonnées du monstre
* \param vit vitesse du monstre
*/

extern
void supprimer_monstre_cb(void * a);

extern
void deplacer_monstre(t_salle * salle, t_joueur * j, int i);


/*
#####################################"PROJECTILE"################################
*/

/* STRUCTURE */
struct s_projectile{
  int x;
  int y;
  int mouv_x;
  int mouv_y;
  int vitesse;
};


extern
void supprimer_projectile_cb(void * p);
/**
* \fn void supprimer_projectile_cb(void * p)
* \brief appelle la fonction supprimer_projectile
* \param p un pointeur sur projectile
*/

extern
t_projectile * creer_projectile(int x,int y,int mouv_x,int mouv_y,int vit);
/**
* \fn t_projectile * creer_projectile(int x,int y,int mouv_x,int mouv_y,int vit)
* \brief créer un projectile avec des coordonnées, une direction et une vitesse (tous passé en paramètre)
* \param x et y les coordonnées du projectile dans la salle
* \param mouv_x et mouv_y la direction du projectile
* \param vit la vitesse du projectile
*/

extern
void tirer_projectile(t_salle * salle, int x, int y, int mouv_x, int mouv_y, int vit);
/**
* \fn void tirer_projectile(t_salle * salle, int x, int y, int mouv_x, int mouv_y, int vit)
* \brief Vérifie si le projectile peut être créer et gére le cas où le projectile et créer sur un montre (en le supprimant)
* \param salle la salle courante
* \param x et y les coordonnées du projectile dans la salle
* \param mouv_x et mouv_y la direction du projectile
* \param vit la vitesse du projectile
*/

extern
void deplacer_projectile(t_salle * salle, t_joueur * j,int i);
/**
* \fn deplacer_projectile(t_salle * salle, t_joueur * j,int i)
* \brief Déplace et gère la collision des projectile avec les mur, les monstres et le joueur
* \param salle la salle courante
* \param j le joueur
* \i variable permettant d'actualiser ou non la position du projectile
*/
