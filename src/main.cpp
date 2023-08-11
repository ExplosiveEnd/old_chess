#include <iostream>
#include <cstdint>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *win = SDL_CreateWindow("CHESS",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       1000, 1000, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, 0);

    SDL_Event event;

    // SDL_Surface *img = SDL_LoadBMP("src/chess_board2.bmp");

    // if(img == NULL){
    //     SDL_ShowSimpleMessageBox(0,"Background Init Error", SDL_GetError(), win);
    // }

    // SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, img);
    
    

    // SDL_RenderCopy(renderer, texture, NULL, NULL);
    
    
    
    

    bool isRunning = true;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        isRunning = false;
                        break;
                    }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        // Rectangle dimensions
        SDL_Rect x;
        x.x = 50;
        x.y = 50;
        x.h = 50;
        x.w = 50;

        // Colors rectangle
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

        //SDL_FillRect(SDL_Render)

    }
    // SDL_DestroyTexture(texture);
    // SDL_FreeSurface(img);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return EXIT_SUCCESS;
}

