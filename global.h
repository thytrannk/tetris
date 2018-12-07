#ifndef TETRIS_GLOBAL_H
#define TETRIS_GLOBAL_H

#define SCR_WIDTH 600
#define SCR_HEIGHT 600

#define BOARD_HEIGHT 30
#define BOARD_WIDTH 10

#define CUBE_SIZE_X 0.05f
#define CUBE_SIZE_Y 0.05f

#define TIME_SHORT 0.05s
#define TIME_MID 0.1s

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
extern const char clearLine[];

#endif //TETRIS_GLOBAL_H
