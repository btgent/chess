#include "knight.h"
#include <vector>
using std::vector;

Knight::Knight(Coord Pos, Colour colour, Type type = Knight): pos{Pos}, colour{colour}, type{type} {
  type = Knight;
  firstMove = true;
}

bool Knight::possibleMove(Coord Pos) {
  if ((Pos.col == pos.col + 2) || (Pos.col == pos.col - 2)) {
    if ((Pos.row == pos.row + 1) || (Pos.row == pos - 1)) return true;
  }
  if ((Pos.col == pos.col + 1) || (Pos.col == pos.col - 1)) {
    if ((Pos.row == pos.row + 2) || (Pos.row == pos - 2)) return true;
  }
  return false;
}

vector<Coord> Knight::requiredEmpty(Coord Pos) {
  vector<Coord> v;
   if (possibleMove(Coord Pos)) {
     v.push_back(Pos);
     return v;
   }
  v.push_back(pos);
  return v;
}
