#ifndef CHIP8
#include "chip8.h"
#endif

#include <stdlib.h>

void set_n(Chip8 * c8, unsigned char reg, char val) {
    c8->v[reg] = val;
}

void add_n(Chip8 * c8, unsigned char reg, char val) {
    c8->v[reg] += val;
}

void set_r(Chip8 * c8, unsigned char reg_x, unsigned char reg_y) {
    c8->v[reg_x] = c8->v[reg_y];
}

void or_r(Chip8 * c8, unsigned char reg_x, unsigned char reg_y) {
    c8->v[reg_x] |= c8->v[reg_y];
}

void and_r(Chip8 * c8, unsigned char reg_x, unsigned char reg_y) {
    c8->v[reg_x] &= c8->v[reg_y];
}

void xor_r(Chip8 * c8, unsigned char reg_x, unsigned char reg_y) {
    c8->v[reg_x] ^= c8->v[reg_y];
}

void add_r(Chip8 * c8, unsigned char reg_x, unsigned char reg_y) {
    c8->v[reg_x] += c8->v[reg_y];
}

void sub_r(Chip8 * c8, unsigned char reg_x, unsigned char reg_y) {
    c8->v[reg_x] -= c8->v[reg_y];
}

void rs_r(Chip8 * c8, unsigned char reg_x, unsigned char reg_y) {
    c8->v[reg_y] >>= 1;
    set_r(c8, reg_x, reg_y);
}

void ls_r(Chip8 * c8, unsigned char reg_x, unsigned char reg_y){
    c8->v[reg_y] <<= 1;
    set_r(c8, reg_x, reg_y);
}

void diff_r(Chip8 * c8, unsigned char reg_x, unsigned char reg_y) {
    c8->v[reg_x] = c8->v[reg_y] - c8->v[reg_x];
}

void rand_r(Chip8 * c8, unsigned char reg, char val) {
    c8->v[reg] = (rand() % 0xff) & val;
}
