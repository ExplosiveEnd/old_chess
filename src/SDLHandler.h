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

    // Vector containing board squares
    std::vector<SDL_Rect*> squares;

    // Initializes the window / renderer
    void initialize();

    // Creates background
    void createBackground();

    // Renders changes to pieces
    void renderPieces(std::vector<Piece*> pieces);

    // Renders possible MOVE locations
    void renderPossibleLocations(std::vector<int> options);

    // Renders possible KILL locations
    void renderPossibleKills(std::vector<int> options);

    // Renders tile for selected piece
    void renderSelected(Piece* selected);

    
};