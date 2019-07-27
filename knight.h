#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "piece.h"
#include "move.h"
#include <vector>
using std::vector;

class Knight: public Piece {
 public:
  Knight(Coord pos, Colour colour, Type type = Knight);
  bool possibleMove(Coord Pos);
  vector<Coord> requiredEmpty(Coord Pos);
};

#endif
