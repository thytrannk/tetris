#ifndef TETRIS_DISPLAY_H
#define TETRIS_DISPLAY_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "shader.h"

extern float startX, startY;
extern unsigned int VBO, VAO, EBO;
Shader compileShader();
void bindBoardVertices();
void render(Shader ourShader);
void dummyRender();

#endif //TETRIS_DISPLAY_H
