#ifndef CHIP8
#include "chip8.h"
#endif

#include <string.h>

void clear_scr(Chip8 * c8) {
    // 0x00e0
    memset(c8->screen, 0, SCR_WIDTH * SCR_HEIGHT / 0x40);
}

void draw(Chip8 * c8, unsigned char reg_x, unsigned char reg_y, char rows);

void load_ch(Chip8 * c8, unsigned char reg);