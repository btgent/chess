#include "queen.h"
#include <vector>
using std::vector;

Queen::Queen(Coord Pos, Colour colour, Type type = Queen): pos{Pos}, colour{colour}, type{type} {
  type = Queen;
  firstMove = true;
}

bool Queen::possibleMove(Coord Pos) {
  if ((Pos.row == pos.row) && (Pos.col == pos.col)) return false;
  else if ((Pos.row - pos.row) == (Pos.col - pos.col)) return true;
  else if ((Pos.row - pos.row) == (pos.col - Pos.col)) return true;
  else if ((pos.row == Pos.row) || (pos.col == Pos.col)) return true;
  return false;
}

vector<Coord> Queen::requiredEmpty(Coord Pos) {
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
    
    elif (pos.col == Pos.col) {
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
    
    if (Pos.row > pos.row) {
      if (Pos.col > pos.col) {
        for (int i = 1; (pos.row + i) <= Pos.row; i++) {
          Coord move {pos.row + i, pos.col + i};
          v.push_back(move);
        }
      }
      else {
        for (int i = 1; (pos.row + i) <= Pos.row; i++) {
          Coord move {pos.row + i, pos.col - i};
          v.push_back(move);
        }
      }
    }
    
    if (Pos.row < pos.row) {
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
