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
    unsigned char delay, sound;
    unsigned char inputs[NUM_INPUTS];
    unsigned char screen[(SCR_WIDTH / 0x8) * (SCR_HEIGHT / 0x8)];
    bool draw;
    unsigned short pc;
} Chip8;

Chip8 * init(char* game);
