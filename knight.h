#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "piece.h"
#include <vector>

class Knight: public Piece {
 public:
  Knight(Coord pos, Colour colour, bool firstMove=true);
  
  bool possibleMove(Coord dest) const override;
  bool possibleMove(int r, int c) const override;
  std::vector<Coord> requiredEmpty(Coord dest) const override;
  std::vector<Coord> requiredEmpty(int r, int c) const override;
  std::vector<Coord> requiredOccupied(Coord dest) const override;
  std::vector<Coord> requiredOccupied(int r, int c) const override;
};

#endif
