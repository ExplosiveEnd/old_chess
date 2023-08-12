#pragma once
#include <SDL2/SDL.h>

class SDLHandler{
public:
    SDL_Window *win;
    SDL_Renderer *renderer;

    void initialize();
    void createBackground();
};