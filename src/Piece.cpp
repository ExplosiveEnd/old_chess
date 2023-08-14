#include "Piece.h"
#include "SDLHandler.h"

Piece::Piece(Type type){
    this->type = type;
}

Piece::Piece(Type type, Point point, Color color){
    this->type = type;
    this->point = point;
    this->color = color;
    getSprite(type, color);
}

SDL_Surface* Piece::getSprite(Type type, Color color){
    SDL_Surface *surface;
    switch(type){
        case PAWN:
            surface = this->color == Color::BLACK ? IMG_Load("src/sprites/Pawn.png") : IMG_Load("src/sprites/WhitePawn.png");
            break;
        case ROOK:
             surface = this->color == Color::BLACK ? IMG_Load("src/sprites/Rook.png") : IMG_Load("src/sprites/WhiteRook.png");
             break;
        case BISHOP:
            surface = this->color == Color::BLACK ? IMG_Load("src/sprites/Bishop.png") : IMG_Load("src/sprites/WhiteBishop.png");
            break;
        case QUEEN:
            surface = this->color == Color::BLACK ? IMG_Load("src/sprites/Queen.png") : IMG_Load("src/sprites/WhiteQueen.png");
            break;
        case KING:
            surface = this->color == Color::BLACK ? IMG_Load("src/sprites/King.png") : IMG_Load("src/sprites/WhiteKing.png");
            break;
        case KNIGHT:
            surface = this->color == Color::BLACK ? IMG_Load("src/sprites/Knight.png") : IMG_Load("src/sprites/WhiteKnight.png");
            break;
    }
    return surface;
}

