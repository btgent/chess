#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "piece.h"
#include "move.h"
#include <vector>
using std::vector;

class Knight: public Piece {
  vector<Coord> moves;
 public:
  Knight(Coord pos, Colour colour);
  bool possibleMove(Coord Pos);
  bool possibleCapture(Coord Pos);
};

#endif
