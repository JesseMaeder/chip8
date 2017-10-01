#include "chip8.h"

#include <stdio.h>
#include <stdlib.h>

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

void jump_off(Chip8 * c8, short addr) {
    // 0xBNNN
    jump(c8, c8->v[0] + addr);
}
