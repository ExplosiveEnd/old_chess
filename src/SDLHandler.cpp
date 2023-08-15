#include "SDLHandler.h"
#include "Piece.h"
#include <SDL2/SDL_image.h>
#include <string>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

void SDLHandler::initialize(){
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    
    win = SDL_CreateWindow("CHESS",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(win, -1, 0);
}

void SDLHandler::createBackground(){
        // Background color
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

        SDL_RenderClear(renderer);

        int32_t width = SCREEN_WIDTH / 8;
        int32_t height = SCREEN_HEIGHT / 8;
        
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                SDL_Rect* square = new SDL_Rect();
                square->x = width*j;
                square->y = height*i;
                square->w = width;
                square->h = height;

                squares.push_back(square);

                if(i%2 == 0){
                    if(j%2 == 0){
                        SDL_SetRenderDrawColor(renderer, 230, 204, 179, SDL_ALPHA_OPAQUE);
                    }
                    else{
                        SDL_SetRenderDrawColor(renderer, 172, 113, 57, SDL_ALPHA_OPAQUE);
                    }
                }
                else{
                    if(j%2 != 0){
                        SDL_SetRenderDrawColor(renderer, 230, 204, 179, SDL_ALPHA_OPAQUE);
                    }
                    else{
                        SDL_SetRenderDrawColor(renderer, 172, 113, 57, SDL_ALPHA_OPAQUE);
                    }
                }

                SDL_RenderFillRect(renderer, square);
            }

        }

}

void SDLHandler::setPieces(){


    // Starting position struct

    if(!pieces.size()){
        Point start;

        // Pawns
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 8; j++){
                if(i == 0){
                    // Creates starting point
                    start.x = j;
                    start.y = 6;
                    
                    // Adds piece information to pieces vector
                    pieces.push_back(new Piece(Type::PAWN, start, Color::BLACK));

                }
                else{
                    start.x = j;
                    start.y = 1;

                    pieces.push_back(new Piece(Type::PAWN, start, Color::WHITE));
                }
            }
        }

        // Rook
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                if(i == 0){
                    if(j == 0){
                        start.x = 0;
                        start.y = 7;
                    }
                    else{
                        start.x = 7;
                        start.y = 7;
                    }
                    pieces.push_back(new Piece(Type::ROOK, start, Color::BLACK));
                }
                else{
                    if(j == 0){
                        start.x = 0;
                        start.y = 0;
                    }
                    else{
                        start.x = 7;
                        start.y = 0;
                    }
                    pieces.push_back(new Piece(Type::ROOK, start, Color::WHITE));
                }

            }
        }

        // Bishop
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                if(i == 0){
                    if(j == 0){
                        start.x = 2;
                        start.y = 7;
                    }
                    else{
                        start.x = 5;
                        start.y = 7;
                    }
                    pieces.push_back(new Piece(Type::BISHOP, start, Color::BLACK));
                }
                else{
                    if(j == 0){
                        start.x = 2;
                        start.y = 0;
                    }
                    else{
                        start.x = 5;
                        start.y = 0;
                    }
                    pieces.push_back(new Piece(Type::BISHOP, start, Color::WHITE));
                }
            }
        }

        // Queen
        for(int i = 0; i < 2; i++){
            if(i == 0){
                start.x = 4;
                start.y = 7;
                pieces.push_back(new Piece(Type::QUEEN, start, Color::BLACK));
            }
            else{
                start.x = 4;
                start.y = 0;
                pieces.push_back(new Piece(Type::QUEEN, start, Color::WHITE));
            }
        }

        // King
        for(int i = 0; i < 2; i++){      
            if(i == 0){
                start.x = 3;
                start.y = 7;
                pieces.push_back(new Piece(Type::KING, start, Color::BLACK));
            }
            else{
                start.x = 3;
                start.y = 0;
                pieces.push_back(new Piece(Type::KING, start, Color::WHITE));
            }
        }

        // Knights
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                if(i == 0){
                    start.y=7;
                    if(j == 0)
                        start.x = 1;
                    else
                        start.x = 6;

                    pieces.push_back(new Piece(Type::KNIGHT, start, Color::BLACK));
                }
                else{
                    start.y = 0;
                    if(j == 0)
                        start.x = 1;
                    else
                        start.x = 6;

                    pieces.push_back(new Piece(Type::KNIGHT, start, Color::WHITE));
                }
            }
        }
    }

    renderPieces();
}

std::vector<int> locations;

void SDLHandler::renderPieces(){
        // Gets sprite surface and displays
    for(auto piece : SDLHandler::pieces){
        text = SDL_CreateTextureFromSurface(renderer, piece->getSprite(piece->type, piece->color));
        SDL_RenderCopy(renderer, text, NULL, squares.at(piece->point.y*8+piece->point.x));
        locations.push_back(piece->point.y*8+piece->point.x);
    }
}

Piece* SDLHandler::getPiece(int32_t x, int32_t y){
    for(auto piece: SDLHandler::pieces){
        if(piece->point.x == x && piece->point.y == y)
            return piece;
    }
    Point empty;
    return new Piece(Type::TYPE_NONE, empty, Color::COLOR_NONE);

}

void SDLHandler::movePiece(Piece* piece, int32_t x, int32_t y){
    return;
}
