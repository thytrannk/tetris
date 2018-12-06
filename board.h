#ifndef TETRIS_BOARD_H
#define TETRIS_BOARD_H

#include "global.h"

class Board {
public:
    Board ();
    int value(int x, int y);
    void assign(int x, int y, int val);
    void deleteLine(int y);
private:
    int board[BOARD_WIDTH][BOARD_HEIGHT];
};

#endif //TETRIS_BOARD_H
