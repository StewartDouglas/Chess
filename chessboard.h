#ifndef __CHESSBOARD_H__
#define __CHESSBOARD_H__

#include "chess.h"
#include "position.h"
#include "piece.h"

class ChessBoard {
private:
    map< Position, Piece* > chessBoard;
    colour colourTurn;
    Position whiteKing;
    Position blackKing;
    bool gameOver; 
public:
    ChessBoard();
    ~ChessBoard();
    void submitMove(string startPos, string endPos);
    colour colourAtPosition(Position &position);
    bool pieceAtPosition(const Position &position);
    colour showColourTurn();
    void incrementTurn();
    void resetBoard();
    // allPossibleMoves: Generates all the possible positons a user
    // could move an arbitrary piece to
    void allPossibleMoves(colour player, vector<Position> &possibleMoves);
    bool inCheck(colour player);
    // nonCheckMoves: Determines whether there are any valid moves a user can make
    // which do not result in them being in check
    bool nonCheckMoves(colour opponentsColour);
    void updateKingPosition(colour player, Position newPosition);
    void clearBoard();
    void gameNowOver();
};

#endif
