#include "rook.h"
#include <vector>
using std::vector;

Rook::Rook(Coord Pos, Colour colour, Type type = Rock): pos{Pos}, colour{colour}, type{type} {
  type = Rock;
  firstMove = true;
}

bool Rook::possibleMove(Coord Pos) {
  if ((pos.row == Pos.row) || (pos.col == Pos.col)) return true;
  else return false;
  }
}

vector<Coord> Rook::requiredEmpty(Coord Pos) {
  vector<Coord> v;
  if (possibleMove(Pos)) {
    if (pos.row == Pos.row) {
      if (pos.col < Pos.col) {
        for (i = pos.col + 1; i <= Pos.col; i++) {
          Coord move {pos.row, i};
          v.push_back(move);
        }
      }
      else {
        for (i = pos.col - 1; i >= Pos.col; i--) {
          Coord move {pos.row, i};
          v.push_back(move);
        }
      }
    }
    
    else {
      if (pos.row < Pos.row) {
        for (i = pos.row + 1; i <= Pos.row; i++) {
          Coord move {i, pos.col};
          v.push_back(move);
        }
      }
      else {
        for (i = pos.row - 1; i >= Pos.row; i--) {
          Coord move {i, pos.col};
          v.push_back(move);
        }
      }
    }
    return v;
  }
  v.push_back(pos);
  return v;
}
