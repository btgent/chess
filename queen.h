#ifndef __QUEEN_H__
#define __QUEEN_H__
#include "piece.h"
#include <vector>
using std::vector;

class Queen: public Piece {
 public:
  Queen(Coord pos, Colour colour, Type type = Queen);
  bool possibleMove(Coord Pos);
  vector<Coord> requiredEmpty(Coord Pos);
};

#endif
