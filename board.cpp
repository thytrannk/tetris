#include "board.h"
#include "main.h"

#define EPSILON 0.001f;

Board::Board() {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            board[i][j] = 0;
        }
    }
    board[0][0] = 7;
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
    startX = -BOARD_WIDTH / 2.0f * CUBE_SIZE;
    startY = -BOARD_HEIGHT / 2.0f * CUBE_SIZE;
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            // bottom left vertex
            // vertex[j][i].x
            vertices[24 * (i * BOARD_WIDTH + j)] = startX + j * CUBE_SIZE;
            // vertex[j][i].y
            vertices[24 * (i * BOARD_WIDTH + j) + 1] = startY + i * CUBE_SIZE;
            // vertex[j][i].z
            vertices[24 * (i * BOARD_WIDTH + j) + 2] = 0.0;
            // vertex[j][i].r
            vertices[24 * (i * BOARD_WIDTH + j) + 3] = color[board[j][i]][0];
            // vertex[j][i].g
            vertices[24 * (i * BOARD_WIDTH + j) + 4] = color[board[j][i]][1];
            // vertex[j][i].b
            vertices[24 * (i * BOARD_WIDTH + j) + 5] = color[board[j][i]][2];

            // bottom right vertex
            // vertex[j][i].x
            vertices[24 * (i * BOARD_WIDTH + j) + 6] = startX + (j + 1) * CUBE_SIZE - EPSILON;
            // vertex[j][i].y
            vertices[24 * (i * BOARD_WIDTH + j) + 7] = startY + i * CUBE_SIZE;
            // vertex[j][i].z
            vertices[24 * (i * BOARD_WIDTH + j) + 8] = 0.0;
            // vertex[j][i].r
            vertices[24 * (i * BOARD_WIDTH + j) + 9] = color[board[j][i]][0];
            // vertex[j][i].g
            vertices[24 * (i * BOARD_WIDTH + j) + 10] = color[board[j][i]][1];
            // vertex[j][i].b
            vertices[24 * (i * BOARD_WIDTH + j) + 11] = color[board[j][i]][2];

            // top right vertex
            // vertex[j][i].x
            vertices[24 * (i * BOARD_WIDTH + j) + 12] = startX + (j + 1) * CUBE_SIZE - EPSILON;
            // vertex[j][i].y
            vertices[24 * (i * BOARD_WIDTH + j) + 13] = startY + (i + 1) * CUBE_SIZE - EPSILON;
            // vertex[j][i].z
            vertices[24 * (i * BOARD_WIDTH + j) + 14] = 0.0;
            // vertex[j][i].r
            vertices[24 * (i * BOARD_WIDTH + j) + 15] = color[board[j][i]][0];
            // vertex[j][i].g
            vertices[24 * (i * BOARD_WIDTH + j) + 16] = color[board[j][i]][1];
            // vertex[j][i].b
            vertices[24 * (i * BOARD_WIDTH + j) + 17] = color[board[j][i]][2];

            // top left vertex
            // vertex[j][i].x
            vertices[24 * (i * BOARD_WIDTH + j) + 18] = startX + j * CUBE_SIZE;
            // vertex[j][i].y
            vertices[24 * (i * BOARD_WIDTH + j) + 19] = startY + (i + 1) * CUBE_SIZE - EPSILON;
            // vertex[j][i].z
            vertices[24 * (i * BOARD_WIDTH + j) + 20] = 0.0;
            // vertex[j][i].r
            vertices[24 * (i * BOARD_WIDTH + j) + 21] = color[board[j][i]][0];
            // vertex[j][i].g
            vertices[24 * (i * BOARD_WIDTH + j) + 22] = color[board[j][i]][1];
            // vertex[j][i].b
            vertices[24 * (i * BOARD_WIDTH + j) + 23] = color[board[j][i]][2];
        }

    }
}

void Board::indices(unsigned int *ind) {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            ind[6 * (i * BOARD_WIDTH + j)] = (unsigned int) 4 * i * BOARD_WIDTH + 4 * j;
            ind[6 * (i * BOARD_WIDTH + j) + 1] = (unsigned int) 4 * i * BOARD_WIDTH + 4 * j + 1;
            ind[6 * (i * BOARD_WIDTH + j) + 2] = (unsigned int) 4 * i * BOARD_WIDTH + 4 * j + 2;
            ind[6 * (i * BOARD_WIDTH + j) + 3] = (unsigned int) 4 * i * BOARD_WIDTH + 4 * j;
            ind[6 * (i * BOARD_WIDTH + j) + 4] = (unsigned int) 4 * i * BOARD_WIDTH + 4 * j + 2;
            ind[6 * (i * BOARD_WIDTH + j) + 5] = (unsigned int) 4 * i * BOARD_WIDTH + 4 * j + 3;
        }
    }
}