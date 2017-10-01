all: chip8

CFLAGS = -std=c99 -pedantic -Wall -Wextra -ggdb

chip8: chip8.o conditionals.o display.o input.o jumps.o operations.o
	gcc -o chip8 chip8.o conditionals.o display.o input.o jumps.o operations.o -lSDL2 

chip8.o: chip8.c
	gcc ${CFLAGS} -c chip8.c

conditionals.o: conditionals.c
	gcc ${CFLAGS} -c conditionals.c

display.o: display.c
	gcc ${CFLAGS} -c display.c

input.o: input.c
	gcc ${CFLAGS} -c input.c

jumps.o: jumps.c
	gcc ${CFLAGS} -c jumps.c

operations.o: operations.c
	gcc ${CFLAGS} -c operations.c

clean:
	rm *.o chip8
