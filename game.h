#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "board.h"
#include "pieces.h"

class Game {
public:
    Game();
    Board board;
private:
    Pieces *currentPiece;
    int pieceX; // x coordinate of the bottom left corner of piece matrix
    int pieceY; // y coordinate of the bottom left corner of piece matrix
    void generatePiece();
    bool gameOver();
};


#endif //TETRIS_GAME_H
