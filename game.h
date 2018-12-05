#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "board.h"
#include "pieces.h"

class Game {
public:
    bool game_over = false;
    void Loop();
    Board board;
    Pieces *currentPiece;
    int pieceX; // x coordinate of the bottom left corner of piece matrix
    int pieceY; // y coordinate of the bottom left corner of piece matrix
    void pieceDown(bool autoFall);
    void pieceHardFall();
private:
    void generatePiece();
    bool invalid();
    void saveBoard(void);
};

#endif //TETRIS_GAME_H
