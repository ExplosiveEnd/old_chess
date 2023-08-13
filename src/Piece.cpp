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
    switch(type){
        case PAWN:
            SDL_Surface *surface = SDL_LoadBMP("src/Pawn-1.bmp");
                // if(surface == NULL)
                //     SDL_ShowSimpleMessageBox(0,"Background Init Error", SDL_GetError(), SDLHandler::win);
            return surface;
    }
}

