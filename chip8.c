#ifndef CHIP8
#include "chip8.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Chip8 * init(char* game) {
    FILE * fp = fopen(game, "r");
    if (fp == 0) {
        fprintf(stderr, "File does not exist: %s\n", game);
        exit(1);
    }
    Chip8 * c8 = malloc(sizeof(Chip8));
    c8->pc = PC_START;
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
    if (c8->sp) {
        c8->pc = c8->stack[--c8->sp];
    } else {
        printf("Exiting.\n");
        shutdown(c8);
        exit(0);
    }
}

void jump(Chip8 * c8, short addr) {
    // 0x1NNN
    c8->pc = addr;
}

void jump_link(Chip8 * c8, short addr) {
    // 0x2NNN
    printf("%d\n", c8->sp);
    if (c8->sp >= STACK_SIZE) {
        fprintf(stderr, "Stack overflow error!\n");
        shutdown(c8);
        exit(2);
    }

    c8->stack[c8->sp++] = c8->pc + 2;
    jump(c8, addr);
}

void if_eq(Chip8 * c8, unsigned char reg, char val) {
    // 0x3XNN
    if (c8->v[reg] == val) c8->pc += 2;
}

void if_neq(Chip8 * c8, unsigned char reg, char val) {
    // 0x4XNN
    if (c8->v[reg] != val) c8->pc += 2;
}

void if_req(Chip8 * c8, unsigned char reg_x, unsigned char reg_y) {
    // 0x5XY0
    if (c8->v[reg_x] == c8->v[reg_y]) c8->pc += 2;
}

void shutdown(Chip8 * c8) {
    printf("Shutting down emulator\n");
    free(c8);
}

int main(int argc, char * argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: chip8 <game file>\n");
        return 1;
    }

    Chip8 * engine = init(argv[1]);

    unsigned short instr, addr;
    unsigned char opcode, reg_x, reg_y, val;
    while (engine->pc < MEM_SIZE) {
        instr = get_instr(engine);
        printf("%04x\n", instr);
        if (instr == 0) break;
        opcode = (instr & 0xf000) >> 12;
        addr = instr & 0xfff;
        reg_x = instr & 0xf00 >> 8;
        reg_y = instr & 0xf0 >> 4;
        val = instr & 0xff;
        switch (opcode) {
            case 0x0:
                if (instr == 0xe0) clear_scr(engine);
                else if (instr == 0xee) ret(engine);
                else {
                    printf("Call RCA 1802 program at 0x%4x\n", addr);
                }
                break;
            case 0x1:
                jump(engine, addr);
                break;
            case 0x2:
                jump_link(engine, addr);
                break;  
            case 0x3:
                if_eq(engine, reg_x, val);
                break;
            case 0x4:
                if_neq(engine, reg_x, val);
                break;
            case 0x5:
                if_req(engine, reg_x, reg_y);
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