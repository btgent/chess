#ifndef _PIECE_H_
#define _PIECE_H_
#include "type.h"
#include "move.h"

class Piece {
  Coord pos;
  Type type;
  Colour colour;
 public:
  Piece(Coord pos, Type type, Colour colour);
  ~Piece();
  bool virtual possibleMove(Coord Pos) = 0;
  void setPos(Coord Pos);
};

#endif
