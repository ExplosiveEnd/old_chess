#include <iostream>
#include <cstdint>

#include "SDLHandler.h"

namespace Chess{

    void run() {

        SDLHandler *handler = new SDLHandler();
        handler->initialize();

        SDL_Event event;

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
                handler->createBackground();
                handler->setPieces();

            }

        }
    }
}


int main(int argc, char *argv[])
{
    Chess::run();
    return EXIT_SUCCESS;
}

