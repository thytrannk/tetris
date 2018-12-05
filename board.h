#ifndef TETRIS_BOARD_H
#define TETRIS_BOARD_H

#include "global.h"

class Board {
public:
    Board ();
    int value(int x, int y);
    void assign(int x, int y, int val);
private:
    int board[BOARD_WIDTH][BOARD_HEIGHT];
    void deleteLine(int y);
};

#endif //TETRIS_BOARD_H
