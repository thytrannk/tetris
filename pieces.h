#ifndef TETRIS_PIECES_H
#define TETRIS_PIECES_H

class Pieces {
public:
    Pieces(int pieceID);
    int *shape;
    int pieceID;
    void StartLocation(int boardWidth, int boardHeight, int &x, int &y);
    bool IsBlockFilled (int piece, int rotation, int x, int y);
};

extern int piecesCode [7][4][5][5];

#endif //TETRIS_PIECES_H
