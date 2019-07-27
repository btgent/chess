#include "pawn.h"
#include <vector>

Pawn::Pawn(Coord Pos, Colour colour): pos{Pos}, colour{colour} {
  type = Pawn;
  if (Pos.row == 1) {
    Coord move1 {2, Pos.col};
    moves.push_back(move1);
    Coord move2 {3, Pos.col};
    moves.push_back(move2);
  }
  else if (Pos.row != 8) {
    Coord move {Pos.row + 1, Pos.col};
    moves.push_back(move);
  }
  
  if (Pos.col == 1 && Pos.row != 8) {
    Coord capture {Pos.row + 1, Pos.col + 1};
    captures.push_back(capture);
  }
  if (Pos.col == 8 && Pos.row != 8) {
    Coord capture {Pos.row + 1, Pos.col -1};
    captures.push_back(capture);
  }
  else if (Pos.row !=8 ) {
    Coord capture1 {Pos.row + 1, Pos.col + 1};
    captures.push_back(capture1);
    Coord captures {Pos.row + 1, Pos,col - 1};
    captures.push_back(capture2);
  }
  
}

Colour Pawn::getColour() {
  return Colour; 
}

bool Pawn::possibleMove(Coord Pos) {
  for (auto i : moves) {
    if (i.col == Pos.col && i.row == Pos.row) return true;
  }
  return false;
}
