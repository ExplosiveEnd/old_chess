#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Piece.h"
#include <vector>

class SDLHandler{
public:
    SDL_Window *win;
    SDL_Renderer *renderer;

    std::vector<Piece*> pieces;
    std::vector<SDL_Rect*> squares;

    void initialize();
    void createBackground();

    void setPieces();
};