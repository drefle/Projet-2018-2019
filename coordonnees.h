#include <stdlib.h>

typedef struct s_coord{
  int absi;
  int ord;
}t_coord;


extern
t_coord * creer_coord(int absi, int ord);

extern
void copier_coord_cb(void * a, void * b);

extern
void supprimer_coord_cb(void * a);
