#include "rook.h"
#include <vector>
using std::vector;

Rook::Rook(Coord pos, Colour colour, bool firstMove)
  : Piece{pos, colour, Type::Rook, firstMove} {}
Piece *clone() { return new Rook(*this); }

bool Rook::possibleMove(Coord dest) const {
  if ((dest.row == pos.row) && (dest.col == pos.col)) return false;
  else if ((dest.row == pos.row) || (dest.col == pos.col)) return true;
  else return false;
}
bool Rook::possibleMove(int r, int c) const {
  return possibleMove(Coord{.row=r, .col=c});
}

vector<Coord> Rook::requiredEmpty(Coord dest) const {
  vector<Coord> v;
  if (!possibleMove(dest)) {
    v.push_back(pos);
    return v;
  }
  if (pos.row == dest.row) {
    if (pos.col < dest.col) {
      // E
      for (int i = pos.col + 1; i < dest.col; i++) {
        Coord move {pos.row, i};
        v.push_back(move);
      }
    } else {
      // W
      for (int i = pos.col - 1; i > dest.col; i--) {
        Coord move {pos.row, i};
        v.push_back(move);
      }
    }
  } else {
    if (pos.row < dest.row) {
      // N
      for (int i = pos.row + 1; i < dest.row; i++) {
        Coord move {i, pos.col};
        v.push_back(move);
      }
    } else {
      // S
      for (int i = pos.row - 1; i > dest.row; i--) {
        Coord move {i, pos.col};
        v.push_back(move);
      }
    }
  }
  return v;
}
vector<Coord> Rook::requiredEmpty(int r, int c) const {
  return requiredEmpty(Coord{.row=r, .col=c});
}

vector<Coord> Rook::requiredOccupied(Coord dest) const {
  vector<Coord> v;
  // all standard pieces except pawn don't require an enemy piece to move
  // in a certain way
  if  (!possibleMove(dest)) {
    v.push_back(pos);
  }
  return v;
}
vector<Coord> Rook::requiredOccupied(int r, int c) const {
  return requiredOccupied(Coord{.row=r, .col=c});
}
