#include "SDLHandler.h"
#include "Piece.h"
#include <SDL_image.h>
#include <string>


constexpr int32_t SCREEN_WIDTH = 800;
constexpr int32_t SCREEN_HEIGHT = 800;

void SDLHandler::initialize(){

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    win = SDL_CreateWindow("CHESS",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(win, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);



}

void SDLHandler::createBackground(){

        std::cout << "Rendering BACKGROUND\n";

        // Background color
        int32_t width = SCREEN_WIDTH / 8;
        int32_t height = SCREEN_HEIGHT / 8;
        bool helper = false;

        if (!SDLHandler::squares.size()) {

            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    SDL_Rect* square = new SDL_Rect();
                    square->x = width * j;
                    square->y = height * i;
                    square->w = width;
                    square->h = height;

                    squares.push_back(square);

                    if (i % 2 == 0) {
                        if (j % 2 == 0) {
                            SDL_SetRenderDrawColor(renderer, 230, 204, 179, SDL_ALPHA_OPAQUE);
                        }
                        else {
                            SDL_SetRenderDrawColor(renderer, 172, 113, 57, SDL_ALPHA_OPAQUE);
                        }
                    }
                    else {
                        if (j % 2 != 0) {
                            SDL_SetRenderDrawColor(renderer, 230, 204, 179, SDL_ALPHA_OPAQUE);
                        }
                        else {
                            SDL_SetRenderDrawColor(renderer, 172, 113, 57, SDL_ALPHA_OPAQUE);
                        }
                    }

                    SDL_RenderFillRect(renderer, square);
                }

            }
        }
        else {
            for (int i = 0; i < SDLHandler::squares.size(); i++) {
                if (i % 8 == 0) {
                    helper = !helper;
                }
                if (i % 2 == 0) {
                    if (helper) {
                        SDL_SetRenderDrawColor(renderer, 230, 204, 179, SDL_ALPHA_OPAQUE);
                        SDL_RenderFillRect(renderer, squares.at(i));
                    }
                    else {
                        SDL_SetRenderDrawColor(renderer, 172, 113, 57, SDL_ALPHA_OPAQUE);
                        SDL_RenderFillRect(renderer, squares.at(i));
                    }
                }
                else {
                    if (helper) {
                        SDL_SetRenderDrawColor(renderer, 172, 113, 57, SDL_ALPHA_OPAQUE);
                        SDL_RenderFillRect(renderer, squares.at(i));
                    }
                    else {
                        SDL_SetRenderDrawColor(renderer, 230, 204, 179, SDL_ALPHA_OPAQUE);
                        SDL_RenderFillRect(renderer, squares.at(i));
                    }
                }
            }
        }

}

void SDLHandler::renderPieces(std::vector<Piece*> pieces){
    std::cout << "Rendering Pieces...\n" << "Size: " << pieces.size() << "\n";
    std::cout << "Pre-render pieces: ";
    for (const auto x : pieces) {
        std::cout << x->typeString << " ";
    }

    // Gets sprite surface and displays
    for (const auto& piece : pieces) {
        //std::cout << "Piece: " << piece->typeString << "\n";
        if (piece->type != TYPE_NONE) {
            SDL_RenderCopy(renderer, piece->sprite, NULL, squares.at(piece->point.y * 8 + piece->point.x));
        }
    }
}

void SDLHandler::renderPossibleLocations(std::vector<int> options) {
    std::cout << "Rendering possible locations... \n";
    SDL_SetRenderDrawColor(this->renderer, 255, 235, 153, SDL_ALPHA_OPAQUE);
    for (const int& location : options) {
        if(squares.at(location))
            SDL_RenderFillRect(renderer, this->squares.at(location));
    }
    SDL_RenderPresent(renderer);
}
