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
    fclose(fp);
    return c8;
}

unsigned short get_instr(Chip8 * c8) {
    unsigned short instr = c8->mem[c8->pc++] << 8;
    instr |= c8->mem[c8->pc++];
    return instr;
}

void shutdown(Chip8 * c8) {
    free(c8);
}

int main(int argc, char * argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: chip8 <game file>\n");
        return 1;
    }
    Chip8 * engine = init(argv[1]);

    while (engine->pc < MEM_SIZE) {
        unsigned short instr = get_instr(engine);
        if (instr == 0) break;
        printf("%x\n", instr);
    }

    shutdown(engine);
    return 0;
}