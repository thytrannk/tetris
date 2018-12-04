#ifndef TETRIS_DISPLAY_H
#define TETRIS_DISPLAY_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

extern float startX, startY;
void render(const char *vertexSource, const char *fragmentSource, GLFWwindow* window);

#endif //TETRIS_DISPLAY_H
