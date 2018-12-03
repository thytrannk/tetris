#ifndef TETRIS_BOARD_H
#define TETRIS_BOARD_H

#define BOARD_HEIGHT 5
#define BOARD_WIDTH 3

class Board {
public:
    Board ();
    void drawBoard(float *vertices);
    void indices(unsigned int *ind);
    int value(int x, int y);
    float startX, startY;
private:
    int board[BOARD_WIDTH][BOARD_HEIGHT];
    void deleteLine(int y);
};

#endif //TETRIS_BOARD_H
