all: Gauntlet

Gauntlet: game.o shop.o heroes.o io.o boss.o fight.o parse.o
	gcc -o Gauntlet game.o shop.o heroes.o io.o boss.o fight.o parse.o
	
game.o: game.c game.h
	gcc -c -g -Wall -Werror game.c
	
shop.o: shop.c game.h
	gcc -c -g -Wall -Werror shop.c
	
heroes.o: heroes.c game.h
	gcc -c -g -Wall -Werror heroes.c
	
io.o: io.c game.h 
	gcc -c -g -Wall -Werror io.c

boss.o: boss.c game.h 
	gcc -c -g -Wall -Werror boss.c
	
fight.o: fight.c game.h 
	gcc -c -g -Wall -Werror fight.c 
	
parse.o: parse.c game.h 
	gcc -c -g -Wall -Werror parse.c 
	
clean: 
	rm Gauntlet game.o shop.o heroes.o io.o boss.o fight.o parse.o