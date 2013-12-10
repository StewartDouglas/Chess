#include "classes.h"
#include "chess.h"

/*
// ==============================================================
//                ******  POSITION  ******
// ==============================================================

Position::Position(char _file,int _rank): file(_file), rank(_rank) { }

char Position::getFile() const {return file;}

int Position::getRank() const {return rank;}


bool operator< (const Position& pos1, const Position& pos2) 
{
  return ((pos1.getRank() < pos2.getRank()) || ((pos1.getRank() == pos2.getRank()) && (pos1.getFile() < pos2.getFile())));
}

bool operator== (const Position& pos1, const Position& pos2) 
{
  return((pos1.getRank() == pos2.getRank()) && (pos1.getFile() == pos2.getFile()));
}

*/
    
/*
Position Position::changeFile(int _changeFile){
    
    rank += _changeFile;
}

Position Position::changeRank(int _changeRank){
    file += _changeRank;
}

*/

/*
// ==============================================================
//                ******  PIECE  ******
// ==============================================================

// Piece constructor
Piece::Piece(colour c, ChessBoard* cb): pieceColour(c), chessBoard(cb) { }

//Pawn::Pawn(colour _pieceColour): Piece(_pieceColour) { }

colour Piece::showColour() {
  return pieceColour; }

pieceType Piece::showType() { return pType; }

bool Piece::takePiece(Position position, vector<Position> &validPositions){
    if(chessBoard->pieceAtPosition(position)){
      if(chessBoard->colourAtPosition(position) != chessBoard->showColourTurn()){
	validPositions.push_back(position);
      }
      return true;
    }
    return false;
}


// ======================= validMoves() =====================================
void King::validMoves(Position position, vector<Position>& validPositions){ 

  char file = position.getFile();
  int  rank = position.getRank();

  if(onBoard(file + 1,rank)){
    Position position(file+1,rank);
    validPositions.push_back(position);
  }

  if(onBoard(file - 1,rank)){
    Position position(file-1,rank);
    validPositions.push_back(position);
  }

  if(onBoard(file,rank+1)){
    Position position(file,rank+1);
    validPositions.push_back(position);
  }

  if(onBoard(file,rank-1)){
    Position positon(file,rank-1);
    validPositions.push_back(position);
  }

  typedef vector<Position>::iterator it;

  for(it i = validPositions.begin(); i < validPositions.end(); ++i){
    if(chessBoard->pieceAtPosition(*i)){
      if(chessBoard->colourAtPosition(*i) == chessBoard->showColourTurn())
	validPositions.erase(i);
    }
  }

}

void Bishop::validMoves(Position position, vector<Position>& validPositions){ 
  
  char file = position.getFile();
  int rank = position.getRank();

  // Traverse north east
  for(int i = 1; onBoard(file+i,rank+i); i++){
    Position position(file+i,rank+i);
    if(takePiece(position, validPositions)){ 
      cout << "appending " << static_cast<char>(file+i) << rank+i << " to validPositions." << endl;
      break;
    }
    validPositions.push_back(position);
  }

  // Traverse north west
  for(int i = 1; onBoard(file-i,rank+i); i++){
    Position position(file-i,rank+i);
    if(takePiece(position, validPositions)){
      break;
    }
    validPositions.push_back(position);
  }

  // Traverse south east
  for(int i = 1; onBoard(file+i,rank-i); i++){ 
    Position position(file+i,rank-i);
    if(takePiece(position, validPositions)){ 
      break;
    }
    validPositions.push_back(position);
  }
  
  // Traverse south west
  for(int i = 1; onBoard(file-i,rank-i); i++){
    Position position(file-i,rank-i);
    if(takePiece(position, validPositions)){ 
      break;
    }
    validPositions.push_back(position);
  }

  
  typedef vector<Position>::iterator it;

  cout << "The Bishop can move to " << validPositions.size() << " potential squares" << endl;
  for(it i = validPositions.begin(); i != validPositions.end(); i++){
    cout << i->getFile() << i->getRank() << endl;
  }
  cout << endl;
  
}

void Castle::validMoves(Position position, vector<Position>& validPositions){ 
  
  char file = position.getFile();
  int rank = position.getRank();

  // Traverse north
  for(int r = rank + 1; onBoard(file,r); r++){
    Position position(file,r);
    if(takePiece(position, validPositions)){ 
      break;
    }
    validPositions.push_back(position);
  }

  // Traverse south
  for(int r = rank - 1; onBoard(file,r); r--){
    Position position(file,r);
    if(takePiece(position, validPositions)) { 
      break;
    }
    validPositions.push_back(position);
  }

  // Traverse east
  for(char f = file + 1; onBoard(f,rank) ;f++){ 
    Position position(f,rank);
    if(takePiece(position, validPositions)){ 
      break;
    }
    validPositions.push_back(position);
  }
  
  // Traverse west
  for(char f = file - 1; onBoard(f,rank); f--){
    Position position(f,rank);
    if(takePiece(position, validPositions)){ 
      break;
  }
    validPositions.push_back(position);
  }

  
  typedef vector<Position>::iterator it;

  cout << "Castle's potential moves" << endl;
  for(it i = validPositions.begin(); i != validPositions.end(); i++){
    cout << i->getFile() << i->getRank() << endl;
  }
  cout << endl;
  


}

void Queen::validMoves(Position position, vector<Position>& validPositions){ 

  Bishop::validMoves(position, validPositions);
  Castle::validMoves(position, validPositions);

}


void Knight::validMoves(Position position, vector<Position>& validPositions){

    char file = position.getFile();
    int rank = position.getRank();
    
    if(onBoard(file + 2, rank + 1)){
        Position position(file + 2, rank + 1);
        validPositions.push_back(position);
    }
    
    if(onBoard(file + 2, rank - 1)){
        Position position(file + 2, rank - 1);
        validPositions.push_back(position);
    }
    
    if(onBoard(file - 2, rank + 1)){
        Position position(file - 2, rank + 1);
        validPositions.push_back(position);
    }
    
    if(onBoard(file - 2, rank - 1)){
        Position position(file - 2, rank - 1);
        validPositions.push_back(position);
    }
    
    if(onBoard(file + 1, rank + 2)){
        Position position(file + 1, rank + 2);
        validPositions.push_back(position);
    }
    
    if(onBoard(file + 1, rank - 2)){
        Position position(file + 1, rank - 2);
        validPositions.push_back(position);
    }
    
    if(onBoard(file - 1, rank + 2)){
        Position position(file - 1, rank + 2);
        validPositions.push_back(position);
    }
    
    if(onBoard(file - 1, rank - 2)){
        Position position(file - 1, rank - 2);
        validPositions.push_back(position);
    }

    typedef vector<Position>::iterator it;

    for(it i = validPositions.begin(); i < validPositions.end(); ++i){
      // Deliberate choice not to have a single if statement here.
      // Otherwise we risk a segmentation fault when trying to find 
      // the colour at a position which our map doesn't contain
      if(chessBoard->pieceAtPosition(*i) && !((*i) == position)){
	if(chessBoard->colourAtPosition(*i) == chessBoard->showColourTurn())
	  validPositions.erase(i);
      }	
    }
}

void Pawn::validMoves(Position position, vector<Position>& validPositions){ 

    char file = position.getFile();
    int rank = position.getRank();

    // ** WHITE PAWNS **

    // If the square in front of the pawn is free, it can move there
    if(chessBoard->showColourTurn() == White){
      Position position1(file,rank+1);
      if(!takePiece(position1,validPositions)){
	//cout << "There's no piece at " << file << rank+1 << endl;
	validPositions.push_back(position1);
	Position position2(file,rank+2);
	if(rank == 2 && !takePiece(position2,validPositions))
	  validPositions.push_back(position2);
      }
      Position position3(file+1,rank+1);
      takePiece(position3, validPositions);
      Position position4(file-1,rank+1);
      takePiece(position4, validPositions);
    }
    
    // ** BLACK PAWNS **

    if(chessBoard->showColourTurn() == Black){
      Position position1(file,rank-1);
      if(!takePiece(position1,validPositions)){
	validPositions.push_back(position1);
	Position position2(file,rank-2);
	if(rank == 7 && !takePiece(position2,validPositions))
	  validPositions.push_back(position2);
      }
      Position position3(file-1,rank-1);
      takePiece(position3, validPositions);
      Position position4(file+1,rank-1);
      takePiece(position4, validPositions);
    }
}

*/
/*
// ==============================================================
//                ******  CHESSBOARD  ******
// ==============================================================

ChessBoard::ChessBoard() : whiteKing('E',1), blackKing('E',8) {
     
    // We've not yet have any player moves
    cout << "A new chess game is started!" << endl;
  
    // White moves first
    colourTurn = White;

    // Generate white pawns
    for (char i = 'A'; i <= 'H'; i++) {
        Position position(i,2);
        chessBoard[position] = new Pawn(White,this);
    }

    // Generate black pawns
    for (int j = 'A'; j <= 'H'; j++) {
        Position position(j,7);
        chessBoard[position] = new Pawn(Black,this);
    }
    
    // Generate remaining pieces, by iterating over each file in ranks 0 and 7
    for (char k = 'A'; k <= 'H'; k++){
        
      // Initial white positions
      Position position1(k,1);
      // Initial black positions
      Position position2(k,8);
        
        if(k == 'A' || k == 'H'){
	  chessBoard[position1] = new Castle(White,this);
	  chessBoard[position2] = new Castle(Black,this);
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


void ChessBoard::submitMove(string startPos, string endPos){

  try{

    stringstream start_stream(startPos), end_stream(endPos);
    if(start_stream.fail() || end_stream.fail() || startPos.size() != 2 || endPos.size() != 2)
      throw INVALID_INPUT;

    char startFile = startPos[0];
    int  startRank = startPos[1] - 48;

    char endFile   = endPos[0];
    int  endRank   = endPos[1] - 48;

    Position startPosition(startFile, startRank);
    Position endPosition(endFile, endRank);

    if(!onBoard(startPosition) || !onBoard(endPosition))
      throw INVALID_INPUT; 

    if(!(this->pieceAtPosition(startPosition)))
       cout << "There is no piece at " << startFile << startRank << "!" << endl;

    if(this->colourAtPosition(startPosition) != colourTurn)
      cout << "It is not " << (colour) colourTurn << "'s turn to move!" << endl;

    // Stored the valid moves in validMoves
    
    vector<Position> validMoves;
    chessBoard[startPosition]->validMoves(startPosition,validMoves);

    // validate that endPosition is within the pieces range of movement
    if((find(validMoves.begin(), validMoves.end(),endPosition) == validMoves.end()))
      throw INVALID_MOVE;

    // If we make the move, will it cause a check?
    Piece *p = chessBoard[startPosition];
    chessBoard.erase(startPosition);
    chessBoard[endPosition] = p;

    vector<Position> possiblePositions;
    typedef vector<Position> it;

    // Get all the possible moves of the opponent
    allPossibleMoves(static_cast<colour>((colourTurn+1)%2), possiblePositions);
    
    Position *pKing;
    (this->showColourTurn() == White) ? pKing = &whiteKing : pKing = &blackKing;
    
    // If the position of the King is in possiblePositions, then the move will result in check
    if(!(find(possiblePositions.begin(), possiblePositions.end(), *pKing)== possiblePositions.end())){
      chessBoard[startPosition] = p;
      chessBoard.erase(endPosition); 
      throw INVALID_MOVE;
    }

   this->incrementTurn();

   this->showBoard();

  }
  catch(int exceptionCode) {
    exceptionHandler(exceptionCode);
  }

}


bool onBoard(char file, int rank){
    return(file >= 'A' && file <= 'H' && rank >= 1 && rank <= 8);
}


bool ChessBoard::onBoard(Position position){
  return(position.getFile() >= 'A' && position.getFile() <= 'H' && position.getRank() > 0 && position.getRank() <= 8);
}


colour ChessBoard::showColourTurn(){
  return colourTurn;
}

void ChessBoard::incrementTurn(){
  colourTurn == White ? colourTurn = Black : colourTurn = White;
}

colour ChessBoard::colourAtPosition(Position &position){
  return chessBoard[position]->showColour();
}

bool ChessBoard::pieceAtPosition(const Position &position){
  return(!(chessBoard[position] == NULL));
  
}

ChessBoard::~ChessBoard(){
    //delete [] v;
}

void ChessBoard::showBoard(){

  map< Position, Piece* >::iterator it;

  cout << endl;
  for(int i = 8; i >= 1; i--){
    for(char ch = 'A'; ch <= 'H'; ch++){
      Position position(ch,i);
      if(chessBoard[position] != NULL)
	cout << ch << i;
      else{
      cout << "--";
      }
    } 
    cout << endl;
  }
  cout << endl;
}

void ChessBoard::allPossibleMoves(colour player, vector<Position> &possibleMoves){

  typedef map< Position, Piece* >::iterator it;

  // Iterate over all the occupied positions on the chessboard
  for(it i = chessBoard.begin(); i != chessBoard.end(); i++){
    // Check there is a piece at that position
    if(this->pieceAtPosition(i->first)){
      // Check whether it is an opponent's piece
      if((i->second)->showColour() == player){
	  (i->second)->validMoves((i->first),possibleMoves);
      }
    }
  }

  // Remove duplicates from the vector possibleMoves
  sort(possibleMoves.begin(),possibleMoves.end());
  possibleMoves.erase(unique(possibleMoves.begin(),possibleMoves.end()),possibleMoves.end());

  
  typedef vector<Position>::iterator vt;

  for(vt j = possibleMoves.begin(); j != possibleMoves.end(); j++){
    cout << j->getFile() << j->getRank() << endl;
  }
  cout << endl;
  
}

*/
