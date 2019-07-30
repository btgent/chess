#ifndef __KING_H__
#define __KING_H__
#include "piece.h"
#include <vector>

class King: public Piece {
 public:
  King(Coord pos, Colour colour, bool firstMove=true);
  Piece *clone() const override;
  
  bool possibleMove(Coord dest) const override;
  bool possibleMove(int r, int c) const override;
  std::vector<Coord> requiredEmpty(Coord dest) const override;
  std::vector<Coord> requiredEmpty(int r, int c) const override;
  std::vector<Coord> requiredOccupied(Coord dest) const override;
  std::vector<Coord> requiredOccupied(int r, int c) const override;
};

#endif
