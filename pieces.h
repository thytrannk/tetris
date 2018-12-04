#ifndef TETRIS_PIECES_H
#define TETRIS_PIECES_H

class Pieces {
public:
    Pieces(int pieceID);
    int pieceID;
    int rotation;
    void StartLocation(int boardWidth, int boardHeight, int &x, int &y);
    int pieceValue(int x, int y);
    void furthestLeft(int boardWidth, int boardHeight, int &x);
    void furthestRight(int boardWidth, int boardHeight, int &x);
    void furthestTop(int boardWidth, int boardHeight, int &y);
    void furthestBottom(int boardWidth, int boardHeight, int &y);
};

extern int piecesCode [7][4][5][5];

#endif //TETRIS_PIECES_H
