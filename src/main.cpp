#include <iostream>
#include <cstdint>
#include <string>

#include <shlobj.h>
#pragma comment(lib, "Shell32.lib")

#include "SDLHandler.h"

namespace Chess{
    void run() {
        // Initializes the handler / creates the event for polling
        SDLHandler *handler = new SDLHandler();
        handler->initialize();

        SDL_Event event;

        // Creates the initial background / pieces
        handler->createBackground();
        handler->setPieces();
        

        bool isRunning = true;
        int32_t mouseX = -1, mouseY = -1;
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
                        if(mouseX != -1 && mouseY != -1){
                            int32_t nextClickX, nextClickY;
            
                            SDL_GetMouseState(&nextClickX, &nextClickY);
                            nextClickX = int(nextClickX/100);
                            nextClickY = int(nextClickY/100);
                            std::cout << "Next Click: (" << nextClickX << ", " << nextClickY << ") \n";
                            std::cout << "Piece: " << selectedPiece->typeString << "\n";
                            selectedPiece->point.x = nextClickX;
                            selectedPiece->point.y = nextClickY;
                            
                            mouseX = -1;
                            mouseY = -1;
                            SDL_RenderClear(handler->renderer);
                            handler->createBackground();
                            handler->renderPieces();
                        }    
                        else{
                            SDL_GetMouseState(&mouseX, &mouseY);
                            mouseX = int(mouseX/100);
                            mouseY = int(mouseY/100);
                            selectedPiece = handler->getPiece(mouseX, mouseY);
                            std::cout << "Point: (" << mouseX << ", " << mouseY <<")\n"; 
                            std::cout << "Piece: " << selectedPiece->typeString << "\n";
                        }
                        break;
                }
            }

            

            

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

