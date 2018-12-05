#ifndef TETRIS_GLOBAL_H
#define TETRIS_GLOBAL_H

#define SCR_WIDTH 600
#define SCR_HEIGHT 600

#define BOARD_HEIGHT 12
#define BOARD_WIDTH 8

#define CUBE_SIZE_X 0.07
#define CUBE_SIZE_Y 0.07

#define TIME 0.5s

#define EPSILON 0.0001f

extern const char vertexSource[];
extern const char fragmentSource[];
extern const char vertexBackground[];
extern const char fragmentBackground[];
extern const char backgroundFile[];

extern const char gameMusic[];
extern const char pieceFall[];
extern const char pieceLock[];
extern const char gameOver[];

#endif //TETRIS_GLOBAL_H
