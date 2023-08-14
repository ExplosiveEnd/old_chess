#include "SDLHandler.h"
#include "Piece.h"
#include <SDL2/SDL_image.h>

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
    SDL_Texture* text;
    // Pawns
    for(int i = 0; i < 8; i++){
        // Creates starting point
        Point start;
        start.x = i;
        start.y = 6;
        
        // Adds piece information to pieces vector
        pieces.push_back(new Piece(Type::PAWN, start));

        // Gets sprite surface and displays
        text = SDL_CreateTextureFromSurface(renderer, pieces[i]->getSprite(pieces[i]->type));
        SDL_RenderCopy(renderer, text, NULL, squares.at(pieces[i]->point.y*8+pieces[i]->point.x));
    }

    // Rook
    for(int i = 0; i < 2; i++){
        Point start;
        if(i == 0){
            start.x = 0;
            start.y = 7;
        }
        else{
            start.x = 7;
            start.y = 7;
        }
        pieces.push_back(new Piece(Type::ROOK, start));
        
        // Gets sprite surface and displays
        text = SDL_CreateTextureFromSurface(renderer, pieces[i+8]->getSprite(pieces[i+8]->type));
        SDL_RenderCopy(renderer, text, NULL, squares.at(pieces[i+8]->point.y*8+pieces[i+8]->point.x));
    }

    // Bishop
    for(int i = 0; i < 2; i++){
        Point start;
        if(i == 0){
            start.x = 2;
            start.y = 7;
        }
        if(i == 1){
            start.x = 5;
            start.y = 7;
        }
        pieces.push_back(new Piece(Type::BISHOP, start));

        // Gets sprite surface and displays
        text = SDL_CreateTextureFromSurface(renderer, pieces[i+8+2]->getSprite(pieces[i+8+2]->type));
        SDL_RenderCopy(renderer, text, NULL, squares.at(pieces[i+8+2]->point.y*8+pieces[i+8+2]->point.x));
        
    }
    // Queen
    Point start;
    for(int i = 0; i < 1; i++){
        start.x = 4;
        start.y = 7;
        pieces.push_back(new Piece(Type::QUEEN, start));


        // Gets sprite surface and displays
        text = SDL_CreateTextureFromSurface(renderer, pieces[8+2+2+i]->getSprite(pieces[8+2+2+i]->type));
        SDL_RenderCopy(renderer, text, NULL, squares.at(pieces[8+2+2+i]->point.y*8+pieces[8+2+2+i]->point.x));
    }

    // King
    for(int i = 0; i < 1; i++){      
        start.x = 3;
        pieces.push_back(new Piece(Type::KING, start));

        // Gets sprite surface and displays
        text = SDL_CreateTextureFromSurface(renderer, pieces[8+2+2+1+i]->getSprite(pieces[8+2+2+1+i]->type));
        SDL_RenderCopy(renderer, text, NULL, squares.at(pieces[8+2+2+1+i]->point.y*8+pieces[8+2+2+1+i]->point.x));
    }

    // Knights
    for(int i = 0; i < 2; i++){
        if(i == 0){
            start.x = 1;
            start.y = 7;
        }
        else{
            start.x = 6;
            start.y = 7;
        }
        pieces.push_back(new Piece(Type::KNIGHT, start));

        text = SDL_CreateTextureFromSurface(renderer, pieces[8+2+2+1+1+i]->getSprite(pieces[8+2+2+1+1+i]->type));
        SDL_RenderCopy(renderer, text, NULL, squares.at(pieces[8+2+2+1+1+i]->point.y*8+pieces[8+2+2+1+1+i]->point.x));
    }



        


    // Renders board + sprites
    SDL_RenderPresent(renderer);
}
