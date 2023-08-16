#include "Game.h"

void Game::createPieces(SDL_Renderer* renderer) {
    if (!pieces.size()) {
        Point start;

        // Pawns
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 8; j++) {
                if (i == 0) {
                    // Creates starting point
                    start.x = j;
                    start.y = 6;

                    // Adds piece information to pieces vector
                    pieces.push_back(new Piece(Type::PAWN, start, Color::BLACK));

                }
                else {
                    start.x = j;
                    start.y = 1;

                    pieces.push_back(new Piece(Type::PAWN, start, Color::WHITE));
                }
            }
        }

        // Rook
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                if (i == 0) {
                    if (j == 0) {
                        start.x = 0;
                        start.y = 7;
                    }
                    else {
                        start.x = 7;
                        start.y = 7;
                    }
                    pieces.push_back(new Piece(Type::ROOK, start, Color::BLACK));
                }
                else {
                    if (j == 0) {
                        start.x = 0;
                        start.y = 0;
                    }
                    else {
                        start.x = 7;
                        start.y = 0;
                    }
                    pieces.push_back(new Piece(Type::ROOK, start, Color::WHITE));
                }

            }
        }

        // Bishop
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                if (i == 0) {
                    if (j == 0) {
                        start.x = 2;
                        start.y = 7;
                    }
                    else {
                        start.x = 5;
                        start.y = 7;
                    }
                    pieces.push_back(new Piece(Type::BISHOP, start, Color::BLACK));
                }
                else {
                    if (j == 0) {
                        start.x = 2;
                        start.y = 0;
                    }
                    else {
                        start.x = 5;
                        start.y = 0;
                    }
                    pieces.push_back(new Piece(Type::BISHOP, start, Color::WHITE));
                }
            }
        }

        // Queen
        for (int i = 0; i < 2; i++) {
            if (i == 0) {
                start.x = 4;
                start.y = 7;
                pieces.push_back(new Piece(Type::QUEEN, start, Color::BLACK));
            }
            else {
                start.x = 4;
                start.y = 0;
                pieces.push_back(new Piece(Type::QUEEN, start, Color::WHITE));
            }
        }

        // King
        for (int i = 0; i < 2; i++) {
            if (i == 0) {
                start.x = 3;
                start.y = 7;
                pieces.push_back(new Piece(Type::KING, start, Color::BLACK));
            }
            else {
                start.x = 3;
                start.y = 0;
                pieces.push_back(new Piece(Type::KING, start, Color::WHITE));
            }
        }

        // Knights
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                if (i == 0) {
                    start.y = 7;
                    if (j == 0)
                        start.x = 1;
                    else
                        start.x = 6;

                    pieces.push_back(new Piece(Type::KNIGHT, start, Color::BLACK));
                }
                else {
                    start.y = 0;
                    if (j == 0)
                        start.x = 1;
                    else
                        start.x = 6;

                    pieces.push_back(new Piece(Type::KNIGHT, start, Color::WHITE));
                }
            }
        }
        

        for (auto piece : Game::pieces) {
            text = SDL_CreateTextureFromSurface(renderer, piece->getSprite(piece->type, piece->color));
            piece->sprite = text;
            this->coords.at(piece->point.y * 8 + piece->point.x) = piece;
        }

        Point empty;

        std::cout << "Pieces using COORDS vector: \n";

        for (int i = 0; i < 64; i++) {
            if (!coords.at(i)) {
                empty.x = i%8;
                empty.y = i/10;
                // Creates empty piece if none with the coordinates are found (empty space)
                auto piece = new Piece(Type::TYPE_NONE, empty, Color::COLOR_NONE);
                pieces.push_back(piece);
                coords.at(i) = piece;
            }
            std::cout << "Piece of type: " << coords.at(i)->typeString << " at " << i << "\n";
        }
    }

}

Piece* Game::getPiece(int32_t x, int32_t y) {
    for (auto piece : Game::pieces) {
        if (piece->point.x == x && piece->point.y == y)
            return piece;
    }

    //Point empty;
    //empty.x = -1;
    //empty.y = -1;

    //// Creates empty piece if none with the coordinates are found (empty space)
    //auto piece = new Piece(Type::TYPE_NONE, empty, Color::COLOR_NONE);
    //pieces.push_back(piece);

}

void Game::handleClick(){
    if(this->mouseX == -1 && this->mouseY == -1){
        SDL_GetMouseState(&this->mouseX, &this->mouseY);
        this->mouseX = int(this->mouseX/100);
        this->mouseY = int(this->mouseY/100);
        this->selectedPiece = this->getPiece(this->mouseX, this->mouseY);
        std::cout << "First Click: (" << mouseX << ", " << mouseY <<")\n"; 
        std::cout << "Piece: " << selectedPiece->typeString << "\n";
        this->secondClick = true;
        this->setPossibleLocations(this->selectedPiece);
    }
    else{
        Game::movePiece(this->selectedPiece);
    }
}

void Game::movePiece(Piece* piece){
    if(this->mouseX != -1 && this->mouseY != -1 && piece->type != TYPE_NONE){
        int32_t nextClickX, nextClickY;

        SDL_GetMouseState(&nextClickX, &nextClickY);
        nextClickX = int(nextClickX/100);
        nextClickY = int(nextClickY/100);
        std::cout << "Second Click: (" << nextClickX << ", " << nextClickY << ") \n";
        std::cout << "Piece: " << selectedPiece->typeString << "\n";
        Game::selectedPiece->point.x = nextClickX;
        Game::selectedPiece->point.y = nextClickY;

        this->mouseX = -1;
        this->mouseY = -1;   
        this->secondClick = false;
    }
}

void Game::setPossibleLocations(Piece* selected) {
    std::cout << "Possible Locations: ";
    for (int i = 0; i < 64; i++) {
        //std::cout << "Piece type: " << coords.at(i)->typeString << " at " << i << "\n";
        if (this->coords.at(i)->type == TYPE_NONE) {
            this->possibleLocations.push_back(i);
        }
    }
    std::cout << std::endl;
}