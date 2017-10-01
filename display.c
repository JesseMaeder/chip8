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

void draw(Chip8 * c8, SDL_Renderer * renderer, unsigned char reg_x, unsigned char reg_y, char rows);

void load_ch(Chip8 * c8, unsigned char reg) {
    //0xfX29
    // characters are 5 bytes each
    c8->i = 0x5 * c8->v[reg];
}
