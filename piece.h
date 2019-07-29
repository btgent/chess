#ifndef __PIECE_H__
#define __PIECE_H__
#include "coord.h"
#include "type.h"
#include "colour.h"
#include <vector>

class Piece {
  Coord pos;
  const Type type;
  const Colour colour;
  bool firstMove;
  
 public:
  Piece(Coord pos, Type type, Colour colour, bool firstMove=true);
  virtual ~Piece();
  
  Coord getPos();
  Type getType();
  Colour getColour();
  bool isFirstMove();
  void setPos(Coord);

  virtual bool possibleMove(Coord dest) = 0;
  virtual bool possibleMove(int r, int c) = 0;
  virtual std::vector<Coord> requiredEmpty(Coord dest) = 0;
  virtual std::vector<Coord> requiredEmpty(int r, int c) = 0;
  virtual std::vector<Coord> requiredOccupied(Coord dest) = 0;
  virtual std::vector<Coord> requiredOccupied(int r, int c) =0;
};

#endif
