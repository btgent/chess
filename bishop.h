    
#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "piece.h"
#include <vector>
using std::vector;

class Bishop: public Piece {
 public:
  Bishop(Coord pos, Colour colour, Type type = Bishop);
  bool possibleMove(Coord Pos);
  vector<Coord> requiredEmpty(Coord Pos);
};

#endif
