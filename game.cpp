#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>
#include <random>
#include "game.h"
#include "main.h"
#include "display.h"
#include "shader.h"
#include <iostream>

using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

#define TIME 0.5s

random_device rd;
mt19937 mt(rd());
uniform_int_distribution<> dist(0.0, 6.0);

void Game::Loop() {
    Shader backgroundShader = compileShader(vertexBackground, fragmentBackground);
    generateBackground();
    Shader gameShader = compileShader(vertexSource, fragmentSource);
    bindBoardVertices();
    generatePiece();
    #ifdef __APPLE__
        dummyRender();
    #endif
    while (!invalid() && !glfwWindowShouldClose(window)) {
        int furthestBottom;
        currentPiece->furthestBottom(BOARD_WIDTH, BOARD_HEIGHT, furthestBottom);
        render(gameShader, backgroundShader);
        fallPiece(furthestBottom);
    }
    cout << "Game Over!" << endl;
    delete currentPiece;
    glDeleteVertexArrays(1, &VAO_board);
    glDeleteBuffers(1, &VBO_boardPositions);
    glDeleteBuffers(1, &EBO_board);
    glDeleteVertexArrays(1, &VAO_background);
    glDeleteBuffers(1, &VBO_background);
    glDeleteBuffers(1, &EBO_background);
}

void Game::fallPiece(int furthestBottom) {
    sleep_for(TIME);
    pieceY--;

    if (invalid() || pieceY < furthestBottom) {
        // reach the bottom
        pieceY++;
        saveBoard();
        delete currentPiece;
        generatePiece();
    }
}

void Game::saveBoard(void) {
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            int pieceCol = currentPiece->pieceValue(x, y);
            if (pieceCol != 8) {
                board.assign(x + pieceX, y + pieceY, pieceCol);
            }
        }
    }
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
    int pieceID = dist(mt);
    currentPiece = new Pieces(pieceID);
    currentPiece->StartLocation(BOARD_WIDTH, BOARD_HEIGHT, pieceX, pieceY);
}