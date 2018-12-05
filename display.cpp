#include <iostream>
#include <FreeImage.h>
#include "display.h"
#include "global.h"
#include "shader.h"
#include "main.h"

using namespace std;

void processInput(GLFWwindow *window);

float startX, startY;
float pcStartX, pcStartY;
unsigned int VBO_boardPositions, VAO_board, EBO_board;
unsigned int VBO_background, VAO_background, EBO_background;
unsigned int texture;
int imageSizeX, imageSizeY, image_nChannel;
BYTE *image;

const char vertexSource[] = "../vertex.vs";
const char fragmentSource[] = "../fragment.fs";
const char vertexBackground[] = "../vertexBackground.vs";
const char fragmentBackground[] = "../fragmentBackground.fs";
const char backgroundFile[] = "../background.jpg";

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

void getBoardVertices(float *vertices) {
    startX = -BOARD_WIDTH / 2.0f * CUBE_SIZE_X;
    startY = -BOARD_HEIGHT / 2.0f * CUBE_SIZE_Y;
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            // bottom left vertex
            // vertex[j][i].x
            vertices[12 * (i * BOARD_WIDTH + j)] = startX + j * CUBE_SIZE_X;
            // vertex[j][i].y
            vertices[12 * (i * BOARD_WIDTH + j) + 1] = startY + i * CUBE_SIZE_Y;
            // vertex[j][i].z
            vertices[12 * (i * BOARD_WIDTH + j) + 2] = 0.0;

            // bottom right vertex
            // vertex[j][i].x
            vertices[12 * (i * BOARD_WIDTH + j) + 3] = startX + (j + 1) * CUBE_SIZE_X - EPSILON;
            // vertex[j][i].y
            vertices[12 * (i * BOARD_WIDTH + j) + 4] = startY + i * CUBE_SIZE_Y;
            // vertex[j][i].z
            vertices[12 * (i * BOARD_WIDTH + j) + 5] = 0.0;

            // top right vertex
            // vertex[j][i].x
            vertices[12 * (i * BOARD_WIDTH + j) + 6] = startX + (j + 1) * CUBE_SIZE_X - EPSILON;
            // vertex[j][i].y
            vertices[12 * (i * BOARD_WIDTH + j) + 7] = startY + (i + 1) * CUBE_SIZE_Y - EPSILON;
            // vertex[j][i].z
            vertices[12 * (i * BOARD_WIDTH + j) + 8] = 0.0;

            // top left vertex
            // vertex[j][i].x
            vertices[12 * (i * BOARD_WIDTH + j) + 9] = startX + j * CUBE_SIZE_X;
            // vertex[j][i].y
            vertices[12 * (i * BOARD_WIDTH + j) + 10] = startY + (i + 1) * CUBE_SIZE_Y - EPSILON;
            // vertex[j][i].z
            vertices[12 * (i * BOARD_WIDTH + j) + 11] = 0.0;
        }

    }
}

void getBoardColor(float *vertices) {
    startX = -BOARD_WIDTH / 2.0f * CUBE_SIZE_X;
    startY = -BOARD_HEIGHT / 2.0f * CUBE_SIZE_Y;
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            // bottom left vertex
            // vertex[j][i].r
            vertices[12 * (i * BOARD_WIDTH + j)] = color[game.board.value(j, i)][0];
            // vertex[j][i].g
            vertices[12 * (i * BOARD_WIDTH + j) + 1] = color[game.board.value(j, i)][1];
            // vertex[j][i].b
            vertices[12 * (i * BOARD_WIDTH + j) + 2] = color[game.board.value(j, i)][2];

            // bottom right vertex
            // vertex[j][i].r
            vertices[12 * (i * BOARD_WIDTH + j) + 3] = color[game.board.value(j, i)][0];
            // vertex[j][i].g
            vertices[12 * (i * BOARD_WIDTH + j) + 4] = color[game.board.value(j, i)][1];
            // vertex[j][i].b
            vertices[12 * (i * BOARD_WIDTH + j) + 5] = color[game.board.value(j, i)][2];

            // top right vertex
            // vertex[j][i].r
            vertices[12 * (i * BOARD_WIDTH + j) + 6] = color[game.board.value(j, i)][0];
            // vertex[j][i].g
            vertices[12 * (i * BOARD_WIDTH + j) + 7] = color[game.board.value(j, i)][1];
            // vertex[j][i].b
            vertices[12 * (i * BOARD_WIDTH + j) + 8] = color[game.board.value(j, i)][2];

            // top left vertex
            // vertex[j][i].r
            vertices[12 * (i * BOARD_WIDTH + j) + 9] = color[game.board.value(j, i)][0];
            // vertex[j][i].g
            vertices[12 * (i * BOARD_WIDTH + j) + 10] = color[game.board.value(j, i)][1];
            // vertex[j][i].b
            vertices[12 * (i * BOARD_WIDTH + j) + 11] = color[game.board.value(j, i)][2];
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

void drawPiece(float *vertices) {
    pcStartX = startX + game.pieceX * CUBE_SIZE_X;
    pcStartY = startY + game.pieceY * CUBE_SIZE_Y;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            // bottom left vertex
            // vertex[j][i].x
            vertices[24 * (i * 5 + j)] = pcStartX + j * CUBE_SIZE_X;
            // vertex[j][i].y
            vertices[24 * (i * 5 + j) + 1] = pcStartY + i * CUBE_SIZE_Y;
            // vertex[j][i].z
            vertices[24 * (i * 5 + j) + 2] = 0.0;
            // vertex[j][i].r
            vertices[24 * (i * 5 + j) + 3] = color[(game.currentPiece)->pieceValue(j, i)][0];
            // vertex[j][i].g
            vertices[24 * (i * 5 + j) + 4] = color[game.currentPiece->pieceValue(j, i)][1];
            // vertex[j][i].b
            vertices[24 * (i * 5 + j) + 5] = color[game.currentPiece->pieceValue(j, i)][2];

            // bottom right vertex
            // vertex[j][i].x
            vertices[24 * (i * 5 + j) + 6] = pcStartX + (j + 1) * CUBE_SIZE_X - EPSILON;
            // vertex[j][i].y
            vertices[24 * (i * 5 + j) + 7] = pcStartY + i * CUBE_SIZE_Y;
            // vertex[j][i].z
            vertices[24 * (i * 5 + j) + 8] = 0.0;
            // vertex[j][i].r
            vertices[24 * (i * 5 + j) + 9] = color[game.currentPiece->pieceValue(j, i)][0];
            // vertex[j][i].g
            vertices[24 * (i * 5 + j) + 10] = color[game.currentPiece->pieceValue(j, i)][1];
            // vertex[j][i].b
            vertices[24 * (i * 5 + j) + 11] = color[game.currentPiece->pieceValue(j, i)][2];
            // top right vertex
            // vertex[j][i].x
            vertices[24 * (i * 5 + j) + 12] = pcStartX + (j + 1) * CUBE_SIZE_X - EPSILON;
            // vertex[j][i].y
            vertices[24 * (i * 5 + j) + 13] = pcStartY + (i + 1) * CUBE_SIZE_Y - EPSILON;
            // vertex[j][i].z
            vertices[24 * (i * 5 + j) + 14] = 0.0;
            // vertex[j][i].r
            vertices[24 * (i * 5 + j) + 15] = color[game.currentPiece->pieceValue(j, i)][0];
            // vertex[j][i].g
            vertices[24 * (i * 5 + j) + 16] = color[game.currentPiece->pieceValue(j, i)][1];
            // vertex[j][i].b
            vertices[24 * (i * 5 + j) + 17] = color[game.currentPiece->pieceValue(j, i)][2];
            // top left vertex
            // vertex[j][i].x
            vertices[24 * (i * 5 + j) + 18] = pcStartX + j * CUBE_SIZE_X;
            // vertex[j][i].y
            vertices[24 * (i * 5 + j) + 19] = pcStartY + (i + 1) * CUBE_SIZE_Y - EPSILON;
            // vertex[j][i].z
            vertices[24 * (i * 5 + j) + 20] = 0.0;
            // vertex[j][i].r
            vertices[24 * (i * 5 + j) + 21] = color[game.currentPiece->pieceValue(j, i)][0];
            // vertex[j][i].g
            vertices[24 * (i * 5 + j) + 22] = color[game.currentPiece->pieceValue(j, i)][1];
            // vertex[j][i].b
            vertices[24 * (i * 5 + j) + 23] = color[game.currentPiece->pieceValue(j, i)][2];
        }

    }
}

void indexPiece(unsigned int *ind) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            ind[6 * (i * 5 + j)] = (unsigned int) 4 * i * 5 + 4 * j;
            ind[6 * (i * 5 + j) + 1] = (unsigned int) 4 * i * 5 + 4 * j + 1;
            ind[6 * (i * 5 + j) + 2] = (unsigned int) 4 * i * 5 + 4 * j + 2;
            ind[6 * (i * 5 + j) + 3] = (unsigned int) 4 * i * 5+ 4 * j;
            ind[6 * (i * 5 + j) + 4] = (unsigned int) 4 * i * 5 + 4 * j + 2;
            ind[6 * (i * 5 + j) + 5] = (unsigned int) 4 * i * 5 + 4 * j + 3;
        }
    }
}

void swapRedwithBlue(){
    GLubyte temp;
    for (int i = 0; i < imageSizeY; i++){
        for (int j = 0; j < imageSizeX; j++){
            temp = image[(i * imageSizeX + j) * image_nChannel]; // blue
            image[(i * imageSizeX + j) * image_nChannel] = image[(i * imageSizeX + j) * image_nChannel + 2];
            image[(i * imageSizeX + j) * image_nChannel + 2] = temp;
        }
    }
}

void loadImage (char *filename) {
    FREE_IMAGE_FORMAT formato = FreeImage_GetFIFFromFilename(filename);
    if (formato == FIF_UNKNOWN) {
        cout << "Image format is unknown!\n";
        exit(1);
    }
    FIBITMAP *img = FreeImage_Load(formato, filename);
    if (!img) {
        cout << "Image cannot be found!";
        exit(1);
    }

    FIBITMAP* tempImg = img;
    img = FreeImage_ConvertTo32Bits(tempImg);
    FreeImage_Unload(tempImg);

    imageSizeX = FreeImage_GetWidth(img);
    imageSizeY = FreeImage_GetHeight(img);
    int image_bpp = FreeImage_GetBPP(img);
    image_nChannel = image_bpp / 8;

    image = FreeImage_GetBits(img);
    if (image == nullptr) {
        cout << "Null pointer in image.\n";
        exit(1);
    }
    swapRedwithBlue();
    FreeImage_Unload(img);
}

void generateBackground() {
    float vertices[] = {
            // positions          // texture coords
            -1.0f, -1.0f, 0.0f,   0.0f, 0.0f,  // bottom left
             1.0f, -1.0f, 0.0f,   1.0f, 0.0f,  // bottom right
             1.0f,  1.0f, 0.0f,   1.0f, 1.0f,  // top right
            -1.0f,  1.0f, 0.0f,   0.0f, 1.0f,  // top left
    };
    unsigned int indices[] = {
            0, 1, 2, // first triangle
            0, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &VAO_background);
    glGenBuffers(1, &VBO_background);
    glGenBuffers(1, &EBO_background);

    glBindVertexArray(VAO_background);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_background);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_background);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // load and create a texture
    // -------------------------

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // load image, create texture and generate mipmaps
    char fileName[100];
    strcpy(fileName, backgroundFile);
    loadImage(fileName);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageSizeX, imageSizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void bindBoardVertices() {
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    // Bind board vertices positions and indices

    int numVertices = BOARD_HEIGHT * BOARD_WIDTH * 4;
    auto *positions = new float[numVertices * 3];
    getBoardVertices(positions);


    int numTriangles = BOARD_WIDTH * BOARD_HEIGHT * 2;
    auto *indices = new unsigned int[numTriangles * 3];
    indexVertices(indices);

    glGenVertexArrays(1, &VAO_board);
    glGenBuffers(1, &VBO_boardPositions);
    glGenBuffers(1, &EBO_board);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO_board);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_boardPositions);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertices * 3, positions, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_board);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numTriangles * 3, indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    delete[] positions;
    delete[] indices;
}

Shader compileShader(const char *vertexSource, const char *fragmentSource) {
    // build and compile our shader program
    // ------------------------------------
    Shader shader(vertexSource, fragmentSource);
    return shader;
}

void render(Shader gameShader, Shader backgroundShader) {

    // Bind board vertices colors
    unsigned int VBO_boardColors;
    int numVertices = BOARD_HEIGHT * BOARD_WIDTH * 4;
    int numTriangles = BOARD_WIDTH * BOARD_HEIGHT * 2;
    auto *colors = new float[numVertices * 3];
    getBoardColor(colors);

    glGenBuffers(1, &VBO_boardColors);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO_board);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_boardColors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertices * 3, colors, GL_STATIC_DRAW);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    delete[] colors;

    // Bind piece vertices position, colors and indices
    int pcNumVertices = 5 * 5 * 4;
    auto *vertices = new float[pcNumVertices * 6];
    drawPiece(vertices);
    int pcNumTriangles = 5 * 5 * 2;
    auto *indices = new unsigned int[pcNumTriangles * 3];
    indexPiece(indices);

    unsigned int VBO_piece, VAO_piece, EBO_piece;
    glGenVertexArrays(1, &VAO_piece);
    glGenBuffers(1, &VBO_piece);
    glGenBuffers(1, &EBO_piece);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO_piece);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_piece);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * pcNumVertices * 6, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_piece);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * pcNumTriangles * 3, indices, GL_STATIC_DRAW);

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

    delete[] vertices;
    delete[] indices;


    // render loop
    // -----------

    // input
    // -----
    processInput(window);

    // render
    // ------
//    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // bind Texture
    glBindTexture(GL_TEXTURE_2D, texture);

    // render container
    backgroundShader.use();
    glBindVertexArray(VAO_background);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    gameShader.use();
    gameShader.setFloat("startX", startX);
    gameShader.setFloat("startY", startY);
    gameShader.setFloat("cubeSizeX", CUBE_SIZE_X);
    gameShader.setFloat("cubeSizeY", CUBE_SIZE_Y);
    gameShader.setInt("boardWidth", BOARD_WIDTH);
    gameShader.setInt("boardHeight", BOARD_HEIGHT);

    // draw board
    glBindVertexArray(VAO_board); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawElements(GL_TRIANGLES, numTriangles * 3, GL_UNSIGNED_INT, 0);

    // draw piece
    glBindVertexArray(VAO_piece);
    glDrawElements(GL_TRIANGLES, pcNumTriangles * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0); // no need to unbind it every time


    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();

    glDeleteBuffers(1, &VBO_boardColors);
    glDeleteVertexArrays(1, &VAO_piece);
    glDeleteBuffers(1, &VBO_piece);
    glDeleteBuffers(1, &EBO_piece);
}

void dummyRender() {

    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();

    int x, y;
    glfwGetWindowPos(window, &x, &y);
    glfwSetWindowPos(window, ++x, y);

}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}