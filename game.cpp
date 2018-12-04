#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "main.h"
#include "display.h"
#include <iostream>

using namespace std;

void Game::Loop() {
    generatePiece();
    if (!gameOver()) {
        render(vertexSource, fragmentSource, window);
    }
}

bool Game::gameOver() {
    return false;
}

void Game::generatePiece() {
    srand(time(NULL));

    /* generate random piece from 0 to 7 */
    int pieceID = rand() % 7;
//    pieceID = 1;
    currentPiece = new Pieces(pieceID);
    currentPiece->StartLocation(BOARD_WIDTH, BOARD_HEIGHT, pieceX, pieceY);
//    delete currentPiece;
}