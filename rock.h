#ifndef __ROCK_H__
#define __ROCK_H__
#include "piece.h"
#include <vector>
using std::vector;

class Rock: public Piece {
 public:
  Rock(Coord pos, Colour colour, Type type = Rock);
  bool possibleMove(Coord Pos);
  vector<Coord> requiredEmpty(Coord Pos);
};

#endif
