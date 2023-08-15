#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Piece.h"
#include <vector>
#include <iostream>

class SDLHandler{
public:
    SDL_Window *win;
    SDL_Renderer *renderer;
    SDL_Renderer *backlog;

    // Texture for surfaces
    SDL_Texture* text;

    std::vector<Piece*> pieces;
    std::vector<SDL_Rect*> squares;

    void initialize();
    void createBackground();

    void setPieces();

    void renderPieces();

    void movePiece(Piece* piece, int32_t x, int32_t y);

    Piece* getPiece(int32_t x, int32_t y);
};