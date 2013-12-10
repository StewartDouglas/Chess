#ifndef Chess_classes_h
#define Chess_classes_h

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm> // Used for definition of find()

using namespace std;

enum colour { White, Black };

enum pieceType { king, queen, castle, knight, bishop, pawn };

bool onBoard(char file, int rank);



class Postion;
class ChessBoard;
class Piece;

// ==============================================================
//                ******  POSITION  ******
// ==============================================================

class Position {
private:
  char file;
  int  rank; 
public:
  Position(char _file, int _rank);
  char getFile() const;
  int  getRank() const;
  friend bool operator< (const Position& pos1, const Position& pos2);
  friend bool operator== (const Position& pos1, const Position& pos2);
};

/*
// ==============================================================
//                ******  CHESSBOARD  ******
// ==============================================================

class ChessBoard {
private:
    map< Position, Piece* > chessBoard;
    colour colourTurn;
    Position whiteKing;
    Position blackKing;
public:
    ChessBoard();
    ~ChessBoard();
    void submitMove(string startPos, string endPos);
    colour colourAtPosition(Position &position);
    bool pieceAtPosition(const Position &position);
    colour showColourTurn();
    void incrementTurn();
    void resetBoard();
    bool onBoard(Position position);
    // Tester method
    void showBoard();
    void allPossibleMoves(colour player, vector<Position> &possibleMoves);
};
*/
/*
// ==============================================================
//                ******  PIECE  ******
// ==============================================================

class Piece {
protected:
    colour pieceColour;
    pieceType pType;
    ChessBoard *chessBoard;
public:
    Piece(colour c, ChessBoard* cb);
    pieceType showType();
    colour showColour();
    // Returns true if there is a piece at a given position.
    // If the piece is of the opponents colour, it will be 
    // added to validPositions.
    bool takePiece(Position position, vector<Position> &validPositions);
    virtual void validMoves(Position position, vector<Position>& validPositions) = 0; // pure virtual function
};

class King : public Piece {
public:
 King(colour c, ChessBoard* cb): Piece(c, cb) { pType = king; };
    void validMoves(Position position, vector<Position>& validPositions);
};
    
class Bishop : public virtual Piece {
public:
 Bishop(colour c, ChessBoard* cb): Piece(c, cb) { };
    virtual void validMoves(Position position, vector<Position>& validPositions);
};

class Castle : public virtual Piece {
public:
 Castle(colour c, ChessBoard* cb): Piece(c, cb) { };
    virtual void validMoves(Position position, vector<Position>& validPositions);
};

class Queen : public virtual Piece, private Bishop, private Castle {
public:
 Queen(colour c, ChessBoard* cb): Piece(c, cb), Bishop(c, cb), Castle(c, cb) { };
    virtual void validMoves(Position position, vector<Position>& validPositions);
};

class Knight : public Piece {
public:
    Knight(colour c, ChessBoard* cb): Piece(c, cb) { };
    void validMoves(Position position, vector<Position>& validPositions);
};

class Pawn : public Piece {
public:
 Pawn(colour c, ChessBoard* cb): Piece(c, cb) { };
    void validMoves(Position position, vector<Position>& validPositions);
};

*/

#endif
