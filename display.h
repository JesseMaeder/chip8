#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>

void init_window(SDL_Window ** window, SDL_Renderer ** renderer);

void destroy_window(SDL_Window * window, SDL_Renderer * renderer);

#endif