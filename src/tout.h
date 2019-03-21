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


//######################COORD######################

struct s_coord{
  int absi;
  int ord;
};


extern
t_coord * creer_coord(int absi, int ord);

extern
void copier_coord_cb(void * a, void * b);

extern
void supprimer_coord_cb(void * a);

//###################### LISTE PTR ######################

struct s_element{
  void * p_val;
  struct s_element* pred;
  struct s_element* succ;
};

struct s_liste{
  void (*copier_elem)(void *, void *);
  void (*supprimer_elem)(void *);
  t_element* drapeau;
  t_element* ec;
  int nb_elem;
};

extern
void init_liste(t_liste * liste, void (*copier_elem)(void *, void *), void (*supprimer_elem)(void *));

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
void valeur_elt(t_liste * liste, void * v);
extern
void modif_elt(t_liste * liste, void * v);

extern
void oter_elt(t_liste * liste);

extern
void ajout_droit(t_liste * liste, void * pt);

extern
void ajout_gauche(t_liste * liste, void * pt);

//##################SALLE##########################

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

/*
static
void init_pattern(int m_pattern[4][NB_PATTERN][M][N]);

static
void remplir_pattern(int m_pattern[4][NB_PATTERN][M][N]);
*/
extern
void init_salle(t_salle * m_map[L][L], int x, int y);

extern
void afficher_salle(int mat[M][N]);

extern
void creer_mat_distance(int mat[M][N], int mat_distance[N][N]);

extern
void afficher_mat_distance(int mat_distance[M][N]); /*wesh*/



//################### MAP #########################


extern
t_coord * creer_coord(int absi, int ord);

extern
void copier_coord_cb(void * a, void * b);

extern
void supprimer_coord_cb(void * a);

extern
void init_map(t_salle * m_map[L][L]);

extern
void afficher_map(t_salle * m_map[L][L], t_joueur * joueur);

extern
int coord_valides(t_salle * m_map[L][L], int x, int y);

extern
void maj_coord_possible(t_salle * m_map[L][L], t_liste * l_coord , int x , int y);

extern
void genmap(t_salle * m_map[L][L], int n);

extern
void maj_map(t_salle * m_map[L][L], int x, int y);



//########################## JOUEUR ##############################


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



//################### MONSTRE #########################

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

extern
void copier_monstre_cb(void * a, void * b);

extern
void supprimer_monstre_cb(void * a);

extern
void deplacer_monstre(t_salle * salle, t_joueur * j, int i);


/*
#####################################"PROJECTILE"################################
*/

struct s_projectile{
  int x;
  int y;
  int mouv_x;
  int mouv_y;
  int vitesse;
};


extern
void supprimer_projectile_cb(void * p);
/*
static
void supprimer_projectile(t_projectile * p);

static
void copier_projectile(t_projectile * a, t_projectile * b);

static
void supprimer_monstre_coord(t_salle * salle, int x, int y);
*/
extern
void copier_projectile_cb(void * a, void * b);


extern
t_projectile * creer_projectile(int x,int y,int mouv_x,int mouv_y,int vit);

extern
void tirer_projectile(t_salle * salle, int x, int y, int mouv_x, int mouv_y, int vit);

extern
void deplacer_projectile(t_salle * salle, t_joueur * j,int i);
