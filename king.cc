#include "king.h"
#include <vector>
using std::vector;

King::King(Coord pos, Colour colour, bool firstMove)
  : Piece{pos, colour, Type::King, firstMove} {}
Piece *King::clone() const { return new King(*this); }

int intabs(int i)  {return (i>0) ? i : -i;}

bool King::possibleMove(Coord dest) const {
  if ((dest.row == pos.row) && (dest.col == pos.col)) return false;
  if ( (intabs(pos.row - dest.row) <= 1) && (intabs(pos.col - dest.col) <= 1) ) return true;
  return false;
}
bool King::possibleMove(int r, int c) const {
  return possibleMove(Coord{.row=r, .col=c});
}

vector<Coord> King::requiredEmpty(Coord dest) const {
  vector<Coord> v;
  // as long as the move is possible, king doesn't need to traverse any squares
  if (!possibleMove(dest)) {
    v.push_back(pos);
  }
  return v;
}
vector<Coord> King::requiredEmpty(int r, int c) const {
  return requiredEmpty(Coord{.row=r, .col=c});
}

vector<Coord> King::requiredOccupied(Coord dest) const {
  vector<Coord> v;
  // all standard pieces except pawn don't require an enemy piece to move
  // in a certain way
  if  (!possibleMove(dest)) {
    v.push_back(pos);
  }
  return v;
}
vector<Coord> King::requiredOccupied(int r, int c) const {
  return requiredOccupied(Coord{.row=r, .col=c});
}
