#include "SDLHandler.h"
#include "Piece.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

void SDLHandler::initialize(){
    SDL_Init(SDL_INIT_EVERYTHING);
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

    
    for(int i = 0; i < 8; i++){
        // Creates starting point
        Point start;
        start.x = i;
        start.y = 1;
        
        // Adds piece information to pieces vector
        pieces.push_back(new Piece(Type::PAWN, start));

        // Gets sprite surface and displays
        SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, pieces[i]->getSprite(pieces[i]->type));
        SDL_RenderCopy(renderer, text, NULL, squares.at(i));
    }

    SDL_RenderPresent(renderer);
}
