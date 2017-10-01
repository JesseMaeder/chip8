#ifndef CHIP8
#include "chip8.h"
#endif

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

void if_rneq(Chip8 * c8, unsigned char reg_x, unsigned char reg_y) {
    // 0x9XY0
    if (c8->v[reg_x] != c8->v[reg_y]) c8->pc += 2;
}
