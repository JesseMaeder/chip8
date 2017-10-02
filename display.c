#include "chip8.h"
#include "display.h"

#include <string.h>

void init_window(SDL_Window ** window, SDL_Renderer ** renderer) {
    int width = SCR_WIDTH * SCR_SCALE;
    int height = SCR_HEIGHT * SCR_SCALE;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width, height, 0, window, renderer);
    SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 0);
    SDL_RenderClear(*renderer);
    SDL_SetRenderDrawColor(*renderer, 255, 255, 255, 255);
    SDL_RenderPresent(*renderer);
}

void destroy_window(SDL_Window * window, SDL_Renderer * renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void clear_scr(Chip8 * c8) {
    // 0x00e0
    memset(c8->screen, 0, SCR_WIDTH * SCR_HEIGHT / 0x40);
}

void draw(Chip8 * c8, SDL_Renderer * renderer, unsigned char reg_x, unsigned char reg_y, char rows) {
    // 0xdXYN
    SDL_Rect sprite;
    sprite.w = SCR_SCALE;
    sprite.h = SCR_SCALE;

    c8->v[0xf] = 0;

    short row_addr;
    unsigned char mask, curr_row;
    for (char row = 0; row < rows; row++) {
        sprite.y = (c8->v[reg_y] + row) * SCR_SCALE;
        row_addr = c8->i + row;

        mask = 128;
        for (char bit = 0; bit < 8; bit++) {
            sprite.x = (c8->v[reg_x] + bit) * SCR_SCALE;
            if ((c8->mem[row_addr] & mask)) {
                // this pixel should be flipped
                // TODO 
                SDL_RenderFillRect(renderer, &sprite);
            }

            mask >>= 1;
        }

        // update pixels in internal screen representation
        //c8->screen[(c8->v[reg_y] + row) * SCR_WIDTH + c8->v[reg_x]] ^= c8->mem[row_addr];
    }
    SDL_RenderPresent(renderer);
}

void load_ch(Chip8 * c8, unsigned char reg) {
    //0xfX29
    // characters are 5 bytes each
    c8->i = 0x5 * c8->v[reg];
}
