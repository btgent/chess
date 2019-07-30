#include "queen.h"
#include <vector>
using std::vector;

Queen::Queen(Coord Pos, Colour colour, bool firstMove)
  : Piece{pos, colour, Type::Queen, firstMove} {}

int abs(int i)  {return (i>0) ? i : -i;}

bool Queen::possibleMove(Coord dest) const {
  if ((dest.row == pos.row) && (dest.col == pos.col)) return false;
  else if (abs(dest.row - pos.row) == abs(dest.col - pos.col)) return true;
  else if ((pos.row == dest.row) || (pos.col == dest.col)) return true;
  return false;
}
bool Queen::possibleMove(int r, int c) const {
  return possibleMove(Coord{.row=r, .col=c});
}

vector<Coord> Queen::requiredEmpty(Coord dest) const {
  vector<Coord> v;
  if (!possibleMove(dest)) {
    v.emplace_back(pos);
    return v;
  }
  
  if (pos.row < dest.row) {
    if (pos.col < dest.col) {
      // NE
      for (int i = 1; (pos.row + i) < dest.row; i++) {
        Coord move {pos.row + i, pos.col + i};
        v.push_back(move);
      }
    } else if (pos.col == dest.col) {
      // N
      for (int i = pos.row + 1; i < dest.row; i++) {
        Coord move {i, pos.col};
        v.push_back(move);
      }
    } else {
      // NW
      for (int i = 1; (pos.row + i) < dest.row; i++) {
        Coord move {pos.row + i, pos.col - i};
        v.push_back(move);
      }
    }
  } else if (pos.row == dest.row) {
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
    if (pos.col < dest.col) {
      // SE
      for (int i = 1; (pos.row - i) > dest.row; i++) {
        Coord move {pos.row - i, pos.col + i};
        v.push_back(move);
      }
    } else if (pos.col == dest.col) {
      // S
      for (int i = pos.row - 1; i > dest.row; i--) {
        Coord move {i, pos.col};
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
vector<Coord> Queen::requiredEmpty(int r, int c) const {
  return requiredEmpty(Coord{.row=r, .col=c});
}

vector<Coord> Queen::requiredOccupied(Coord dest) const {
  vector<Coord> v;
  // all standard pieces except pawn don't require an enemy piece to move
  // in a certain way
  if  (!possibleMove(dest)) {
    v.push_back(pos);
  }
  return v;
}
vector<Coord> Queen::requiredOccupied(int r, int c) const {
  return requiredOccupied(Coord{.row=r, .col=c});
}
