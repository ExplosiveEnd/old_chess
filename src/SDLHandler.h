#pragma once
#include <SDL.h>
#include "Piece.h"
#include <vector>
#include <iostream>

class SDLHandler{
public:
    SDL_Window *win;
    SDL_Renderer *renderer;
    SDL_Renderer *backlog;

    // Texture for surfaces
    //SDL_Texture* text;

    //std::vector<Piece*> pieces;
    std::vector<SDL_Rect*> squares;

    // Initializes the window / renderer
    void initialize();

    // Creates background
    void createBackground();

    // Renders changes to pieces
    void renderPieces(std::vector<Piece*> pieces);

    
};