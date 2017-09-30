all: chip8

chip8: chip8.o
	gcc -o chip8 chip8.o

chip8.o: chip8.c
	gcc -std=c99 -pedantic -Wall -ggdb -c chip8.c

clean:
	rm *.o chip8
