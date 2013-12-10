#ifndef __CHESSBOARD_CPP__
#define __CHESSBOARD_CPP__

#include "chessboard.h"

typedef map< Position, Piece* >::iterator it;
typedef vector<Position>::iterator v_itr;

// ==================================================================================
//                            **  METHOD: Constructor **
// ==================================================================================

ChessBoard::ChessBoard() : whiteKing('E',1), blackKing('E',8) {
    cout << "A new chess game is started!" << endl;
    resetBoard();
}

// ==================================================================================
//                            ** METHOD:  Destructor **
// ==================================================================================

ChessBoard::~ChessBoard(){
  clearBoard();
}

// ==================================================================================
//                           **  METHOD: submitMove **
// ==================================================================================

void ChessBoard::submitMove(string startPos, string endPos){

  bool pieceTakenFlag = false;
  bool inCheckFlag = false;
  bool inCheckMateFlag = false;
  bool stalemateFlag = false;
    
  try{

    if(gameOver){
      Exception exep(GAME_OVER);
      throw exep;
    }

    stringstream start_stream(startPos), end_stream(endPos);

    // If the input is not a string of length two then we have an invalid input
    if(start_stream.fail() || end_stream.fail() || startPos.size() != 2 || endPos.size() != 2){  
      Exception exep(INVALID_INPUT);
      throw exep;
    }

    // '0' is the 48th ASCII character
    char startFile = startPos[0];
    int  startRank = startPos[1] - 48;
    char endFile   = endPos[0];
    int  endRank   = endPos[1] - 48;

    Position startPosition(startFile, startRank);
    Position endPosition(endFile, endRank);
     
    // Get the opponent's colour
    colour opponentsColour = static_cast<colour>(((this->showColourTurn())+1)%2);

    // Check that both of the user inputs are on the board
    if(!onBoard(startFile,startRank) || !onBoard(endFile,endRank)){
      Exception exep(INVALID_INPUT);
      throw exep;
    }

    // Check there is a piece at the user's specified start position
    if(!(this->pieceAtPosition(startPosition))){
      Exception exep(NO_PIECE,startFile,startRank);
      throw exep;
    }
    
    // Check the user is not trying to move a piece of the incorrect colour
    if(colourAtPosition(startPosition) != showColourTurn()){
      Exception exep(WRONG_PLAYER,startFile,startRank,opponentsColour);
      throw exep;
    }

    // Store the valid moves of the piece we're moving in validMoves
    vector<Position> validMoves;
    chessBoard[startPosition]->validMoves(startPosition,validMoves);

    // Validate that endPosition is within the piece's range of movement
    if((find(validMoves.begin(), validMoves.end(),endPosition) == validMoves.end())){
      Exception exep(INVALID_MOVE,endFile,endRank,showColourTurn(),chessBoard[startPosition]->showType());
        throw exep;
    }
          
    // ========================== Make the move ========================================
      
    Piece *takenPiece = chessBoard[endPosition];
    if(this->pieceAtPosition(endPosition)){
        chessBoard.erase(endPosition);
        pieceTakenFlag = true;
    }
    Piece *p = chessBoard[startPosition];
    chessBoard.erase(startPosition);
    chessBoard[endPosition] = p;
    // Handle the case where we are moving our King
    if(p->showType() == king){
        this->updateKingPosition(this->showColourTurn(),endPosition);
    }
    
    // ==================================================================================
    //          **  If we make the move, will it cause us to be in check?  **
    // ==================================================================================
    // If the move puts us in check, then it is an invalid move, which we must undo.
    
    // ========================== Undo the move, if necessary ===========================

    if(inCheck(this->showColourTurn())){
      chessBoard[startPosition] = p;
      chessBoard.erase(endPosition);
      if(pieceTakenFlag){
	    chessBoard[endPosition] = takenPiece;
        pieceTakenFlag = false;
      }
      // Handle the case where we are moving our King
      if(p->showType() == king){
        this->updateKingPosition(showColourTurn(),startPosition);
      }
      Exception exep(INVALID_MOVE,endFile,endRank,showColourTurn(),chessBoard[startPosition]->showType());
        throw exep;
    }

    // ==================================================================================
    //             **  Are we putting our opponent in check or check mate?  **
    // ==================================================================================
      
    if(inCheck(opponentsColour)){
      inCheckFlag = true;
           
      if(nonCheckMoves(opponentsColour)){
        inCheckMateFlag = true;
        gameNowOver();
      }
    }

    // ==================================================================================
    //                          **  Are we in stalemate?  **
    // ==================================================================================
    // Stalemate occurs if the player is not currently in check, but does not have any
    // valid moves they can make. For every piece of the opponent, check whether
    // there are any valid moves they can make, using nonCheckMoves function.
    
    if(nonCheckMoves(opponentsColour) && !inCheckFlag){
      stalemateFlag = true;
	  gameNowOver();
    }
     
    // ==================================================================================
    //                       **  Output to the console **
    // ==================================================================================
       
    cout << this->showColourTurn() << "'s " << *p << " moves from " << startPosition << " to " << endPosition;
      
    if(pieceTakenFlag)
      cout << " taking " << opponentsColour << "'s " << *takenPiece;
      
    if(inCheckFlag && !inCheckMateFlag){
      cout << endl;
      cout << opponentsColour << " is in check";
    }
      
    if(inCheckMateFlag){
      cout << endl;
      cout << opponentsColour << " is in check mate";
    }
      
    cout << endl;
       
    if(stalemateFlag){
      cout << "The game is now in stalemate" <<endl;;
    }
       
    this->incrementTurn();

   }
   catch(Exception exceptionCode) {
     exceptionHandler(exceptionCode);
   }
}

// METHOD: showColourTurn. Show to colour of the current player
colour ChessBoard::showColourTurn(){
  return colourTurn;
}

// METHOD: incrementTurn. Change the current player.
void ChessBoard::incrementTurn(){
  colourTurn == White ? colourTurn = Black : colourTurn = White;
}

// METHOD: colourAtPosition: returns the colour of the piece at the specified position
colour ChessBoard::colourAtPosition(Position &position){
  return chessBoard[position]->showColour();
}

// METHOD: pieceAtPosition: returns true if there is a piece at the specified position
bool ChessBoard::pieceAtPosition(const Position &position){
  return(!(chessBoard[position] == NULL));
  
}

// ==================================================================================
//                      **  METHOD: allPossibleMoves **
// ==================================================================================
/* For a given state of the board, what are all the possible postions that player 
   can move to?                                                                    */

void ChessBoard::allPossibleMoves(colour player, vector<Position> &possibleMoves){

  // Iterate over all the occupied positions on the chessboard
  for(it i = chessBoard.begin(); i != chessBoard.end(); i++){
    // Check there is a piece at that position
    if(this->pieceAtPosition(i->first)){
      // Check whether it is one of your pieces
        if((i->second)->showColour() == player){
            (i->second)->validMoves((i->first),possibleMoves);
      }
    }
  }

  // Remove duplicates from the vector possibleMoves
  sort(possibleMoves.begin(),possibleMoves.end());
  possibleMoves.erase(unique(possibleMoves.begin(),possibleMoves.end()),possibleMoves.end());
    
}

// ==================================================================================
//                          ** METHOD: inCheck  **
// ==================================================================================
// Check whether, given the current board layout, a player is in check.

bool ChessBoard::inCheck(colour player){
  
  Position *myKing;
  (player == White) ? (myKing = &whiteKing) : (myKing = &blackKing);
    
  vector<Position> opponentsPossiblePositions;
  allPossibleMoves(static_cast<colour>((player+1)%2),opponentsPossiblePositions);
    
  return(find(opponentsPossiblePositions.begin(),opponentsPossiblePositions.end(),*myKing) != opponentsPossiblePositions.end());

}

// ==================================================================================
//                         ** METHOD: nonCheckMoves  **
// ==================================================================================
// The nonCheckMoves method checks whether, for a given player, there are any valid
// moves they can make which do not put them in check. This is used for determining
// both whether a player is in check mate and whether the game is in stalemate.
// If there are **are** such moves we return false, otherwise we return true.


bool ChessBoard::nonCheckMoves(colour opponentsColour){
    
  bool takenPieceFlag = false;

  map<Position, Piece*> opponentsPieces;
    
  // Copy the relevant key-values pairs from our chessboard map to make sure
  // that we are not iterating over and editing the same object
  for(it i = chessBoard.begin(); i != chessBoard.end(); i++){
              
    // Only copy over those key-value pairs relevant to the opponent
    if(pieceAtPosition(i->first)){
      if((i->second)->showColour() == opponentsColour)
	    opponentsPieces[i->first] = i->second;
      }
    }
    
    vector<Position> validMvs;
    // Iterate over all the opponents positions & pieces pairs
    for(it j = opponentsPieces.begin(); j != opponentsPieces.end(); j++){
              
      validMvs.clear();

      // Record the set of places the opponent could move to
      (j->second)->validMoves(j->first, validMvs);
           
      // For each possible move, make the move and check whether the opponent is still in check
      for(v_itr v = validMvs.begin(); v != validMvs.end(); v++){

        Piece *takenPiece = chessBoard[*v];
        // Handle the case where we take an opponent's piece
        if(pieceAtPosition(*v)){
          chessBoard.erase(*v);
          takenPieceFlag = true;
        }
	
        // Handle the case where we are moving our King
        if((j->second)->showType() == king){
	      updateKingPosition(opponentsColour,*v);
	    }

        // Get the relevant piece type
        Piece *pi = j->second;
        // Erase the Position:Piece* entry in the chessboard map
        chessBoard.erase(j->first);
        // Create a new entry in the map
        chessBoard[*v] = pi;
                  
        if(!inCheck(opponentsColour)){

	      // Undo the change we made to our chessboard
          chessBoard[j->first] = j->second;
          chessBoard.erase(*v);
          if(takenPieceFlag){
	        chessBoard[*v] = takenPiece;
            takenPieceFlag = false;
          }
	      // Return the king position to its initival value
	      if((j->second)->showType() == king){
            updateKingPosition(opponentsColour,j->first);
	      }
	    return false;
        }
             
	    // Undo the change we made to our chessboard
        chessBoard[j->first] = j->second;
        chessBoard.erase(*v);
        if(takenPieceFlag){
	      chessBoard[*v] = takenPiece;
	      takenPieceFlag = false;
        }

	    // Return the king position to its initival value
	    if((j->second)->showType() == king){
	      updateKingPosition(opponentsColour,j->first);
	    }
    }
  }
  // If we have got to this stage, then we know there are not any valid
  // moves the player can make which will not put them in check.
  return true;
}

// ==================================================================================
//                          **  METHOD: resetBoard **
// ==================================================================================

void ChessBoard::resetBoard(){

    clearBoard();
    
    // The game is now currently in play
    gameOver = false;

    // White moves first
    colourTurn = White;

    // Generate white's pawns
    for (char i = 'A'; i <= 'H'; i++) {
        Position position(i,2);
        chessBoard[position] = new Pawn(White,this);
    }

    // Generate black pawns
    for (int j = 'A'; j <= 'H'; j++) {
        Position position(j,7);
        chessBoard[position] = new Pawn(Black,this);
    }
    
    // Generate remaining pieces, by iterating over each file in ranks 1 and 8
    for (char k = 'A'; k <= 'H'; k++){
        
      // Initial white positions
      Position position1(k,1);
      // Initial black positions
      Position position2(k,8);
        
        if(k == 'A' || k == 'H'){
	      chessBoard[position1] = new Rook(White,this);
	      chessBoard[position2] = new Rook(Black,this);
        }
        else if(k == 'B' || k == 'G'){
	      chessBoard[position1] = new Knight(White,this);
	      chessBoard[position2] = new Knight(Black,this);
        }
        else if(k == 'C' || k == 'F'){
	      chessBoard[position1] = new Bishop(White,this);
	      chessBoard[position2] = new Bishop(Black,this);
        }
        else if(k == 'D'){
	      chessBoard[position1] = new Queen(White,this);
	      chessBoard[position2] = new Queen(Black,this);
        }
        else if(k == 'E'){
	      chessBoard[position1] = new King(White,this);
	      chessBoard[position2] = new King(Black,this);
        }
    }  
}

// METHOD: updateKingPosition: updates the record of the specified King
void ChessBoard::updateKingPosition(colour player, Position newPosition){
    (player == White) ? (whiteKing = newPosition) : (blackKing = newPosition);
}

// METHOD: clearBoard: clear the free store
void ChessBoard::clearBoard(){
  for(it i = chessBoard.begin(); i != chessBoard.end(); i++){
    if(i->second){
      delete i->second;
    }
   }

  chessBoard.clear();
}

// METHOD: gameNowOver: set the gameOver flag to true
void ChessBoard::gameNowOver(){
  gameOver = true;
}

#endif
