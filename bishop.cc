#include "bishop.h"
#include <vector>
using std::vector;

Bishop::Bishop(Coord pos, Colour colour, bool firstMove)
  : Piece{pos, colour, Type::Bishop, firstMove} {}

int abs(int i)  {return (i>0) ? i : -i;}

bool Bishop::possibleMove(Coord dest) const {
  if ((dest.row == pos.row) && (dest.col == pos.col)) return false;
  else if (abs(dest.row - pos.row) == abs(dest.col - pos.col)) return true;
  return false;
}
bool Bishop::possibleMove(int r, int c) const {
  return possibleMove(Coord{.row=r, .col=c});
}

vector<Coord> Bishop::requiredEmpty(Coord dest) const {
  vector<Coord> v;
  if (!possibleMove(dest)) {
    v.push_back(pos);
    return v;
  }
  if (dest.row > pos.row) {
    if (dest.col > pos.col) {
      // NE
      for (int i = 1; (pos.row + i) < dest.row; i++) {
        Coord move {pos.row + i, pos.col + i};
        v.push_back(move);
      }
    } else {
      // NW
      for (int i = 1; (pos.row + i) < dest.row; i++) {
        Coord move {pos.row + i, pos.col - i};
        v.push_back(move);
      }
    }
  } else {
    if (dest.col > pos.col) {
      // SE
      for (int i = 1; (pos.row - i) > dest.row; i++) {
        Coord move {pos.row - i, pos.col + i};
        v.push_back(move);
      }
    } else {
      // SW
      for (int i = 1; (pos.row - i) > dest.row; i++) {
        Coord move {pos.row - i, pos.col - i};
        v.push_back(move);
      }
    }
  }
  return v;
}
vector<Coord> Bishop::requiredEmpty(int r, int c) const {
  return requiredEmpty(Coord{.row=r, .col=c});
}

vector<Coord> Bishop::requiredOccupied(Coord dest) const {
  vector<Coord> v;
  // all standard pieces except pawn don't require an enemy piece to move
  // in a certain way
  if  (!possibleMove(dest)) {
    v.push_back(pos);
  }
  return v;
}
vector<Coord> Bishop::requiredOccupied(int r, int c) const {
  return requiredOccupied(Coord{.row=r, .col=c});
}
