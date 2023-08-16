#include <iostream>
#include <cstdint>
#include <string>

#ifdef _WIN32
    #include <shlobj.h>
    #pragma comment(lib, "Shell32.lib")
#endif


#include "SDLHandler.h"
#include "Game.h"

namespace Chess{
    void run() {
        // Initializes the handler / creates the event for polling
        SDLHandler *handler = new SDLHandler();
        Game* game = new Game();

        handler->initialize();


        SDL_Event event;

        // Creates the initial background / pieces
        handler->createBackground();
        game->createPieces(handler->renderer);
        handler->renderPieces(game->pieces);

        bool isRunning = true;
        
        Piece* selectedPiece;

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
                    case SDL_MOUSEBUTTONDOWN:
                        game->handleClick();

                        if (game->secondClick) {
                            handler->renderPossibleLocations(game->possibleLocations);
                        }
                        else {
                            SDL_RenderClear(handler->renderer);
                            handler->createBackground();
                            handler->renderPieces(game->pieces);
                            SDL_RenderPresent(handler->renderer);
                        }
                        
                        break;
                }
            }

            #ifdef __APPLE__
                handler->createBackground();
                handler->renderPieces(game->pieces);
            #endif
            

            // Renders page
            SDL_RenderPresent(handler->renderer);

        }

        SDL_DestroyWindow(handler->win);

        SDL_Quit();

    }


}


int main(int argc, char *argv[])
{
    Chess::run();
    return EXIT_SUCCESS;
}

