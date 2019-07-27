#ifndef __ROOK_H__
#define __ROOK_H__
#include "piece.h"
#include <vector>
using std::vector;

class Rook: public Piece {
 public:
  Rook(Coord pos, Colour colour, Type type = Rock);
  bool possibleMove(Coord Pos);
  vector<Coord> requiredEmpty(Coord Pos);
};

#endif