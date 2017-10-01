#ifndef CHIP8
#include "chip8.h"
#endif

void set_n(Chip8 * c8, unsigned char reg, char val);

void add_n(Chip8 * c8, unsigned char reg, char val);

void set_r(Chip8 * c8, unsigned char reg_x, unsigned char reg_y);

void or_r(Chip8 * c8, unsigned char reg_x, unsigned char reg_y);

void and_r(Chip8 * c8, unsigned char reg_x, unsigned char reg_y);

void xor_r(Chip8 * c8, unsigned char reg_x, unsigned char reg_y);

void add_r(Chip8 * c8, unsigned char reg_x, unsigned char reg_y);

void sub_r(Chip8 * c8, unsigned char reg_x, unsigned char reg_y);

void rs_r(Chip8 * c8, unsigned char reg_x, unsigned char reg_y);

void diff_r(Chip8 * c8, unsigned char reg_x, unsigned char reg_y);

void ls_r(Chip8 * c8, unsigned char reg_x, unsigned char reg_y);

void set_i(Chip8 * c8, short addr);

void add_i(Chip8 * c8, unsigned char reg);

void rand_r(Chip8 * c8, unsigned char reg, char val);
