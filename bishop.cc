#include "bishop.h"
#include <vector>
using std::vector;

Bishop::Bishop(Coord Pos, Colour colour, Type type = Bishop): pos{Pos}, colour{colour}, type{type} {
  type = Bishop;
  firstMove = true;
}

bool Bishop::possibleMove(Coord Pos) {
  if ((Pos.row == pos.row) && (Pos.col == pos.col)) return false;
  else if ((Pos.row - pos.row) == (Pos.col - pos.col)) return true;
  else if ((Pos.row - pos.row) == (pos.col - Pos.col)) return true;
  return false;
}

vector<Coord> Bishop::requiredEmpty(Coord Pos) {
  vector<Coord> v;
  if (possibleMove(Pos)) {
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
    
    else {
      if (Pos.col > pos.col) {
        for (int i = 1; (pos.row - i) >= Pos.row; i++) {
          Coord move {pos.row - i, pos.col + i};
          v.push_back(move);
        }
      }
      else {
        for (int i = 1; (pos.row - i) >= Pos.row; i++) {
          Coord move {pos.row - i, pos.col - i};
          v.push_back(move);
        }
      }
    }
    return v;
  }
  v.push_back(pos);
  return v;
}
