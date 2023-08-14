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
    // Texture for surfaces
    SDL_Texture* text;

    // Starting position struct
    Point start;

    // Current index for piece placement
    int32_t current = 0;

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
            // Gets sprite surface and displays
            text = SDL_CreateTextureFromSurface(renderer, pieces[current]->getSprite(pieces[current]->type, pieces[current]->color));
            SDL_RenderCopy(renderer, text, NULL, squares.at(pieces[current]->point.y*8+pieces[current]->point.x));
            current++;
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
            
            // Gets sprite surface and displays
            text = SDL_CreateTextureFromSurface(renderer, pieces[current]->getSprite(pieces[current]->type, pieces[current]->color));
            SDL_RenderCopy(renderer, text, NULL, squares.at(pieces[current]->point.y*8+pieces[current]->point.x));
            current++;
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

            // Gets sprite surface and displays
            text = SDL_CreateTextureFromSurface(renderer, pieces[current]->getSprite(pieces[current]->type, pieces[current]->color));
            SDL_RenderCopy(renderer, text, NULL, squares.at(pieces[current]->point.y*8+pieces[current]->point.x));
            current++;
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

        // Gets sprite surface and displays
        text = SDL_CreateTextureFromSurface(renderer, pieces[current]->getSprite(pieces[current]->type, pieces[current]->color));
        SDL_RenderCopy(renderer, text, NULL, squares.at(pieces[current]->point.y*8+pieces[current]->point.x));
        current++;
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

        // Gets sprite surface and displays
        text = SDL_CreateTextureFromSurface(renderer, pieces[current]->getSprite(pieces[current]->type, pieces[current]->color));
        SDL_RenderCopy(renderer, text, NULL, squares.at(pieces[current]->point.y*8+pieces[current]->point.x));
        current++;
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
            text = SDL_CreateTextureFromSurface(renderer, pieces[current]->getSprite(pieces[current]->type, pieces[current]->color));
            SDL_RenderCopy(renderer, text, NULL, squares.at(pieces[current]->point.y*8+pieces[current]->point.x));
            current++;
        }
    }

    // Renders board + sprites
    SDL_RenderPresent(renderer);
}
