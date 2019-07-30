#ifndef __PIECE_H__
#define __PIECE_H__
#include "coord.h"
#include "type.h"
#include "colour.h"
#include <vector>

class Piece {
 protected:
  Coord pos;
  const Colour colour;
  const Type type;
  bool firstMove;
  
 public:
  Piece(Coord pos, Colour colour, Type type, bool firstMove=true);
  virtual ~Piece();
  
  Coord getPos() const;
  Colour getColour() const;
  Type getType() const;
  bool isFirstMove() const;
  void setPos(Coord);
  Piece *clone() = 0;

  //  Returns whether a move to dest could be considered as a valid move
  // (excluding special moves like castling or a case where a pawn is allowed to
  //  move like a knight, for example)
  virtual bool possibleMove(Coord dest) const = 0;
  virtual bool possibleMove(int r, int c) const = 0;
  // Returns a list of Coord which must be empty for a move to dest to be possible
  // (excluding special moves, and if possibleMove would be false, then requiredEmpty
  // returns a vector with the current coordinates of the piece)
  virtual std::vector<Coord> requiredEmpty(Coord dest) const = 0;
  virtual std::vector<Coord> requiredEmpty(int r, int c) const = 0;
  // Returns a list of Coord which must be occupied by a opposing piece for a move to
  // dest to be possible (excluding special moves, and if possibleMove would be false,
  // then requiredEmpty returns a vector with the current coordinates of the piece)
  virtual std::vector<Coord> requiredOccupied(Coord dest) const = 0;
  virtual std::vector<Coord> requiredOccupied(int r, int c) const = 0;
  
  // If the 3 methods above have their requirements fulfilled and dest is not occupied
  // with a piece of the same colour, then the move can happen as long as the king is not
  // in check afterwards
};

#endif
