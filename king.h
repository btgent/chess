#ifndef __KING_H__
#define __KING_H__
#include "piece.h"
#include <vector>
using std::vector;

class King: public Piece {
 public:
  King(Coord pos, Colour colour, Type type = King);
  bool possibleMove(Coord Pos);
  vector<Coord> requiredEmpty(Coord Pos);
};

#endif
