#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <irrKlang.h>
#include <chrono>
#include <thread>
#include <mutex>
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

mutex mtx;

random_device rd;
mt19937 mt(rd());
uniform_int_distribution<> dist(0.0, 6.0);

ISoundEngine *SoundEngine = createIrrKlangDevice();

const char gameMusic[] = "../audio/background.wav";
const char pieceFall[] = "../audio/button.wav";
const char pieceLock[] = "../audio/beep.wav";
const char gameOver[] = "../audio/gameOver.wav";

//Game::Game() {
//    game_over = false;
//}

void Game::Loop() {
    ISound *game_Music = SoundEngine->play2D(gameMusic, true, false, true);
    Shader backgroundShader = compileShader(vertexBackground, fragmentBackground);
    generateBackground();
    Shader gameShader = compileShader(vertexSource, fragmentSource);
    bindBoardVertices();
    generatePiece();
    #ifdef __APPLE__
        dummyRender();
    #endif
    while (!game_over && !glfwWindowShouldClose(window)) {
        for (int i = 0; i < 5; i++) {
            render(gameShader, backgroundShader);
            sleep_for(TIME_SHORT);
        }
        pieceDown();
    }
    while (invalid()) {
        pieceY++;
    }
    render(gameShader, backgroundShader);
    cout << "Game Over!" << endl;
    game_Music->stop();
    SoundEngine->play2D(gameOver, false);
    delete currentPiece;
    glDeleteVertexArrays(1, &VAO_board);
    glDeleteBuffers(1, &VBO_boardPositions);
    glDeleteBuffers(1, &EBO_board);
    glDeleteVertexArrays(1, &VAO_background);
    glDeleteBuffers(1, &VBO_background);
    glDeleteBuffers(1, &EBO_background);
}

void Game::pieceDown() {
    if (!game_over) {
        pieceY--;

        int furthestBottom;
        currentPiece->furthestBottom(BOARD_WIDTH, BOARD_HEIGHT, furthestBottom);

        if (invalid() || pieceY < furthestBottom) {
            // reach the bottom
            pieceY++;
            saveBoard();
            delete currentPiece;
            SoundEngine->play2D(pieceLock, false);
            sleep_for(TIME_LONG);
            generatePiece();
            if (invalid()) {
                game_over = true;
            }
        }
        SoundEngine->play2D(pieceFall, false);
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
                if (x + pieceX <= BOARD_WIDTH - 1 && y + pieceY <= BOARD_HEIGHT - 1) {
                    // Game has already been over, moving the piece up to render last frame
                    int boardCol = board.value(x + pieceX, y + pieceY);
                    if (boardCol) {
                        return true;
                    }
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