#ifndef TETRIS_MAIN_H
#define TETRIS_MAIN_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "game.h"

const float CUBE_SIZE_X = 0.07;
const float CUBE_SIZE_Y = 0.07;

extern const char vertexSource[];
extern const char fragmentSource[];
extern GLFWwindow *window;

extern Game game;

#endif //TETRIS_MAIN_H
