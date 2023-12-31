#include "Game.h"


void Game::createPieces(SDL_Renderer* renderer) {
    bool isZero = true;
    for (const auto loc : coords) {
        if (loc != 0)
            isZero = false;
    }

    if (isZero) {
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
        
        // Ties texture to Piece* and populates coords vector
        for (auto piece : pieces) {
            text = SDL_CreateTextureFromSurface(renderer, piece->getSprite(piece->type, piece->color));
            piece->sprite = text;
            this->coords.at(piece->point.y * 8 + piece->point.x) = piece;
        }


        // Fills empty locations in coords vector with TYPE_NONE pieces.
        Point empty;
        std::cout << "Pieces using COORDS vector: \n";

        for (int i = 0; i < 64; i++) {
            if (!coords.at(i)) {
                empty.x = i%8;
                empty.y = i/8;
                // Creates empty piece if none with the coordinates are found (empty space)
                auto piece = new Piece(Type::TYPE_NONE, empty, Color::COLOR_NONE);
                pieces.push_back(piece);
                this->coords.at(i) = piece;
            }
            //std::cout << "Piece of type: " << this->coords.at(i)->typeString << " at " << i << "\n";
        }
        //std::cout << "Pre-sort: ";
        //for (const auto& x : coords) {
        //    std::cout << x->typeString << " -> (" << x->point.x << ", " << x->point.y << ")\n";
        //}

        //std::sort(this->coords.begin(), this->coords.end(), less_than_point());
        //std::cout << "\nPost-sort: ";
        //for (const auto& x : coords) {
        //    std::cout << x->typeString << " -> (" << x->point.x << ", " << x->point.y << ")\n";
        //}
    }

}

Piece* Game::getPiece(int32_t x, int32_t y) {
    for (auto piece : this->coords) {
        if (piece->point.x == x && piece->point.y == y)
            return piece;
    }
}

void Game::handleClick(){
    if(!secondClick){
        SDL_GetMouseState(&this->mouseX, &this->mouseY);
        this->mouseX = int(this->mouseX/100);
        this->mouseY = int(this->mouseY/100);
        this->selectedPiece = this->getPiece(this->mouseX, this->mouseY);

        if (selectedPiece->type != TYPE_NONE) {
            std::cout << "First Click: (" << mouseX << ", " << mouseY << ")\n";
            std::cout << "Piece: " << selectedPiece->typeString << "\n";
            this->secondClick = true;
            this->setPossibleLocations(this->selectedPiece);
        }
        else {
            this->mouseX = -1;
            this->mouseY = -1;
        }
    }
    else{
        Game::movePiece(this->selectedPiece);
        this->possibleLocations.clear();
        this->possibleKills.clear();
    }
}

void Game::movePiece(Piece* piece){

    if (piece->color == this->turn) {
        int32_t nextClickX, nextClickY;

        SDL_GetMouseState(&nextClickX, &nextClickY);
        nextClickX = int(nextClickX / 100);
        nextClickY = int(nextClickY / 100);
        std::cout << "Second Click: (" << nextClickX << ", " << nextClickY << ") \n";
        std::cout << "Piece: " << this->selectedPiece->typeString << "\n";

        int32_t oldX = piece->point.x;
        int32_t oldY = piece->point.y;


        auto replaced = coords.at(nextClickY * 8 + nextClickX);
        std::cout << "Replacing " << replaced->typeString << std::endl;

        // Ensures the second click is a validMove (EMPTY target)
        auto it = std::find(this->possibleLocations.begin(), this->possibleLocations.end(), nextClickY * 8 + nextClickX);
        if (it != possibleLocations.end()) {
            std::cout << "FOUND IT";
            piece->point.x = nextClickX;
            piece->point.y = nextClickY;

            replaced->point.x = oldX;
            replaced->point.y = oldY;
            piece->pawnFirstMove = false;
            this->turn = this->turn == Color::BLACK ? Color::WHITE : Color::BLACK;
        }

        Point em;


        if (possibleKills.size()) {
            it = std::find(this->possibleKills.begin(), this->possibleKills.end(), nextClickY * 8 + nextClickX);
            if (it != possibleKills.end()) {
                em.x = replaced->point.x;
                em.y = replaced->point.y;

                replaced = new Piece(Type::TYPE_NONE, em, Color::COLOR_NONE);

                coords.at(replaced->point.y * 8 + replaced->point.x) = replaced;

                replaced->point.x = oldX;
                replaced->point.y = oldY;
                sortCoords();

                piece->point.x = nextClickX;
                piece->point.y = nextClickY;
                this->turn = this->turn == Color::BLACK ? Color::WHITE : Color::BLACK;
            }
        }
    }

    //std::sort(this->coords.begin(), this->coords.end(), less_than_point());
    //std::cout << "\nPost-move: ";

    //for (const auto& x : coords) {
    //    std::cout << x->typeString << " -> (" << x->point.x << ", " << x->point.y << ")\n";
    //}

    this->mouseX = -1;
    this->mouseY = -1;   
    this->secondClick = false;

    sortCoords();
   
}

void Game::setPossibleLocations(Piece* selected) {
    std::cout << "Possible Locations: ";
    for (int i = 0; i < 64; i++) {
        switch (selected->type) {
        case(Type::PAWN):
            if (selected->color == Color::BLACK) {
                // Checks if pawn can move up two / one
                if (selected->pawnFirstMove) {
                    // TOP-LEFT ENEMY CHECK FIRST MOVE
                    if (coords.at((selected->point.y - 1) * 8 + selected->point.x - 1)->type != Type::TYPE_NONE
                        && coords.at((selected->point.y - 1) * 8 + selected->point.x - 1)->color != selected->color) {
                        this->possibleKills.push_back((selected->point.y - 2) * 8 + selected->point.x - 1);
                    }

                    // TOP-RIGHT ENEMY CHECK FIRST MOVE
                    if (coords.at((selected->point.y - 1) * 8 + selected->point.x + 1)->type != Type::TYPE_NONE
                        && coords.at((selected->point.y - 1) * 8 + selected->point.x + 1)->color != selected->color) {
                        this->possibleKills.push_back((selected->point.y - 1) * 8 + selected->point.x + 1);
                    }

                    // FORWARD CHECK (one space)
                    if (coords.at((selected->point.y - 1) * 8 + selected->point.x)->type == Type::TYPE_NONE) {
                        // FORWARD CHECK (two spaces)
                        if (coords.at((selected->point.y - 2) * 8 + selected->point.x)->type == Type::TYPE_NONE)
                            this->possibleLocations.push_back((selected->point.y - 2) * 8 + selected->point.x);
                        this->possibleLocations.push_back((selected->point.y - 1) * 8 + selected->point.x);
                    }
                }
                else {
                    // Checks if pawn is at END
                    if (selected->point.y == 0) {
                        break;
                    }
                    else {
                        // TOP-LEFT ENEMY CHECK
                        if (coords.at((selected->point.y - 1) * 8 + selected->point.x + 1)->type != Type::TYPE_NONE
                            && coords.at((selected->point.y - 1) * 8 + selected->point.x + 1)->color != selected->color) {
                            this->possibleKills.push_back((selected->point.y - 1) * 8 + selected->point.x + 1);

                        }
                        // TOP-RIGHT ENEMY CHECK
                        if (coords.at((selected->point.y - 1) * 8 + selected->point.x - 1)->type != Type::TYPE_NONE
                            && coords.at((selected->point.y - 1) * 8 + selected->point.x - 1)->color != selected->color) {
                            this->possibleKills.push_back((selected->point.y - 1) * 8 + selected->point.x - 1);

                        }
                        // FORWARD CHECK
                        if (coords.at((selected->point.y - 1) * 8 + selected->point.x)->type == Type::TYPE_NONE)
                            this->possibleLocations.push_back((selected->point.y - 1) * 8 + selected->point.x);
                    }
                }
            }
            else if(selected->color == Color::WHITE) {
                // Checks if pawn can move up two / one
                if (selected->pawnFirstMove) {
                    // BOTTOM-LEFT ENEMY CHECK FIRST MOVE
                    if (coords.at((selected->point.y + 1) * 8 + selected->point.x - 1)->type != Type::TYPE_NONE
                        && coords.at((selected->point.y + 1) * 8 + selected->point.x - 1)->color != selected->color) {
                        this->possibleKills.push_back((selected->point.y + 1) * 8 + selected->point.x - 1);
                    }

                    // BOTTOM-RIGHT ENEMY CHECK FIRST MOVE
                    if (coords.at((selected->point.y + 1) * 8 + selected->point.x + 1)->type != Type::TYPE_NONE
                        && coords.at((selected->point.y + 1) * 8 + selected->point.x + 1)->color != selected->color) {
                        this->possibleKills.push_back((selected->point.y + 1) * 8 + selected->point.x + 1);
                    }

                    // FORWARD CHECK (one space)
                    if (coords.at((selected->point.y + 1) * 8 + selected->point.x)->type == Type::TYPE_NONE) {
                        // FORWARD CHECK (two spaces)
                        if (coords.at((selected->point.y + 2) * 8 + selected->point.x)->type == Type::TYPE_NONE)
                            this->possibleLocations.push_back((selected->point.y + 2) * 8 + selected->point.x);
                        this->possibleLocations.push_back((selected->point.y + 1) * 8 + selected->point.x);
                    }
                }
                else {
                    // Checks if pawn is at END
                    if (selected->point.y == 7) {
                        break;
                    }

                    // TOP-LEFT ENEMY CHECK
                    if (coords.at((selected->point.y + 1) * 8 + selected->point.x + 1)->type != Type::TYPE_NONE
                        && coords.at((selected->point.y + 1) * 8 + selected->point.x + 1)->color != selected->color) {
                        this->possibleKills.push_back((selected->point.y + 1) * 8 + selected->point.x + 1);

                    }
                    // TOP-RIGHT ENEMY CHECK
                    if (coords.at((selected->point.y + 1) * 8 + selected->point.x - 1)->type != Type::TYPE_NONE
                        && coords.at((selected->point.y + 1) * 8 + selected->point.x - 1)->color != selected->color) {
                        this->possibleKills.push_back((selected->point.y + 1) * 8 + selected->point.x - 1);

                    }
                    // FORWARD CHECK
                    if (coords.at((selected->point.y + 1) * 8 + selected->point.x)->type == Type::TYPE_NONE)
                        this->possibleLocations.push_back((selected->point.y + 1) * 8 + selected->point.x);
                }
            }
            break;

        case(Type::ROOK):
        {
            int32_t yClone = selected->point.y;
            int32_t xClone = selected->point.x;
            
            // ABOVE
            while (yClone >= 0) {
                // Ensures not itself
                if (yClone != selected->point.y) {
                    // Makes sure kill is on a real piece
                    if (coords.at(yClone * 8 + selected->point.x)->type != Type::TYPE_NONE) {
                        // Makes sure piece is enemy
                        if(coords.at(yClone * 8 + selected->point.x)->color != selected->color)
                            this->possibleKills.push_back(yClone * 8 + selected->point.x);
                        break;
                    }
                    this->possibleLocations.push_back(yClone * 8 + selected->point.x);
                }   
                yClone--;
            }

            // BELOW
            yClone = selected->point.y;
            while (yClone <= 7) {
                if (yClone != selected->point.y) {
                    if (coords.at(yClone * 8 + selected->point.x)->type != Type::TYPE_NONE) {
                        if (coords.at(yClone * 8 + selected->point.x)->color != selected->color)
                            this->possibleKills.push_back(yClone * 8 + selected->point.x);
                        break;
                    }
                    this->possibleLocations.push_back(yClone * 8 + selected->point.x);
                }
 
                yClone++;
            }
            // LEFT
            while (xClone >= 0) {
                if (xClone != selected->point.x) {
                    if (coords.at(selected->point.y * 8 + xClone)->type != Type::TYPE_NONE) {
                        if (coords.at(selected->point.y * 8 + xClone)->color != selected->color)
                            this->possibleKills.push_back(selected->point.y * 8 + xClone);
                        break;
                    }
                    this->possibleLocations.push_back(selected->point.y * 8 + xClone);
                }   
                xClone--;
            }
            // RIGHT
            xClone = selected->point.x;
            while (xClone <= 7) {
                if (xClone != selected->point.x) {
                    if (coords.at(selected->point.y * 8 + xClone)->type != Type::TYPE_NONE) {
                        if (coords.at(selected->point.y * 8 + xClone)->color != selected->color)
                            this->possibleKills.push_back(selected->point.y * 8 + xClone);
                        break;
                    }
                    this->possibleLocations.push_back(selected->point.y * 8 + xClone);
                }
                xClone++;
            }
        }
            break;
        case(Type::BISHOP):
        {
            // North-West
            int32_t yClone = selected->point.y;
            int32_t xClone = selected->point.x;
            while (yClone > 0 && xClone > 0) {
                if (coords.at((yClone - 1) * 8 + (xClone - 1))->type != Type::TYPE_NONE) {
                    if (coords.at((yClone - 1) * 8 + (xClone - 1))->color != selected->color)
                        this->possibleKills.push_back((yClone - 1) * 8 + (xClone - 1));
                    break;
                }
                this->possibleLocations.push_back((yClone - 1) * 8 + (xClone - 1));
                yClone--;
                xClone--;
            }


            // North-East
            yClone = selected->point.y;
            xClone = selected->point.x;
            while (yClone > 0 && xClone < 7) {
                if (coords.at((yClone - 1) * 8 + (xClone + 1))->type != Type::TYPE_NONE) {
                    if (coords.at((yClone - 1) * 8 + (xClone + 1))->color != selected->color)
                        this->possibleKills.push_back((yClone - 1) * 8 + (xClone + 1));
                    break;
                }
                this->possibleLocations.push_back((yClone - 1) * 8 + (xClone + 1));
                yClone--;
                xClone++;
            }


            // South-West
            yClone = selected->point.y;
            xClone = selected->point.x;
            while (yClone < 7 && xClone > 0) {
                if (coords.at((yClone + 1) * 8 + (xClone - 1))->type != Type::TYPE_NONE) {
                    if (coords.at((yClone + 1) * 8 + (xClone - 1))->color != selected->color)
                        this->possibleKills.push_back((yClone + 1) * 8 + (xClone - 1));
                    break;
                }
                this->possibleLocations.push_back((yClone + 1) * 8 + (xClone - 1));
                yClone++;
                xClone--;
            }

            // South-East
            yClone = selected->point.y;
            xClone = selected->point.x;
            while (yClone < 7 && xClone < 7) {
                if (coords.at((yClone + 1) * 8 + (xClone + 1))->type != Type::TYPE_NONE) {
                    if (coords.at((yClone + 1) * 8 + (xClone + 1))->color != selected->color)
                        this->possibleKills.push_back((yClone + 1) * 8 + (xClone + 1));
                    break;
                }
                this->possibleLocations.push_back((yClone + 1) * 8 + (xClone + 1));
                yClone++;
                xClone++;
            }
        }
        break;

        case(Type::KING):
            // ABOVE
            if (selected->point.y > 0) {
                // TOP-LEFT
                if (selected->point.x > 0 && coords.at((selected->point.y - 1) * 8 + (selected->point.x - 1))->type == Type::TYPE_NONE)
                    this->possibleLocations.push_back((selected->point.y - 1) * 8 + (selected->point.x-1));
                // ENEMY TOP-LEFT 
                else if (coords.at((selected->point.y - 1) * 8 + (selected->point.x - 1))->color != selected->color) 
                        this->possibleKills.push_back((selected->point.y - 1) * 8 + (selected->point.x - 1));

                // TOP-RIGHT
                if(selected->point.x < 7 && coords.at((selected->point.y - 1) * 8 + (selected->point.x + 1))->type == Type::TYPE_NONE)
                    this->possibleLocations.push_back((selected->point.y - 1) * 8 + (selected->point.x + 1));
                // ENEMY TOP-RIGHT
                else if (coords.at((selected->point.y - 1) * 8 + (selected->point.x + 1))->color != selected->color)
                        this->possibleKills.push_back((selected->point.y - 1) * 8 + (selected->point.x + 1));

                // FORWARD
                if (coords.at((selected->point.y - 1) * 8 + selected->point.x)->type == Type::TYPE_NONE)
                    this->possibleLocations.push_back((selected->point.y - 1) * 8 + selected->point.x);
                // ENEMY FORWARD
                else if (coords.at((selected->point.y - 1) * 8 + selected->point.x)->color != selected->color)
                    this->possibleKills.push_back((selected->point.y - 1) * 8 + selected->point.x);
            }
            // BELOW
            if (selected->point.y < 7) {
                // BOTTOM-LEFT
                if (selected->point.x > 0 && coords.at((selected->point.y + 1) * 8 + (selected->point.x - 1))->type == Type::TYPE_NONE)
                    this->possibleLocations.push_back((selected->point.y + 1) * 8 + (selected->point.x - 1));
                // ENEMY BOTTOM-LEFT
                else if (coords.at((selected->point.y + 1) * 8 + (selected->point.x - 1))->color != selected->color)
                    this->possibleKills.push_back((selected->point.y + 1) * 8 + (selected->point.x - 1));
                // BOTTOM-RIGHT
                if (selected->point.x < 7 && coords.at((selected->point.y + 1) * 8 + (selected->point.x + 1))->type == Type::TYPE_NONE)
                    this->possibleLocations.push_back((selected->point.y + 1) * 8 + (selected->point.x + 1));
                // ENEMY BOTTOM-RIGHT
                else if (coords.at((selected->point.y + 1) * 8 + (selected->point.x + 1))->color != selected->color)
                    this->possibleKills.push_back((selected->point.y + 1) * 8 + (selected->point.x + 1));

                // BEHIND
                if(coords.at((selected->point.y + 1) * 8 + selected->point.x)->type == Type::TYPE_NONE)
                    this->possibleLocations.push_back((selected->point.y + 1) * 8 + selected->point.x);
                // ENEMY BEHIND
                else if(coords.at((selected->point.y + 1) * 8 + selected->point.x)->color != selected->color)
                    this->possibleKills.push_back((selected->point.y + 1) * 8 + selected->point.x);
            }
            // LEFT
            if (selected->point.x > 0) {
                if(coords.at(selected->point.y * 8 + (selected->point.x - 1))->type == Type::TYPE_NONE)
                    this->possibleLocations.push_back(selected->point.y * 8 + (selected->point.x - 1));
                // ENEMY LEFT
                else if (coords.at(selected->point.y * 8 + (selected->point.x - 1))->color != selected->color) 
                    this->possibleKills.push_back(selected->point.y * 8 + (selected->point.x - 1));
                
            }
            // RIGHT
            if (selected->point.x < 7) {
                if (coords.at(selected->point.y * 8 + (selected->point.x + 1))->type == Type::TYPE_NONE)
                    this->possibleLocations.push_back(selected->point.y * 8 + (selected->point.x + 1));
                else if (coords.at(selected->point.y * 8 + (selected->point.x + 1))->color != selected->color)
                    this->possibleKills.push_back(selected->point.y * 8 + (selected->point.x + 1));
            }
            break;

        case(Type::KNIGHT):
            // ABOVE CHECK
            if (selected->point.y > 1) {
                // ABOVE-LEFT
                if (selected->point.x > 0 && coords.at((selected->point.y - 2) * 8 + (selected->point.x - 1))->type == Type::TYPE_NONE)
                    this->possibleLocations.push_back((selected->point.y - 2) * 8 + (selected->point.x - 1));
                // ENEMY TOP-LEFT
                else if (selected->point.x > 0 && coords.at((selected->point.y - 2) * 8 + (selected->point.x - 1))->color != selected->color)
                    this->possibleKills.push_back((selected->point.y - 2) * 8 + (selected->point.x - 1));

                // ABOVE-RIGHT
                if (selected->point.x < 7 && coords.at((selected->point.y - 2) * 8 + (selected->point.x + 1))->type == Type::TYPE_NONE)
                    this->possibleLocations.push_back((selected->point.y - 2) * 8 + (selected->point.x + 1));
                else if (selected->point.x < 7 && coords.at((selected->point.y - 2) * 8 + (selected->point.x + 1))->color != selected->color)
                    this->possibleKills.push_back((selected->point.y - 2) * 8 + (selected->point.x + 1));
            }
            // BELOW CHECK
            if (selected->point.y < 6) {
                // BELOW-LEFT
                if (selected->point.x > 0 && coords.at((selected->point.y + 2) * 8 + (selected->point.x - 1))->type == Type::TYPE_NONE)
                    this->possibleLocations.push_back((selected->point.y + 2) * 8 + (selected->point.x - 1));
                else if (selected->point.x > 0 && coords.at((selected->point.y + 2) * 8 + (selected->point.x - 1))->color != selected->color)
                    this->possibleKills.push_back((selected->point.y + 2) * 8 + (selected->point.x - 1));

                // BELOW-RIGHT
                if (selected->point.x < 7 && coords.at((selected->point.y + 2) * 8 + (selected->point.x + 1))->type == Type::TYPE_NONE)
                    this->possibleLocations.push_back((selected->point.y + 2) * 8 + (selected->point.x + 1));
                else if (selected->point.x < 7 && coords.at((selected->point.y + 2) * 8 + (selected->point.x + 1))->color != selected->color)
                    this->possibleKills.push_back((selected->point.y + 2) * 8 + (selected->point.x + 1));
            }
            // LEFT CHECK
            if (selected->point.x > 1) {
                // LEFT-ABOVE
                if (selected->point.y > 0 && coords.at((selected->point.y - 1) * 8 + (selected->point.x - 2))->type == Type::TYPE_NONE)
                    this->possibleLocations.push_back((selected->point.y - 1) * 8 + (selected->point.x - 2));
                else if (selected->point.y > 0 && coords.at((selected->point.y - 1) * 8 + (selected->point.x - 2))->color != selected->color)
                    this->possibleKills.push_back((selected->point.y - 1) * 8 + (selected->point.x - 2));

                // LEFT-BELOW
                if (selected->point.y < 7 && coords.at((selected->point.y + 1) * 8 + (selected->point.x - 2))->type == Type::TYPE_NONE)
                    this->possibleLocations.push_back((selected->point.y + 1) * 8 + (selected->point.x - 2));
                // ENEMY LEFT-BELOW
                else if (selected->point.y < 7 && coords.at((selected->point.y + 1) * 8 + (selected->point.x - 2))->color != selected->color)
                    this->possibleKills.push_back((selected->point.y + 1) * 8 + (selected->point.x - 2));

            }
            // RIGHT CHECK
            if (selected->point.x < 6) {
                // RIGHT-ABOVE
                if (selected->point.y > 0 && coords.at((selected->point.y - 1) * 8 + (selected->point.x + 2))->type == Type::TYPE_NONE)
                    this->possibleLocations.push_back((selected->point.y - 1) * 8 + (selected->point.x + 2));
                // ENEMY RIGHT-ABOVE
                else if (selected->point.y > 0 && coords.at((selected->point.y - 1) * 8 + (selected->point.x + 2))->color != selected->color)
                    this->possibleKills.push_back((selected->point.y - 1) * 8 + (selected->point.x + 2));

                // RIGHT-BELOW
                if (selected->point.y < 7 && coords.at((selected->point.y + 1) * 8 + (selected->point.x + 2))->type == Type::TYPE_NONE)
                    this->possibleLocations.push_back((selected->point.y + 1) * 8 + (selected->point.x + 2));
                else if (selected->point.y < 7 && coords.at((selected->point.y + 1) * 8 + (selected->point.x + 2))->color != selected->color)
                    this->possibleKills.push_back((selected->point.y + 1) * 8 + (selected->point.x + 2));
            }
            break;

        case(Type::QUEEN):
            // BISHOP ABILITIES
        {
            // North-West
            int32_t yClone = selected->point.y;
            int32_t xClone = selected->point.x;
            while (yClone > 0 && xClone > 0) {
                if (coords.at((yClone - 1) * 8 + (xClone - 1))->type != Type::TYPE_NONE) {
                    if (coords.at((yClone - 1) * 8 + (xClone - 1))->color != selected->color)
                        this->possibleKills.push_back((yClone - 1) * 8 + (xClone - 1));
                    break;
                }
                this->possibleLocations.push_back((yClone - 1) * 8 + (xClone - 1));
                yClone--;
                xClone--;
            }


            // North-East
            yClone = selected->point.y;
            xClone = selected->point.x;
            while (yClone > 0 && xClone < 7) {
                if (coords.at((yClone - 1) * 8 + (xClone + 1))->type != Type::TYPE_NONE) {
                    if (coords.at((yClone - 1) * 8 + (xClone + 1))->color != selected->color)
                        this->possibleKills.push_back((yClone - 1) * 8 + (xClone + 1));
                    break;
                }
                this->possibleLocations.push_back((yClone - 1) * 8 + (xClone + 1));
                yClone--;
                xClone++;
            }


            // South-West
            yClone = selected->point.y;
            xClone = selected->point.x;
            while (yClone < 7 && xClone > 0) {
                if (coords.at((yClone + 1) * 8 + (xClone - 1))->type != Type::TYPE_NONE) {
                    if (coords.at((yClone + 1) * 8 + (xClone - 1))->color != selected->color)
                        this->possibleKills.push_back((yClone + 1) * 8 + (xClone - 1));
                    break;
                }
                this->possibleLocations.push_back((yClone + 1) * 8 + (xClone - 1));
                yClone++;
                xClone--;
            }

            // South-East
            yClone = selected->point.y;
            xClone = selected->point.x;
            while (yClone < 7 && xClone < 7) {
                if (coords.at((yClone + 1) * 8 + (xClone + 1))->type != Type::TYPE_NONE) {
                    if (coords.at((yClone + 1) * 8 + (xClone + 1))->color != selected->color)
                        this->possibleKills.push_back((yClone + 1) * 8 + (xClone + 1));
                    break;
                }
                this->possibleLocations.push_back((yClone + 1) * 8 + (xClone + 1));
                yClone++;
                xClone++;
            }
        }

            // ROOK ABILITIES
        {
            int32_t yClone = selected->point.y;
            int32_t xClone = selected->point.x;

            // ABOVE
            while (yClone >= 0) {
                // Ensures not itself
                if (yClone != selected->point.y) {
                    // Makes sure kill is on a real piece
                    if (coords.at(yClone * 8 + selected->point.x)->type != Type::TYPE_NONE) {
                        // Makes sure piece is enemy
                        if (coords.at(yClone * 8 + selected->point.x)->color != selected->color)
                            this->possibleKills.push_back(yClone * 8 + selected->point.x);
                        break;
                    }
                    this->possibleLocations.push_back(yClone * 8 + selected->point.x);
                }
                yClone--;
            }

            // BELOW
            yClone = selected->point.y;
            while (yClone <= 7) {
                if (yClone != selected->point.y) {
                    if (coords.at(yClone * 8 + selected->point.x)->type != Type::TYPE_NONE) {
                        if (coords.at(yClone * 8 + selected->point.x)->color != selected->color)
                            this->possibleKills.push_back(yClone * 8 + selected->point.x);
                        break;
                    }
                    this->possibleLocations.push_back(yClone * 8 + selected->point.x);
                }

                yClone++;
            }
            // LEFT
            while (xClone >= 0) {
                if (xClone != selected->point.x) {
                    if (coords.at(selected->point.y * 8 + xClone)->type != Type::TYPE_NONE) {
                        if (coords.at(selected->point.y * 8 + xClone)->color != selected->color)
                            this->possibleKills.push_back(selected->point.y * 8 + xClone);
                        break;
                    }
                    this->possibleLocations.push_back(selected->point.y * 8 + xClone);
                }
                xClone--;
            }
            // RIGHT
            xClone = selected->point.x;
            while (xClone <= 7) {
                if (xClone != selected->point.x) {
                    if (coords.at(selected->point.y * 8 + xClone)->type != Type::TYPE_NONE) {
                        if (coords.at(selected->point.y * 8 + xClone)->color != selected->color)
                            this->possibleKills.push_back(selected->point.y * 8 + xClone);
                        break;
                    }
                    this->possibleLocations.push_back(selected->point.y * 8 + xClone);
                }
                xClone++;
            }
        }
            break;

        default:
            if (this->coords.at(i)->type == TYPE_NONE) {
                this->possibleLocations.push_back(i);
                std::cout << i << " ";
            }
            break;
        }

    }
}

void setPossibleKills(Piece* selected) {
    return;
}

bool validMove() {
    return false;
}

void Game::sortCoords() {
    // Sorting algorithm
    std::sort(this->coords.begin(), this->coords.end(), less_than_point());
}