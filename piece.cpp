#ifndef __PIECE_CPP__
#define __PIECE_CPP__

#include "piece.h"

// ==================================================================================
//                            **  METHOD: Constructor **
// ==================================================================================

Piece::Piece(colour c, ChessBoard* cb): pieceColour(c), chessBoard(cb) { }

// ==================================================================================
//                            ** METHOD:  Destructor **
// ==================================================================================

Piece::~Piece() {}

// ==================================================================================

// METHOD: showColour: return the colour of a piece
colour Piece::showColour() { return pieceColour; }

// METHOD: showType: return the type of a piece (e.g. Knight, Rook etc.)
pieceType Piece::showType() const { return pType; }

// METHOD: takePiece: Returns true if there is a chess piece at the specified position. False
// otherwise. If the piece at the position is of a different colour from the piece invoking
// this method then the poisition in question will be added to the validPositions vector
bool Piece::takePiece(Position position, vector<Position> &validPositions){
    if(chessBoard->pieceAtPosition(position)){
      if(chessBoard->colourAtPosition(position) != this->showColour()){
          validPositions.push_back(position);
      }
      return true;
    }
    return false;
}

// ==================================================================================
//                            ** METHOD:  validMoves **
// ==================================================================================

// Each subclass or Piece has a different implementation of validMoves. In each
// implementation every valid move a piece can make, not taking into account check,
// is added to the vector validPositions.


// ============================= King ===============================================

void King::validMoves(Position position, vector<Position>& validPositions){

  char file = position.getFile();
  int  rank = position.getRank();

  for(int i = -1; i <= 1; i++){
    for(int j = -1; j <= 1; j++){
      // Of the 9 possible (i,j) pairs, all potentially represent valid moves,
      // except (0,0) which would represent the King staying in the same position.
      if(i == 0 && j == 0) continue;
      if(onBoard(file+i,rank+j)){
	    Position position(file+i,rank+j);
	    if(chessBoard->pieceAtPosition(position)){
	      if(chessBoard->colourAtPosition(position) != this->showColour()){
	        validPositions.push_back(position);
	      }
	    }
	    else validPositions.push_back(position);
      }
    }
  }
}

// ============================= Bishop =============================================
// To calculate the validPositions, we iterate in the four diagonal directions in
// which a Bishop is permitted to move. We traverse in each direction until we
// reach another piece (or move off the board). If we reach another piece of the
// opposite colour, we add that piece's position to validPositons and then stop
// iterating. The logic for handling encountering other pieces is contained in
// the takePiece method.

void Bishop::validMoves(Position position, vector<Position>& validPositions){ 
  
  char file = position.getFile();
  int rank = position.getRank();

  // Traverse north east
  for(int i = 1; onBoard(file+i,rank+i); i++){
    Position positionNE(file+i,rank+i);
    if(takePiece(positionNE, validPositions)){
      break;
    }
    validPositions.push_back(positionNE);
  }

  // Traverse north west
  for(int i = 1; onBoard(file-i,rank+i); i++){
    Position positionNW(file-i,rank+i);
    if(takePiece(positionNW, validPositions)){
      break;
    }
    validPositions.push_back(positionNW);
  }

  // Traverse south east
  for(int i = 1; onBoard(file+i,rank-i); i++){ 
    Position positionSE(file+i,rank-i);
    if(takePiece(positionSE, validPositions)){
      break;
    }
    validPositions.push_back(positionSE);
  }
  
  // Traverse south west
  for(int i = 1; onBoard(file-i,rank-i); i++){
    Position positionSW(file-i,rank-i);
    if(takePiece(positionSW, validPositions)){
      break;
    }
    validPositions.push_back(positionSW);
  }
}

// ============================= Rook ===============================================
/* To calculate the validPositions, we iterate in the four directions in
   which a Rook is permitted to move. We traverse in each direction until we
   reach another piece (or move off the board). If we reach another piece of the
   opposite colour, we add that piece's position to validPositons and then stop
   iterating. The logic for handling encountering other pieces is contained in
   the takePiece method.                                                           */

void Rook::validMoves(Position position, vector<Position>& validPositions){
  
  char file = position.getFile();
  int rank = position.getRank();

  // Traverse north
  for(int r = rank + 1; onBoard(file,r); r++){
    Position positionN(file,r);
    if(takePiece(positionN, validPositions)){
      break;
    }
    validPositions.push_back(positionN);
  }

  // Traverse south
  for(int r = rank - 1; onBoard(file,r); r--){
    Position positionS(file,r);
    if(takePiece(positionS, validPositions)) {
      break;
    }
    validPositions.push_back(positionS);
  }

  // Traverse east
  for(char f = file + 1; onBoard(f,rank) ;f++){ 
    Position positionE(f,rank);
    if(takePiece(positionE, validPositions)){
      break;
    }
    validPositions.push_back(positionE);
  }
  
  // Traverse west
  for(char f = file - 1; onBoard(f,rank); f--){
    Position positionW(f,rank);
    if(takePiece(positionW, validPositions)){
      break;
  }
    validPositions.push_back(positionW);
  }
}

// ============================= Queen ==============================================

void Queen::validMoves(Position position, vector<Position>& validPositions){ 

    Bishop::validMoves(position, validPositions);
    Rook::validMoves(position, validPositions);

}

// ============================= Knight =============================================

void Knight::validMoves(Position position, vector<Position>& validPositions){

    char file = position.getFile();
    int rank = position.getRank();

    for(int i = -2; i <= 2; i++){
      for(int j = -2; j <= 2; j++){
        // Of the 25 (i,j) pairs, only those with abs(i)+abs(j)==3 are relevant
	    if((abs(i) + abs(j) == 3) && onBoard(file+i,rank+j)){
	      Position position(file+i,rank+j);
	      if(chessBoard->pieceAtPosition(position)){
	        if(chessBoard->colourAtPosition(position) != this->showColour()){
	          validPositions.push_back(position);
	        }
	      }
	      else validPositions.push_back(position);
	    }
      }
    }

}

// ============================= Pawn =============================================
/* The Pawn is the most complicated piece to handle, because it movement is dependent
   on its position on the board, and we have asymmetry: black pawns are different
   from white pawns in terms of their movement (unlike the other pieces). Because of
   this complexity I handle white pawns and black pawns separately.              */

void Pawn::validMoves(Position position, vector<Position>& validPositions){ 

  char file = position.getFile();
    int rank = position.getRank();

    // ** WHITE PAWNS **
    // If the square in front of the pawn is free, it can move there
    if(chessBoard->colourAtPosition(position) == White){
      Position position1(file,rank+1);
      if(!(chessBoard->pieceAtPosition(position1))){
          validPositions.push_back(position1);
          Position position2(file,rank+2);
          //If the pawn is at its starting position, it can move two squares
          if(rank == 2 && !(chessBoard->pieceAtPosition(position2)))
            validPositions.push_back(position2);
          }
      // The pawn can only take pieces diagonally
      Position position3(file+1,rank+1);
      takePiece(position3, validPositions);
      Position position4(file-1,rank+1);
      takePiece(position4, validPositions);
    }
    
    // ** BLACK PAWNS **
    if(chessBoard->colourAtPosition(position) == Black){
      Position position1(file,rank-1);
      if(!(chessBoard->pieceAtPosition(position1))){
          validPositions.push_back(position1);
          Position position2(file,rank-2);
          if(rank == 7 && !(chessBoard->pieceAtPosition(position2)))
              validPositions.push_back(position2);
      }
      Position position3(file-1,rank-1);
      takePiece(position3, validPositions);
      Position position4(file+1,rank-1);
      takePiece(position4, validPositions);
    }
}

// ==================================================================================
//                    **  FREIND FUNCTION: output to the console **
// ==================================================================================

ostream& operator<< (ostream& o, const Piece& piece){
    o << piece.showType();
    return o;
}

#endif
