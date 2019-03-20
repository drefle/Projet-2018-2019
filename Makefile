jeu : jeu.o joueur.o map.o salle.o coordonnees.o liste_ptr.o projectile.o monstre.o
	gcc jeu.o joueur.o map.o salle.o coordonnees.o liste_ptr.o monstre.o projectile.o -o jeu -lncurses

joueur.o : joueur.c tout.h
	gcc -c joueur.c -o joueur.o -lncurses

jeu.o : jeu.c tout.h
	gcc -c jeu.c -o jeu.o -lncurses

map.o : map.c  tout.h
	gcc -c map.c -o map.o -lncurses

salle.o : salle.c tout.h
	gcc -c salle.c -o salle.o -lncurses

coordonnees.o : coordonnees.c tout.h
	gcc -c coordonnees.c -o coordonnees.o -lncurses

liste_ptr.o : liste_ptr.c tout.h
	gcc -c liste_ptr.c -o liste_ptr.o -lncurses

monstre.o : monstre.c tout.h
	gcc -c monstre.c -o monstre.o -lncurses

projectile.o : projectile.c tout.h
	gcc -c projectile.c -o projectile.o -lncurses


clean :
	- rm -f *.o
	- rm -f jeu
