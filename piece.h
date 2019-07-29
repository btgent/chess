#ifndef __PIECE_H__
#define __PIECE_H__
#include "coord.h"
#include "type.h"
#include "colour.h"
#include <vector>

class Piece {
  Coord pos;
  const Colour colour;
  const Type type;
  bool firstMove;
  
 public:
  Piece(Coord pos, Colour colour, Type type, bool firstMove=true);
  virtual ~Piece();
  
  Coord getPos();
  Colour getColour();
  Type getType();
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
