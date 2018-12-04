#ifndef TETRIS_BOARD_H
#define TETRIS_BOARD_H

#define BOARD_HEIGHT 5
#define BOARD_WIDTH 7

class Board {
public:
    Board ();
    int value(int x, int y);

private:
    int board[BOARD_WIDTH][BOARD_HEIGHT];
    void deleteLine(int y);
};

#endif //TETRIS_BOARD_H
