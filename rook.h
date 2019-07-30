#ifndef __ROOK_H__
#define __ROOK_H__
#include "piece.h"
#include <vector>

class Rook: public Piece {
 public:
  Rook(Coord pos, Colour colour, bool firstMove=true);
  
  bool possibleMove(Coord dest) const override;
  bool possibleMove(int r, int c) const override;
  std::vector<Coord> requiredEmpty(Coord dest) const override;
  std::vector<Coord> requiredEmpty(int r, int c) const override;
  std::vector<Coord> requiredOccupied(Coord dest) const override;
  std::vector<Coord> requiredOccupied(int r, int c) const override;
};

#endif
