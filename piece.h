#ifndef __PIECE_H__
#define __PIECE_H__
#include "type.h"
#include "move.h"
#include <vector>

class Piece {
  Coord pos;
  Type type;
  Colour colour;
  bool firstMove;
 public:
  Piece(Coord pos, Type type, Colour colour);
  virtual ~Piece();
  Colour getColour();
  bool virtual possibleMove(Coord Pos) = 0;
  std::vetor<Coord> virtual requireEmpty(Coord Pos) = 0;
  bool virtual possibleMove(Coord Pos) = 0;
  void setPos(Coord Pos);
};

#endif
