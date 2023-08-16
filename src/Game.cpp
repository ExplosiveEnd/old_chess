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
        }
    }

}

Piece* Game::getPiece(int32_t x, int32_t y) {
    for (auto piece : Game::pieces) {
        if (piece->point.x == x && piece->point.y == y)
            return piece;
    }

    Point empty;
    empty.x = NULL;
    empty.y = NULL;

    // Creates empty piece if none with the coordinates are found (empty space)
    auto piece = new Piece(Type::TYPE_NONE, empty, Color::COLOR_NONE);
    pieces.push_back(piece);

    return piece;

}