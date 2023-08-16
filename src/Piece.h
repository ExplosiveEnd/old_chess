#pragma once
#include <string>
#include <SDL.h>
#include <iostream>


struct Point{
    int32_t x;
    int32_t y;
};

enum Type: int32_t{
    TYPE_NONE = 0,
    PAWN,
    ROOK,
    BISHOP,
    QUEEN,
    KNIGHT,
    KING
};

enum Color: int32_t{
    COLOR_NONE=0,
    BLACK,
    WHITE
};

class Piece {
public:
    SDL_Texture* sprite;
    Type type;
    Point point;
    Color color;

    std::string typeString;

    Piece(Type type);

    ~Piece() {
        std::cout << "Delete Piece\n";
    }

    Piece(Type type, Point point, Color color);

    SDL_Surface* getSprite(Type type, Color color);


};