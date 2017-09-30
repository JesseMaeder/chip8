#ifndef CHIP8
#include "chip8.h"
#endif

#include <stdio.h>
#include <stdlib.h>

Chip8 * init(char* game) {
    Chip8 * c8 = malloc(sizeof(Chip8));
    c8->pc = PC_START;

    FILE * fp = fopen(game, "r");
    fgets((char *) c8->mem + PC_START, MEM_SIZE - PC_START, fp);
    return c8;
}

int main(int argc, char * argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: chip8 <game file>\n");
        return 1;
    }
    Chip8 * engine = init(argv[1]);
    return 0;
}