// chip8.h - definitions of the virtual machine
#define CHIP8
#include <stdbool.h>

// system specs
#define MEM_SIZE 0x1000
#define STACK_SIZE 0x18
#define NUM_REGISTERS 0x10
#define NUM_INPUTS 0x10
#define SCR_WIDTH 0x40
#define SCR_HEIGHT 0x20
#define PC_START 0x200

typedef struct {
    unsigned char mem[MEM_SIZE];
    unsigned char v[NUM_REGISTERS];
    unsigned char i;
    unsigned short stack[STACK_SIZE];
    unsigned short sp;
    unsigned char delay, sound;
    unsigned char inputs[NUM_INPUTS];
    unsigned char screen[SCR_WIDTH * SCR_HEIGHT / 0x40];
    bool draw;
    unsigned short pc;
} Chip8;

Chip8 * init(char* game);

void shutdown(Chip8 * c8);

unsigned short get_instr(Chip8 * c8);

void clear_scr(Chip8 * c8);

void ret(Chip8 *c8);

void jump(Chip8 * c8, short addr);

void jump_link(Chip8 * c8, short addr);

void if_eq(Chip8 * c8, unsigned char reg, char val);

void if_neq(Chip8 * c8, unsigned char reg, char val);

void if_req(Chip8 * c8, unsigned char reg_x, unsigned char reg_y);