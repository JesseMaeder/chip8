all: chip8

chip8: chip8.o conditionals.o display.o input.o jumps.o operations.o
	gcc -o chip8 chip8.o conditionals.o display.o input.o jumps.o operations.o -lncurses 

chip8.o: chip8.c
	gcc -std=c99 -pedantic -Wall -ggdb -c chip8.c

conditionals.o: conditionals.c
	gcc -std=c99 -pedantic -Wall -ggdb -c conditionals.c

display.o: display.c
	gcc -std=c99 -pedantic -Wall -ggdb -c display.c

input.o: input.c
	gcc -std=c99 -pedantic -Wall -ggdb -c input.c

jumps.o: jumps.c
	gcc -std=c99 -pedantic -Wall -ggdb -c jumps.c

operations.o: operations.c
	gcc -std=c99 -pedantic -Wall -ggdb -c operations.c

clean:
	rm *.o chip8
