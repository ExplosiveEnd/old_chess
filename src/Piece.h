#pragma once
#include <string>
#include <SDL.h>
#include <iostream>


struct Point{
    int32_t x;
    int32_t y;

    bool operator==(const Point b) {
        return b.x == x && b.y == y;
    }
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

    bool pawnFirstMove = false;

    std::string typeString;

    Piece(Type type);

    bool operator< (const Piece &other) {
        return (point.y * 8 + point.x) < (other.point.y * 8 + other.point.x);
    }

    Piece(Type type, Point point, Color color);

    SDL_Surface* getSprite(Type type, Color color);


};

struct less_than_point {
    bool operator()(const Piece* p1, const Piece* p2) {
        return (p1->point.y * 8 + p1->point.x) < (p2->point.y * 8 + p2->point.x);
    }
};