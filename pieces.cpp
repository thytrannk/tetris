#include "pieces.h"

int piecesCode [7 /*kind */ ][4 /* rotation */ ][5 /* horizontal blocks */ ][5 /* vertical blocks */ ] =
        {
        // Square
            {
                {
                    {8, 8, 8, 8, 8},
                    {8, 8, 8, 8, 8},
                    {8, 8, 1, 1, 8},
                    {8, 8, 1, 1, 8},
                    {8, 8, 8, 8, 8}
                },
                {
                    {8, 8, 8, 8, 8},
                    {8, 8, 8, 8, 8},
                    {8, 8, 1, 1, 8},
                    {8, 8, 1, 1, 8},
                    {8, 8, 8, 8, 8}
                },
                {
                    {8, 8, 8, 8, 8},
                    {8, 8, 8, 8, 8},
                    {8, 8, 1, 1, 8},
                    {8, 8, 1, 1, 8},
                    {8, 8, 8, 8, 8}
                },
                {
                    {8, 8, 8, 8, 8},
                    {8, 8, 8, 8, 8},
                    {8, 8, 1, 1, 8},
                    {8, 8, 1, 1, 8},
                    {8, 8, 8, 8, 8}
                }
            },
        // I
            {
                {
                    {8, 8, 8, 8, 8},
                    {8, 8, 8, 8, 8},
                    {8, 2, 2, 2, 2},
                    {8, 8, 8, 8, 8},
                    {8, 8, 8, 8, 8}
                },
                {
                    {8, 8, 8, 8, 8},
                    {8, 8, 2, 8, 8},
                    {8, 8, 2, 8, 8},
                    {8, 8, 2, 8, 8},
                    {8, 8, 2, 8, 8}
                },
                {
                    {8, 8, 8, 8, 8},
                    {8, 8, 8, 8, 8},
                    {2, 2, 2, 2, 8},
                    {8, 8, 8, 8, 8},
                    {8, 8, 8, 8, 8}
                },
                {
                    {8, 8, 2, 8, 8},
                    {8, 8, 2, 8, 8},
                    {8, 8, 2, 8, 8},
                    {8, 8, 2, 8, 8},
                    {8, 8, 8, 8, 8}
                }
            },
        // L
            {
                {
                    {8, 8, 8, 8, 8},
                    {8, 8, 3, 8, 8},
                    {8, 8, 3, 8, 8},
                    {8, 8, 3, 3, 8},
                    {8, 8, 8, 8, 8}
                },
                {
                    {8, 8, 8, 8, 8},
                    {8, 8, 8, 8, 8},
                    {8, 3, 3, 3, 8},
                    {8, 3, 8, 8, 8},
                    {8, 8, 8, 8, 8}
                },
                {
                    {8, 8, 8, 8, 8},
                    {8, 3, 3, 8, 8},
                    {8, 8, 3, 8, 8},
                    {8, 8, 3, 8, 8},
                    {8, 8, 8, 8, 8}
                },
                {
                    {8, 8, 8, 8, 8},
                    {8, 8, 8, 3, 8},
                    {8, 3, 3, 3, 8},
                    {8, 8, 8, 8, 8},
                    {8, 8, 8, 8, 8}
                }
            },
        // L mirrored
            {
                {
                    {8, 8, 8, 8, 8},
                    {8, 8, 4, 8, 8},
                    {8, 8, 4, 8, 8},
                    {8, 4, 4, 8, 8},
                    {8, 8, 8, 8, 8}
                },
                {
                    {8, 8, 8, 8, 8},
                    {8, 4, 8, 8, 8},
                    {8, 4, 4, 4, 8},
                    {8, 8, 8, 8, 8},
                    {8, 8, 8, 8, 8}
                },
                {
                    {8, 8, 8, 8, 8},
                    {8, 8, 4, 4, 8},
                    {8, 8, 4, 8, 8},
                    {8, 8, 4, 8, 8},
                    {8, 8, 8, 8, 8}
                },
                {
                    {8, 8, 8, 8, 8},
                    {8, 8, 8, 8, 8},
                    {8, 4, 4, 4, 8},
                    {8, 8, 8, 4, 8},
                    {8, 8, 8, 8, 8}
                }
            },
        // Z
            {
                {
                    {8, 8, 8, 8, 8},
                    {8, 8, 8, 5, 8},
                    {8, 8, 5, 5, 8},
                    {8, 8, 5, 8, 8},
                    {8, 8, 8, 8, 8}
                },
                {
                    {8, 8, 8, 8, 8},
                    {8, 8, 8, 8, 8},
                    {8, 5, 5, 8, 8},
                    {8, 8, 5, 5, 8},
                    {8, 8, 8, 8, 8}
                },
                {
                    {8, 8, 8, 8, 8},
                    {8, 8, 5, 8, 8},
                    {8, 5, 5, 8, 8},
                    {8, 5, 8, 8, 8},
                    {8, 8, 8, 8, 8}
                },
                {
                    {8, 8, 8, 8, 8},
                    {8, 5, 5, 8, 8},
                    {8, 8, 5, 5, 8},
                    {8, 8, 8, 8, 8},
                    {8, 8, 8, 8, 8}
                }
            },
        // S
            {
                {
                    {8, 8, 8, 8, 8},
                    {8, 8, 6, 8, 8},
                    {8, 8, 6, 6, 8},
                    {8, 8, 8, 6, 8},
                    {8, 8, 8, 8, 8}
                },
                {
                    {8, 8, 8, 8, 8},
                    {8, 8, 8, 8, 8},
                    {8, 8, 6, 6, 8},
                    {8, 6, 6, 8, 8},
                    {8, 8, 8, 8, 8}
                },
                {
                    {8, 8, 8, 8, 8},
                    {8, 6, 8, 8, 8},
                    {8, 6, 6, 8, 8},
                    {8, 8, 6, 8, 8},
                    {8, 8, 8, 8, 8}
                },
                {
                    {8, 8, 8, 8, 8},
                    {8, 8, 6, 6, 8},
                    {8, 6, 6, 8, 8},
                    {8, 8, 8, 8, 8},
                    {8, 8, 8, 8, 8}
                }
            },
        // T
            {
                {
                    {8, 8, 8, 8, 8},
                    {8, 8, 7, 8, 8},
                    {8, 8, 7, 7, 8},
                    {8, 8, 7, 8, 8},
                    {8, 8, 8, 8, 8}
                },
                {
                    {8, 8, 8, 8, 8},
                    {8, 8, 8, 8, 8},
                    {8, 7, 7, 7, 8},
                    {8, 8, 7, 8, 8},
                    {8, 8, 8, 8, 8}
                },
                {
                    {8, 8, 8, 8, 8},
                    {8, 8, 7, 8, 8},
                    {8, 7, 7, 8, 8},
                    {8, 8, 7, 8, 8},
                    {8, 8, 8, 8, 8}
                },
                {
                    {8, 8, 8, 8, 8},
                    {8, 8, 7, 8, 8},
                    {8, 7, 7, 7, 8},
                    {8, 8, 8, 8, 8},
                    {8, 8, 8, 8, 8}
                }
            }
        };

// Pieces definition
Pieces::Pieces(int id) {
    pieceID = id;
    rotation = 0;
}

void Pieces::StartLocation(int boardWidth, int boardHeight, int &x, int &y) {
    // save the starting point board coordinates of a piece
    x = boardWidth / 2 - 2;
    furthestTop(boardWidth, boardHeight, y);
}

//float piecesColor [7 /*kind*/] =
//        {
//        // Square
//            1,
//        // I
//            2,
//        // L
//            3,
//        // L mirrored
//            4,
//        // Z
//            5,
//        // S
//            6,
//        // T
//            7,

int Pieces::pieceValue(int x, int y) {

    return (piecesCode[pieceID][rotation][4-y][x]);
//    cout << "pieceID=" << pieceID << endl;
//    cout << "rotation=" << rotation << endl;
//    cout << "piecesCode[pieceID][rotation][x][y]" << piecesCode[pieceID][rotation][x][y] << endl;
//    return 2;
}

void Pieces::furthestBottom(int boardWidth, int boardHeight, int &y){
    if (pieceID == 0) {
        // square
        y = -1;
    } else if (pieceID == 1) {
        // I
        y = -2;
    } else if (pieceID == 2) {
        // L
        y = -1;
    } else if (pieceID == 3) {
        // L mirrored
        y = -1;
    } else if (pieceID == 4) {
        // Z
        y = -1;
    } else if (pieceID == 5) {
        // S
        y = -1;
    } else {
        // T
        y = -1;
    }
}

void Pieces::furthestTop(int boardWidth, int boardHeight, int &y) {
    if (pieceID == 0) {
        // square
        y = boardHeight - 3;
    } else if (pieceID == 1) {
        // I
        y = boardHeight - 3;
    } else if (pieceID == 2) {
        // L
        y = boardHeight - 4;
    } else if (pieceID == 3) {
        // L mirrored
        y = boardHeight - 4;
    } else if (pieceID == 4) {
        // Z
        y = boardHeight - 4;
    } else if (pieceID == 5) {
        // S
        y = boardHeight - 4;
    } else {
        // T
        y = boardHeight - 4;
    }
}

void Pieces::furthestLeft(int boardWidth, int boardHeight, int &x) {
    if (pieceID == 0) {
        // square
        x = boardWidth - 2;
    } else if (pieceID == 1) {
        // I
        if (rotation == 0) {
            x = boardWidth - 1;
        } else if (rotation == 1) {
            x = boardWidth - 2;
        } else if (rotation == 2) {
            x = boardWidth;
        } else if (rotation == 3) {
            x = boardWidth - 2;
        }
    } else if (pieceID == 2 || pieceID == 3) {
        // L or L mirrored
        if (rotation == 2) {
            x = boardHeight - 2;
        } else {
            x = boardHeight - 1;
        }
    } else {
        // Z or S or T
        if (rotation == 0) {
            x = boardHeight - 2;
        } else {
            x = boardHeight - 1;
        }
    }
}