#ifndef _PIECE_H_
#define _PIECE_H_
#include "type.h"
#incldue "move.h"

class Piece {
  Coord pos;
  Type type;
  Colour colour;
 public:
  bool virtual possibleMove(Coord Pos) = 0;
  void virtual setPos(Coord Pos) = 0;
}

#endif
