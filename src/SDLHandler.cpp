#include "SDLHandler.h"

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
                SDL_Rect square;
                square.x = height*j;
                square.y = width*i;
                square.w = width;
                square.h = height;

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

                SDL_RenderFillRect(renderer, &square);
            }

        }

        SDL_RenderPresent(renderer);
}
