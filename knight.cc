#include "knight.h"
#include <vector>
using std::vector;

Knight::Knight(Coord Pos, Colour colour, bool firstMove)
  : Piece{pos, colour, Type::Knight, firstMove} {}

bool Knight::possibleMove(Coord dest) const {
  if ((dest.col == pos.col + 2) || (dest.col == pos.col - 2)) {
    if ((dest.row == pos.row + 1) || (dest.row == pos - 1)) return true;
  }
  if ((dest.col == pos.col + 1) || (dest.col == pos.col - 1)) {
    if ((dest.row == pos.row + 2) || (dest.row == pos - 2)) return true;
  }
  return false;
}
bool Knight::possibleMove(int r, int c) const {
  return possibleMove(Coord{.row=r, .col=c});
}

vector<Coord> Knight::requiredEmpty(Coord dest) const {
  vector<Coord> v;
  // as long as the move is possible, knight doesn't need to traverse any squares
  if (!possibleMove(dest)) {
    v.push_back(pos);
  }
  return v;
}
vector<Coord> Knight::requiredEmpty(int r, int c) const {
  return requiredEmpty(Coord{.row=r, .col=c});
}

vector<Coord> Knight::requiredOccupied(Coord dest) const {
  vector<Coord> v;
  // all standard pieces except pawn don't require an enemy piece to move
  // in a certain way
  if  (!possibleMove(dest)) {
    v.push_back(pos);
  }
  return v;
}
vector<Coord> Knight::requiredOccupied(int r, int c) const {
  return requiredOccupied(Coord{.row=r, .col=c});
}
