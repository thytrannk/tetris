#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <irrKlang.h>
#include <chrono>
#include <thread>
#include <random>
#include "game.h"
#include "main.h"
#include "display.h"
#include "global.h"
#include "shader.h"
#include <iostream>

using namespace std;
using namespace irrklang;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

random_device rd;
mt19937 mt(rd());
uniform_int_distribution<> dist(0.0, 6.0);

ISoundEngine *SoundEngine = createIrrKlangDevice();

void Game::Loop() {
    SoundEngine->play2D("../audio/background.wav", GL_FALSE);
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
    while (invalid()) {
        pieceY++;
        cout << "y=" << pieceY << endl;
    }
    cout << "ID=" << currentPiece->pieceID << endl;
    render(gameShader, backgroundShader);
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
        SoundEngine->play2D("../audio/beep.wav", GL_FALSE);
        sleep_for(TIME);
        generatePiece();
    }
    SoundEngine->play2D("../audio/button.wav", GL_FALSE);
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
                if (x + pieceX > BOARD_WIDTH - 1 || y + pieceY > BOARD_HEIGHT - 1) {
                    // Game has already been over, moving the piece up to render last frame
                    return false;
                }
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