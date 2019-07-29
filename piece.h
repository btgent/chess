#ifndef __PIECE_H__
#define __PIECE_H__
#include "type.h"
#include "move.h"
#include <vector>

class Piece {
  Coord pos;
  Type type;
  Colour colour;
 public:
  bool firstMove;
  Piece(Coord pos, Colour colour, Type type);
  virtual ~Piece();
  Colour getColour();
  Type getType();
  Coord getPos();
  bool virtual possibleMove(Coord Pos) = 0;
  std::vetor<Coord> virtual requireEmpty(Coord Pos) = 0;
  void setPos(Coord Pos);
};

#endif
