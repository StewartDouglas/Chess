#ifndef __CHESS_CPP__
#define __CHESS_CPP__

#include "chess.h"

// Overload operator<< for my colour enumeration
ostream& operator<< (ostream& o, const colour _colour){
    
    (_colour == White) ? (o << "White") : (o << "Black");
    return o;
}

// Overload operator<< for my pieceType enumeration
ostream& operator<< (ostream& o, const pieceType pType){
    
    if(pType == king)
        o << "King";
    else if(pType == queen)
        o << "Queen";
    else if(pType == rook)
        o << "Rook";
    else if(pType == knight)
        o << "Knight";
    else if(pType == bishop)
        o << "Bishop";
    else if(pType == queen)
        o << "Queen";
    else
        o << "Pawn";
    return o;
}

// Global function onBoard. Returns true is a position, as specifed by a file and a rank,
// would be on a chess board. Used by both Piece and ChessBoard classes.
bool onBoard(char file, int rank){
    return(file >= 'A' && file <= 'H' && rank >= 1 && rank <= 8);
}

// Handle the various user input 'errors' which could arise.
void exceptionHandler(Exception exception){

  switch(exception.type) {
    case INVALID_INPUT:
      cout << "At least one of the input coordinates is not valid." << endl; break;
    case INVALID_MOVE:
      cout << static_cast<colour>(exception.c) << "'s " << exception.pi << " cannot move to " << exception.file << exception.rank << "!" << endl; break;
    case NO_PIECE:
      cout << "There is no piece at position " << exception.file << exception.rank << "!" << endl; break;
    case WRONG_PLAYER:
      cout << "It is not " << exception.c << "'s turn to move!" << endl; break;
    case GAME_OVER:
      cout << "The game is over." << endl; break;
    default:
      cout << "Unknown exception thrown." << endl;
  }
}

#endif
