#ifndef TETRIS_DISPLAY_H
#define TETRIS_DISPLAY_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "shader.h"

extern unsigned int VBO_boardPositions, VAO_board, EBO_board;
extern unsigned int VBO_background, VAO_background, EBO_background;
void generateBackground();
void bindBoardVertices();
void render(Shader &gameShader, Shader &backgroundShader, bool currentPiece);
void dummyRender();

#endif //TETRIS_DISPLAY_H
