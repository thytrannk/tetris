#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <thread>
#include "game.h"
#include "main.h"
#include "display.h"
#include <iostream>

using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

#define TIME 0.8s

void Game::Loop() {
    srand((unsigned int) time(nullptr));
    generatePiece();
    while (!invalid() && !glfwWindowShouldClose(window)) {
        int furthestBottom;
        currentPiece->furthestBottom(BOARD_WIDTH, BOARD_HEIGHT, furthestBottom);
        render(vertexSource, fragmentSource, window);
        sleep_for(TIME);
        pieceY--;

        if (invalid() || pieceY < furthestBottom) {
            // reach the bottom
            pieceY++;
            for (int y = 0; y < 5; y++) {
                for (int x = 0; x < 5; x++) {
                    int pieceCol = currentPiece->pieceValue(x, y);
                    if (pieceCol != 8) {
                        board.assign(x + pieceX, y + pieceY, pieceCol);
                    }
                }
            }
            generatePiece();
        }
    }
    cout << "Game Over!" << endl;
}

bool Game::invalid() {
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            int pieceCol = currentPiece->pieceValue(x, y);
            if (pieceCol != 8) {
                int boardCol = board.value(x + pieceX, y + pieceY);
                if (boardCol) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Game::generatePiece() {
    /* generate random piece from 0 to 7 */
    int pieceID = rand() % 7;
//    pieceID = 3;
    currentPiece = new Pieces(pieceID);
    currentPiece->StartLocation(BOARD_WIDTH, BOARD_HEIGHT, pieceX, pieceY);
//    delete currentPiece;
}