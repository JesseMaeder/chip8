#include "chip8.h"
#include "input.h"
#include "display.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

Chip8 * init_emu(char* game) {
    FILE * fp = fopen(game, "r");
    if (fp == 0) {
        fprintf(stderr, "File does not exist: %s\n", game);
        exit(1);
    }

    Chip8 * c8 = malloc(sizeof(Chip8));

    // load font information
    FILE * font = fopen(FONT_FILE, "r");
    if (font) {
        fread((char *) c8->mem, 1, PC_START, font);
        fclose(font);
    } else {
        fprintf(stderr, "Cannot load font information.\n");
    }

    // load game into memory at PC_START (0x200 by default)
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

void set_i(Chip8 * c8, short addr) {
    // 0xaNNN
    c8->i = addr;
}

void add_i(Chip8 * c8, unsigned char reg) {
    // 0xfX1e
    c8->i += c8->v[reg];
}

void get_delay(Chip8 * c8, unsigned char reg) {
    // 0xfX07
    c8->v[reg] = c8->delay;
}

void set_delay(Chip8 * c8, unsigned char reg) {
    // 0xfX15
    c8->delay = c8->v[reg];
}

void set_sound(Chip8 * c8, unsigned char reg) {
    // 0xfX18
    c8->sound = c8->v[reg];
}

void store_bcd(Chip8 * c8, unsigned char reg);

void dump_reg(Chip8 * c8, unsigned char reg);

void load_reg(Chip8 * c8, unsigned char reg);

void shutdown_emu(Chip8 * c8) {
    printf("Shutting down emulator\n");
    free(c8);
}

int main(int argc, char * argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: chip8 <game file>\n");
        return 1;
    }

    Chip8 * engine = init_emu(argv[1]);

    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    init_window(&window, &renderer);

    unsigned short instr, addr;
    unsigned char opcode, reg_x, reg_y, val, mod;
    while (engine->pc < MEM_SIZE) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT) break;

        // update timers
        if (engine->delay > 0) engine->delay--;
        if (engine->sound > 0) engine->sound--;
        if (engine->sound == 1) printf("BEEP\n");

        instr = get_instr(engine);
        // printf("%04x\n", instr);
        if (!instr) break;

        opcode = (instr & 0xf000) >> 12;
        addr = instr & 0xfff;
        reg_x = instr & 0xf00 >> 8;
        reg_y = instr & 0xf0 >> 4;
        val = instr & 0xff;
        mod = instr & 0xf;

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
                set_n(engine, reg_x, val);
                break;
            case 0x7:
                add_n(engine, reg_x, val);
                break;
            case 0x8:
                switch (mod) {
                    case 0x0:
                        set_r(engine, reg_x, reg_y);
                        break;
                    case 0x1:
                        or_r(engine, reg_x, reg_y);
                        break;
                    case 0x2:
                        and_r(engine, reg_x, reg_y);
                        break;
                    case 0x3:
                        xor_r(engine, reg_x, reg_y);
                        break;
                    case 0x4:
                        add_r(engine, reg_x, reg_y);
                        break;
                    case 0x5:
                        sub_r(engine, reg_x, reg_y);
                        break;
                    case 0x6:
                        rs_r(engine, reg_x, reg_y);
                        break;
                    case 0x7:
                        diff_r(engine, reg_x, reg_y);
                        break;
                    case 0xe:
                        ls_r(engine, reg_x, reg_y);
                        break;
                }
                break;
            case 0x9:
                if_rneq(engine, reg_x, reg_y);
                break;
            case 0xa:
                set_i(engine, addr);
                break;
            case 0xb:
                jump_off(engine, addr);
                break;
            case 0xc:
                rand_r(engine, reg_x, val);
                break;
            case 0xd:
                break;
            case 0xe:
                if (val == 0x9e) if_key(engine, reg_x);
                else if (val == 0xa1) if_nkey(engine, reg_x);
                break;
            case 0xf:
                switch (val) {
                    case 0x0a:
                        get_key(engine, reg_x);
                        break;
                    case 0x07:
                        get_delay(engine, reg_x);
                        break;
                    case 0x15:
                        set_delay(engine, reg_x);
                        break;
                    case 0x18:
                        set_sound(engine, reg_x);
                        break;
                    case 0x1e:
                        add_i(engine, reg_x);
                        break;
                    case 0x29:
                        load_ch(engine, reg_x);
                        break;
                }
                break;
        }
    }

    shutdown_emu(engine);
    destroy_window(window, renderer);
    return 0;
}