#include "pawn.h"
#include <vector>
using std::vector;

Pawn::Pawn(Coord Pos, Colour colour, bool firstMove)
  : Piece{pos, Type::Pawn, colour, firstMove} {}

bool Pawn::possibleMove(Coord dest) const {
  switch(colour) {
    case White :
      // forward move
      if (pos.col == dest.col) {
        if (dest.row == (pos.row + 1)) return true; 
        else if (firstMove && dest.row == (pos.row + 2)) return true;
      }
      // capture move
      else if (pos.col == (dest.col + 1) && dest.row == (pos.row + 1)) return true;
      else if (pos.col == (dest.col - 1) && dest.row == (pos.row + 1)) return true;
      break;
    
    case Black :
      if (pos.col == dest.col) {
        if (dest.row == (pos.row - 1)) return true; 
        else if (firstMove && dest.row == (pos.row - 2)) return true;
      }
      else if (pos.col == (dest.col + 1) && dest.row == (pos.row - 1)) return true;
      else if (pos.col == (dest.col - 1) && dest.row == (pos.row - 1)) return true;
  }
  // If all cases fail, then the move is generally not allowed
  return false;
}
bool Pawn::possibleMove(int r, int c) const {
  return possibleMove(Coord{.row=r, .col=c});
}

vector<Coord> Pawn::requiredEmpty(Coord dest) const {
  vector<Coord> v;
  // If move is not possible, return vector with current position
  if (!possibleMove(dest)) {
    v.push_back(pos);
    return v;
  }
  
  switch(colour) {
    case White :
      // forward move (general case does not require empty spaces
      //               for capture move)
      if (pos.col == dest.col) {
        for (int i = pos.row+1; i <= dest.row; i++) {
          Coord move{i, dest.col};
          v.push_back(move);
        }
      }
      break;
    
    case Black :
      if (pos.col == dest.col) {
        for (int i = pos.row-1; i >= dest.row; i--) {
          Coord move{i, dest.col};
          v.push_back(move);
        }
      }
      break;
  }
  return v;
}
vector<Coord> Pawn::requiredEmpty(int r, int c) const {
  return requiredEmpty(Coord{.row=r, .col=c});
}
                 
vector<Coord> Pawn::requiredOccupied(Coord dest) const {
  vector<Coord> v;
  // If move is not possible, return vector with current position
  if (!possibleMove(dest)) {
    v.push_back(pos);
    return v;
  }
  // If the move is a capture move, add dest must be occupied
  // (enpassant is a special case not covered by this method)
  if (pos.col != dest.col) {
    v.push_back(dest);
  }
  return v;
}
vector<Coord> Pawn::requiredOccupied(int r, int c) const {
  return requiredOccupied(Coord{.row=r, .col=c});
}
