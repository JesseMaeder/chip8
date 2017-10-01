#ifndef CHIP8
#include "chip8.h"
#endif

#include <stdio.h>
#include <stdlib.h>

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

void get_delay(Chip8 * c8, unsigned char reg);

void set_delay(Chip8 * c8, unsigned char reg);

void set_sound(Chip8 * c8, unsigned char reg);

void store_bcd(Chip8 * c8, unsigned char reg);

void dump_reg(Chip8 * c8, unsigned char reg);

void load_reg(Chip8 * c8, unsigned char reg);

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