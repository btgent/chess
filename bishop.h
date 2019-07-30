    
#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "piece.h"
#include <vector>

class Bishop: public Piece {
 public:
  Bishop(Coord pos, Colour colour, bool firstMove=true);
  Piece *clone() const override;
  
  bool possibleMove(Coord dest) const override;
  bool possibleMove(int r, int c) const override;
  std::vector<Coord> requiredEmpty(Coord dest) const override;
  std::vector<Coord> requiredEmpty(int r, int c) const override;
  std::vector<Coord> requiredOccupied(Coord dest) const override;
  std::vector<Coord> requiredOccupied(int r, int c) const override;
};

#endif
