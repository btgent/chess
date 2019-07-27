#ifndef _PAWN_H_
#define _PAWN_H_
#include "piece.h"
#include <vector>
using std::vector;

class Pawn: public Piece {
 public:
  Pawn(Coord pos, Colour colour, Type type = Pawn);
  bool possibleMove(Coord Pos);
  vector<Coord> requiredEmpty(Coord Pos);
  vector<Coord> requiredOccupied(Coord Pos);
};

#endif
