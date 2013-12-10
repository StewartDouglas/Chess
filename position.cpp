#ifndef __POSITION_CPP__
#define __POSITION_CPP__

#include "position.h"

// ==================================================================================
//                            **  METHOD: Constructor **
// ==================================================================================

Position::Position(char _file,int _rank): file(_file), rank(_rank) { }

// METHOD: getFile: returns a position's file
char Position::getFile() const {return file;}

// METHOD: getRank: returns a position's rank
int Position::getRank() const {return rank;}


// ==================================================================================
//                            **  Overloaded operators **
// ==================================================================================

bool operator< (const Position& pos1, const Position& pos2) 
{
  return ((pos1.getRank() < pos2.getRank()) || ((pos1.getRank() == pos2.getRank()) && (pos1.getFile() < pos2.getFile())));
}

bool operator== (const Position& pos1, const Position& pos2) 
{
  return((pos1.getRank() == pos2.getRank()) && (pos1.getFile() == pos2.getFile()));
}

ostream& operator<< (ostream& o, const Position& pos){
    o << pos.getFile() << pos.getRank();
    return o;
    
}

#endif
