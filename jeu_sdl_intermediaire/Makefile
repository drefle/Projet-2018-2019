CC=gcc

SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include

LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I${SDLINC_DIR}

PROG=jeu

all:jeu

jeu : jeu.o joueur.o map.o salle.o coordonnees.o liste_ptr.o projectile.o monstre.o fonc_sdl.o
	${CC} jeu.o joueur.o map.o salle.o coordonnees.o liste_ptr.o monstre.o projectile.o fonc_sdl.o -o jeu -lncurses ${LIBS} ${INCLUDES}

joueur.o : joueur.c tout.h
	${CC} -c joueur.c -o joueur.o -lncurses ${LIBS} ${INCLUDES}

jeu.o : jeu.c tout.h
	${CC} -c jeu.c -o jeu.o -lncurses ${LIBS} ${INCLUDES}

map.o : map.c  tout.h
	${CC} -c map.c -o map.o -lncurses ${LIBS} ${INCLUDES}

salle.o : salle.c tout.h
	${CC} -c salle.c -o salle.o -lncurses ${LIBS} ${INCLUDES}

coordonnees.o : coordonnees.c tout.h
	${CC} -c coordonnees.c -o coordonnees.o -lncurses ${LIBS} ${INCLUDES}

liste_ptr.o : liste_ptr.c tout.h
	${CC} -c liste_ptr.c -o liste_ptr.o -lncurses ${LIBS} ${INCLUDES}

monstre.o : monstre.c tout.h
	${CC} -c monstre.c -o monstre.o -lncurses ${LIBS} ${INCLUDES}

projectile.o : projectile.c tout.h
	${CC} -c projectile.c -o projectile.o -lncurses ${LIBS} ${INCLUDES}

fonc_sdl.o: fonc_sdl.c tout.h
	${CC} -c fonc_sdl.c -o fonc_sdl.o -lncurses ${LIBS} ${INCLUDES}

clean:
	rm -f ${PROG}
	rm -f *.o
