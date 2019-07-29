#ifndef _PAWN_H_
#define _PAWN_H_
#include "piece.h"
#include <vector>

class Pawn: public Piece {
 public:
  Pawn(Coord pos, Colour colour, bool firstMove=true);
  
  bool possibleMove(Coord dest) const override;
  bool possibleMove(int r, int c) const override;
  std::vector<Coord> requiredEmpty(Coord dest) const override;
  std::vector<Coord> requiredEmpty(int r, int c) const override;
  std::vector<Coord> requiredOccupied(Coord dest) const override;
  std::vector<Coord> requiredOccupied(int r, int c) const override;
};

#endif
