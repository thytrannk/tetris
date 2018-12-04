#ifndef TETRIS_DISPLAY_H
#define TETRIS_DISPLAY_H

//#include <GLFW/glfw3.h>
#include "shader.h"

extern float startX, startY;
void drawBoard(float *vertices);
void indexVertices(unsigned int *ind);
void render(const char *vertexSource, const char *fragmentSource, GLFWwindow* window);

#endif //TETRIS_DISPLAY_H
