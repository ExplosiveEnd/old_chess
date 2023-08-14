#pragma once
#include <SDL2/SDL.h>

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

    Piece(Type type);

    Piece(Type type, Point point, Color color);

    SDL_Surface* getSprite(Type type, Color color);


};