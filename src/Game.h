#pragma once

#include <stdio.h>
#include <SDL.h>
#include <vector>
#include "Piece.h"

class Game{
public:
    // Texture for surfaces
    SDL_Texture* text;

    // Vector containing all pieces on the board
    std::vector<Piece*> pieces;
    
    // Creates Pieces and populates vector
    void createPieces(SDL_Renderer* renderer);

    // Gets piece with coordinates
    Piece* getPiece(int32_t x, int32_t y);

};