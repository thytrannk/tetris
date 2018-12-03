#include "display.h"
#include "board.h"
#include "game.h"
#include "main.h"

#define EPSILON 0.0001f;

float startX, startY;

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

void drawBoard(float *vertices) {
    startX = -BOARD_WIDTH / 2.0f * CUBE_SIZE_X;
    startY = -BOARD_HEIGHT / 2.0f * CUBE_SIZE_Y;
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            // bottom left vertex
            // vertex[j][i].x
            vertices[24 * (i * BOARD_WIDTH + j)] = startX + j * CUBE_SIZE_X;
            // vertex[j][i].y
            vertices[24 * (i * BOARD_WIDTH + j) + 1] = startY + i * CUBE_SIZE_Y;
            // vertex[j][i].z
            vertices[24 * (i * BOARD_WIDTH + j) + 2] = 0.0;
            // vertex[j][i].r
            vertices[24 * (i * BOARD_WIDTH + j) + 3] = color[game.board.value(j, i)][0];
            // vertex[j][i].g
            vertices[24 * (i * BOARD_WIDTH + j) + 4] = color[game.board.value(j, i)][1];
            // vertex[j][i].b
            vertices[24 * (i * BOARD_WIDTH + j) + 5] = color[game.board.value(j, i)][2];

            // bottom right vertex
            // vertex[j][i].x
            vertices[24 * (i * BOARD_WIDTH + j) + 6] = startX + (j + 1) * CUBE_SIZE_X - EPSILON;
            // vertex[j][i].y
            vertices[24 * (i * BOARD_WIDTH + j) + 7] = startY + i * CUBE_SIZE_Y;
            // vertex[j][i].z
            vertices[24 * (i * BOARD_WIDTH + j) + 8] = 0.0;
            // vertex[j][i].r
            vertices[24 * (i * BOARD_WIDTH + j) + 9] = color[game.board.value(j, i)][0];
            // vertex[j][i].g
            vertices[24 * (i * BOARD_WIDTH + j) + 10] = color[game.board.value(j, i)][1];
            // vertex[j][i].b
            vertices[24 * (i * BOARD_WIDTH + j) + 11] = color[game.board.value(j, i)][2];

            // top right vertex
            // vertex[j][i].x
            vertices[24 * (i * BOARD_WIDTH + j) + 12] = startX + (j + 1) * CUBE_SIZE_X - EPSILON;
            // vertex[j][i].y
            vertices[24 * (i * BOARD_WIDTH + j) + 13] = startY + (i + 1) * CUBE_SIZE_Y - EPSILON;
            // vertex[j][i].z
            vertices[24 * (i * BOARD_WIDTH + j) + 14] = 0.0;
            // vertex[j][i].r
            vertices[24 * (i * BOARD_WIDTH + j) + 15] = color[game.board.value(j, i)][0];
            // vertex[j][i].g
            vertices[24 * (i * BOARD_WIDTH + j) + 16] = color[game.board.value(j, i)][1];
            // vertex[j][i].b
            vertices[24 * (i * BOARD_WIDTH + j) + 17] = color[game.board.value(j, i)][2];

            // top left vertex
            // vertex[j][i].x
            vertices[24 * (i * BOARD_WIDTH + j) + 18] = startX + j * CUBE_SIZE_X;
            // vertex[j][i].y
            vertices[24 * (i * BOARD_WIDTH + j) + 19] = startY + (i + 1) * CUBE_SIZE_Y - EPSILON;
            // vertex[j][i].z
            vertices[24 * (i * BOARD_WIDTH + j) + 20] = 0.0;
            // vertex[j][i].r
            vertices[24 * (i * BOARD_WIDTH + j) + 21] = color[game.board.value(j, i)][0];
            // vertex[j][i].g
            vertices[24 * (i * BOARD_WIDTH + j) + 22] = color[game.board.value(j, i)][1];
            // vertex[j][i].b
            vertices[24 * (i * BOARD_WIDTH + j) + 23] = color[game.board.value(j, i)][2];
        }

    }
}

void indexVertices(unsigned int *ind) {
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