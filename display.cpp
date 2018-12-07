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

float color [11 /*colors*/][3 /*rgb*/] =
        {
                // 0 Empty
                {0.0, 0.0, 0.0},
                // 1 Square
                {1.0, 1.0, 0.0},
                // 2 I
                {0.0, 1.0, 1.0},
                // 3 L
                {1.0, 0.5, 0.0},
                // 4 L mirrored
                {0.0, 0.0, 1.0},
                // 5 Z
                {1.0, 0.0, 0.0},
                // 6 S
                {0.0, 1.0, 0.0},
                // 7 T
                {1.0, 0.0, 1.0},
                // 8 Transparent
                {1.0, 1.0, 1.0},
                // 9 Ghost
                {0.3, 0.3, 0.3},
                // 10 Highlighted (clearing)
                {1.0, 0.8, 0.0},
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

void drawPiece(float *vertices, const string type) {
    if (type == "current" || type == "ghost") {
        pcStartX = startX + game.pieceX * CUBE_SIZE_X;
    } else if (type == "hold") {
        pcStartX = CUBE_SIZE_X * (-BOARD_WIDTH / 2.0f - 7.0f);
    } else {
        pcStartX = CUBE_SIZE_X * (BOARD_WIDTH / 2.0f + 2.0f);
    }
    if (type == "ghost") {
        pcStartY = startY + game.ghostY * CUBE_SIZE_Y;
    } else if (type == "next1" || type == "hold") {
        pcStartY = CUBE_SIZE_Y * (BOARD_HEIGHT / 2.0f - 5.0f);
    } else if (type == "next2") {
        pcStartY = CUBE_SIZE_Y * (BOARD_HEIGHT / 2.0f - 12.0f);
    } else {
        pcStartY = startY + game.pieceY * CUBE_SIZE_Y;
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            // bottom left vertex
            // vertex[j][i].x
            vertices[24 * (i * 5 + j)] = pcStartX + j * CUBE_SIZE_X;
            // vertex[j][i].y
            vertices[24 * (i * 5 + j) + 1] = pcStartY + i * CUBE_SIZE_Y;
            // vertex[j][i].z
            vertices[24 * (i * 5 + j) + 2] = 0.0;

            // bottom right vertex
            // vertex[j][i].x
            vertices[24 * (i * 5 + j) + 6] = pcStartX + (j + 1) * CUBE_SIZE_X - EPSILON;
            // vertex[j][i].y
            vertices[24 * (i * 5 + j) + 7] = pcStartY + i * CUBE_SIZE_Y;
            // vertex[j][i].z
            vertices[24 * (i * 5 + j) + 8] = 0.0;

            // top right vertex
            // vertex[j][i].x
            vertices[24 * (i * 5 + j) + 12] = pcStartX + (j + 1) * CUBE_SIZE_X - EPSILON;
            // vertex[j][i].y
            vertices[24 * (i * 5 + j) + 13] = pcStartY + (i + 1) * CUBE_SIZE_Y - EPSILON;
            // vertex[j][i].z
            vertices[24 * (i * 5 + j) + 14] = 0.0;

            // top left vertex
            // vertex[j][i].x
            vertices[24 * (i * 5 + j) + 18] = pcStartX + j * CUBE_SIZE_X;
            // vertex[j][i].y
            vertices[24 * (i * 5 + j) + 19] = pcStartY + (i + 1) * CUBE_SIZE_Y - EPSILON;
            // vertex[j][i].z
            vertices[24 * (i * 5 + j) + 20] = 0.0;

            if (type == "ghost") {
                if (game.currentPiece->pieceValue(j, i) != 8) {
                    // bottom left vertex
                    // vertex[j][i].r
                    vertices[24 * (i * 5 + j) + 3] = color[9][0];
                    // vertex[j][i].g
                    vertices[24 * (i * 5 + j) + 4] = color[9][1];
                    // vertex[j][i].b
                    vertices[24 * (i * 5 + j) + 5] = color[9][2];

                    // bottom right vertex
                    // vertex[j][i].r
                    vertices[24 * (i * 5 + j) + 9] = color[9][0];
                    // vertex[j][i].g
                    vertices[24 * (i * 5 + j) + 10] = color[9][1];
                    // vertex[j][i].b
                    vertices[24 * (i * 5 + j) + 11] = color[9][2];

                    // top right vertex
                    // vertex[j][i].r
                    vertices[24 * (i * 5 + j) + 15] = color[9][0];
                    // vertex[j][i].g
                    vertices[24 * (i * 5 + j) + 16] = color[9][1];
                    // vertex[j][i].b
                    vertices[24 * (i * 5 + j) + 17] = color[9][2];

                    // top left vertex
                    // vertex[j][i].r
                    vertices[24 * (i * 5 + j) + 21] = color[9][0];
                    // vertex[j][i].g
                    vertices[24 * (i * 5 + j) + 22] = color[9][1];
                    // vertex[j][i].b
                    vertices[24 * (i * 5 + j) + 23] = color[9][2];
                } else {
                    // bottom left vertex
                    // vertex[j][i].r
                    vertices[24 * (i * 5 + j) + 3] = color[8][0];
                    // vertex[j][i].g
                    vertices[24 * (i * 5 + j) + 4] = color[8][1];
                    // vertex[j][i].b
                    vertices[24 * (i * 5 + j) + 5] = color[8][2];

                    // bottom right vertex
                    // vertex[j][i].r
                    vertices[24 * (i * 5 + j) + 9] = color[8][0];
                    // vertex[j][i].g
                    vertices[24 * (i * 5 + j) + 10] = color[8][1];
                    // vertex[j][i].b
                    vertices[24 * (i * 5 + j) + 11] = color[8][2];

                    // top right vertex
                    // vertex[j][i].r
                    vertices[24 * (i * 5 + j) + 15] = color[8][0];
                    // vertex[j][i].g
                    vertices[24 * (i * 5 + j) + 16] = color[8][1];
                    // vertex[j][i].b
                    vertices[24 * (i * 5 + j) + 17] = color[8][2];

                    // top left vertex
                    // vertex[j][i].r
                    vertices[24 * (i * 5 + j) + 21] = color[8][0];
                    // vertex[j][i].g
                    vertices[24 * (i * 5 + j) + 22] = color[8][1];
                    // vertex[j][i].b
                    vertices[24 * (i * 5 + j) + 23] = color[8][2];
                }
            } else {
                int val;
                if (type == "next1") {
                    val = game.next1Piece->pieceValue(j, i);
                } else if (type == "next2") {
                    val = game.next2Piece->pieceValue(j, i);
                } else if (type == "hold") {
                    if (game.holdPiece) {
                        val = game.holdPiece->pieceValue(j, i);
                    } else {
                        val = 0;
                    }
                } else {
                    if (game.currentPiece) {
                        val = game.currentPiece->pieceValue(j, i);
                    } else {
                        val = 8; // current piece has been deleted, so render as transparent
                    }
                }
                // bottom left vertex
                // vertex[j][i].r
                vertices[24 * (i * 5 + j) + 3] = color[val][0];
                // vertex[j][i].g
                vertices[24 * (i * 5 + j) + 4] = color[val][1];
                // vertex[j][i].b
                vertices[24 * (i * 5 + j) + 5] = color[val][2];

                // bottom right vertex
                // vertex[j][i].r
                vertices[24 * (i * 5 + j) + 9] = color[val][0];
                // vertex[j][i].g
                vertices[24 * (i * 5 + j) + 10] = color[val][1];
                // vertex[j][i].b
                vertices[24 * (i * 5 + j) + 11] = color[val][2];

                // top right vertex
                // vertex[j][i].r
                vertices[24 * (i * 5 + j) + 15] = color[val][0];
                // vertex[j][i].g
                vertices[24 * (i * 5 + j) + 16] = color[val][1];
                // vertex[j][i].b
                vertices[24 * (i * 5 + j) + 17] = color[val][2];

                // top left vertex
                // vertex[j][i].r
                vertices[24 * (i * 5 + j) + 21] = color[val][0];
                // vertex[j][i].g
                vertices[24 * (i * 5 + j) + 22] = color[val][1];
                // vertex[j][i].b
                vertices[24 * (i * 5 + j) + 23] = color[val][2];
            }
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

//Shader compileShader(const char *vertexSource, const char *fragmentSource) {
//    // build and compile our shader program
//    // ------------------------------------
//    Shader shader(vertexSource, fragmentSource);
//    return shader;
//}

void bindPiece(string type, unsigned int *indices, unsigned int *VBO_piece, unsigned int *VAO_piece, unsigned int EBO_piece) {
    const int pcNumVertices = 100; // 5 blocks * 5 blocks * 4 corners
    auto *piece = new float[pcNumVertices * 6];
    drawPiece(piece, type);

    // bind vertex array

    glGenVertexArrays(1, VAO_piece);
    glGenBuffers(1, VBO_piece);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(*VAO_piece);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO_piece);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * pcNumVertices * 6, piece, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_piece);

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

    delete[] piece;
}

void render(Shader &gameShader, Shader &backgroundShader, bool currentPiece) {

    // if currentPiece == true, current piece is rendered
    // if currentPiece == false, rendering the board when lines are being cleared, so current piece is not rendered

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

    // Create current piece, next pieces and ghost vertices position, colors and indices

    unsigned int VBO_current, VAO_current, EBO_piece, VBO_ghost, VAO_ghost,
            VBO_next1, VAO_next1, VBO_next2, VAO_next2, VBO_hold, VAO_hold;

    auto *indices = new unsigned int[150]; // 5 blocks * 5 blocks * 2 triangles * 3 vertices
    indexPiece(indices);

    glGenBuffers(1, &EBO_piece);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_piece);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 150, indices, GL_STATIC_DRAW);

    if (currentPiece) {
        // bind vertex array for ghost
        bindPiece("ghost", indices, &VBO_ghost, &VAO_ghost, EBO_piece);
        // bind vertex array for current piece
        bindPiece("current", indices, &VBO_current, &VAO_current, EBO_piece);
    }

    // bind vertex array for next1 piece
    bindPiece("next1", indices, &VBO_next1, &VAO_next1, EBO_piece);

    // bind vertex array for next2 piece
    bindPiece("next2", indices, &VBO_next2, &VAO_next2, EBO_piece);

    // bind vertex array for hold piece
    bindPiece("hold", indices, &VBO_hold, &VAO_hold, EBO_piece);

    // render loop
    // -----------

    // input
    // -----
    processInput(window);

    // render
    // ------
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
    gameShader.setBool("nextPc", false);
    gameShader.setFloat("cubeSizeX", CUBE_SIZE_X);
    gameShader.setFloat("cubeSizeY", CUBE_SIZE_Y);
    gameShader.setInt("boardWidth", BOARD_WIDTH);
    gameShader.setInt("boardHeight", BOARD_HEIGHT);

    // draw board
    glBindVertexArray(VAO_board); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawElements(GL_TRIANGLES, numTriangles * 3, GL_UNSIGNED_INT, 0);

    if (currentPiece) {
        // draw ghost
        glBindVertexArray(VAO_ghost);
        glDrawElements(GL_TRIANGLES, 150, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0); // no need to unbind it every time

        // draw current piece
        glBindVertexArray(VAO_current);
        glDrawElements(GL_TRIANGLES, 150, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0); // no need to unbind it every time
    }

    gameShader.setFloat("startX", CUBE_SIZE_X * (BOARD_WIDTH / 2.0f + 2.0f));
    gameShader.setFloat("startY", CUBE_SIZE_X * (BOARD_WIDTH / 2.0f - 12.0f));
    gameShader.setBool("nextPc", true);

    // draw next1 piece
    glBindVertexArray(VAO_next1);
    glDrawElements(GL_TRIANGLES, 150, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0); // no need to unbind it every time

    // draw next2 piece
    glBindVertexArray(VAO_next2);
    glDrawElements(GL_TRIANGLES, 150, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0); // no need to unbind it every time

    gameShader.setFloat("startX", CUBE_SIZE_X * (-BOARD_WIDTH / 2.0f - 7.0f));
    gameShader.setFloat("startY", CUBE_SIZE_X * (BOARD_WIDTH / 2.0f - 5.0f));

    // draw hold piece
    glBindVertexArray(VAO_hold);
    glDrawElements(GL_TRIANGLES, 150, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0); // no need to unbind it every time

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();

    glDeleteBuffers(1, &VBO_boardColors);
    if (currentPiece) {
        glDeleteVertexArrays(1, &VAO_current);
        glDeleteBuffers(1, &VBO_current);
        glDeleteVertexArrays(1, &VAO_ghost);
        glDeleteBuffers(1, &VBO_ghost);
    }
    glDeleteVertexArrays(1, &VAO_next1);
    glDeleteBuffers(1, &VBO_next1);
    glDeleteVertexArrays(1, &VAO_next2);
    glDeleteBuffers(1, &VBO_next2);
    glDeleteVertexArrays(1, &VAO_hold);
    glDeleteBuffers(1, &VBO_hold);
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
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}