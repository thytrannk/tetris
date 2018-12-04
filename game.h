#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "board.h"
#include "pieces.h"

class Game {
public:
    void Loop();
    Board board;
    Pieces *currentPiece;
    int pieceX; // x coordinate of the bottom left corner of piece matrix
    int pieceY; // y coordinate of the bottom left corner of piece matrix
private:
    void generatePiece();
    bool invalid();
};


#endif //TETRIS_GAME_H
