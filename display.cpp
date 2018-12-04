#include "display.h"
#include "shader.h"
#include "main.h"

#define EPSILON 0.0001f;

void processInput(GLFWwindow *window);

float startX, startY;

float color [9 /*colors*/][3 /*rgb*/] =
        {
                // Empty
                {0.0, 0.0, 0.0},
                // Square
                {1.0, 1.0, 0.0},
                // I
                {0.0, 1.0, 1.0},
                // L
                {0.0, 0.0, 1.0},
                // L mirrored
                {1.0, 0.5, 0.0},
                // Z
                {1.0, 0.0, 0.0},
                // S
                {0.0, 1.0, 0.0},
                // T
                {1.0, 0.0, 1.0},
                // Transparent
                {1.0, 1.0, 1.0},
        };

void drawBoard(float *vertices) {
    startX = -BOARD_WIDTH / 2.0f * CUBE_SIZE_X;
    startY = -BOARD_HEIGHT / 2.0f * CUBE_SIZE_Y;
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            // bottom left vertex
            // vertex[j][i].x
            vertices[24 * (i * BOARD_WIDTH + j)] = startX + j * CUBE_SIZE_X;
            // vertex[j][i].y
            vertices[24 * (i * BOARD_WIDTH + j) + 1] = startY + i * CUBE_SIZE_Y;
            // vertex[j][i].z
            vertices[24 * (i * BOARD_WIDTH + j) + 2] = 0.0;
            // vertex[j][i].r
            vertices[24 * (i * BOARD_WIDTH + j) + 3] = color[game.board.value(j, i)][0];
            // vertex[j][i].g
            vertices[24 * (i * BOARD_WIDTH + j) + 4] = color[game.board.value(j, i)][1];
            // vertex[j][i].b
            vertices[24 * (i * BOARD_WIDTH + j) + 5] = color[game.board.value(j, i)][2];

            // bottom right vertex
            // vertex[j][i].x
            vertices[24 * (i * BOARD_WIDTH + j) + 6] = startX + (j + 1) * CUBE_SIZE_X - EPSILON;
            // vertex[j][i].y
            vertices[24 * (i * BOARD_WIDTH + j) + 7] = startY + i * CUBE_SIZE_Y;
            // vertex[j][i].z
            vertices[24 * (i * BOARD_WIDTH + j) + 8] = 0.0;
            // vertex[j][i].r
            vertices[24 * (i * BOARD_WIDTH + j) + 9] = color[game.board.value(j, i)][0];
            // vertex[j][i].g
            vertices[24 * (i * BOARD_WIDTH + j) + 10] = color[game.board.value(j, i)][1];
            // vertex[j][i].b
            vertices[24 * (i * BOARD_WIDTH + j) + 11] = color[game.board.value(j, i)][2];

            // top right vertex
            // vertex[j][i].x
            vertices[24 * (i * BOARD_WIDTH + j) + 12] = startX + (j + 1) * CUBE_SIZE_X - EPSILON;
            // vertex[j][i].y
            vertices[24 * (i * BOARD_WIDTH + j) + 13] = startY + (i + 1) * CUBE_SIZE_Y - EPSILON;
            // vertex[j][i].z
            vertices[24 * (i * BOARD_WIDTH + j) + 14] = 0.0;
            // vertex[j][i].r
            vertices[24 * (i * BOARD_WIDTH + j) + 15] = color[game.board.value(j, i)][0];
            // vertex[j][i].g
            vertices[24 * (i * BOARD_WIDTH + j) + 16] = color[game.board.value(j, i)][1];
            // vertex[j][i].b
            vertices[24 * (i * BOARD_WIDTH + j) + 17] = color[game.board.value(j, i)][2];

            // top left vertex
            // vertex[j][i].x
            vertices[24 * (i * BOARD_WIDTH + j) + 18] = startX + j * CUBE_SIZE_X;
            // vertex[j][i].y
            vertices[24 * (i * BOARD_WIDTH + j) + 19] = startY + (i + 1) * CUBE_SIZE_Y - EPSILON;
            // vertex[j][i].z
            vertices[24 * (i * BOARD_WIDTH + j) + 20] = 0.0;
            // vertex[j][i].r
            vertices[24 * (i * BOARD_WIDTH + j) + 21] = color[game.board.value(j, i)][0];
            // vertex[j][i].g
            vertices[24 * (i * BOARD_WIDTH + j) + 22] = color[game.board.value(j, i)][1];
            // vertex[j][i].b
            vertices[24 * (i * BOARD_WIDTH + j) + 23] = color[game.board.value(j, i)][2];
        }

    }
}

void indexVertices(unsigned int *ind) {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            ind[6 * (i * BOARD_WIDTH + j)] = (unsigned int) 4 * i * BOARD_WIDTH + 4 * j;
            ind[6 * (i * BOARD_WIDTH + j) + 1] = (unsigned int) 4 * i * BOARD_WIDTH + 4 * j + 1;
            ind[6 * (i * BOARD_WIDTH + j) + 2] = (unsigned int) 4 * i * BOARD_WIDTH + 4 * j + 2;
            ind[6 * (i * BOARD_WIDTH + j) + 3] = (unsigned int) 4 * i * BOARD_WIDTH + 4 * j;
            ind[6 * (i * BOARD_WIDTH + j) + 4] = (unsigned int) 4 * i * BOARD_WIDTH + 4 * j + 2;
            ind[6 * (i * BOARD_WIDTH + j) + 5] = (unsigned int) 4 * i * BOARD_WIDTH + 4 * j + 3;
        }
    }
}

void render(const char *vertexSource, const char *fragmentSource, GLFWwindow* window) {
    // build and compile our shader program
    // ------------------------------------
    Shader ourShader(vertexSource, fragmentSource);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    int numVertices = BOARD_HEIGHT * BOARD_WIDTH * 4;
    auto *vertices = new float[numVertices * 6];
    drawBoard(vertices);

    int numTriangles = BOARD_WIDTH * BOARD_HEIGHT * 2;
    auto *indices = new unsigned int[numTriangles * 3];
    indexVertices(indices);

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertices * 6, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numTriangles * 3, indices, GL_STATIC_DRAW);

    delete[] vertices;
    delete[] indices;

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle

        ourShader.use();
        ourShader.setFloat("startX", startX);
        ourShader.setFloat("startY", startY);
        ourShader.setFloat("cubeSizeX", CUBE_SIZE_X);
        ourShader.setFloat("cubeSizeY", CUBE_SIZE_Y);

        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, numTriangles * 3, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}