#include <stdlib.h>
#include <time.h>
#include "game.h"

Game::Game(){
    generatePiece();
    if (!gameOver()) {

    }
}

bool Game::gameOver() {
    return false;
}

void Game::generatePiece() {
    srand(time(NULL));

    /* generate random piece from 0 to 7 */
    int pieceID = rand() % 7;
    currentPiece = new Pieces(pieceID);
    delete currentPiece;
}