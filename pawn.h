#ifndef _PAWN_H_
#define _PAWN_H_
#include "piece.h"
#include <vector>
using std::vector;

class Pawn: public Piece {
  vector<Coord> moves;
  vector<Coord> captures;
 public:
  Pawn(Coord pos, Colour colour);
  bool possibleMove(Coord Pos);
  bool possibleCapture(Coord Pos);

};

#endif
