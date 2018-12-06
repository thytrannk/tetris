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
    while (1) {
        for (int i = 0; i < 10; i++) {
            if (!game_over && !glfwWindowShouldClose(window)) {
                render(gameShader, backgroundShader);
                sleep_for(TIME_SHORT);
            } else {
                goto over;
            }
        }
        pieceDown(true);
    }

over:
    while (invalid(false)) {
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

void Game::pieceDown(bool autoFall) {
    if (!game_over) {
        pieceY--;

        int furthestBottom;
        currentPiece->furthestBottom(BOARD_WIDTH, BOARD_HEIGHT, furthestBottom);

        if (invalid(false) || pieceY < furthestBottom) {
            // reach the bottom
            pieceY++;
            if (autoFall) {
                SoundEngine->play2D(pieceLock, false);
                mtx.lock();
                saveBoard();
                delete currentPiece;
                sleep_for(TIME_LONG);
                generatePiece();
                mtx.unlock();
                SoundEngine->play2D(pieceFall, false);
                if (invalid(false)) {
                    game_over = true;
                }
            }
        } else if (autoFall) {
            SoundEngine->play2D(pieceFall, false);
        }
    }
}

void Game::pieceLeft() {
    if (!game_over) {
        int furthestLeft;
        currentPiece->furthestLeft(BOARD_WIDTH, BOARD_HEIGHT, furthestLeft);

        pieceX--;

        if (invalid(false) || pieceX < furthestLeft) {
            // cannot go left
            pieceX++;
        } else {
            calcGhost();
        }
//        cout << "pieceX=" << pieceX << endl;
//        cout << "furthestLeft=" << furthestLeft << endl;
    }
}

void Game::pieceRight() {
    if (!game_over) {
        int furthestRight;
        currentPiece->furthestRight(BOARD_WIDTH, BOARD_HEIGHT, furthestRight);

        pieceX++;

        if (invalid(false) || pieceX > furthestRight) {
            // cannot go right
            pieceX--;
        } else {
            calcGhost();
        }
    }
}

void Game::pieceRotationRight() {
    if (!game_over) {
        if (currentPiece->rotation == 3) {
            currentPiece->rotation = 0;
        } else {
            currentPiece->rotation++;
        }
        if (invalid(false)) {
            // cannot rotate
            pieceRotationLeft();
        } else {
            int furthestRight;
            currentPiece->furthestRight(BOARD_WIDTH, BOARD_HEIGHT, furthestRight);
            int furthestLeft;
            currentPiece->furthestLeft(BOARD_WIDTH, BOARD_HEIGHT, furthestLeft);
            int furthestBottom;
            currentPiece->furthestBottom(BOARD_WIDTH, BOARD_HEIGHT, furthestBottom);
            int furthestTop;
            currentPiece->furthestTop(BOARD_WIDTH, BOARD_HEIGHT, furthestTop);
            int i = 0;
            if (pieceX > furthestRight) {
                while (pieceX > furthestRight) {
                    pieceX--;
                    i++;
                }
                if (invalid(false)) {
                    while (i > 0) {
                        pieceX++;
                        i--;
                    }
                    pieceRotationLeft();
                }
            } else if (pieceX < furthestLeft) {
                while (pieceX < furthestLeft) {
                    pieceX++;
                    i++;
                }
                if (invalid(false)) {
                    while (i > 0) {
                        pieceX--;
                        i--;
                    }
                    pieceRotationLeft();
                }
            } else if (pieceY < furthestBottom) {
                while (pieceY < furthestBottom) {
                    pieceY++;
                    i++;
                }
                if (invalid(false)) {
                    while (i > 0) {
                        pieceY--;
                        i--;
                    }
                    pieceRotationLeft();
                }
            } else if (pieceY > furthestTop) {
                while (pieceY > furthestTop) {
                    pieceY--;
                    i++;
                }
                if (invalid(false)) {
                    while (i > 0) {
                        pieceY++;
                        i--;
                    }
                    pieceRotationLeft();
                }
            }
//            cout << "pieceX=" << pieceX << endl;
//            cout << "furthestLeft=" << furthestLeft << endl;
        }
        calcGhost();

    }
}

void Game::pieceRotationLeft() {
    if (!game_over) {
        if (currentPiece->rotation == 0) {
            currentPiece->rotation = 3;
        } else {
            currentPiece->rotation--;
        }
        if (invalid(false)) {
            // cannot rotate
            pieceRotationRight();
        } else {
            int furthestRight;
            currentPiece->furthestRight(BOARD_WIDTH, BOARD_HEIGHT, furthestRight);
            int furthestLeft;
            currentPiece->furthestLeft(BOARD_WIDTH, BOARD_HEIGHT, furthestLeft);
            int furthestBottom;
            currentPiece->furthestBottom(BOARD_WIDTH, BOARD_HEIGHT, furthestBottom);
            int furthestTop;
            currentPiece->furthestTop(BOARD_WIDTH, BOARD_HEIGHT, furthestTop);
            int i = 0;
            if (pieceX > furthestRight) {
                while (pieceX > furthestRight) {
                    pieceX--;
                    i++;
                }
                if (invalid(false)) {
                    while (i > 0) {
                        pieceX++;
                        i--;
                    }
                    pieceRotationRight();
                }
            } else if (pieceX < furthestLeft) {
                while (pieceX < furthestLeft) {
                    pieceX++;
                    i++;
                }
                if (invalid(false)) {
                    while (i > 0) {
                        pieceX--;
                        i--;
                    }
                    pieceRotationRight();
                }
            } else if (pieceY < furthestBottom) {
                while (pieceY < furthestBottom) {
                    pieceY++;
                    i++;
                }
                if (invalid(false)) {
                    while (i > 0) {
                        pieceY--;
                        i--;
                    }
                    pieceRotationRight();
                }
            } else if (pieceY > furthestTop) {
                while (pieceY > furthestTop) {
                    pieceY--;
                    i++;
                }
                if (invalid(false)) {
                    while (i > 0) {
                        pieceY++;
                        i--;
                    }
                    pieceRotationRight();
                }
            }
        }
        calcGhost();
    }
}

void Game::calcGhost() {
    ghostY = pieceY;
    int furthestBottom;
    currentPiece->furthestBottom(BOARD_WIDTH, BOARD_HEIGHT, furthestBottom);
    while (!invalid(true) && ghostY >= furthestBottom) {
        ghostY--;
    }

    // reach the bottom
    ghostY++;

//    cout << "ghostY=" << ghostY << endl;
//    cout << "furthestBottom=" << furthestBottom << endl;
}

void Game::pieceHardFall() {
    if (!game_over) {
        pieceY = ghostY;
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

bool Game::invalid(bool ghost) {
    // Returns true if the piece overlaps with a non-empty location of the board
    // bool ghost: true if ghost piece, false if actual piece
    // When the game is over, and the last piece is partially within the board but does not overlap any non-empty
    // location on the board, the function returns false

    int yy;
    if (ghost) {
        yy = ghostY;
    } else {
        yy = pieceY;
    }

    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            int pieceCol = currentPiece->pieceValue(x, y);
            if (pieceCol != 8) {
                if (x + pieceX < BOARD_WIDTH
                        && x + pieceX >= 0
                        && y + yy < BOARD_HEIGHT
                        && y + yy >= 0) {
                    // Piece within board
                    int boardCol = board.value(x + pieceX, y + yy);
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
    calcGhost();
    if (pieceID == 0) {
        cout << "square" << endl;
    } else if (pieceID == 0) {
        cout << "square" << endl;
    } else if (pieceID == 1) {
        cout << "I" << endl;
    } else if (pieceID == 2) {
        cout << "L" << endl;
    } else if (pieceID == 3) {
        cout << "L-mirrored" << endl;
    } else if (pieceID == 4) {
        cout << "Z" << endl;
    } else if (pieceID == 5) {
        cout << "S" << endl;
    } else if (pieceID == 6) {
        cout << "T" << endl;
    }
}