#ifndef __PIECE_H__
#define __PIECE_H__

#include "chess.h"
#include "chessboard.h"
#include "position.h"

// ==================================================================================
//                         ** SUPERCLASS: Piece **
// ==================================================================================

class Piece {
protected:
    colour pieceColour;
    pieceType pType;
    ChessBoard *chessBoard;
public:
    Piece(colour c, ChessBoard* cb);
    virtual ~Piece();
    pieceType showType() const;
    colour showColour();
    // Returns true if there is a chess piece at the specified position. False otherwise.
    // If the piece at the position is of a different colour from the piece invoking this method
    // then the poisition in question will be added to the validPositions vector
    bool takePiece(Position position, vector<Position> &validPositions);
    virtual void validMoves(Position position, vector<Position>& validPositions) = 0; // pure virtual function
    friend ostream& operator<< (ostream& o, const Piece& piece);
};

// ==================================================================================
//                         ** SUBCLASS: King **
// ==================================================================================

class King : public Piece {
public:
    King(colour c, ChessBoard* cb): Piece(c, cb) { pType = king; };
    void validMoves(Position position, vector<Position>& validPositions);
};

// ==================================================================================
//                         ** SUBCLASS: Bishop **
// ==================================================================================

class Bishop : public virtual Piece {
public:
 Bishop(colour c, ChessBoard* cb): Piece(c, cb) { pType = bishop; };
    virtual void validMoves(Position position, vector<Position>& validPositions);
};

// ==================================================================================
//                         ** SUBCLASS: Rook **
// ==================================================================================

class Rook : public virtual Piece {
public:
 Rook(colour c, ChessBoard* cb): Piece(c, cb) { pType = rook; };
    virtual void validMoves(Position position, vector<Position>& validPositions);
};

// ==================================================================================
//                         ** SUBCLASS: Queen **
// ==================================================================================

class Queen : public virtual Piece, private Bishop, private Rook {
public:
 Queen(colour c, ChessBoard* cb): Piece(c, cb), Bishop(c, cb), Rook(c, cb) { pType = queen; };
    virtual void validMoves(Position position, vector<Position>& validPositions);
};

// ==================================================================================
//                         ** SUBCLASS: Knight **
// ==================================================================================

class Knight : public Piece {
public:
    Knight(colour c, ChessBoard* cb): Piece(c, cb) { pType = knight; };
    void validMoves(Position position, vector<Position>& validPositions);
};

// ==================================================================================
//                         ** SUBCLASS: Pawn **
// ==================================================================================

class Pawn : public Piece {
public:
 Pawn(colour c, ChessBoard* cb): Piece(c, cb) { pType = pawn; };
    void validMoves(Position position, vector<Position>& validPositions);
};


#endif
