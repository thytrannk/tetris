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
    Pieces *next1Piece;
    Pieces *next2Piece;
    Pieces *holdPiece;
    bool held = false;
    int pieceX; // x coordinate of the bottom left corner of piece matrix
    int pieceY; // y coordinate of the bottom left corner of piece matrix
    int ghostY;
    void hold();
    void pieceDown(bool autoFall);
    void pieceHardFall();
    void pieceLeft();
    void pieceRight();
    void pieceRotationRight();
    void pieceRotationLeft();
private:
    void generatePiece(Pieces **piece, int pieceID);
    void calcGhost();
    bool invalid(bool ghost);
    void saveBoard();
    void clearLines();
};

#endif //TETRIS_GAME_H
