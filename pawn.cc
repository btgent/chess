#include "pawn.h"
#include <vector>
using std::vector;

Pawn::Pawn(Coord Pos, Colour colour, Type type = Pawn): pos{Pos}, colour{colour}, type{type} {
  type = Pawn;
  firstMove = true;
}

bool Pawn::possibleMove(Coord Pos) {
  if ((Pos.row == pos.row) && (Pos.col == pos.col)) return false;
  switch(colour) {
    case White :
      if (pos.col == Pos.col) {
        if (firstMove && Pos.row == (pos.row + 2) return true;
        else if (Pos.row == (pos.row + 1) return true; 
      }
      else if (pos.col == (Pos.col + 1) && Pos.row == (pos.row + 1)) return true;
      else if (pos.col == (Pos.col - 1) && Pos.row == (pos.row + 1)) return true;
      else return false;
      break;
    
    case Black :
      if (pos.col == Pos.col) {
        if (firstMove && Pos.row == (pos.row - 2) return true;
        else if (Pos.row == (pos.row - 1) return true; 
      }
      else if (pos.col == (Pos.col + 1) && Pos.row == (pos.row - 1)) return true;
      else if (pos.col == (Pos.col - 1) && Pos.row == (pos.row - 1)) return true;
      else return false;
      break;
  }
  return false;
}

vector<Coord> Pawn::requiredEmpty(Coord Pos) {
  vector<Coord> v;
  if (possibleMove(Pos)) {
    switch(colour) {
      case White :
        if (pos.col == Pos.col) {
          for (int i = pos.row; i <= Pos.row; i++) {
            Coord move{i, Pos.col};
            v.push_back(move);
          }
        }
        break;
      
      case Black :
        if (pos.col == Pos.col) {
          for (int i = pos.row; i >= Pos.row; i--) {
            Coord move{i, Pos.col};
            v.push_back(move);
          }
        }
        break;
    }
    return v;
  }
  v.push_back(pos);
  return v;
}
                 
vector<Coord> Pawn::requiredOccupied(Coord Pos) {
  vector<Coord> v;
  if (possibleMove(Pos)) {
    v.push_back(Pos);
    return v;
  }
  v.push_bacK(pos);
  return v;
}
