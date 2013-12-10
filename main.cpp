#include "main.h"

int main(){

    ChessBoard cb;
    
cb.submitMove("A2","A4");
cb.submitMove("A7","A5");
cout << endl;
cb.submitMove("B2","B4");
cb.submitMove("B7","B5");
cout << endl;
cb.submitMove("C2","C4");
cb.submitMove("C7","C5");
cout << endl;
cb.submitMove("D2","D4");
cb.submitMove("D7","D5");
cout << endl;
cb.submitMove("E2","E4");
cb.submitMove("E7","E5");
cout << endl;
cb.submitMove("F2","F4");
cb.submitMove("F7","F5");
cout << endl;
cb.submitMove("G2","G4");
cb.submitMove("G7","G5");
cout << endl;
cb.submitMove("H2","H4");
cb.submitMove("H7","H5");
cout << endl;
cb.submitMove("H4","G5");
cb.submitMove("H5","G4");
cout << endl;
cb.submitMove("H1","H4");
cb.submitMove("H8","H5");
cout << endl;
cb.submitMove("A4","B5");
cb.submitMove("A5","B4");
cout << endl;
cb.submitMove("C4","D5");
cb.submitMove("C5","D4");
cout << endl;
cb.submitMove("E4","F5");
cb.submitMove("E5","F4");
cout << endl;
cb.submitMove("H4","G4");
cb.submitMove("H5","G5");
cout << endl;
cb.submitMove("G4","F4");
cb.submitMove("G5","F5");
cout << endl;
cb.submitMove("F4","D4");
cb.submitMove("F5","D5");
cout << endl;
cb.submitMove("D4","B4");
cb.submitMove("D5","B5");
cout << endl;
cb.submitMove("B4","A4");
cb.submitMove("B5","B1");
cout << endl;
cb.submitMove("C1","A3");
cb.submitMove("D8","D3");
cout << endl;
cb.submitMove("A3","B2");
cb.submitMove("D3","D2");
cout << endl;

    // ==================================================
    // Check which are the valid moves for a castle or knight piece
    // ==================================================

    /*

    Castle castle(white,&cb);
    Knight knight(white,&cb);

    Position pos('B',1);
    Position pos2('C',3);

    
    vector<Position> vec1;
    vector<Position> vec2;

    castle.validMoves(pos,vec1);
    knight.validMoves(pos2,vec2);
    


    // White


    // Black
    cb.submitMove("B7","B6");

    // White
    cb.submitMove("D2","D3");

    // Black    
    cb.submitMove("C7","C6");

    // White    
    cb.submitMove("E2","E3");

    // Black
    cb.submitMove("D7","D6");

    // White
    cb.submitMove("D1","D2");

    // Black
    cb.submitMove("E7","E6");

    // White
    cb.submitMove("D2","A5");

    cb.submitMove("Z2","A5");
  


    */

    //cb.showBoard();
    /*

    typedef vector<Position>:: iterator it;

    for(it i = vec2.begin(); i < vec2.end(); i++)
      cout << (*i).getFile() << " " << (*i).getRank() << endl;

    */
    // ==================================================
    // ==================================================


    return 0;    

};
