#ifndef __POSITION_H__
#define __POSITION_H__

#include "chess.h"

class Position {
private:
  char file;
  int  rank; 
public:
  Position(char _file, int _rank);
  char getFile() const;
  int  getRank() const;
  // We overload the less than operator, so that we can apply it directly
  // to instances of Position. If position1 has a lower file than position2,
  // we say that position1 is less than position2 (e.g A1 is lower than B1).
  // For position with the same file, we compare by rank.
  friend bool operator< (const Position& pos1, const Position& pos2);
  friend bool operator== (const Position& pos1, const Position& pos2);
  friend ostream& operator<< (ostream& o, const Position& pos);
};

#endif
