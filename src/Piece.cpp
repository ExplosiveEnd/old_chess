#include "Piece.h"
#include "SDLHandler.h"

Piece::Piece(Type type){
    this->type = type;
}

Piece::Piece(Type type, Point point){
    this->type = type;
    this->point = point;
    getSprite(type);
}

SDL_Surface* Piece::getSprite(Type type){
    SDL_Surface *surface;
    switch(type){
        case PAWN:
             surface = IMG_Load("src/sprites/Pawn.png");
                // if(surface == NULL)
                //     SDL_ShowSimpleMessageBox(0,"Background Init Error", SDL_GetError(), SDLHandler::win);
            break;
        case ROOK:
             surface = IMG_Load("src/sprites/Rook.png");
             break;
        case BISHOP:
            surface = IMG_Load("src/sprites/Bishop.png");
            break;
        case QUEEN:
            surface = IMG_Load("src/sprites/Queen.png");
            break;
        case KING:
            surface = IMG_Load("src/sprites/King.png");
            break;
        case KNIGHT:
            surface = IMG_Load("src/sprites/Knight.png");
            break;
    }
    return surface;
}

