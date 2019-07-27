#include "king.h"
#include <vector>
using std::vector;

King::King(Coord Pos, Colour colour, Type type = King): pos{Pos}, colour{colour}, type{type} {
  type = King;
  firstMove = true;
}

bool King::possibleMove(Coord Pos) {
  if ((Pos.row == pos.row) && (Pos.col == pos.col)) return false;
  elif (((Pos.row - pos.row) >= -1) && ((Pos.row - pos.row) <= 1)) {
    if (((Pos.col - pos.col) >= -1) && ((Pos.col - pos.col) <= 1)) return true;
  }
  return false;
}

vector<Coord> King::requiredEmpty(Coord Pos) {
  vector<Coord> v;
  if (possibleMove(Pos)) {
    v.push_back(Pos);
  }
  v.push_back(pos);
  return v;  
}
