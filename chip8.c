#ifndef CHIP8
#include "chip8.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Chip8 * init(char* game) {
    Chip8 * c8 = malloc(sizeof(Chip8));
    c8->pc = PC_START;

    FILE * fp = fopen(game, "r");
    fread((char *) c8->mem + PC_START, 1, MEM_SIZE - PC_START, fp);
    fclose(fp);
    return c8;
}

unsigned short get_instr(Chip8 * c8) {
    unsigned short instr = (c8->mem[c8->pc] << 8) | c8->mem[c8->pc + 1];
    c8->pc += 2;
    return instr;
}

void clear_scr(Chip8 * c8) {
    // 0x00e0
    memset(c8->screen, 0, SCR_WIDTH * SCR_HEIGHT / 0x40);
}

void ret(Chip8 * c8) {
    // 0x00ee
    if (c8->sp--) {
        c8->pc = c8->stack[c8->sp];
    } else {
        printf("Exiting.\n");
        shutdown(c8);
        exit(0);
    }
}

void jump(Chip8 * c8, short addr) {
    c8->pc = addr;
}

void jump_link(Chip8 * c8, short addr) {
    printf("%d\n", c8->sp);
    if (c8->sp >= STACK_SIZE) {
        fprintf(stderr, "Stack overflow error!\n");
        shutdown(c8);
        exit(2);
    }

    c8->stack[c8->sp++] = c8->pc + 2;
    jump(c8, addr);
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

    unsigned short instr, addr;
    unsigned char opcode;
    while (engine->pc < MEM_SIZE) {
        instr = get_instr(engine);
        opcode = (instr & 0xf000) >> 12;
        printf("%04x -> %x\n", instr, opcode);
        if (instr == 0) break;
        switch (opcode) {
            case 0x0:
                if (instr == 0xe0) clear_scr(engine);
                else if (instr == 0xee) ret(engine);
                else {
                    addr = instr & 0x0fff;
                    printf("Call RCA 1802 program at 0x%4x\n", addr);
                }
                break;
            case 0x1:
                addr = instr & 0xfff;
                jump(engine, addr);
                break;
            case 0x2:
                addr = instr & 0xfff;
                jump_link(engine, addr);
                break;  
            case 0x3:
                break;
            case 0x4:
                break;
            case 0x5:
                break;
            case 0x6:
                break;
            case 0x7:
                break;
            case 0x8:
                break;
            case 0x9:
                break;
            case 0xa:
                break;
            case 0xb:
                break;
            case 0xc:
                break;
            case 0xd:
                break;
            case 0xe:
                break;
            case 0xf:
                break;
        }
    }

    shutdown(engine);
    return 0;
}