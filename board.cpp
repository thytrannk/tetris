#include "board.h"

Board::Board() {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            board[i][j] = 0;
        }
    }
//    board[0][0] = 7;
//    board[0][1] = 3;
//    board[0][2] = 4;
//    board[0][3] = 1;
//    board[0][4] = 0;
//    board[1][0] = 7;
//    board[1][1] = 6;
//    board[1][2] = 5;
//    board[1][3] = 3;
//    board[1][4] = 4;
//    board[2][0] = 2;
//    board[2][1] = 0;
//    board[2][2] = 1;
//    board[2][3] = 5;
//    board[2][4] = 7;
}

int Board::value(int x, int y) {
    return board[x][y];
}

void Board::assign(int x, int y, int val) {
    board[x][y] = val;
}

void Board::deleteLine(int y) {

}