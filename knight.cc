#include "knight.h"
#include <vector>
using std::vector;

Knight::Knight(Coord Pos, Colour colour): pos{Pos}, colour{colour} {
  type = Pawn;
  firstMove = true;
}

bool Knight::possibleMove(Coord Pos) {
  if ((Pos.col == pos.col + 2) || (Pos.col == pos.col - 2)) {
    if ((Pos.row == pos.row + 1) || (Pos.row == pos - 1)) return true;
    else return false;
  }
  if ((Pos.col == pos.col + 1) || (Pos.col == pos.col - 1)) {
    if ((Pos.row == pos.row + 2) || (Pos.row == pos - 2)) return true;
    else return false;
  }
}

vector<Coord> Knight::requiredEmpty(Coord Pos) {
   if (possibleMove(Coord Pos)) {
     vector<Coord> v;
     v.push_back(Pos);
   }
}
