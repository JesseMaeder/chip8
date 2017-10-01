// chip8.h - definitions of the virtual machine
#ifndef CHIP8
#define CHIP8
#include <stdbool.h>
#include <SDL2/SDL.h>

// system specs
#define MEM_SIZE 0x1000
#define STACK_SIZE 0x18
#define NUM_REGISTERS 0x10
#define NUM_INPUTS 0x10
#define SCR_WIDTH 0x40
#define SCR_HEIGHT 0x20
#define SCR_SCALE 0x14
#define PC_START 0x200
#define FONT_FILE "FONT"

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

Chip8 * init_emu(char* game);

void shutdown_emu(Chip8 * c8);

unsigned short get_instr(Chip8 * c8);

void clear_scr(Chip8 * c8);

void ret(Chip8 *c8);

void jump(Chip8 * c8, short addr);

void jump_link(Chip8 * c8, short addr);

void jump_off(Chip8 * c8, short addr);

void if_eq(Chip8 * c8, unsigned char reg, char val);

void if_neq(Chip8 * c8, unsigned char reg, char val);

void if_req(Chip8 * c8, unsigned char reg_x, unsigned char reg_y);

void if_rneq(Chip8 * c8, unsigned char reg_x, unsigned char reg_y);

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

void draw(Chip8 * c8, SDL_Renderer * renderer, unsigned char reg_x, unsigned char reg_y, char rows);

void if_key(Chip8 * c8, unsigned char reg);

void if_nkey(Chip8 * c8, unsigned char reg);

void get_delay(Chip8 * c8, unsigned char reg);

void get_key(Chip8 * c8, unsigned char reg);

void set_delay(Chip8 * c8, unsigned char reg);

void set_sound(Chip8 * c8, unsigned char reg);

void load_ch(Chip8 * c8, unsigned char reg);

void store_bcd(Chip8 * c8, unsigned char reg);

void dump_reg(Chip8 * c8, unsigned char reg);

void load_reg(Chip8 * c8, unsigned char reg);

#endif