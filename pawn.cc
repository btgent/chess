#include "pawn.h"
#include <vector>
using std::vector;

Pawn::Pawn(Coord Pos, Colour colour): pos{Pos}, colour{colour} {
  type = Pawn;
  firstMove = true;
}

bool Pawn::possibleMove(Coord Pos) {
  switch(colour) {
    case "White" :
      if (pos.col == Pos.col) {
        if (firstMove && Pos.row == (pos.row + 2) return true;
        else if (Pos.row == (pos.row + 1) return true; 
      }
      else if (pos.col == (Pos.col + 1) && Pos.row == (pos.row + 1)) return true;
      else if (pos.col == (Pos.col - 1) && Pos.row == (pos.row + 1)) return true;
      else return false;
    
    case "Black" :
      if (pos.col == Pos.col) {
        if (firstMove && Pos.row == (pos.row - 2) return true;
        else if (Pos.row == (pos.row - 1) return true; 
      }
      else if (pos.col == (Pos.col + 1) && Pos.row == (pos.row - 1)) return true;
      else if (pos.col == (Pos.col - 1) && Pos.row == (pos.row - 1)) return true;
      else return false;
  }
}

vector<Coord> Pawn::requiredEmpty(Coord Pos) {
  if (possibleMove(Pos)) {
    vector<Coord> v;
    switch(colour) {
      case "White" :
        if (pos.col == Pos.col) {
          for (int i = pos.row; i <= Pos.row; i++) {
            Coord move{i, Pos.col};
            v.push_back(move);
          }
        }
      
      case "Black" :
        if (pos.col == Pos.col) {
          for (int i = pos.row; i >= Pos.row; i--) {
            Coord move{i, Pos.col};
            v.push_back(move);
          }
        }
    }
  return v;
  }
}
                 
vector<Coord> Pawn::requiredOccupied(Coord Pos) {
  if (possibleMove(Pos)) {
    vector<Coord> v;
    v.push_back(Pos);
    return v;
  }
}
