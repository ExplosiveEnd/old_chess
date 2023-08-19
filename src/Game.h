#pragma once

#include <stdio.h>
#include <SDL.h>
#include <vector>
#include "Piece.h"
#include <algorithm>

class Game{
public:
    // Texture for surfaces
    SDL_Texture* text;

    // Holds selected piece
    Piece* selectedPiece;

    // First mouse input
    int32_t mouseX = -1, mouseY = -1;

    // Vector containing all pieces on the board
    std::vector<Piece*> pieces;


    bool secondClick = false;

    //Proper piece coords
    std::vector<Piece*> coords = std::vector<Piece*>(64);

    // Vector containing possible move locations after click
    std::vector<int> possibleLocations;

    //
    std::vector<int> possibleKills;
    
    // Creates Pieces and populates vector
    void createPieces(SDL_Renderer* renderer);

    // Gets piece with coordinates
    Piece* getPiece(int32_t x, int32_t y);

    void movePiece(Piece* piece);

    void handleClick();

    void setPossibleLocations(Piece* selected);

    void sortCoords();

};