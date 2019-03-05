test_map : test_map.o joueur.o map.o salle.o coordonnees.o liste_ptr.o
	gcc test_map.o joueur.o map.o salle.o coordonnees.o liste_ptr.o -o test_map -lncurses

joueur.o : joueur.c joueur.h
	gcc -c joueur.c -o joueur.o -lncurses

test_map.o : test_map.c joueur.h
	gcc -c test_map.c -o test_map.o -lncurses

map.o : map.c map.h salle.h
	gcc -c map.c -o map.o -lncurses

salle.o : salle.c salle.h
	gcc -c salle.c -o salle.o -lncurses

coordonnees.o : coordonnees.c coordonnees.h
	gcc -c coordonnees.c -o coordonnees.o -lncurses

liste_ptr.o : liste_ptr.c liste_ptr.h
	gcc -c liste_ptr.c -o liste_ptr.o -lncurses

clean :
	- rm -f *.o
	- rm -f test_map
