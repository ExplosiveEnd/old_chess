#pragma once
#include <SDL2/SDL.h>

struct Point{
    int32_t x;
    int32_t y;
};

enum Type: int32_t{
    NONE = 0,
    PAWN,
    ROOK,
    BISHOP,
    QUEEN,
    KNIGHT,
    KING
};

class Piece {
public:
    SDL_Texture* sprite;
    Type type;
    Point point;

    Piece(Type type);

    Piece(Type type, Point point);

    SDL_Surface* getSprite(Type type);


};