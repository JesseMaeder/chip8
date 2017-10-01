#include "chip8.h"
#include "input.h"

#include <string.h>

void if_key(Chip8 * c8, unsigned char reg) {
    // 0xeX9e
    if (c8->inputs[c8->v[reg]]) c8->pc += 2;
}

void if_nkey(Chip8 * c8, unsigned char reg) {
    // 0xeXa1
    if (!c8->inputs[c8->v[reg]]) c8->pc += 2;
}

void get_key(Chip8 * c8, unsigned char reg) {
    // 0xfX0a
    int key;
    do {
        key = read_key(c8);
    } while (key == -1);

    c8->inputs[reg] = key;
}

int read_key(Chip8 * c8) {
    memset(c8->inputs, 0, NUM_INPUTS);
    char ch = 49;
    int map = -1;
    switch (ch) {
        case 49:  // 1
            map = 0xa;
            break;
        case 50:  // 2
            map = 0xb;
            break;
        case 51:  // 3
            map = 0xc;
            break;
        case 52:  // 4
            map = 0xd;
            break;
        case 113: // q
            map = 0x7;
            break;
        case 119: // w
            map = 0x8;
            break;
        case 101: // e
            map = 0x9;
            break;
        case 114: // r
            map = 0xe;
            break;
        case 97:  // a
            map = 0x4;
            break;
        case 115: // s
            map = 0x5;
            break;
        case 100: // d
            map = 0x6;
            break;
        case 102: // f
            map = 0xf;
            break;
        case 122: // z
            map = 0x1;
            break;
        case 120: // x
            map = 0x2;
            break;
        case 99:  // c
            map = 0x3;
            break;
        case 118: // v
            map = 0x0;
            break;
    }
    if (map >= 0) c8->inputs[map] = 1;
    return map;
}
