#ifndef __CHESS_H__
#define __CHESS_H__

/* ================== Error Codes ===================  */

#define INVALID_INPUT     1
#define INVALID_MOVE      2
#define NO_PIECE          3
#define WRONG_PLAYER      4
#define GAME_OVER         5

/* ================== Libraries =====================  */

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm> // Used for definition of find()
#include <cmath> // Used for the abs function

using namespace std;


/* ============== Forward declarations ==============  */

class Piece;
class Position;
class ChessBoard;

/* ================== Enumerations===================  */

enum colour { White, Black };

ostream& operator<< (ostream& o, const colour _colour);

enum pieceType { king, queen, rook, knight, bishop, pawn };

ostream& operator<< (ostream& o, const pieceType pType);

// An Exception struct can be thrown & caught in the ChessBoard::submitMove method.
// The use of a struct allows us to carry more information than
// simply throwing an int.
struct Exception {
    int type;
    char file;
    int rank;
    colour c;
    pieceType pi;
    Exception(int t) : type(t) {};
    Exception(int t, char f, int r) : type(t), file(f), rank(r) {};
    Exception(int t, char f, int r, colour _c) : type(t), file(f), rank(r), c(_c) {};
    Exception(int t, char f, int r, colour _c, pieceType _p) : type(t), file(f), rank(r), c(_c), pi(_p) {};
};


/* ============== Function prototypes ===============  */

bool onBoard(char file, int rank);

void exceptionHandler(Exception exception);

#endif 
