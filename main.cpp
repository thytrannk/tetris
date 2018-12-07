#include <iostream>
#include <glad/glad.h>
#include "global.h"
#include "main.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

Game game;
GLFWwindow *window;

int main() {

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Tetris", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    game.Loop();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        game.pieceDown(false);
    } else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        game.pieceHardFall();
    } else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        game.pieceLeft();
    } else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        game.pieceRight();
    } else if ((key == GLFW_KEY_X && action == GLFW_PRESS) || (key == GLFW_KEY_UP && action == GLFW_PRESS)) {
        game.pieceRotationRight();
    } else if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
        game.pieceRotationLeft();
    } else if ((key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) || (key == GLFW_KEY_RIGHT_SHIFT && action == GLFW_PRESS)) {
        game.hold();
    }
}