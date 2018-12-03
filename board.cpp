#include "board.h"
#include "main.h"

Board::Board() {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            board[i][j] = 0;
        }
    }
    board[0][0] = 2;
    board[0][1] = 3;
    board[0][2] = 4;
    board[0][3] = 1;
    board[0][4] = 0;
    board[1][0] = 7;
    board[1][1] = 6;
    board[1][2] = 5;
    board[1][3] = 3;
    board[1][4] = 4;
    board[2][0] = 2;
    board[2][1] = 0;
    board[2][2] = 1;
    board[2][3] = 5;
    board[2][4] = 7;


}

int Board::value(int x, int y) {
    return board[x][y];
}

void Board::deleteLine(int y) {

}

float color [8 /*colors*/][4 /*rgb*/] =
        {
                // Empty
                {0.0, 0.0, 0.0},
                // Square
                {1.0, 1.0, 0.0},
                // I
                {0.0, 1.0, 1.0},
                // L
                {0.0, 0.0, 1.0},
                // L mirrored
                {1.0, 0.5, 0.0},
                // Z
                {1.0, 0.0, 0.0},
                // S
                {0.0, 1.0, 0.0},
                // T
                {1.0, 0.0, 1.0},
        };

void Board::drawBoard(float *vertices) {
    float startX = -BOARD_WIDTH / 2.0f * CUBE_SIZE;
    float startY = -BOARD_HEIGHT / 2.0f * CUBE_SIZE;
    for (int i = 0; i < BOARD_HEIGHT + 1; i++) {
        for (int j = 0; j < BOARD_WIDTH + 1; j++) {
            // vertex[j][i].x
            vertices[6 * (i * (BOARD_WIDTH + 1) + j)] = startX + j * CUBE_SIZE;
            // vertex[j][i].y
            vertices[6 * (i * (BOARD_WIDTH + 1) + j) + 1] = startY + i * CUBE_SIZE;
            // vertex[j][i].z
            vertices[6 * (i * (BOARD_WIDTH + 1) + j) + 2] = 0.0;
            int ii = i;
            int jj = j;
            if (i == BOARD_HEIGHT) {
                ii--;
            }
            if (j == BOARD_WIDTH) {
                jj--;
            }
            // vertex[j][i].r
            vertices[6 * (i * (BOARD_WIDTH + 1) + j) + 3] = color[board[jj][ii]][0];
            // vertex[j][i].g
            vertices[6 * (i * (BOARD_WIDTH + 1) + j) + 4] = color[board[jj][ii]][1];
            // vertex[j][i].b
            vertices[6 * (i * (BOARD_WIDTH + 1) + j) + 5] = color[board[jj][ii]][2];
        }
    }
}

void Board::indices(unsigned int *ind) {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            ind[6 * (i * BOARD_WIDTH + j)] = (unsigned int) i * (BOARD_WIDTH + 1) + j;
            ind[6 * (i * BOARD_WIDTH + j) + 1] = (unsigned int) i * (BOARD_WIDTH + 1) + j + 1;
            ind[6 * (i * BOARD_WIDTH + j) + 2] = (unsigned int) (i + 1) * (BOARD_WIDTH + 1) + j + 1;
            ind[6 * (i * BOARD_WIDTH + j) + 3] = (unsigned int) i * (BOARD_WIDTH + 1) + j;
            ind[6 * (i * BOARD_WIDTH + j) + 4] = (unsigned int) (i + 1) * (BOARD_WIDTH + 1) + j;
            ind[6 * (i * BOARD_WIDTH + j) + 5] = (unsigned int) (i + 1) * (BOARD_WIDTH + 1) + j + 1;
        }
    }
}