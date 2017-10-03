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
    SDL_SetRenderDrawColor(*renderer, 150, 150, 150, 150);
    SDL_RenderPresent(*renderer);
}

void destroy_window(SDL_Window * window, SDL_Renderer * renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void clear_scr(Chip8 * c8, SDL_Renderer * renderer) {
    // 0x00e0

    // clear screen data
    memset(c8->screen, 0, SCR_WIDTH * SCR_HEIGHT / 0x40);

    // clear window
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 150);
    SDL_RenderPresent(renderer);
}

void draw(Chip8 * c8, SDL_Renderer * renderer, unsigned char reg_x, unsigned char reg_y, char rows) {
    // 0xdXYN
    SDL_Rect pixel;
    pixel.w = SCR_SCALE;
    pixel.h = SCR_SCALE;

    // clear VF
    c8->v[0xf] = 0;

    short row_addr;
    unsigned char screen_byte1, screen_byte2, sprite_byte1, sprite_byte2;
    unsigned int byte_index;
    for (char row = 0; row < rows; row++) {
        /*
        THINGS GET A LITTLE WILD HERE
        Sprites are 8 pixels wide so I thought I could represent each row of them with a char
        in the emulator... not taking into account that sprites can be drawn "misaligned"
        with the cells of the screen represented by chars. So, to get the current state of 
        the screen where the sprite is being drawn, a bit (heh) of trickery is needed.

            +--------((VX / 8) * 8)
            |    +---VX
            |    |
        VY [.....###] [#####...]
            |----|
                 +---(VX % 8)

        The brackets denote the start and end of the chars in c8->screen. Drawing a sprite 
        at (VX, VY) means the sprite pixels are split between two chars of c8->screen.

        So, we only look at the last (8 - (VX % 8)) bits of the first byte and the first
        (VX % 8) bits of the second byte
        */
        byte_index = ((c8->v[reg_y] + row) * SCR_WIDTH) + ((c8->v[reg_x] / 8) * 8);
        
        // mask the first byte to only get the righmost (8 - VX % 8) bits
        screen_byte1 = c8->screen[byte_index] & (0xff >> (c8->v[reg_x] % 8));

        // mask the second byte to only get the first (VX % 8) bits
        screen_byte2 = c8->screen[byte_index + 1] & (0xff << (8 - (c8->v[reg_x] % 8)));

        // the address of the row to be drawn
        row_addr = c8->i + row;

        // split the row of the sprite between the two bytes
        sprite_byte1 = c8->mem[row_addr] >> (c8->v[reg_x] % 8);
        sprite_byte2 = c8->mem[row_addr] << (8 - (c8->v[reg_x] % 8));

        pixel.y = (c8->v[reg_y] + row) * SCR_SCALE;

        // if there are any pixel collisions, set VF
        if ((screen_byte1 & sprite_byte1) | (screen_byte2 & sprite_byte2)) {
            c8->v[0xf] = 1;
        }

        /* 
        initialize mask to the corresponding bit of the first byte of the sprite. 
        If ANDing the mask and the current sprite byte is nonzero,
        then the pixel at that bit position should be flipped. Shifting the mask right
        one bit at a time allows us to individually check each pixel for the row
        */
        unsigned char mask = 128 >> (c8->v[reg_x] % 8);
        unsigned char curr_sprite = sprite_byte1;
        unsigned char curr_screen = screen_byte1;
        for (char bit = 0; bit < 8; bit++) {
            pixel.x = (c8->v[reg_x] + bit) * SCR_SCALE;
            if (curr_sprite & mask) {
                // this pixel should be flipped
                if (curr_screen & mask) {
                    // The pixel is already white, switch to black
                    // (actually switch to red for now so I can see where it happens)
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
                }
                SDL_RenderFillRect(renderer, &pixel);
                SDL_SetRenderDrawColor(renderer, 150, 150, 150, 150);

            }
            mask >>= 1;
            // once we reach the end of this byte, switch to the next
            if (mask == 0) {
                mask = 128;
                curr_sprite = sprite_byte2;
                curr_screen = screen_byte2;
            }
        }
        // TODO update pixels in internal screen representation
        // this breaks for some reason (but doesn't crash??)
        // c8->screen[byte_index] = sprite_byte1;
        // c8->screen[byte_index + 1] = sprite_byte2;      
    }
    SDL_RenderPresent(renderer);
}

void load_ch(Chip8 * c8, unsigned char reg) {
    //0xfX29
    // characters are 5 bytes each
    c8->i = 0x5 * c8->v[reg];
}
